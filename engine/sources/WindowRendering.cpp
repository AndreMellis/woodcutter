#include "WindowRendering.h"

#include <iostream>


WindowRendering *WindowRendering::pInstance = nullptr;

WindowRendering *WindowRendering::getInstance()
{
	if(!pInstance)
	{
		pInstance = new WindowRendering();
	}
	return pInstance;
}

WindowRendering::WindowRendering()
{
	gWindow = nullptr;
	gRenderer = nullptr;
	gTextureBuffer = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{ // failed to initialize video
		std::cerr << "failed to initialize SDL Video! SDL_Error: " << SDL_GetError() << "\n";
		exit(1); // exit out the game
	} else
	{
		gWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP); //create fullscreen window

		if(!gWindow)
		{
			std::cerr << "failed to create window! SDL_Error: " << SDL_GetError() << "\n";
			exit(1); // exit out the game
		} else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED); //create renderer
			if(!gRenderer)
			{
				std::cerr << "failed to create renderer! SDL_Error: " << SDL_GetError() << "\n";
				exit(1); // exit out the game
			} else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //draw in white
				
				//initialize png loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) //load png and make sure it actuall was png
				{ 
					std::cerr << "SDL_Image failed to initialize! IMG_Error:" << IMG_GetError() << "\n";
					exit(1); //fail out the program
				} else
				{
					if( TTF_Init() == -1)
					{
						std::cerr << "Failed to initialize TTF! TTF_Error: " << TTF_GetError() << "\n";
						exit(1);
					}
				}

			}
		}
	}

}

void WindowRendering::clearBuffer()
{
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00); //make the next thing I draw black
	SDL_RenderClear( gRenderer ); //draw all black to screen
}

void WindowRendering::close()
{
	SDL_DestroyTexture(gTextureBuffer);
	gTextureBuffer = nullptr;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = nullptr;
	gWindow = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void WindowRendering::drawSolidRect(SDL_Rect *shape)
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); // make the next thing I draw white
	SDL_RenderFillRect(gRenderer, shape);
}

SDL_Texture *WindowRendering::stringToSurface(std::string inputStr, SDL_Color color, int fontSize, std::string fontName)
{
	TTF_Font *ttfFont = TTF_OpenFont(fontName.c_str(), fontSize);
	if(!ttfFont)
	{
		std::cerr << "Failed to open TTF_Font " << inputStr << " TTF_Error: " << TTF_GetError() <<"\n";
	}

	SDL_Surface *surfaceMessage = TTF_RenderText_Solid(ttfFont, inputStr.c_str(), color);
	SDL_Texture *messageTexture = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);

	TTF_CloseFont(ttfFont);
	SDL_FreeSurface(surfaceMessage);
	surfaceMessage = nullptr;

	return messageTexture;
}

void WindowRendering::drawString(std::string inputStr, SDL_Rect *shape)
{ // draws a string to screen
	SDL_Color white = {255, 255, 255};
	SDL_Texture *tempText = stringToSurface(inputStr, white, 24, "assets/fonts/Orbitron-Bold.ttf");

	SDL_RenderCopy(gRenderer, tempText, NULL, shape);

	SDL_DestroyTexture(tempText);
	tempText=nullptr;
}

void WindowRendering::drawImg(std::string path, SDL_Rect *shape)
{ // draws a png to screen
	SDL_Texture *pLoadedText = nullptr;

	SDL_Surface *pLoadedSurface = IMG_Load( path.c_str() );
	if( !pLoadedSurface )
	{
		std::cerr << "Failed to load " << path << " SDL_Image Error " << IMG_GetError() << "\n";
	} else
	{
		pLoadedText = SDL_CreateTextureFromSurface(gRenderer, pLoadedSurface);
		if( !pLoadedText )
		{
			std::cerr << "Failed to create texture from " << path << " SDL_Error: " << SDL_GetError() << "\n";
		} else
		{
			SDL_RenderCopy(gRenderer, pLoadedText, NULL, shape);
		}
	}

	SDL_FreeSurface(pLoadedSurface);
	SDL_DestroyTexture(pLoadedText);
	pLoadedText = nullptr;
	pLoadedSurface = nullptr;
}