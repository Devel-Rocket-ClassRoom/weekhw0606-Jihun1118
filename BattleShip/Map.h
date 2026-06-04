#pragma once
#include "Ship.h"
class Map
{

private:

public:
	const int Tile_Width = 10;
	const int Tile_Height = 10;

	int* Tiles = nullptr;
	int* PlayerTiles = nullptr;

	Map();
	~Map();

	void PlaceShip();
	void printMap();
	void printPlayerMap();
	bool IsAllShipDestroyed();
	void Attack();

 
	enum TileType
	{
		UnknownTile = 0,
		EmptyTile,
		ShipTile,
		HitTile,
		MissTile
	};

private:

};