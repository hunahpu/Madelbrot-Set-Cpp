#ifndef FRACTAL_H
#define FRACTAL_H
#include <SDL2/SDL.h>
struct point{
    float x;
    float y;
};
class Fractal{
  private:
    int* _pfractal;
    //int _maxIter{64};
    int _width;
    int _height;
    //point _center{0,0};
    const point _fractl{-2,1};
    const point _fracbr{1,-1};
    //float _zoom{1.0f};
    inline float map(float val, float mini, float maxi, float mino, float maxo){
	    return (mini-val)/(mini-maxi)*(maxo-mino)+mino;
    };
  public:
    float _zoom{1.0f};
    int _maxIter{64};
    point _center{0,0};
    void render(SDL_Renderer *render);
    Fractal(int w, int h);
    ~Fractal();
    void computeFractal(point pixtl, point pixbr, point fractl, point fracbr,int iterations);
    void computeFractalOpti(point pixtl, point pixbr, point fractl, point fracbr,int iterations);
    void threadFractal(point pixtl, point pixbr, point fractl, point fracbr, int nThreads);
    void threadFractal(int nThreads);
};


#endif