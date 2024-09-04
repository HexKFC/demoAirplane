#include <SDL.h>
#include <SDL_image.h>
#include <object/Laser.h>
#include <utils/log.h>
#include <string>

Laser::Laser(SDL_Renderer* renderer,std::string image_path,int laser_pos_x,int laser_pos_y):
laser_renderer(renderer),
pos_x(laser_pos_x),pos_y(laser_pos_y)
{

    laser_speed = 1;

    //加载子弹材质
    SDL_Surface* laser_surf=IMG_Load(image_path.c_str());
    if(laser_surf==NULL)
	{
		ulog(MSG_ERROR, "create_laser_surf Error");
		return;
	}
	laser_texture=SDL_CreateTextureFromSurface(renderer,laser_surf);
	if(laser_texture==NULL)
	{
		ulog(MSG_ERROR, "load_texture Error");
		return;
	}
    SDL_FreeSurface(laser_surf);


}