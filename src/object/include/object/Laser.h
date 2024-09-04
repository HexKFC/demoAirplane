#ifndef LASER_H
#define LASER_H

class Laser{

public:
    Laser(SDL_Renderer* renderer,std::string image_path,int laser_pos_x,int laser_pos_y,int window_height);

    void UpdateLaserState();

    void ShowLaser();

private:

    SDL_Renderer* laser_renderer=NULL;
    SDL_Texture* laser_texture=NULL;

    int pos_x,pos_y;//子弹生成位置
    int x_laser_size,y_laser_size;
    int pos_border;//窗口上边界

    int laser_speed;
    bool render_flag;


};


#endif 