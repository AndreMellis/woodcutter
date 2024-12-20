#ifndef GAMESETTINGS_HEADER_
#define GAMESETTINGS_HEADER_

struct GameSettings
{
    constexpr static int windowWidth = 1600;
    constexpr static int windowHeight = 900;

    constexpr static int tileHeight = 30;
    constexpr static int tileWidth = 30;

    constexpr static int tileWidthCount = windowWidth / tileWidth;
    constexpr static int tileHeightCount = windowHeight / tileHeight;
};

#endif