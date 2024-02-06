#include "..\include\TileLayer.h"

TileLayer::TileLayer(TileSetList tilesets, TileMap tilemap, int tilesize, int rowcount, int colcount)
	: _tileSize(tilesize), _rowCount(rowcount), _colCount(colcount), _tileMap(tilemap), _tileSets(tilesets)
{
	LoadTilesetTextures();
}

void TileLayer::Render()
{
    for (size_t i = 0; i < _rowCount; i++) 
    {
        for (size_t j = 0; j < _colCount; j++) 
        {
            int tileID = _tileMap[i][j];

            if (tileID == 0)
                continue;

            else 
            {
                for (size_t k = 0; k < _tileSets.size(); k++) 
                {
                    const TileSet& ts = _tileSets[k];

                    if (tileID >= ts.firstGID && tileID <= ts.lastID) 
                    {
                        int adjustedID = tileID - ts.firstGID;
                        int tileRow = adjustedID / ts.colCount;
                        int tileCol = adjustedID % ts.colCount;

                        TextureManager::GetInstance()->DrawTile(ts.name, ts.tileSize, j * ts.tileSize, i * ts.tileSize, tileRow, tileCol);
                        break;
                    }
                }
            }
        }
    }
}

void TileLayer::Update()
{
}

void TileLayer::LoadTilesetTextures()
{
	for (const auto& tileset : _tileSets) 
    {
		TextureManager::GetInstance()->LoadTexture(tileset.name, ".\\assets\\map\\" + tileset.source);
	}
}
