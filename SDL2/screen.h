#include <SDL2/SDL.h>
#include <vector>

using namespace std;

class Screen {
  SDL_Event event;
  SDL_Window *window;
  SDL_Renderer *renderer;
  vector<SDL_FPoint> points;

public:
  Screen() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640 , 480 , 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 2, 2);
  }

  void pixel(float x, float y) {
    points.emplace_back(x, y); // emplace_back is faster than push_back
  }

  void show() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (auto &p : points) {
      SDL_RenderDrawPointF(renderer, p.x, p.y);
    }
    SDL_RenderPresent(renderer);
  }

  void clear() {
    
    points.clear();
  }

  void input() {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        SDL_Quit();
        exit(0);
      }
    }
  }
};
