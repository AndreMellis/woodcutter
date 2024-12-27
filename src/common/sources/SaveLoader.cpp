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

    std::ofstream inventoryFile(strInventorySave);
    if( inventoryFile.is_open() )
    {
        inventoryFile << pGameInventory->wood << "\n";
        inventoryFile << pGameInventory->totalEmployees << "\n";
        inventoryFile << pGameInventory->idleEmployees << "\n";
        inventoryFile << pGameInventory->money << "\n";
    } else
    {
        std::cerr << "Failed to save file " << strInventorySave << "\n";
    }
    inventoryFile.close();
}

void SaveLoader::loadGame()
{
    std::ifstream baseMapFile(strBaseMapSave);
    if( baseMapFile.is_open() )
    {
        int row = 0;
        int col = 0;
        int rowCount = GameSettings::mapHeight;
        int colCount = GameSettings::mapWidth;
        std::string fileLine;

        while( std::getline( baseMapFile, fileLine  ) )
        {
            switch( std::stoi(fileLine) ) // convert line from string to int
            {
                case static_cast<int>( TileType::Grass ):
                    pGameMap->changeBaseMapTileType( col, row, TileType::Grass );
                    break;

                case static_cast<int>( TileType::Water):
                    pGameMap->changeBaseMapTileType( col, row, TileType::Water);
                    break;

                case static_cast<int>( TileType::Road):
                    pGameMap->changeBaseMapTileType( col, row, TileType::Road);
                    break;
            }

            col++;
            if(col >= GameSettings::mapWidth)
            {
                col = 0;
                row++;
            }
        }
    }
    baseMapFile.close();

    std::ifstream objectMapFile(strObjectMapSave);
    if( objectMapFile.is_open() )
    {
        int row = 0;
        int col = 0;
        int rowCount = GameSettings::mapHeight;
        int colCount = GameSettings::mapWidth;
        std::string fileLine;

        while( std::getline( objectMapFile, fileLine  ) )
        {
            switch( std::stoi(fileLine) ) // convert line from string to int
            {
                case static_cast<int>( TileType::Tree):
                    pGameMap->changeObjectMapTileType( col, row, TileType::Tree);
                    break;

                case static_cast<int>( TileType::Empty):
                    pGameMap->changeObjectMapTileType( col, row, TileType::Empty);
                    break;

                case static_cast<int>( TileType::Stump):
                    pGameMap->changeObjectMapTileType( col, row, TileType::Stump);
                    break;

                case static_cast<int>( TileType::Concrete):
                    pGameMap->changeObjectMapTileType( col, row, TileType::Concrete);
                    break;

                case static_cast<int>( TileType::Mill):
                    pGameMap->changeObjectMapTileType( col, row, TileType::Mill);
                    break;

                case static_cast<int>( TileType::UnclaimedLumber):
                    pGameMap->changeObjectMapTileType( col, row, TileType::UnclaimedLumber);
                    break;

                case static_cast<int>( TileType::Worker):
                    pGameMap->changeObjectMapTileType( col, row, TileType::Worker);
                    break;

            }

            col++;
            if(col >= GameSettings::mapWidth)
            {
                col = 0;
                row++;
            }
        }
    }
    objectMapFile.close();

    std::ifstream inventoryFile(strInventorySave);
    if( inventoryFile.is_open() )
    {
        std::string fileLine;

        std::getline(inventoryFile, fileLine);
        pGameInventory->wood = std::stoi(fileLine);

        std::getline(inventoryFile, fileLine);
        pGameInventory->totalEmployees = std::stoi(fileLine);

        std::getline(inventoryFile, fileLine);
        pGameInventory->idleEmployees = std::stoi(fileLine);

        std::getline(inventoryFile, fileLine);
        pGameInventory->money = std::stoi(fileLine);
    } else
    {
        std::cerr << "Failed to open save file " << strInventorySave << "\n";
    }
}