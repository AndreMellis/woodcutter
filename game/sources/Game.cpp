#include "Game.h"

Game::Game()
{
    renderer = nullptr;
    window = nullptr;
}

bool Game::init()
{
    int success = 1;
    srand(time(0));

    if( SDL_CreateWindowAndRenderer("Woodsman", GameSettings::windowWidth, GameSettings::windowHeight, SDL_WINDOW_FULLSCREEN, &window, &renderer) )
    {
        SDL_SetRenderDrawColor(renderer, 0Xff, 0xFF, 0xFF, 0xFF);
        if( loadAssets() )
        {
            gameMap.genMap();
        } else
        {
            std::cerr << "Failed to load game assets!\n";
            success = 0;
        }
    } else
    {
        std::cerr << "Failed to create the window and renderer! SDL_ERROR: " << SDL_GetError() << "\n";
        success = 0;
    }
    return success;
}

void Game::close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

bool Game::loadAssets()
{
    //load map assets
    gameMap.loadAssets(renderer);

    return 1;
}

void Game::run()
{
    SDL_Event event;
    int running = 1;

    // initial clear and render
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    gameMap.render(renderer);
    SDL_RenderPresent(renderer);

    while(running)
    {
        while( SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_EVENT_QUIT )
            {
                running = 0;
                break;
            } else
            {
                gameMap.handleEvent(event);
            }
        }
        if( !running )
            break;

        // rerender the screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        gameMap.render(renderer);
        SDL_RenderPresent(renderer);
    }
}