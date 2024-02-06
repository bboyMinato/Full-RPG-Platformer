#include "../include/MapParser.h"
#include "GameMap.h"
MapParser* MapParser::_instance = nullptr;

MapParser* MapParser::GetInstance()
{
    if (_instance == nullptr)
        _instance = new MapParser();

    return _instance;
}

bool MapParser::Load()
{
    if (!Parse("Level", "assets\\map\\map.tmx"))
        return false;

    return true;
}

void MapParser::Clean()
{
    std::map<std::string, GameMap*>::iterator it;
    for (it = _maps.begin(); it != _maps.end(); it++)
        it->second = nullptr;
}

bool MapParser::Parse(std::string id, std::string source)
{
    TiXmlDocument xml(source);
    if (!xml.LoadFile())
    {
        throw std::runtime_error("Failed to load XML file: " + std::string(source));
    }

    TiXmlElement* mapElement = xml.RootElement();
    if (!mapElement)
    {
        throw std::runtime_error("Invalid Tiled map format. No root element found.");
    }

    int rowCount, colCount, tileSize;
    if (mapElement->QueryIntAttribute("width", &colCount) != TIXML_SUCCESS ||
        mapElement->QueryIntAttribute("height", &rowCount) != TIXML_SUCCESS ||
        mapElement->QueryIntAttribute("tilewidth", &tileSize) != TIXML_SUCCESS)
    {
        throw std::runtime_error("Invalid Tiled map format. Missing or invalid 'width', 'height', or 'tilewidth' attribute.");
    }

    // Parse tilesets
    TileSetList tilesets;
    for (TiXmlElement* e = mapElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
            tilesets.push_back(ParseTileset(e));
    }

    // Parse tile layers
    GameMap* gameMap = new GameMap();
    for (TiXmlElement* e = mapElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tileSize, rowCount, colCount);
            gameMap->_mapLayers.push_back(tilelayer);
        }
    }

    _maps[id] = gameMap;

    return true;
}

TileSet MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
    TileSet tileset;

    const char* nameAttr = xmlTileset->Attribute("name");
    if (nameAttr)
    {
        tileset.name = nameAttr;
    }

    if (xmlTileset->QueryIntAttribute("firstgid", &tileset.firstGID) != TIXML_SUCCESS || xmlTileset->QueryIntAttribute("tilecount", &tileset.tileCount) != TIXML_SUCCESS)
    {
        throw std::runtime_error("Invalid Tiled map format. Missing or invalid 'firstgid' or 'tilecount' attribute in tileset.");
    }

    tileset.lastID = tileset.firstGID + tileset.tileCount - 1;

    if (xmlTileset->QueryIntAttribute("columns", &tileset.colCount) != TIXML_SUCCESS)
    {
        throw std::runtime_error("Invalid Tiled map format. Missing or invalid 'columns' attribute in tileset.");
    }

    if (xmlTileset->QueryIntAttribute("tilewidth", &tileset.tileSize) != TIXML_SUCCESS)
    {
        throw std::runtime_error("Invalid Tiled map format. Missing or invalid 'tilewidth' attribute in tileset.");
    }

    TiXmlElement* image = xmlTileset->FirstChildElement();
    if (image)
    {
        const char* sourceAttr = image->Attribute("source");

        if (sourceAttr)
        {
            tileset.source = sourceAttr;
        }
    }
    else
    {
        throw std::runtime_error("Invalid Tiled map format. Missing 'image' element in tileset.");
    }

    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tilesets, int tilesize, int rowcount, int colcount)
{
    // TileMap = std::vector<std::vector<int>>  
    TileMap tileMap(rowcount, std::vector<int>(colcount, 0));

    TiXmlElement* dataElement = xmlLayer->FirstChildElement("data");
    if (!dataElement)
    {
        throw std::runtime_error("Invalid Tiled map format. Missing 'data' element in a layer.");
    }

    const char* tileDataString = dataElement->GetText();
    std::istringstream iss(tileDataString);

    for (int row = 0; row < rowcount; row++)
    {
        for (int col = 0; col < colcount; col++)
        {
            std::string tileID;
            std::getline(iss, tileID, ',');
            std::stringstream converter(tileID);
            converter >> tileMap[row][col];
        }
    }

    return (new TileLayer(tilesets, tileMap, tilesize, rowcount, colcount));
}
