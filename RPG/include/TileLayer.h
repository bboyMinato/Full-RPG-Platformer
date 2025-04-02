#pragma once
#include "Layer.h"
#include "TextureManager.h"
#include <string>
#include <vector>

struct TileSet
{
	std::string name, source;
	int firstGID;
	int tileCount;
	int colCount; 
	int lastID;
	int tileSize;
};

using TileSetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer : public Layer
{
public:
	TileLayer(TileSetList tilesets, TileMap tilemap, std::string layerName, int tilesize, int rowcount, int colcount);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTileMap() { return _tileMap; }
	std::string GetName() const { return name; }

private:	
	std::string name; 
	int _tileSize;
	int _rowCount;
	int _colCount;

	TileMap _tileMap;
	TileSetList _tileSets;

	void LoadTilesetTextures();
};