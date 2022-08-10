#include<SDL2/SDL.h>
#include<numeric>
#include<iostream>
using namespace std;
#include<vector>

class Screen{
	
	// couple of structurs used in the program 
	SDL_Event e;
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	// vector to store the points or coordinates
    	vector<SDL_FPoint> points;
    	
    	
	
	// constructor to initialize the window
	Screen()
	{
	
    	SDL_Init(SDL_INIT_VIDEO);
    	
    // creating the window
	   SDL_CreateWindowAndRenderer(640*2,480*2,0,&window,&renderer);
	   
	// setting scale for the window
	   SDL_RenderSetScale(renderer,2,2);
	   
    }


     // pixel function for drawing the pixel on the screen
        void pixel(float x,float y)
        {
        	point.emplace_back(x,y);
        	
		}
		
	// show() function to show the pixel on the screen
	   void show()
	   {
	   	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	   	SDL_RenderClear(renderer);
	   	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	   	
	   	// drawing points on the window
	   	   for(auto& point:points)
	   	   {
	   	     	SDL_RenderDrawPointF(renderer,point.x,point.y);
		   }
			  
			  SDL_RenderPresent(renderer);
	   }
	   
	   void clear()
	   {
	   	points.clear();
	   }
	   
	   
	   void input()
	   {
	   	while(SDL_PollEvent(&e))
	   	{
	   		if(e.type==SDL_QUIT)
	   		{
	   			SDL_Quit();
	   			exit(0);
			   }
		}
	   }	
	
	
};


void line(Screen& screen,float x1,float y1,float x2,float y2)
{
	float dx=x2-x1;
	float dy=y2-y1;
	
	float length=sqrt(dx*dx+dy*dy);
	float angle=atan2(dx,dy);
	  
	  for(float i=0;i<length;i++){
	  	screen.pixel( x1+cos(angle)*i, y1+sin(angle)*i );
	  }
}

struct vec3{
	float x,y,z;
};

struct connection{int a,b};

void rotate(vec3& point,float x=1,float y=1,float z=1)
{
	float rad=0;
	
	rad=x;
	point.y=cos(rad)*point y-sin(rad)*point z;
	point.z=sin(rad)*point.y+cos(rad)*point.z;
	
	rad=y;
	point.x=cos(rad)*point x+sin(rad)*point z;
	point.z=sin(rad)*point.x+cos(rad)*point.z;
	
	rad=z;
	point.x=cos(rad)*point.x-sin(rad)*point.y;
	point.y=sin(rad)*point.x+cos(rad)*point.y;
	
}
int main()
{
	Screen screen;
	vector<vec3> points
	{
		{100,100,100},{200,100,100},{200,200,100},{100,200,100},
		{100,100,200},{200,100,200},{200,200,200},{100,200,200}
	};
	
	vector<connection> connections
	{
		{0,4},
		{1,5},
		{2,6},
		{3,7},
		
		
		{0,1},
		{1,2},
		{2,3},
		{3,0},
		
		
		{4,5},
		{5,6},
		{6,7},
		{7,4}
	};
	
	vec3 c{0,0,0};
	
	
	while(true){
	
	// finding centroid of the cube
    	for(auto& p:points)
    	{
	    	c.x += p.x;
	    	c.y += p.y;
	    	c.z += p.z;
    	}
    	
    	
    // dividing the centroid points by the size of the pixel 	
    	c.x/=points.size();
    	c.y/=points.size();
    	c.z/=points.size();
    	for(auto& p:points){
    		p.x-=c.x;
    		p.y-=c.y;
    		p.z-=c.z;
    // for rotation of the cube below function is define
    		rotate(p,0.02,0.01,0.04);
    		
    		p.x+=c.x;
    		p.y+=c.y;
    		p.z=+c.z;
    		screen.pixel(p.x,p.y);
    		
		}
		
		for(auto& conn:connections)
		{
			line(screen,
			points[conn.a].x,
			points[conn.a].y,
			points[conn.b].x,
			points[conn.b].y);
		}
		screen.show();
		screen.clear();
		SDL_Delay(30);
		
	}
	return 0;
}
