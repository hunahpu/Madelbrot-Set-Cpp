#include "renderer.h"
Renderer::Renderer(int windowHeight, int windowWidth): _windowHeight{windowHeight}, _windowWidth{windowWidth}{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logSDLError(std::cout, "SDL COULDN'T INIT");
    }

     _window = SDL_CreateWindow("Mandelbrot Set",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth,
            windowHeight, SDL_WINDOW_SHOWN);

    if (_window == NULL) {
		logSDLError(std::cout, "SDL COULDN'T CREATE WINDOW");
        SDL_Quit();
    }

    // We create a renderer with hardware acceleration, we also present according with the vertical sync refresh.
    _render = SDL_CreateRenderer(_window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ;
    if (nullptr == _render) {
        logSDLError(std::cout, "SDL COULDN'T CREATE RENDERERD");
    }
}
Renderer::~Renderer(){
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_render);
    SDL_Quit();
}
void Renderer::loop(Fractal &f){
    Uint32 fps_lasttime = SDL_GetTicks(); //the last recorded time.
	Uint32 fps_current; //the current FPS.
	Uint32 fps_frames = 0;
    while(running){
        controller(f);
        //f.threadFractal(point{0,0},point{float(_windowWidth),float(_windowHeight)},point{-2,1},point{1,-1},5);
        f.threadFractal(5);
		// We clear what we draw before
        SDL_RenderClear(_render);
        // Set our color for the draw functions
        SDL_SetRenderDrawColor(_render, 0xFF, 0xFF, 0xFF, 0xFF);

		f.render(_render);
        SDL_SetRenderDrawColor(_render, 0x00, 0x00, 0x00, 0xFF);
		fps_frames++;
		if (fps_lasttime < SDL_GetTicks() - 1000)
		{
			fps_lasttime = SDL_GetTicks();
			fps_current = fps_frames;
			fps_frames = 0;
		}
		std::cout << "fps: " << fps_current << std::endl;

        SDL_RenderPresent(_render);
    }
}

void Renderer::controller(Fractal& mandelbrot){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
 		   		running = false;
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
}