#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif

#include <iostream>
#include <SDL.h>

SDL_Texture *tex = NULL;
SDL_Renderer *ren = NULL;
SDL_Window *win = NULL;

int Load_texture();
void Quit();
int Init();
int main(int argc, char* argv[]) 
{
    //initialization
    if(Init()<0){
        std::cout << "init Error" << std::endl;
        return -1;
    }

    for (int i = 0; i < 3; ++i) {
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
        SDL_Delay(10000);
    }

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

    if(!Load_texture()){
        std::cout << "load_texture Error" << std::endl;
        SDL_Quit();
        return -1;
    }

}

int Load_texture(){

    std::string imagePath = "nacho.bmp";

    SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
    if (bmp == nullptr) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 0;
    }

    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 0;
    }

    return 1;
}

void Quit(){

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}