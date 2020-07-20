//#include<SDL/SDL.h> 
#include <SDL2/SDL.h>
#include<iostream>
#include<string>
#include<chrono>
#include "fractal.h"
#include "renderer.h"
using namespace std;
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}


const int windowHeight = 600;
const int windowWidth = 800;

int main() {
	Renderer render(windowHeight,windowWidth);
	Fractal mandelbrot(windowWidth,windowHeight);
	render.loop(mandelbrot);

    /*if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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
	Uint32 fps_lasttime = SDL_GetTicks(); //the last recorded time.
	Uint32 fps_current; //the current FPS.
	Uint32 fps_frames = 0;
	Fractal mandelbrot(windowWidth,windowHeight);
    while (!quit) {

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
        SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
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
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(s);
    SDL_Quit();
*/
}