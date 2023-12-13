#pragma once
#include "Layer.h"
#include "TextureManager.h"
#include <string>
#include <vector>

struct TileSet
{
	int firstID, lastID;
	int rowCount, colCount;
	int tileCount, tileSize;
	std::string name, source;
};

using TileSetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer : public Layer
{
public:
	TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TileSetList tilesets);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTileMap() { return _tileMap; }
	

	int _tileSize = 0;
	int _rowCount = 0;
	int _colCount = 0;
private:	
	TileMap _tileMap;
	TileSetList _tileSets;
};

