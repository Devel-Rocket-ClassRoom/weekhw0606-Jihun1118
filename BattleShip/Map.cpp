#include "Map.h"
#include <iostream>

Map::Map()
{
	Tiles = new int[Tile_Width * Tile_Height];
	PlayerTiles = new int[Tile_Width * Tile_Height];

	for (int i = 0; i < Tile_Width * Tile_Height; i++)
	{
		Tiles[i] = EmptyTile;
		PlayerTiles[i] = UnknownTile;
	}
}
Map::~Map()
{
	delete[] Tiles;
	delete[] PlayerTiles;
	Tiles = nullptr;
	PlayerTiles = nullptr;
}

void Map::printMap()
{
	printf("   0  1  2  3  4  5  6  7  8  9\n");
	for (int y = 0; y < Tile_Height; y++)
	{
		printf("%d  ", y);
		for (int x = 0; x < Tile_Width; x++)
		{ 
			int Index = y * Tile_Width + x;
			if (Tiles[Index] == EmptyTile)
			{
			printf(".  ");
			}
			else if (Tiles[Index] == ShipTile)
			{
				printf("S  ");
			}
			else if (Tiles[Index] == HitTile)
			{
				printf("O  ");
			}
		}
		printf("\n");
	}
	
}

void Map::PlaceShip()
{
	Ship::ShipSize Ships[4] =
	{
		Ship::Carrier,
		Ship::Battleship,
		Ship::Cruiser,
		Ship::Destroyer
	};


	for (int ShipLength : Ships)
	{ 
		while (true)
		{
		int StartX = rand() % Tile_Width;		// 배 시작 X좌표
		int StartY = rand() % Tile_Height;		// 배 시작 Y좌표
		bool IsHorizontal = rand() % 2 == 0;
		bool CanPlace = true;

		for (int i = 0; i < ShipLength; i++)
		{
			int X = StartX;
			int Y = StartY;

			if (IsHorizontal)
			{
				X = StartX + i;
			}
			else
			{
				Y = StartY + i;
			}

			if (X < 0 || X >= Tile_Width || Y < 0 || Y >= Tile_Height)
			{
				CanPlace = false;
				break;
			}
			int Index = Y * Tile_Width + X;
			if (Tiles[Index] != EmptyTile)
			{
				CanPlace = false;
				break;
			}
		}
		if (CanPlace == false)
		{
			continue;
		}

		for (int i = 0; i < ShipLength; i++)
		{
			int X = StartX;
			int Y = StartY;

			if (IsHorizontal)
			{
				X = StartX + i;
			}
			else
			{
				Y = StartY + i;
			}
			int Index = Y * Tile_Width + X;
			Tiles[Index] = ShipTile;
			}
		break;
		}
	}
	
}

bool Map::IsAllShipDestroyed()
{
	for (int i = 0; i < Tile_Width * Tile_Height; i++)
	{
		if (Tiles[i] == ShipTile)
		{
			return false;
		}
	}
	printf("모든 함선을 파괴하였습니다!");
	return true;
}

void Map::printPlayerMap()
{
	printf("   0  1  2  3  4  5  6  7  8  9\n");
	for (int y = 0; y < Tile_Height; y++)
	{
		printf("%d  ", y);
		for (int x = 0; x < Tile_Width; x++)
		{
			int Index = y * Tile_Width + x;
			if (PlayerTiles[Index] == UnknownTile)
			{
				printf(".  ");
			}
			else if (PlayerTiles[Index] == MissTile)
			{
				printf("X  ");
			}
			else if (PlayerTiles[Index] == HitTile)
			{
				printf("O  ");
			}
		}
		printf("\n");
	}
}


void Map::Attack()
{
	int AttackCount = 0;

	while (AttackCount < 30 && !IsAllShipDestroyed())
	{
		int X;
		int Y;

		printf("\n공격할 좌표를 입력하세요. (X , Y) : ");
		std::cin >> X >> Y;

		int Index = Y * Tile_Width + X;
		if (X < 0 || X >= 10 || Y < 0 || Y >= 10)
		{
			printf("잘못된 좌표입니다.\n");
			continue;
		}
		
		if (PlayerTiles[Index] == MissTile || PlayerTiles[Index] == HitTile)
		{
			printf("이미 공격한 좌표입니다.\n");
			continue;
		}

		AttackCount++;
		if (Tiles[Index] == EmptyTile)
		{
			printf("공격에 실패하였습니다.\n");
			PlayerTiles[Index] = MissTile;
		}

		if (Tiles[Index] == ShipTile)
		{
			printf("공격에 성공하였습니다\n");
			PlayerTiles[Index] = HitTile;
		}
		printf("\n남은 공격 횟수 : %d\n", 30 - AttackCount);
		printPlayerMap();
	}

	printf("\n===== 게임 종료 =====\n");

	if (IsAllShipDestroyed())
	{
		printf("승리! 모든 함선을 격침했습니다.\n");
	}
	else
	{
		printf("패배! 공격 횟수를 모두 사용했습니다.\n");
	}

	printf("\n===== 플레이어 맵 =====\n");
	printPlayerMap();

	printf("\n===== 실제 맵 =====\n");
	printMap();
}
