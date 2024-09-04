#include <SDL.h>
#include <SDL_image.h>
#include <object/Laser.h>
#include <utils/log.h>
#include <string>


Laser::~Laser ()
{
	SDL_DestroyTexture(laser_texture); 
	laser_texture=NULL;
	laser_renderer=NULL;
	
}

void Laser::LaserInit(SDL_Renderer* renderer,std::string image_path,int laser_pos_x,int laser_pos_y,int window_height)
{
    laser_renderer=renderer;
    pos_x=laser_pos_x;
    pos_y=laser_pos_y;
    pos_border=window_height;
    x_laser_size=10;y_laser_size=10;
    laser_speed = 10;
    render_flag = false;
    laser_busy = false;

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

void Laser::UpdateLaserState()
{
    if(pos_y<=pos_border && laser_busy)
    {
        render_flag=true;//正常更新位置并渲染
        pos_y+=laser_speed;
    }
    else if(pos_y>pos_border && laser_busy)
    {
        render_flag=false;//复位，不渲染
        laser_busy=false;
        pos_x =0;
        pos_y =0;
    }

}


void Laser::ShootLaser(int plane_pos_x, int plane_pos_y)
{
    laser_busy = true;
    pos_x=plane_pos_x;
    pos_y=plane_pos_y;
}

void Laser::ShowLaser()
{
    if(render_flag){
        SDL_Rect render_laser_rect ={pos_x,pos_y,x_laser_size,y_laser_size};	
	    SDL_RenderCopy(laser_renderer,laser_texture,NULL,&render_laser_rect);
    }

}

bool Laser::GetLaserStatus(){
    return laser_busy;
}