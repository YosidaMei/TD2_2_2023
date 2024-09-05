#include "Boss.h"

//初期位置に戻る
void BossResetMoveRight(Boss& boss, int map[MapHeight][MapWidth]) {
	boss.isLeft = true;
	boss.vel.x += 2.0f;
	if (boss.pos.x >= WinWidth - boss.Radius) {
		boss.pos.x = WinWidth - boss.Radius;
		boss.vel.x = 0;
	}
	BossCheckMap(boss, map);
	BossGravity(boss);
}

void BossResetMoveLeft(Boss& boss, int map[MapHeight][MapWidth]) {
	boss.isLeft = false;
	boss.vel.x -= 2.0f;
	if (boss.pos.x <= boss.Radius) {
		boss.pos.x = boss.Radius;
		boss.vel.x = 0;
	}
	BossCheckMap(boss, map);
	BossGravity(boss);
}