#include "fractal.h"
#include<iostream>
#include<thread>
#include<complex>
Fractal::Fractal(int w, int h): _width{w}, _height{h} {
    _pfractal = (int*)malloc(sizeof(int)*w*h);
}
Fractal::~Fractal(){
    free(_pfractal);
}

void Fractal::computeFractal(point pixtl, point pixbr, point fractl, point fracbr,int iterations){
	std::complex<float> c;
	std::complex<float> z;
	for(int x = pixtl.x; x < pixbr.x; x++){
			
			c.real(map(x,pixtl.x,pixbr.x,fractl.x,fracbr.x)+_center.x);
        	for(int y=pixtl.y; y < pixbr.y; y++){
			c.imag(map(y,pixtl.y,pixbr.y,fracbr.y,fractl.y)+_center.y);
			z=c;
			int i = 0;
			while((z.real()*z.real() + z.imag()*z.imag() < 4) && i < iterations){
				z = z*z + c;
				i++;
			}
			_pfractal[x + y*_width]=i;
		}
	}
}


void Fractal::computeFractalOpti(point pixtl, point pixbr, point fractl, point fracbr,int iterations){
	std::complex<float> c;
	std::complex<float> z;
	for(int x = pixtl.x; x < pixbr.x; x++){
			c.real(map(x,pixtl.x,pixbr.x,fractl.x,fracbr.x)/ _zoom + _center.x);
        	for(int y=pixtl.y; y < pixbr.y; y++){
			c.imag(map(y,pixtl.y,pixbr.y,fracbr.y,fractl.y)/ _zoom + _center.y);
			z=c;
			double q = (c.real()-.25)*(c.real()-.25)+c.imag()*c.imag();
			int i = 0;
			if(q*(q+(c.real()-.25)) < .25*c.imag()*c.imag())
				i=_maxIter;
			else{
				while((z.real()*z.real() + z.imag()*z.imag() < 4) && i < _maxIter){
					z = z*z + c;
					i++;
				}
			}
			_pfractal[x + y*_width]=i;
		}
	}
}

void Fractal::threadFractal(point pixtl, point pixbr, point fractl, point fracbr, int nThreads){
	int nSectionWidth = (pixbr.x - pixtl.x) / nThreads;
	float dFractalWidth = (fracbr.x - fractl.x) / float(nThreads);

	std::thread t[nThreads];


	for (int i = 0; i < nThreads; i++)
		t[i] = std::thread(&Fractal::computeFractalOpti, this,
			point{pixtl.x + nSectionWidth * (i), pixtl.y},
			point{pixtl.x + nSectionWidth * (i + 1), pixbr.y},
			point{fractl.x + dFractalWidth * float(i), fractl.y},
			point{fractl.x + dFractalWidth * float(i + 1), fracbr.y},
			_maxIter);
		//t[i] = std::thread(computeFractal,
		//point{pixtl.x + nSectionWidth * (i), pixtl.y},
		//point{pixtl.x + nSectionWidth * (i), pixtl.y},
		//point{pixtl.x + nSectionWidth * (i), pixtl.y},
		//point{pixtl.x + nSectionWidth * (i), pixtl.y}, 64); 

	for (size_t i = 0; i < nThreads; i++)
		t[i].join();
}

void Fractal::render(SDL_Renderer *render){
    for(int x = 0; x < _width; x++){
        for(int y=0; y < _height; y++){
        int i = _pfractal[x + y*_width];
        float n = float(i);
        float a = 0.1f;
        Uint32 r = (0.5f * sin(a * n) + 0.5f)*22;
        Uint32 g = (0.5f * sin(a * n + 2.094f) + 0.5f)*255;
        Uint32 b = (0.5f * sin(a * n + 4.188f) + 0.5f)*255;
        SDL_SetRenderDrawColor(render, r, g, b, 0xFF);
        SDL_RenderDrawPoint(render,x,y);	
        }
    }
}