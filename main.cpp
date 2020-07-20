//#include<SDL/SDL.h> 
#include <SDL2/SDL.h>
#include<iostream>
#include<string>
#include<complex>
#include<thread>
#include<chrono>
using namespace std;
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

int* pfractal;
float zoom = 1.0;
struct point
{
	/* data */
	float x;
	float y;
};

point center{
	0,0
};

const int windowHeight = 600;
const int windowWidth = 800;

auto map = [](float val, float mini, float maxi, float mino, float maxo){
	return (mini-val)/(mini-maxi)*(maxo-mino)+mino;
};

void foo(int Z) 
{ 
    for (int i = 0; i < Z; i++) { 
        cout << "Thread using function"
               " pointer as callable\n"; 
    } 
} 

void computeFractal(point pixtl, point pixbr, point fractl, point fracbr,int iterations){
	std::complex<float> c;
	std::complex<float> z;
	for(int x = pixtl.x; x < pixbr.x; x++){
			
			c.real(map(x,pixtl.x,pixbr.x,fractl.x,fracbr.x)+center.x);
        	for(int y=pixtl.y; y < pixbr.y; y++){
			c.imag(map(y,pixtl.y,pixbr.y,fracbr.y,fractl.y)+center.y);
			z=c;
			int i = 0;
			while((z.real()*z.real() + z.imag()*z.imag() < 4) && i < iterations){
				z = z*z + c;
				i++;
			}
			pfractal[x + y*windowWidth]=i;
		}
	}
}


void computeFractalOpti(point pixtl, point pixbr, point fractl, point fracbr,int iterations){
	std::complex<float> c;
	std::complex<float> z;
	for(int x = pixtl.x; x < pixbr.x; x++){
			c.real(map(x,pixtl.x,pixbr.x,fractl.x,fracbr.x)/zoom+center.x);
        	for(int y=pixtl.y; y < pixbr.y; y++){
			c.imag(map(y,pixtl.y,pixbr.y,fracbr.y,fractl.y)/zoom+center.y);
			z=c;
			double q = (c.real()-.25)*(c.real()-.25)+c.imag()*c.imag();
			int i = 0;
			if(q*(q+(c.real()-.25)) < .25*c.imag()*c.imag())
				i=iterations;
			else{
				while((z.real()*z.real() + z.imag()*z.imag() < 4) && i < iterations){
					z = z*z + c;
					i++;
				}
			}
			pfractal[x + y*windowWidth]=i;
		}
	}
}

void threadFractal(point pixtl, point pixbr, point fractl, point fracbr, int iterations, int nThreads){
	int nSectionWidth = (pixbr.x - pixtl.x) / nThreads;
	float dFractalWidth = (fracbr.x - fractl.x) / float(nThreads);

	std::thread t[nThreads];


	for (int i = 0; i < nThreads; i++)
		t[i] = std::thread(computeFractalOpti, 
			point{pixtl.x + nSectionWidth * (i), pixtl.y},
			point{pixtl.x + nSectionWidth * (i + 1), pixbr.y},
			point{fractl.x + dFractalWidth * float(i), fractl.y},
			point{fractl.x + dFractalWidth * float(i + 1), fracbr.y},
			iterations);
		//t[i] = std::thread(computeFractal,
		//point{pixtl.x + nSectionWidth * (i), pixtl.y},
		//point{pixtl.x + nSectionWidth * (i), pixtl.y},
		//point{pixtl.x + nSectionWidth * (i), pixtl.y},
		//point{pixtl.x + nSectionWidth * (i), pixtl.y}, 64); 

	for (size_t i = 0; i < nThreads; i++)
		t[i].join();
}
int maxIter =64;
int main() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
        logSDLError(std::cout, "SDL INIT");
    }

    SDL_Window *window = SDL_CreateWindow("Practice making sdl Window",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth,
            windowHeight, SDL_WINDOW_SHOWN);

    if (window == NULL) {
		logSDLError(std::cout, "SDL WINDOW");
        SDL_Quit();
        return 2;
    }

    // We create a renderer with hardware acceleration, we also present according with the vertical sync refresh.
    SDL_Renderer *s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ;


    bool quit = false;
    SDL_Event event;
	pfractal = (int*)malloc(sizeof(int)*windowHeight*windowWidth);
	Uint32 fps_lasttime = SDL_GetTicks(); //the last recorded time.
	Uint32 fps_current; //the current FPS.
	Uint32 fps_frames = 0;
	std::complex<float> c;
	std::complex<float> z;
    while (!quit) {
        //drawing particles
        //setting up objects
        //repeated over and over again

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
 		   		quit = true;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z) {
 		   		maxIter*=2;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x) {	
				if(maxIter !=1)
					maxIter/=2;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
				center.x +=0.2 /zoom;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
				center.x -=0.2/zoom;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
 		   		center.y-=0.2/zoom;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) {
				center.y+=0.2/zoom;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c) {
 		   		zoom *= 1.1;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_v) {
				zoom*= 0.9;
			}
        }

        // We clear what we draw before
        SDL_RenderClear(s);
        // Set our color for the draw functions
        SDL_SetRenderDrawColor(s, 0xFF, 0xFF, 0xFF, 0xFF);
        // Now we can draw our point
		//computeFractalOpti({0,0},{windowWidth,windowHeight},{-2,1},{1,-1},64);
		threadFractal({0,0},{windowWidth,windowHeight},{-2,1},{1,-1},maxIter,10);
		for(int x = 0; x < windowWidth; x++){
        	for(int y=0; y < windowHeight; y++){
			int i = pfractal[x + y*windowWidth];
			float n = float(i);
			float a = 0.1f;
			Uint32 r = (0.5f * sin(a * n) + 0.5f)*22;
			Uint32 g = (0.5f * sin(a * n + 2.094f) + 0.5f)*255;
			Uint32 b = (0.5f * sin(a * n + 4.188f) + 0.5f)*255;
			SDL_SetRenderDrawColor(s, r, g, b, 0xFF);
			SDL_RenderDrawPoint(s,x,y);	
			}
		}
        // Set the color to what was before
        SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
        // .. you could do some other drawing here
        // And now we present everything we draw after the clear.
		fps_frames++;
		if (fps_lasttime < SDL_GetTicks() - 1000)
		{
			fps_lasttime = SDL_GetTicks();
			fps_current = fps_frames;
			fps_frames = 0;
		}
		std::cout << "fps: " << fps_current << std::endl;

        SDL_RenderPresent(s);
    }
	free(pfractal);
    SDL_DestroyWindow(window);
    // We have to destroy the renderer, same as with the window.
    SDL_DestroyRenderer(s);
    SDL_Quit();

}