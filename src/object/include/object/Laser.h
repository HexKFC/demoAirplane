#ifndef LASER_H
#define LASER_H

#include <SDL.h>
#include <string>
#include <SDL_image.h>

class Laser{

public:

    ~Laser ();

    void LaserInit(SDL_Renderer* renderer,std::string image_path,int laser_pos_x,int laser_pos_y,int window_height);

    void UpdateLaserState();

    void ShowLaser();

    void ShootLaser(int plane_pos_x, int plane_pos_y);

    bool GetLaserStatus();//获取子弹是否正在飞行的标志

private:

    SDL_Renderer* laser_renderer=NULL;
    SDL_Texture* laser_texture=NULL;

    int pos_x,pos_y;//子弹生成位置
    int x_laser_size,y_laser_size;
    int pos_border;//窗口上边界

    int laser_speed;
    bool render_flag;
    bool laser_busy;


};


#endif 