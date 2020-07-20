//#include<SDL/SDL.h> 
#include <SDL2/SDL.h>
#include<iostream>
#include<string>
#include<complex>
#include<thread>
#include<chrono>
#include "fractal.h"
using namespace std;
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
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
	//pfractal = (int*)malloc(sizeof(int)*windowHeight*windowWidth);
	Uint32 fps_lasttime = SDL_GetTicks(); //the last recorded time.
	Uint32 fps_current; //the current FPS.
	Uint32 fps_frames = 0;
	//std::complex<float> c;
	//std::complex<float> z;
	Fractal mandelbrot(windowWidth,windowHeight);
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
 		   		mandelbrot._maxIter *= 2;
				std::cout << mandelbrot._maxIter << std::endl;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x) {	
				if(mandelbrot._maxIter !=1)
					mandelbrot._maxIter /= 2;
				std::cout << mandelbrot._maxIter << std::endl;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
				mandelbrot._center.x +=0.2 /mandelbrot._zoom;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
				mandelbrot._center.x -=0.2/mandelbrot._zoom;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
 		   		mandelbrot._center.y-=0.2/mandelbrot._zoom;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) {
				mandelbrot._center.y+=0.2/mandelbrot._zoom;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c) {
 		   		mandelbrot._zoom *= 1.1;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_v) {
				mandelbrot._zoom*= 0.9;
			}
        }

		mandelbrot.threadFractal({0,0},{windowWidth,windowHeight},{-2,1},{1,-1},5);
        // We clear what we draw before
        SDL_RenderClear(s);
        // Set our color for the draw functions
        SDL_SetRenderDrawColor(s, 0xFF, 0xFF, 0xFF, 0xFF);
 		mandelbrot.render(s);
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
	//free(pfractal);
    SDL_DestroyWindow(window);
    // We have to destroy the renderer, same as with the window.
    SDL_DestroyRenderer(s);
    SDL_Quit();

}