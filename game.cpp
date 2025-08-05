#include "game.hpp"
#include "sprites.hpp"

game::game()
{
    is_running = false;
    window = nullptr;
    renderer = nullptr;
}

game::~game()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void game::init(const char* title, int xpos, int ypos, 
                                    int window_width, int window_height)
{
    this->window_width = window_width;
    this->window_height = window_height;

    int flags = 0;

    // initialize window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "subsystems initialized..." << std::endl;

        window = SDL_CreateWindow(title, 
                                  xpos, 
                                  ypos, 
                                  window_width, 
                                  window_height, 
                                  flags);

        if (window)
        {
            std::cout << "window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, 
                                      -1, 
                                      0);

        if (renderer)
        {
            std::cout << "renderer created" << std::endl;
        }

        is_running = true;
    }
    else
    {
        is_running = false;
    }

    // initializing background
    map.init(window_width,
             window_height,
             cell_size);

    // initializing points
    point1 = {p1_xpos,
              p1_ypos,
              p1_size,
              p1_speed,
              window_width,
              window_height,
              p1_color,
              p1_outline};
    point2 = {p2_xpos,
              p2_ypos,
              p2_size,
              p2_speed,
              window_width,
              window_height,
              p2_color,
              p2_outline};
}

void game::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                is_running = false;
                break;
              
            default:
                break;
        }
    }
}

void game::update()
{
    int mouse_xpos, mouse_ypos;
    const Uint32 buttons = SDL_GetMouseState(&mouse_xpos, &mouse_ypos);

    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        map.fill_cells(mouse_xpos, mouse_ypos);
    }
    if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
        map.remove_cells(mouse_xpos, mouse_ypos);
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);
       
    point1.move(keys, 
                SDL_SCANCODE_W, 
                SDL_SCANCODE_S, 
                SDL_SCANCODE_A, 
                SDL_SCANCODE_D);
    point2.move(keys, 
                SDL_SCANCODE_I, 
                SDL_SCANCODE_K, 
                SDL_SCANCODE_J, 
                SDL_SCANCODE_L); 
}

void game::render()
{
    SDL_SetRenderDrawColor(renderer, 29, 32, 33, SDL_ALPHA_OPAQUE);

    SDL_RenderClear(renderer);
 
    map.draw(renderer);

    point1.draw(renderer);
    point2.draw(renderer);

    ray.cast_ray(renderer, point1.xpos, point1.ypos, point2.xpos, point2.ypos, map.get_layout(), cell_size);

    SDL_RenderPresent(renderer);
}

void game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "game cleaned" << std::endl;
}

bool game::running()
{
    return is_running;
}
