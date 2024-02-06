#pragma once
#include <map>
#include <string>
#include "TileLayer.h"
#include "tinyxml.h"

class GameMap;

class MapParser
{
public:
	static MapParser* GetInstance();

	bool Load();
	void Clean();

	inline GameMap* GetMap(std::string id)
	{
		return _maps[id];
	}

private:
	MapParser() {}

	bool Parse(std::string id, std::string source);
	TileSet ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tilesets, int tilesize, int rowcount, int colcount);

	static MapParser* _instance;
	std::map<std::string, GameMap*> _maps;
};