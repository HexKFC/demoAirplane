#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif

#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <vector>
#include <algorithm>



typedef struct Enemy_INFO
{
	SDL_Rect enemy_rect;
	int blood=20;
	int speed=5;
}Enemy_INFO;


class Enemy{
	
	
public:
	

	
	Enemy(SDL_Renderer* temprenderer,std::string imagepath,int screensizex,int screensizey);

	~Enemy();
	
	void AddEnemy(SDL_Rect rect); 
	
	void UpdateEnemyPosition(); 
	
	void ShowEnemy();
	
	void AutoDestroy();
	
	bool Collapse(SDL_Rect rect);
	
private:

	std::vector<Enemy_INFO> enemy; 

	SDL_Renderer* renderer=NULL;
	SDL_Texture* enemy_texture=NULL;
	
	int x_window_size,y_window_size;//size of the window
	
	
	
};

#endif
