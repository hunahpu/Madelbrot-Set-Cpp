#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include "fractal.h"
#include <iostream>
#include <string>
class Renderer{
    private:
      SDL_Window *_window;
      SDL_Renderer *_render; 
      int _windowWidth;
      int _windowHeight;
      void logSDLError(std::ostream &os, const std::string &msg){
	    os << msg << " error: " << SDL_GetError() << std::endl;
      }
      bool running{true};
      
    public:
      Renderer(int windowHeight, int windowWidth);
      ~Renderer();
      void loop(Fractal &f);
      void controller(Fractal &f);

};
#endif