#include "..\include\TileLayer.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TileSetList tilesets)
{
	_tileSize = tilesize;
	_rowCount = rowcount;
	_colCount = colcount;
	_tileMap = tilemap;
	_tileSets = tilesets;

	for (size_t i = 0; i < _tileSets.size(); i++)
		TextureManager::GetInstance()->LoadTexture(_tileSets[i].name, ".\\assets\\map\\" + _tileSets[i].source);
}

void TileLayer::Render()
{
	for (int i = 0; i < _rowCount; i++)
	{
		for (int j = 0; j < _colCount; j++)
		{
			int tileID = _tileMap[i][j];

			if (tileID == 0)
				continue;

			else
			{
				int index = 0;

				if (_tileSets.size() >= 1)
				{
					for (int k = 0; k < _tileSets.size(); k++)
					{
						if (tileID >= _tileSets[k].firstID && tileID <= _tileSets[k].lastID)
						{
							tileID = tileID + _tileSets[k].tileCount - _tileSets[k].lastID;
							index = k;
							break;
						}
					}
				}

				TileSet ts = _tileSets[index];
				int tileRow = tileID / ts.colCount;
				int tileCol = tileID - tileRow * ts.colCount - 1;

				//if this tile is one in the last column
				if (tileID % ts.colCount == 0)
				{
					tileRow--;
					tileCol = ts.colCount - 1;
				}

				TextureManager::GetInstance()->DrawTile(ts.name, ts.tileSize, j * ts.tileSize, i * ts.tileSize, tileRow, tileCol);
			}
		}
	}
}

void TileLayer::Update()
{
}
