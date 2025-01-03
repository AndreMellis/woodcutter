#ifndef USERINTERFACE_HEADER_
#define USERINTERFACE_HEADER_

#include <SDL3/SDL.h>
#include "TextureHandler.h"
#include "Inventory.h"

class UserInterface
{
private:
    enum enumUIComponents {UI_MAIN_BOX, UI_TOP_BANNER, UI_QUIT_BUTTON, UI_COMPONENT_COUNT};
    enum enumBaseUIComponents { UI_MONEY_BOX, UI_EMPLOYEE_BOX, UI_IDLE_EMPLOYEE_BOX, UI_WOOD_COUNT_BOX , BASE_UI_COMPONENT_COUNT };

    const Uint8 arrUIPrimaryColor[4] = { 136, 170, 119, 225 };
    const Uint8 arrUISecondaryColor[4] = { 204, 153, 102, 225 };
    const Uint8 arrUIThirdColor[4] = { 170, 102, 119, 225 };
    const Uint8 arrUIBackGroundColor[4] = { 119, 102, 119, 255 };


    SDL_FRect arrUIRects[ UI_COMPONENT_COUNT ];
    SDL_FRect arrBaseUIRects[ BASE_UI_COMPONENT_COUNT ];

    SDL_Texture *pMoneyTexture;
    SDL_Texture *pEmployeeTexture;
    SDL_Texture *pIdleEmployeeTexture;
    SDL_Texture *pWoodCountTexture;

    void drawUIShell(SDL_Renderer *pGameRenderer, float fXCord, float fYCord, float fWidth, float fHeight); // draws the base UI to the given XY Cord
public:
    UserInterface();

    void drawBaseUI(SDL_Renderer *pGameRenderer, Inventory *pGameInventory, TTF_Font *pGameFont, float fXCord, float fYCord); // draws the base UI to the given XY Cord
    void closeBaseUI();

};

#endif