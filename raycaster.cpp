#include "raycaster.hpp"

raycaster::raycaster()
{
}
        
raycaster::~raycaster()
{
}
        
void raycaster::cast_ray(SDL_Renderer* renderer, int start_xpos, 
                            int start_ypos, int end_xpos, int end_ypos, 
                    const std::vector<std::vector<cell>> map, int cell_size)
{
    float dx = end_xpos - start_xpos;
    float dy = end_ypos - start_ypos;

    // put in smthin to prevent divide by 0
    float length = sqrtf(dx * dx + dy * dy);

    dx /= length;
    dy /= length;

    int map_xcoord = start_xpos / cell_size;
    int map_ycoord = start_ypos / cell_size;
    float xpos = ((float) start_xpos) / cell_size;
    float ypos = ((float) start_ypos) / cell_size;
    
    float xlen, ylen;
    int cell_xhit, cell_yhit;
    int xdir, ydir;
    bool hit = false;

    float check_xpos = xpos;
    float check_ypos = ypos;

    if (dx > 0 && dy > 0)
    {   
        while (!hit)
        {
            xlen = (map_xcoord + 1 - check_xpos) / dx;
            ylen = (map_ycoord + 1 - check_ypos) / dy;
    
            if (xlen < ylen)
            {
                check_xpos += xlen * dx;
                check_ypos += xlen * dy;
                map_xcoord++;
            }
            else
            {
                check_xpos += ylen * dx;
                check_ypos += ylen * dy;
                map_ycoord++;
            }

            if (map_xcoord * cell_size >= end_xpos || map_ycoord * cell_size >= end_ypos)
            {
                check_xpos = (float) end_xpos / cell_size;
                check_ypos = (float) end_ypos / cell_size;
                hit = true;
            }
            else if (map[map_ycoord][map_xcoord].active)
            {
                hit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, start_xpos, start_ypos, check_xpos * cell_size, check_ypos * cell_size);
    }   
}
