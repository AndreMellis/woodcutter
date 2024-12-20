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
    for( int i = 0; i < asset_AssetCount; i++ )
    {
        SDL_DestroyTexture( pTextureArray[i] );
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

SDL_Texture *Game::makeTexture(std::string path)
{
    SDL_Surface *tempSurface = nullptr;
    SDL_Texture *tempTexture = nullptr;

    tempSurface = IMG_Load( path.c_str() );

    if(!tempSurface)
    {
        std::cerr << "Failed to load image " << path << "! SDL_Error: " << SDL_GetError() << "\n";
    } else
    {
        tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        
        if(!tempTexture)
        {
            std::cerr << "Failed to load texture from " << path << "! SDL_Error: " << SDL_GetError() << "\n";
        }
    }

    SDL_DestroySurface(tempSurface);
    tempSurface = nullptr;

    return tempTexture;

}

bool Game::loadAssets()
{
    // load grass
    pTextureArray[asset_Grass] = makeTexture("assets/terrain/grass.png");
    if(pTextureArray[asset_Grass] == nullptr)
        return 0;
    
    // load water
    pTextureArray[asset_Water] = makeTexture("assets/terrain/water.png");
    if(pTextureArray[asset_Water] == nullptr)
        return 0;

    return 1;
}

void Game::run()
{
    SDL_Event event;
    int running = 1;

    // initial clear and render
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    gameMap.render(renderer, pTextureArray);
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
        gameMap.render(renderer, pTextureArray);
        SDL_RenderPresent(renderer);
    }
}