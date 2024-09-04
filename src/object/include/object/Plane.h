#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif

#ifndef PLANE_H
#define PLANE_H

#include <SDL.h>
#include <string>
#include <SDL_image.h>

enum{
	PLANE_UP,
	PLANE_DOWN,
	PLANE_LEFT,
	PLANE_RIGHT
};



class Plane{
	
	
public:
	
	Plane(SDL_Renderer* plane_renderer,std::string image_path,int T_x,int T_y,int W_x,int W_y);// 

	~Plane ();
	
	void AddSpeed(int speed_to_change);
	
	void SubSpeed(int speed_to_change);

	void UpdatePlaneSpeed();
	
	void ShowPlane();
	
	void ChangeMaxSpeed(int abs_x,int abs_y);
	
	void ChangeMaxAcc(int abs_x,int abs_y);
	
	SDL_Rect GetPlaneRect();
	
private:
	SDL_Texture* plane_texture=NULL;
	SDL_Renderer* renderer=NULL;
	
	SDL_Rect render_plane_rect;//Rect of the plane
	
	
	int x_max_acc,y_max_acc;//maximum acc
	int x_acc,y_acc;//now acc
	
	
	int x_max_speed,y_max_speed;//maximum speed
	int x_speed,y_speed;//current speed
	
	
	int x_plane_size;
	int y_plane_size;//size of the plane
	
	
	int x_window_size,y_window_size;//size of the window
	

	int x_plane_pos,y_plane_pos;//position of the plane
	
	
	int positive_x_acc,negative_x_acc;
	int positive_y_acc,negative_y_acc;//speed direction of the plane
	
	
};

#endif
