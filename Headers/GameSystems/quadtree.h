#pragma once
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "pixel.h"

class Quadtree {
    static const int MAX_PIXELS = 6;
    static const int MAX_LEVELS = 5;

    int level;
    SDL_Rect bounds;
    std::vector<Pixel*> pixels;
    std::vector<std::unique_ptr<Quadtree>> nodes;

public:
    Quadtree(int level, SDL_Rect bounds);
    void clear();
    void split();
    int getIndex(const SDL_Rect& rect) const;
    void insert(Pixel* pixel);
    void retrieve(std::vector<Pixel*>& returnPixels, const SDL_Point& area);
    void draw(SDL_Renderer* renderer) const;
};
