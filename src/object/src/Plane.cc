#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif



#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <algorithm>
#include <object/Plane.h>
//T_x,T_y initial position of the plane
//W_x W_y initial size of the window

Plane::Plane(SDL_Renderer* plane_renderer,std::string image_path,int T_x,int T_y,int W_x,int W_y):
renderer(plane_renderer),
x_plane_pos(T_x),y_plane_pos(T_y),
x_window_size(W_x),y_window_size(W_y)
{
	//renderer=temprenderer; 
	
	x_plane_size=120;y_plane_size=120;
	x_speed=0;y_speed=0;
	x_max_speed=1;y_max_speed=1;
	positive_x_acc=0;positive_y_acc=0;
	negative_x_acc=0;negative_y_acc=0;
	x_acc=0;y_acc=0;
	x_max_acc=1;y_max_acc=1;
	
	SDL_Surface* plane_surf=IMG_Load(image_path.c_str());
	if(plane_surf==NULL)
	{
		printf("error loading img\n");
		return;
	}
	plane_texture=SDL_CreateTextureFromSurface(renderer,plane_surf);
	if(plane_texture==NULL)
	{
		printf("error\n%s\n",SDL_GetError());
		return;
	}
	SDL_FreeSurface(plane_surf);	
	

}




Plane::~Plane ()
{
	
	SDL_DestroyTexture(plane_texture); 
	plane_texture=NULL;
	renderer=NULL;
	
}



void Plane::AddSpeed(int speedtochange)
{
	switch(speedtochange)
	{
		case PLANE_UP:
			negative_y_acc=1;
			break;
		case PLANE_DOWN:
			positive_y_acc=1;
			break;
		case PLANE_LEFT:
			negative_x_acc=1;
			break;
		case PLANE_RIGHT:
			positive_x_acc=1; 
			break;
			
	}
}

void Plane::SubSpeed(int speedtochange)
{
	switch(speedtochange)
	{
		case PLANE_UP:
			negative_y_acc=0;
			break;
		case PLANE_DOWN:
			positive_y_acc=0;
			break;
		case PLANE_LEFT:
			negative_x_acc=0;
			break;
		case PLANE_RIGHT:
			positive_x_acc=0; 
			break;
			
	}
}

void Plane::UpdatePlaneSpeed()
{
	
	

	if(x_speed+x_acc>=x_max_speed){
		x_speed=x_max_speed;
	}
	else if(x_speed+x_acc<=-x_max_speed){
		x_speed=-x_max_speed;
	}
	else x_speed+=x_acc;
	
	if(y_speed+y_acc>=y_max_speed){
		y_speed=y_max_speed;
	}
	else if(y_speed+y_acc<=-y_max_speed){
		y_speed=-y_max_speed;
	}
	else y_speed+=y_acc;
/*	
	if(xacc!=0)x += (newxspeed*newxspeed - xspeed*xspeed) / (2*xacc);
	else x+=xspeed;
	if(yacc!=0)y += (newyspeed*newyspeed - yspeed*yspeed) / (2*yacc);
	else y+=yspeed;
	
	xspeed=newxspeed;
	yspeed=newyspeed;
	*/
	
	//x= (x+xspeed>=0) ? ( (x+xspeed<=xwindowsize-xplanesize) ? (x+xspeed):(xwindowsize-xplanesize) ): 0;
	//y= (y+yspeed>=0) ? ( (y+yspeed<=ywindowsize-yplanesize) ? (y+yspeed):(ywindowsize-yplanesize) ): 0;
	
	
	if((x_plane_pos+x_speed>0)&&(x_plane_pos+x_speed<x_window_size-x_plane_size))
	{
		x_plane_pos+=x_speed;
	}
	else if(x_plane_pos+x_speed<=0)
	{
		x_plane_pos=0;
		x_speed=0;
	}
	else if(x_plane_pos+x_speed>=x_window_size-x_plane_size)
	{
		x_plane_pos=x_window_size-x_plane_size;
		x_speed=0;
	}
	
	if((y_plane_pos+y_speed>0)&&(y_plane_pos+y_speed<y_window_size-y_plane_size))
	{
		y_plane_pos+=y_speed;
	}
	else if(y_plane_pos+y_speed<=0)
	{
		y_plane_pos=0;
		y_speed=0;
	}
	else if(y_plane_pos+y_speed>=y_window_size-y_plane_size)
	{
		y_plane_pos=y_window_size-y_plane_size;
		y_speed=0;
	}
	
}

void Plane::ShowPlane()
{
	
	x_acc=(positive_x_acc-negative_x_acc)*x_max_acc;
	y_acc=(positive_y_acc-negative_y_acc)*y_max_acc;
	
	
	SDL_Rect render_plane_rect ={x_plane_pos,y_plane_pos,x_plane_size,y_plane_size};	
	SDL_RenderCopy(renderer,plane_texture,NULL,&render_plane_rect);
	SDL_RenderPresent(renderer);
	
}



void Plane::ChangeMaxSpeed(int x_difference,int y_difference)
{
	x_max_speed+=x_difference;
	y_max_speed+=y_difference;
}
	
	
void Plane::ChangeMaxAcc(int x_difference,int y_difference)
{
	x_max_acc+=x_difference;
	y_max_acc+=y_difference;
}


