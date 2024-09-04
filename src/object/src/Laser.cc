#include <SDL.h>
#include <SDL_image.h>
#include <object/Laser.h>
#include <string>

Laser::Laser(SDL_Renderer* renderer,std::string image_path,int laser_pos_x,int laser_pos_y):
laser_renderer(renderer),
pos_x(laser_pos_x),pos_y(laser_pos_y)
{

}