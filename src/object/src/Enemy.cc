#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif



#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <algorithm>

#include <utils/log.h>
#include <utils/crash_check.h>
#include <object/Enemy.h>
//T_x,T_y initial position of the plane
//W_x W_y initial size of the window


Enemy::Enemy(SDL_Renderer* temprenderer,std::string imagepath,int screensizex,int screensizey):
renderer(temprenderer),
x_window_size(screensizex),
y_window_size(screensizey)
{
	SDL_Surface* surface=IMG_Load(imagepath.c_str());
	
	if(surface==NULL)
	{
		//print error
		ulog(MSG_ERROR,SDL_GetError());
		exit(0);
	}
	
	enemy_texture=SDL_CreateTextureFromSurface(renderer,surface);
	
	if(enemy_texture==NULL)
	{
		//print error
		ulog(MSG_ERROR,SDL_GetError());
		exit(0);
	}
	
	SDL_FreeSurface(surface);
	
	
	
}



Enemy::~Enemy()
{
	
	renderer=NULL;
	SDL_DestroyTexture(enemy_texture);
	
	
}



void Enemy::AddEnemy(int new_enemy_x_pos,int enemy_type)//enemy_type用于生成不同种类的敌人
{
	Enemy_INFO tempenemyinfo;
	SDL_Rect new_enemy_rect;
	//根据enemy_type修改血量、速度
	switch (enemy_type)
	{
		case 0:
			new_enemy_rect={new_enemy_x_pos,-50,75,75};//随机生成新敌人位置
			tempenemyinfo.enemy_rect=new_enemy_rect;
			tempenemyinfo.blood=40;
			tempenemyinfo.speed=2;
			break;
		case 1:
			new_enemy_rect={new_enemy_x_pos,-50,50,50};//随机生成新敌人位置
			tempenemyinfo.enemy_rect=new_enemy_rect;
			tempenemyinfo.blood=20;
			tempenemyinfo.speed=5;
			break;
		case 2:
			new_enemy_rect={new_enemy_x_pos,-50,100,100};//随机生成新敌人位置
			tempenemyinfo.enemy_rect=new_enemy_rect;
			tempenemyinfo.blood=60;
			tempenemyinfo.speed=2;
			break;
		default:
			new_enemy_rect={new_enemy_x_pos,-50,50,50};//随机生成新敌人位置
			tempenemyinfo.enemy_rect=new_enemy_rect;
			tempenemyinfo.blood=40;
			tempenemyinfo.speed=2;
			break;
	}

	enemy.push_back(tempenemyinfo);
}

void Enemy::UpdateEnemyPosition()
{
	
	if(!enemy.empty()) 
	{
	
		for(int i=0;i<enemy.size();i++)
		{
			enemy[i].enemy_rect.y=enemy[i].speed+enemy[i].enemy_rect.y;
		}
	}
	
	else
	{
		//print error
		ulog(MSG_WARN,"Enemy vector is empty!\n");
	}
	

	
}


void Enemy::ShowEnemy()
{
	
	if(!enemy.empty()) 
	{
	
		for(int i=0;i<enemy.size();i++)
		{
			
			SDL_RenderCopy(renderer,enemy_texture,NULL,&enemy[i].enemy_rect);
			
			//SDL_Delay(200);
			
		}
	
	
		
	
	}
	
	else
	{
		//print error
		ulog(MSG_WARN,"Enemy vector is empty!\n");
	}
}


void Enemy::AutoDestroy()
{
	int i=0;
	for(int i=0;i<enemy.size();i++)
	{
		if(enemy[i].enemy_rect.y>=y_window_size)
		{
			enemy.erase(enemy.begin()+i);
		}
	}
}

bool Enemy::Collapse(SDL_Rect rect)
{
	bool state=false;//state用于判断子弹是否销毁
	for(int i=0;i<enemy.size();i++)
	{
		if(CrashCheck(&enemy[i].enemy_rect,&rect))
		{
			enemy[i].blood-=20;//子弹扣敌人生命值
			if(enemy[i].blood<=0)
				enemy.erase(enemy.begin()+i);
			state=true;
		}
	}
	return state;
}
