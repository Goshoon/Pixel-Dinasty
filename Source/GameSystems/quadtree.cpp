#include "quadtree.h"

Quadtree::Quadtree(int level, SDL_Rect bounds)
    : level(level), bounds(bounds) {}

void Quadtree::clear() {
    pixels.clear();
    for (auto& node : nodes) {
        if (node) node->clear();
    }
    nodes.clear();
}

void Quadtree::split() {
    int subWidth = bounds.w / 2;
    int subHeight = bounds.h / 2;
    int x = bounds.x;
    int y = bounds.y;

    nodes.emplace_back(std::make_unique<Quadtree>(level + 1, SDL_Rect{x + subWidth, y, subWidth, subHeight}));
    nodes.emplace_back(std::make_unique<Quadtree>(level + 1, SDL_Rect{x, y, subWidth, subHeight}));
    nodes.emplace_back(std::make_unique<Quadtree>(level + 1, SDL_Rect{x, y + subHeight, subWidth, subHeight}));
    nodes.emplace_back(std::make_unique<Quadtree>(level + 1, SDL_Rect{x + subWidth, y + subHeight, subWidth, subHeight}));
}

int Quadtree::getIndex(const SDL_Rect& rect) const 
{
    int verticalMidpoint = bounds.x + bounds.w / 2;
    int horizontalMidpoint = bounds.y + bounds.h / 2;

    bool top = rect.y + rect.h < horizontalMidpoint;
    bool bottom = rect.y > horizontalMidpoint;
    bool left = rect.x + rect.w < verticalMidpoint;
    bool right = rect.x > verticalMidpoint;

    if (top && right) return 0;
    if (top && left) return 1;
    if (bottom && left) return 2;
    if (bottom && right) return 3;

    return -1;  // doesn't fit neatly into a quadrant
}

void Quadtree::insert(Pixel* pixel) 
{
  if (!nodes.empty()) 
  {
    SDL_Rect tempRect = { pixel->position.x, pixel->position.y, 1, 1 }; // Convertion of SDL_Point to SDL_Rect
    int index = getIndex(tempRect);
    if (index != -1)
    {
      nodes[index]->insert(pixel);
      return;
    }
  }

  pixels.push_back(pixel);

  if (pixels.size() > MAX_PIXELS && level < MAX_LEVELS)
  {
    if (nodes.empty()) split();
    auto it = pixels.begin();

    while (it != pixels.end())
    {
      SDL_Rect tempArea = { (*it)->position.x, (*it)->position.y, 1, 1 };
      int index = getIndex(tempArea);
      if (index != -1)
      {
        nodes[index]->insert(*it);
        it = pixels.erase(it);
      } 
      else
      {
        ++it;
      }
    }
  }
}

void Quadtree::retrieve(std::vector<Pixel*>& returnPixels, const SDL_Point& area) {
    SDL_Rect rectArea = { area.x, area.y, 0, 0 };
    int index = getIndex(rectArea);
    if (index != -1 && !nodes.empty()) {
        nodes[index]->retrieve(returnPixels, area);
    }

    returnPixels.insert(returnPixels.end(), pixels.begin(), pixels.end());
}

void Quadtree::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Red borders
    SDL_RenderDrawRect(renderer, &bounds);

    for (const auto& node : nodes) {
        if (node) node->draw(renderer);
    }
}
