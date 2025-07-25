#ifndef sprites_hpp
#define sprites_hpp

#include <SDL2/SDL.h>
#include <vector>

struct cell
{
    bool active = false;
};

class grid {
    public:
        grid();
        ~grid();

        void init(int window_width, int window_height, int cell_size);
        void draw(SDL_Renderer* renderer);
        void fill_cells(int xpos, int ypos);
        void remove_cells(int xpos, int ypos);

    private:
        int cell_size;
        int rows;
        int cols;
        
        const SDL_Color active = {225, 211, 186, SDL_ALPHA_OPAQUE};
        const SDL_Color outline = {50, 48, 47, SDL_ALPHA_OPAQUE};

        std::vector<std::vector<cell>> layout;
};

struct point
{
    int xpos, ypos, size, speed, bound_w, bound_h;
    SDL_Color fill, outline;

    void draw(SDL_Renderer* renderer);
    void move(const Uint8* keys, SDL_Scancode up, SDL_Scancode down,
                                    SDL_Scancode left, SDL_Scancode right);
};

#endif
