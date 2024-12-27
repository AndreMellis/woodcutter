#ifndef SAVELOADER_HEADER_
#define SAVELOADER_HEADER_

//#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "GameSettings.h"
#include "Inventory.h"
#include "Tile.h"
#include "Map.h"


class SaveLoader
{
private:
    #ifdef _WIN32 
        /*
        TCHAR userProfilePath[MAX_PATH];
        DWORD bufferSize = MAX_PATH;
        GetUserProfileDirectory(NULL, userProfilePath, &bufferSize);
        std::wstring wstrUserProfilePath(userProfilePath);
        std::string strProfilePath(wstrUserProfilePath.begin(), wstrUserProfilePath.end());
        */
    #else
        std::string strProfilePath = getenv("HOME");
    #endif

    const std::string strSaveFolderPath = strProfilePath + ".local/share/woodsman/";
    const std::string strBaseMapSave = strSaveFolderPath + "base.map";
    const std::string strObjectMapSave = strSaveFolderPath + "objects.map";

    Map *pGameMap;
    Inventory *pGameInventory;

public:
    SaveLoader();

    void init(Inventory *inventory);

    void saveGame();
};

#endif