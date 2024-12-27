#include "SaveLoader.h"

SaveLoader::SaveLoader()
{
    pGameInventory = nullptr;
    pGameMap = nullptr;
}

void SaveLoader::init(Inventory *inventory)
{
    pGameInventory = inventory;
    pGameMap = Map::getInstance();
}

void SaveLoader::saveGame()
{
    std::ofstream baseMapFile(strBaseMapSave);
    if(baseMapFile.is_open())
    {
        for( int row = 0; row < GameSettings::mapHeight; row++ )
        {
            for( int col = 0; col < GameSettings::mapWidth; col++ )
            {
                baseMapFile << static_cast<int>(pGameMap->getBaseMapTileType(col, row)) << "\n";
            }
        }
    } else
    {
        std::cerr << "Failed to open save file " << strBaseMapSave << "\n";
    }
    baseMapFile.close();

    std::ofstream objectMapFile(strObjectMapSave);
    if(objectMapFile.is_open())
    {
        for( int row = 0; row < GameSettings::mapHeight; row++ )
        {
            for( int col = 0; col < GameSettings::mapWidth; col++ )
            {
                objectMapFile << static_cast<int>(pGameMap->getObjectMapTileType(col, row)) << "\n";
            }
        }
    } else
    {
        std::cerr << "Failed to open save file " << strObjectMapSave << "\n";
    }
    objectMapFile.close();
}
