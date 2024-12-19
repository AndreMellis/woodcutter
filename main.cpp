#include "WindowRendering.h"
#include "Map.h"

#include <SDL.h>
#include <ctime>
#include <cstdlib>

int main(int argc, char *args[])
{
    srand(time(0));

    SDL_Event event;
    WindowRendering *pWindowRenderer = WindowRendering::getInstance();

    //testing block
    Map map;

    pWindowRenderer->clearBuffer();
    map.render();
    pWindowRenderer->renderPresent();

    bool quit = 0;
    
    while(!quit)
    {
        while( SDL_PollEvent( &event ) != 0)
        {
            if( event.type == SDL_QUIT )
            {
                pWindowRenderer->close();
                quit=1;
            }
        }
    }

    return 0;
}