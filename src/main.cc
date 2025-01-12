#include "SDL_error.h"
#include <cstdio>
#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif

#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <stdlib.h>
#include <utils/log.h>
#include <object/Plane.h>
#include <object/Laser.h>
#include <object/Enemy.h>


SDL_Renderer *ren = NULL;
SDL_Window *win = NULL;
SDL_Event MainEvent;
SDL_DisplayMode dpmode;

int FPS=10;
int move_time=15;
const int laser_number=20;

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
        exit(-1);
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

    if(SDL_GetDesktopDisplayMode(0, &dpmode))
    {
        ulog(MSG_ERROR, "SDL_GetDesktopDisplayMode Error: \n", SDL_GetError());
        Quit();
        return true;
    }

    win = SDL_CreateWindow("demoAirplane", 100, 100, dpmode.w, dpmode.h, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (win == nullptr) {
        ulog(MSG_ERROR, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        Quit();
        return true;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        ulog(MSG_ERROR, "SDL_CreateRender Error: \n", SDL_GetError());
        Quit();
        return true;
    }
    


    return false;
}


void Play(){

    //创建用户飞机对象
    Plane user_plane(ren,"plane.png",dpmode.w/2,dpmode.h-50,dpmode.w,dpmode.h);
    //创建用户敌人对象
    Enemy user_enemy(ren,"enemy.png",dpmode.w,dpmode.h);
    //创建用户子弹对象
    Laser user_laser[laser_number];
    //初始化子弹对象
    for(int i=0;i<laser_number;i++)
        user_laser[i].LaserInit(ren,"laser.png");

    //启用计时器
    Uint32 start_time=SDL_GetTicks();
    //设置飞机最大速度
    user_plane.ChangeMaxSpeed(10,10);
    //敌人生成计数器
    int times=7;

    //为了限制长按连发的状态变量
    bool laser_ready = true;

    while(true){//游戏循环
        Uint32 now_time=SDL_GetTicks();
        if(now_time-start_time>=move_time)
		{
			start_time=now_time;
			user_plane.UpdatePlaneSpeed();

            for(int i=0;i<laser_number;i++)
                user_laser[i].UpdateLaserState();

            user_enemy.UpdateEnemyPosition();
            times++;
			
			if(times==8)
			{
				SDL_Rect newenemy={rand()%(dpmode.w-50),-50,50,50};
				user_enemy.AddEnemy(newenemy,0);
				times=0;
			}
		}
		if(now_time-start_time==FPS)
		{
            SDL_RenderClear(ren);//更新屏幕

            //死亡判定
            if(user_enemy.Collapse(user_plane.GetPlaneRect()))
            {
                Quit();
                break;

            }


            user_enemy.AutoDestroy();

		    for(int i=0;i<laser_number;i++)
            {
                if(user_enemy.Collapse(user_laser[i].GetLaserRect()))//敌人和子弹销毁
                    user_laser[i].Reset();
            }

            


            for(int i=0;i<laser_number;i++)
                user_laser[i].ShowLaser();

		    user_enemy.ShowEnemy();

            user_plane.ShowPlane();

            SDL_RenderPresent(ren);

	        while (SDL_PollEvent(&MainEvent))
	        {
	        	switch (MainEvent.type)
	        	{
	        	case SDL_QUIT:
                    Quit();
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
                    
                    case SDLK_SPACE:

                        if(laser_ready){
                            for(int i=0;i<laser_number;i++){
                                if(user_laser[i].GetLaserStatus()==false)//子弹已准备就绪
                                {
                                    user_laser[i].ShootLaser(user_plane.GetPlaneRect().x+user_plane.GetPlaneRect().w/2,user_plane.GetPlaneRect().y);//此处需plane类的获取飞机位置的接口
                                    laser_ready=false;
                                    break;
                                }
                            }
                        }

                        break;
                        
	    	    	case SDLK_ESCAPE:
                        //show the Easter egg image
                        //展示彩蛋图片


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

                    case SDLK_SPACE:

                        laser_ready=true;
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

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}
