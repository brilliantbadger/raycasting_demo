#include "game.hpp"

game* demo = nullptr;

int main(int argc, const char* argv[])
{
    const char* title = "raycaster_demo";
    const int xpos = SDL_WINDOWPOS_CENTERED;
    const int ypos = SDL_WINDOWPOS_CENTERED;
    const int width = 800;
    const int height = 600;

    const int fps = 60;
    const int frame_delay = 1000 / fps;

    Uint32 frame_start;
    int frame_time;

    demo = new game();
    demo->init(title,
               SDL_WINDOWPOS_CENTERED,
               SDL_WINDOWPOS_CENTERED,
               width,
               height);

    while (demo->running())
    {
        frame_start = SDL_GetTicks();

        demo->handle_events();
        demo->update();
        demo->render();
        
        // sets frame rate
        frame_time = SDL_GetTicks() - frame_start;

        if (frame_delay > frame_time)
        {
            SDL_Delay(frame_delay - frame_time);
        }
    }

    demo->clean();
    delete demo;

    return 0;
}
