#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <iostream>

#include "sprites.hpp"
#include "raycaster.hpp"

class game
{
    public:
        game();
        ~game();

        void init(const char* title, int xpos, int ypos, 
                                        int window_width, int window_height);
        void handle_events();
        void update();
        void render();
        void clean();

        bool running();
    
    private:
        bool is_running;
        SDL_Window *window;
        SDL_Renderer *renderer;

        int window_width, window_height;
        int left_click_held;
        int right_click_held;

        const int cell_size = 40;

        // values for points
        const int p1_xpos = 200;
        const int p1_ypos = 300;
        const int p1_size = 20;
        const int p1_speed = 5;
        const SDL_Color p1_color = {169, 182, 101, SDL_ALPHA_OPAQUE};
        const SDL_Color p1_outline = {50, 48, 47, SDL_ALPHA_OPAQUE};

        const int p2_xpos = 600;
        const int p2_ypos = 300;
        const int p2_size = 20;
        const int p2_speed = 5;
        const SDL_Color p2_color = {125, 174, 163, SDL_ALPHA_OPAQUE};
        const SDL_Color p2_outline = {50, 48, 47, SDL_ALPHA_OPAQUE};

        grid map;

        point point1, point2;

        raycaster ray;
};

#endif
