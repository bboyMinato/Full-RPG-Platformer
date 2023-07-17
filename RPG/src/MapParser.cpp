#include "../include/MapParser.h"
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
    TiXmlDocument xml;
    xml.LoadFile(source);

    if (xml.Error())
    {
        std::cerr << "Failed to load: " << source << std::endl;
        return false;
    }

    else
        std::cerr << "XML file loaded successfully!" << std::endl;

    TiXmlElement* root = xml.RootElement();
    int rowcount, colcount, tilesize = 0;

    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    //parse tile sets
    TileSetList tilesets;
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
            tilesets.push_back(ParseTileset(e));
    }

    //parse layers
    GameMap* gameMap = new GameMap();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gameMap->_mapLayers.push_back(tilelayer);
        }
    }

    _maps[id] = gameMap;
    return true;
}

TileSet MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
    TileSet tileset;

    if (xmlTileset->Attribute("name"))
        tileset.name = xmlTileset->Attribute("name");

    if (xmlTileset->Attribute("firstgid"))
        xmlTileset->Attribute("firstgid", &tileset.firstID);

    if (xmlTileset->Attribute("tilecount"))
        xmlTileset->Attribute("tilecount", &tileset.tileCount);
    tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;

    if (xmlTileset->Attribute("columns"))
        xmlTileset->Attribute("columns", &tileset.colCount);

    if (xmlTileset->Attribute("tilewidth"))
        xmlTileset->Attribute("tilewidth", &tileset.tileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();

    if (image->Attribute("source"))
        tileset.source = image->Attribute("source");

    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tilesets, int tilesize, int rowcount, int colcount)
{
    TiXmlElement* data;
    std::string matrix;

    std::cout << matrix << std::endl;

    for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            data = e;
            matrix = data->GetText();
            break;
        }
    }

    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));

    for (int row = 0; row < rowcount; row++)
    {
        for (int col = 0; col < colcount; col++)
        {
            std::getline(iss, id, ',');
            std::stringstream converter(id);
            converter >> tilemap[row][col];

            if (!iss.good())
                break;
        }
    }

    return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}
