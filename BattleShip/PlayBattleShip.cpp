#include "PlayBattleShip.h"
#include "Map.h"
#include <iostream>
void PlayBattleShip()
{
	Map map;
	map.PlaceShip();
	map.printPlayerMap();
	map.Attack();
}
