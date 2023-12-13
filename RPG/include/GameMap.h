#pragma once
#include <vector>
#include <iostream>
#include "Layer.h"

class GameMap
{
public:
	void Render()
	{
		for (size_t i = 0; i < _mapLayers.size(); i++)
		{
			_mapLayers[i]->Render();
		}
	}

	void Update()
	{
		for (size_t i = 0; i < _mapLayers.size(); i++)
		{
			_mapLayers[i]->Update();
		}
	}

	std::vector<Layer*> GetMapLayers() 
	{ 		
		return _mapLayers; 
	}

private:
	friend class MapParser;
	std::vector<Layer*> _mapLayers;
};

