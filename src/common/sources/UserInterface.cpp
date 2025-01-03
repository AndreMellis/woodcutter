#include "UserInterface.h"

UserInterface::UserInterface()
{
    pMoneyTexture = nullptr;
}

void UserInterface::drawUIShell(SDL_Renderer *pGameRenderer, float fXCord, float fYCord, float fWidth, float fHeight)
{ // draws the base UI to the given XY Cord
    const float fQuitButtonSize = 15;
    const float fTopBannerHeight = 15;

    arrUIRects[UI_MAIN_BOX] = { fXCord, fYCord, fWidth, fHeight + fTopBannerHeight };

    arrUIRects[UI_TOP_BANNER] = {
                                    fXCord,
                                    fYCord,
                                    fWidth,
                                    fTopBannerHeight// the top banner will be a solid fQuitButtonSize pixels
                                    };

    arrUIRects[UI_QUIT_BUTTON] = {
                                    fXCord + fWidth - fQuitButtonSize,
                                    fYCord,
                                    fQuitButtonSize,
                                    fQuitButtonSize                                    
                                    }; // the quit button will be the top right fQuitButtonSize pixels
    
    
    // all my drawing here

    // main background box
    SDL_SetRenderDrawColor( pGameRenderer, arrUIBackGroundColor[0], arrUIBackGroundColor[1], arrUIBackGroundColor[2], arrUIBackGroundColor[3] );
    SDL_RenderFillRect( pGameRenderer, &arrUIRects[UI_MAIN_BOX] );

    // top banner
    SDL_SetRenderDrawColor( pGameRenderer, arrUISecondaryColor[0], arrUISecondaryColor[1], arrUISecondaryColor[2], arrUISecondaryColor[3] );
    SDL_RenderFillRect( pGameRenderer, &arrUIRects[UI_TOP_BANNER] );

    // close button
    SDL_SetRenderDrawColor( pGameRenderer, arrUIThirdColor[0], arrUIThirdColor[1], arrUIThirdColor[2], arrUIThirdColor[3] );
    SDL_RenderFillRect( pGameRenderer, &arrUIRects[UI_QUIT_BUTTON] );

    // draw the X on the exit button
    SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 255 ); // black
    float fPadding = 2;

    SDL_RenderLine( pGameRenderer, 
                    fXCord + fWidth - fQuitButtonSize + fPadding,
                    fYCord + fPadding,
                    fXCord + fWidth - fPadding,
                    fYCord + fQuitButtonSize - fPadding
                    );
    SDL_RenderLine( pGameRenderer, 
                    fXCord + fWidth - fPadding,
                    fYCord + fPadding,
                    fXCord + fWidth - fQuitButtonSize + fPadding,
                    fYCord + fQuitButtonSize - fPadding
                    );
}

void UserInterface::drawBaseUI(SDL_Renderer *pGameRenderer, Inventory *pGameInventory, TTF_Font *pGameFont, float fXCord, float fYCord)
{ // draws the UI dedicated to the base and inventory
    float fInventoryIconSize = 30;
    float fPaddingBetweenIcons = 10;
    float fBaseUIWidth = (fInventoryIconSize + fPaddingBetweenIcons) * 5; // I want 5 items per row
    float fBaseUIHeight = (fInventoryIconSize + fPaddingBetweenIcons) * 10; // I want 5 rows of items
    float fFontLineThickness = 20;

    // C and not c++ code to make sMoney contain all our money
    if( !pMoneyTexture )
    { // I only want to do this work when I open for the first time
        char sMoney[17] = "Money: "; //note, there will be errors if I ever have more than 999,999,999 money
        char sMoneyCount[10];
        sprintf( sMoneyCount, "%d", pGameInventory->money);
        strcat( sMoney, sMoneyCount );

        char sIdleEmployees[26] = "Idle Employees: ";
        char sIdleEmployeeCount[10];
        sprintf( sIdleEmployeeCount, "%d", pGameInventory->idleEmployees);
        strcat( sIdleEmployees, sIdleEmployeeCount);

        char sEmployees[27] = "Total Employees: ";
        char sEmployeeCount[10];
        sprintf( sEmployeeCount, "%d", pGameInventory->totalEmployees);
        strcat( sEmployees, sEmployeeCount);

        char sWoodHarvested[26] = "Wood Harvested: ";
        char sWoodCount[10];
        sprintf( sWoodCount, "%d", pGameInventory->wood);
        strcat( sWoodHarvested, sWoodCount);


        pMoneyTexture = TextureHandler::renderTextureFromFont( sMoney, pGameFont, pGameRenderer );
        pEmployeeTexture = TextureHandler::renderTextureFromFont( sEmployees, pGameFont, pGameRenderer );
        pIdleEmployeeTexture = TextureHandler::renderTextureFromFont( sIdleEmployees, pGameFont, pGameRenderer );
        pWoodCountTexture = TextureHandler::renderTextureFromFont( sWoodHarvested, pGameFont, pGameRenderer );

        // I'm cheating and using this to configure the rect once too
        arrBaseUIRects[UI_MONEY_BOX] = { fXCord, fYCord + fFontLineThickness, 100, fFontLineThickness};
        arrBaseUIRects[UI_EMPLOYEE_BOX] = { fXCord, fYCord + (fFontLineThickness * 2), 150, fFontLineThickness};
        arrBaseUIRects[UI_IDLE_EMPLOYEE_BOX] = { fXCord, fYCord + (fFontLineThickness * 3), 150, fFontLineThickness};
        arrBaseUIRects[UI_WOOD_COUNT_BOX] = { fXCord, fYCord + (fFontLineThickness * 4), 150, fFontLineThickness};
    }

    drawUIShell( pGameRenderer, fXCord, fYCord, fBaseUIWidth, fBaseUIHeight );

    //print stats
    SDL_RenderTexture( pGameRenderer, pMoneyTexture, NULL, &arrBaseUIRects[UI_MONEY_BOX] );
    SDL_RenderTexture( pGameRenderer, pEmployeeTexture, NULL, &arrBaseUIRects[UI_EMPLOYEE_BOX] );
    SDL_RenderTexture( pGameRenderer, pIdleEmployeeTexture, NULL, &arrBaseUIRects[UI_IDLE_EMPLOYEE_BOX] );
    SDL_RenderTexture( pGameRenderer, pWoodCountTexture, NULL, &arrBaseUIRects[UI_WOOD_COUNT_BOX] );
}

void UserInterface::closeBaseUI()
{
    SDL_DestroyTexture(pMoneyTexture);
    SDL_DestroyTexture(pEmployeeTexture);
    SDL_DestroyTexture(pIdleEmployeeTexture);
    SDL_DestroyTexture(pWoodCountTexture);
    pMoneyTexture = nullptr;
    pEmployeeTexture = nullptr;
    pIdleEmployeeTexture = nullptr;
    pWoodCountTexture = nullptr;
}