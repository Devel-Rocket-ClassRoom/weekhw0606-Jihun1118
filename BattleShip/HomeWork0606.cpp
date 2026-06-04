#include <iostream>
#include "Map.h"
#include "time.h"
#include "PlayBattleShip.h"
int main()
{
	unsigned int Seed = (unsigned int)time(0);
	//Seed = 0;		// 테스트용으로 임시로 설정
	srand(Seed);	// 시드값 초기화
	PlayBattleShip();
}
