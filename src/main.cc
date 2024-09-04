#include "SDL_error.h"
#include <cstdio>
#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif

#include <iostream>
#include <SDL.h>
#include <stdlib.h>
#include <utils/log.h>
#include <object/Plane.h>

SDL_Texture *egg_tex = NULL;
SDL_Renderer *ren = NULL;
SDL_Window *win = NULL;
SDL_Surface *egg_surf = NULL;
SDL_Event MainEvent;

int FPS=20;
int move_time=25;

bool LoadTexture();
void Quit();
bool Init();
void Play();

int main(int argc, char* argv[]) 
{
#ifdef __linux
    // fix bug of desktop stuck when running SDL programmes: disable composition
    putenv((char *)"SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR=0");
#endif

    //initialization
    if(Init()){
        std::cout << "init Error" << std::endl;
        return -1;
    }

    // main loop
    while(SDL_WaitEvent(&MainEvent)) {
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
            case SDLK_SPACE:
                SDL_Delay(100);
                Play();
                break;
			default:
				break;
			}
			break;

		default:
			break;
		}
    }

    Quit();

    // Return
    return 0;
}

bool Init(){

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        ulog(MSG_ERROR, "SDL_Init Error: %s\n", SDL_GetError());
        return true;
    }

    win = SDL_CreateWindow("demoAirplane", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    if (win == nullptr) {
        ulog(MSG_ERROR, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return true;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        ulog(MSG_ERROR, "SDL_CreateRender Error: \n", SDL_GetError());
        SDL_Quit();
        return true;
    }

    if(LoadTexture()){
        ulog(MSG_ERROR, "load_texture Error");
        SDL_Quit();
        return true;
    }

    return false;
}

bool LoadTexture(){

    std::string imagePath = "nacho.bmp";

    egg_surf = SDL_LoadBMP(imagePath.c_str());
    if (egg_surf == nullptr) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        ulog(MSG_ERROR, "SDL_LoadBMP Error: ", SDL_GetError());
        SDL_Quit();
        return true;
    }

    egg_tex = SDL_CreateTextureFromSurface(ren, egg_surf);
    SDL_FreeSurface(egg_surf);
    if (egg_tex == nullptr) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        ulog(MSG_ERROR, "SDL_CreateTextureFromSurface Error: ", SDL_GetError());
        SDL_Quit();
        return true;
    }

    return false;
}

void Play(){

    //创建用户飞机对象
    Plane user_plane(ren,"plane.png",50,50,640,480);
    //启用计时器
    Uint32 start_time=SDL_GetTicks();
    //设置飞机最大速度
    user_plane.ChangeMaxSpeed(25,25);

    while(true){//游戏循环
        Uint32 now_time=SDL_GetTicks();
        if(now_time-start_time>=move_time)
		{
			start_time=now_time;
			user_plane.UpdatePlaneSpeed();
		}
		
		if(now_time-start_time==FPS)
		{
            SDL_RenderClear(ren);//更新屏幕
            user_plane.ShowPlane();
	        while (SDL_PollEvent(&MainEvent))
	        {
	        	switch (MainEvent.type)
	        	{
	        	case SDL_QUIT:
	        		return;
	        		break;
		
	         	case SDL_KEYDOWN:

	        		switch (MainEvent.key.keysym.sym)
	    	    	{
                    case 'w':
						
						user_plane.AddSpeed(PLANE_UP);					
						break;
						
					case 's':
						
						user_plane.AddSpeed(PLANE_DOWN);
						break;
						
					case 'a':
						
						user_plane.AddSpeed(PLANE_LEFT);
						break;
						
					case 'd':
						
						user_plane.AddSpeed(PLANE_RIGHT);
						break;

	    	    	case SDLK_ESCAPE:
                        //show the Easter egg image
                        //展示彩蛋图片
                        SDL_RenderClear(ren);
                        SDL_RenderCopy(ren, egg_tex, NULL, NULL);
                        SDL_RenderPresent(ren);
                        
	    	    		return;
	    	    		break;
	    	    	default:
	    	    		break;
	    	    	}
	    	    	break;

                case SDL_KEYUP:
			    
				
				    switch(MainEvent.key.keysym.sym)
				    {
					case 'w':

						user_plane.SubSpeed(PLANE_UP);
						break;
					case 's':
						
						user_plane.SubSpeed(PLANE_DOWN);
						break;
					case 'a':
						
						user_plane.SubSpeed(PLANE_LEFT);
						break;
					case 'd':
						
						user_plane.SubSpeed(PLANE_RIGHT);
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
    }
}

void Quit(){

    SDL_DestroyTexture(egg_tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}
