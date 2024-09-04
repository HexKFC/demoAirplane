#ifndef LASER_H
#define LASER_H

class Laser{

public:
    Laser(SDL_Renderer* renderer,std::string image_path,int laser_pos_x,int laser_pos_y);

private:

    SDL_Renderer* laser_renderer=NULL;

    int pos_x,pos_y;//子弹生成位置




};


#endif 