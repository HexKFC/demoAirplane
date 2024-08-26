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

Plane::Plane(SDL_Renderer* temprenderer,std::string imagepath,int T_x,int T_y,int W_x,int W_y):renderer(temprenderer),x(T_x),y(T_y),xwindowsize(W_x),ywindowsize(W_y)
{
	//renderer=temprenderer; 
	
	xplanesize=120;yplanesize=120;xspeed=0;yspeed=0;xmaxspeed=1;ymaxspeed=1;pxacc=0;pyacc=0;nxacc=0;nyacc=0;xacc=0;yacc=0;xmaxacc=1;ymaxacc=1;
	
	SDL_Surface* loadImage=IMG_Load(imagepath.c_str());
	if(loadImage==NULL)
	{
		printf("error loading img\n");
		return;
	}
	texture=SDL_CreateTextureFromSurface(renderer,loadImage);
	if(texture==NULL)
	{
		printf("error\n%s\n",SDL_GetError());
		return;
	}
	SDL_FreeSurface(loadImage);	
	

}




Plane::~Plane ()
{
	
	SDL_DestroyTexture(texture); 
	texture=NULL;
	renderer=NULL;
	
}



void Plane::addSpeed(int speedtochange)
{
	switch(speedtochange)
	{
		case PLANE_UP:
			nyacc=1;
			break;
		case PLANE_DOWN:
			pyacc=1;
			break;
		case PLANE_LEFT:
			nxacc=1;
			break;
		case PLANE_RIGHT:
			pxacc=1; 
			break;
			
	}
}

void Plane::subSpeed(int speedtochange)
{
	switch(speedtochange)
	{
		case PLANE_UP:
			nyacc=0;
			break;
		case PLANE_DOWN:
			pyacc=0;
			break;
		case PLANE_LEFT:
			nxacc=0;
			break;
		case PLANE_RIGHT:
			pxacc=0; 
			break;
			
	}
}

void Plane::updatePlaneSpeed()
{
	
	

	if(xspeed+xacc>=xmaxspeed){
		xspeed=xmaxspeed;
	}
	else if(xspeed+xacc<=-xmaxspeed){
		xspeed=-xmaxspeed;
	}
	else xspeed+=xacc;
	
	if(yspeed+yacc>=ymaxspeed){
		yspeed=ymaxspeed;
	}
	else if(yspeed+yacc<=-ymaxspeed){
		yspeed=-ymaxspeed;
	}
	else yspeed+=yacc;
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
	
	
	if((x+xspeed>0)&&(x+xspeed<xwindowsize-xplanesize))
	{
		x+=xspeed;
	}
	else if(x+xspeed<=0)
	{
		x=0;
		xspeed=0;
	}
	else if(x+xspeed>=xwindowsize-xplanesize)
	{
		x=xwindowsize-xplanesize;
		xspeed=0;
	}
	
	if((y+yspeed>0)&&(y+yspeed<ywindowsize-yplanesize))
	{
		y+=yspeed;
	}
	else if(y+yspeed<=0)
	{
		y=0;
		yspeed=0;
	}
	else if(y+yspeed>=ywindowsize-yplanesize)
	{
		y=ywindowsize-yplanesize;
		yspeed=0;
	}
	
}

void Plane::showPlane()
{
	
	xacc=(pxacc-nxacc)*xmaxacc;
	yacc=(pyacc-nyacc)*ymaxacc;
	
	
	SDL_Rect renderQuad ={x,y,xplanesize,yplanesize};	
	SDL_RenderCopy(renderer,texture,NULL,&renderQuad);
	SDL_RenderPresent(renderer);
	
}



void Plane::changeMaxSpeed(int absx,int absy)
{
	xmaxspeed+=absx;
	ymaxspeed+=absy;
}
	
	
void Plane::changeMaxAcc(int absx,int absy)
{
	xmaxacc+=absx;
	ymaxacc+=absy;
}


