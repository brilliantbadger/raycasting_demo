#include "sprites.hpp"

grid::grid()
{
}

grid::~grid()
{
}

void grid::init(int window_width, int window_height, int cell_size)
{
    rows = window_height / cell_size;
    cols = window_width / cell_size;
    this->cell_size = cell_size;

    layout.resize(rows, std::vector<cell>(cols));
}

void grid::draw(SDL_Renderer* renderer)
{
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            SDL_Rect rect = {col * cell_size,
                             row * cell_size,
                             cell_size,
                             cell_size};

            if (layout[row][col].active) 
            {
                SDL_SetRenderDrawColor(renderer, 
                                       active.r, 
                                       active.g, 
                                       active.b,
                                       active.a);
                SDL_RenderFillRect(renderer, &rect);
            }
                
            SDL_SetRenderDrawColor(renderer,
                                   outline.r,
                                   outline.g,
                                   outline.b,
                                   outline.a);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void grid::fill_cells(int xpos, int ypos)
{
    int col = xpos / cell_size;
    int row = ypos / cell_size;

    if (row >= 0 && row < rows && col >= 0 && col < cols)
    {
        cell& cur_cell = layout[row][col];
        cur_cell.active = true;
    }
}

void grid::remove_cells(int xpos, int ypos)
{
    int col = xpos / cell_size;
    int row = ypos / cell_size;

    if (row >= 0 && row < rows && col >= 0 && col < cols)
    {
        cell& cur_cell = layout[row][col];
        cur_cell.active = false;
    }
}

void point::draw(SDL_Renderer* renderer) 
{
    SDL_Rect rect = {xpos,
                     ypos,
                     size,
                     size};

    SDL_SetRenderDrawColor(renderer,
                           fill.r,
                           fill.g,
                           fill.b,
                           fill.a);    
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer,
                           outline.r,
                           outline.g,
                           outline.b,
                           outline.a);
    SDL_RenderDrawRect(renderer, &rect);    
}

void point::move(const Uint8* keys, SDL_Scancode up, SDL_Scancode down,
                                    SDL_Scancode left, SDL_Scancode right) 
{
    if (keys[up])
    {
        if (ypos - speed <= 0)
        {
            ypos = 0;
        }
        else 
        {
            ypos -= speed;
        }
    }

    if (keys[down])
    {
        if (ypos + speed >= bound_h - size)
        {
            ypos = bound_h - size;
        }
        else
        {
            ypos += speed;
        }
    }

    if (keys[left])
    {
        if (xpos - speed <= 0)
        {
            xpos = 0;
        } 
        else
        {
            xpos -= speed;
        }
    }

    if (keys[right])
    {
        if (xpos + speed >= bound_w - size)
        {
            xpos = bound_w - size;
        }
        else
        {
            xpos += speed;
        }
    }
}
