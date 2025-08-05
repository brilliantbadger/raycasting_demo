#ifndef raycaster_hpp
#define raycaster_hpp

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

#include "sprites.hpp"

class raycaster
{
    public:
        raycaster();
        ~raycaster();

        void cast_ray(SDL_Renderer* renderer, int start_xpos,
                        int start_ypos, int end_xpos, int end_ypos, 
                    const std::vector<std::vector<cell>> grid, int cell_size);

    private:
        float dx, dy;
        const int max_distance = 100;
};

#endif
