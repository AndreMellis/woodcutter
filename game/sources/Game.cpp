#include "Game.h"

Game::Game()
{
    renderer = nullptr;
    window = nullptr;
    pGameFont = nullptr;
    pGameMap = Map::getInstance();
    
    inventory.wood = 0;
    inventory.totalEmployees = 1; // you start the game alone
    inventory.idleEmployees = 1;
    inventory.money = 100000; // a lot of money for testing
    inventory.day = 1;
}

bool Game::init()
{
    int success = 1;
    srand(time(0));

    if( SDL_CreateWindowAndRenderer("Woodsman", GameSettings::windowWidth, GameSettings::windowHeight, SDL_WINDOW_FULLSCREEN, &window, &renderer) )
    {
        SDL_SetRenderDrawColor(renderer, 0Xff, 0xFF, 0xFF, 0xFF);
        if(TTF_Init() == -1)
        {
            std::cerr << "Failed to initialize TTF! SDL_ERROR: " << SDL_GetError() << "\n";
        } else
        {
            if( loadAssets() )
            {
                pGameMap->genMap();
                actionHandler.init( &inventory );
                saveLoader.init(&inventory);
                worldClock.init(&inventory);
            } else
            {
                std::cerr << "Failed to load game assets!\n";
                success = 0;
            }
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
    pGameMap->loadAssets(renderer);
    builder.loadAssets(renderer);

    pGameFont = TTF_OpenFont( "assets/fonts/rye.ttf", 14 );
    if(pGameFont == nullptr)
    {
        std::cerr << "Failed to open font assets/fonts/rye.ttf! SDL_Error: " << SDL_GetError() << "\n";
        return 0;
    }

    return 1;
}

void Game::run()
{
    SDL_Event event;
    int running = 1;

    // initial clear and render
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    pGameMap->render(renderer);
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
                builder.handleEvent(event);
                pGameMap->handleKeyboardEvent(event);
                pGameMap->handleMouseEvent(event, builder.uiIsTriggered());
                actionHandler.handleEvent(event);
            }
        }
        if( !running )
            break;

        // UI Shiz
        if(builder.bSaveIsTriggered)
        {
            builder.bSaveIsTriggered = 0;
            saveLoader.saveGame();
        } else if(builder.bLoadIsTriggered)
        {
            builder.bLoadIsTriggered = 0;
            saveLoader.loadGame();
        }

        //before rendering stuff
        builder.buildItem();
        actionHandler.step();
        worldClock.progress();
        
        // rerender the screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        pGameMap->render(renderer);
        builder.renderUI(renderer);
        uiHandler.drawBaseUI( renderer, &inventory, pGameFont, 450, 300 );
        SDL_RenderPresent(renderer);
    }
}