#include "Boss.h"
#include<cmath>
//
float bossNormalizeDis = 0;
Vector2 bossOldPos = { 0,0 };

void BossRun(Boss& boss, Player& player, int map[MapHeight][MapWidth]) {

	//距離を測る
	bossOldPos = Guided(player.pos, boss.pos);
	//正規化
	bossNormalizeDis = sqrt(bossOldPos.x * bossOldPos.x + bossOldPos.y * bossOldPos.y);

	boss.vel.x = bossOldPos.x / bossNormalizeDis * (boss.SpeedMax - 1);

	if (boss.pos.x > player.pos.x)
	{
		if (boss.posTmp.x <= player.pos.x)
		{
			boss.isLeft = false;
		}
	}
	else
	{
		if (boss.posTmp.x >= player.pos.x)
		{
			boss.isLeft = true;
		}
	}

	int cooltime = 0;

	boss.cooltime = cooltime;

	BossCheckMap(boss, map);
};