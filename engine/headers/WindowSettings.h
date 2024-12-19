#ifndef WINDOWSETTINGS_HEADER_
#define WINDOWSETTINGS_HEADER_

struct WindowSettings
{
    constexpr static int windowHeight = 600;
    constexpr static int windowWidth = 1800;

    constexpr static int tileHeight = 30;
    constexpr static int tileWidth = 30;

    constexpr static int tileWidthCount = windowWidth / tileWidth;
    constexpr static int tileHeightCount = windowHeight / tileHeight;
};

#endif