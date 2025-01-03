#include "UserInterface.h"

void UserInterface::drawBaseUI(SDL_Renderer *pGameRenderer, float fXCord, float fYCord, float fWidth, float fHeight)
{ // draws the base UI to the given XY Cord
    float fQuitButtonSize = 15;

    arrUIRects[UI_MAIN_BOX] = { fXCord, fYCord, fWidth, fHeight };

    arrUIRects[UI_TOP_BANNER] = {
                                    fXCord,
                                    fYCord,
                                    fWidth,
                                    fQuitButtonSize // the top banner will be a solid fQuitButtonSize pixels
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