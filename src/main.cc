#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif

#include <iostream>
#include <SDL.h>
#include <stdlib.h>

SDL_Texture *egg_tex = NULL;
SDL_Renderer *ren = NULL;
SDL_Window *win = NULL;
SDL_Surface *egg_surf = NULL;
SDL_Event MainEvent;

int LoadTexture();
void Quit();
int Init();
void Play();

int main(int argc, char* argv[]) 
{

    //initialization
    if(Init()<0){
        std::cout << "init Error" << std::endl;
        return -1;
    }

    Play();

    Quit();

    // Return
    return 0;
}

int Init(){

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    win = SDL_CreateWindow("demoAirplane", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRender Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    if(LoadTexture()<0){
        std::cout << "load_texture Error" << std::endl;
        SDL_Quit();
        return -1;
    }

}

int LoadTexture(){

    std::string imagePath = "nacho.bmp";

    egg_surf = SDL_LoadBMP(imagePath.c_str());
    if (egg_surf == nullptr) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    egg_tex = SDL_CreateTextureFromSurface(ren, egg_surf);
    SDL_FreeSurface(egg_surf);
    if (egg_tex == nullptr) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    return 0;
}

void Play(){

    //show the Easter egg image
    //展示彩蛋图片
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, egg_tex, NULL, NULL);
    SDL_RenderPresent(ren);

	while (SDL_WaitEvent(&MainEvent))
	{
		switch (MainEvent.type)
		{
		case SDL_QUIT:
			Quit();
			break;
		
		case SDL_KEYDOWN:

			switch (MainEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Quit();
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}

}

void Quit(){

    SDL_DestroyTexture(egg_tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}