#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif


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
	
	Plane(SDL_Renderer* temprenderer,std::string imagepath,int T_x,int T_y,int W_x,int W_y);// 


	~Plane ();
	
	void addSpeed(int speedtochange);
	
	void subSpeed(int speedtochange);

	void updatePlaneSpeed();
	
	void showPlane();
	
	void changeMaxSpeed(int absx,int absy);
	
	void changeMaxAcc(int absx,int absy);
	
private:
	SDL_Texture* texture=NULL;
	SDL_Renderer* renderer=NULL;
	
	
	int xmaxacc,ymaxacc;//maximum acc
	int xacc,yacc;//now acc
	
	
	int xmaxspeed,ymaxspeed;//maximum speed
	int xspeed,yspeed;//current speed
	
	
	int xplanesize;
	int yplanesize;//size of the plane
	
	
	int xwindowsize,ywindowsize;//size of the window
	

	int x,y;//position of the plane
	
	
	int pxacc,nxacc;
	int pyacc,nyacc;//speed direction of the plane
	
	
};
