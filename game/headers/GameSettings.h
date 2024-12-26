#ifndef GAMESETTINGS_HEADER_
#define GAMESETTINGS_HEADER_

struct GameSettings
{
    constexpr static int windowWidth = 1600;
    constexpr static int windowHeight = 900;

    constexpr static int tileHeight = 30;
    constexpr static int tileWidth = 30;

    constexpr static int mapWidth = 200;
    constexpr static int mapHeight = 200;

    constexpr static int windowTileWidthCount = windowWidth / tileWidth;
    constexpr static int windowTileHeightCount = windowHeight / tileHeight;

    constexpr static int millXLocation = 13;
    constexpr static int millYLocation = mapHeight / 2;
};

#endif