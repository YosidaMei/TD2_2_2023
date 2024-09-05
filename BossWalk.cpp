#include "Boss.h"

void BossWalk(Boss &boss,Player &player, int map[MapHeight][MapWidth]) {

	int cooltime = 0;

	if (player.pos.x < boss.pos.x) {
		boss.isLeft = true;
		boss.vel.x = -0.5f;
	}
	else {
		boss.isLeft = false;
		boss.vel.x = 0.5f;
	}
	BossCheckMap(boss, map);
	boss.cooltime = cooltime;
}

void BossGravity(Boss& boss) {
	//重力
	if (boss.isGround == false) {
		boss.vel.y += boss.acc.y;
	}
	else {
		boss.vel.y = 0;
	}
}

 void BossCheckMap(Boss &boss, int map[MapHeight][MapWidth]){
	 //x座標
	//仮移動
	 boss.posTmp.x = boss.pos.x + boss.vel.x;
	 boss.posTmp.y = boss.pos.y;
	 if (boss.isLeft) {
		 //画面外確認
		 if (boss.posTmp.x <= boss.Radius) {
			 boss.pos.x = boss.Radius;
		 }
		 if (boss.posTmp.x >= WinWidth - boss.Radius) {
			 boss.pos.x = WinWidth - boss.Radius;
		 }
		 //通れる
		 else if (CollisionMap(map, boss.posTmp.x, boss.posTmp.y, boss.Radius, leftTop) == none &&
			 CollisionMap(map, boss.posTmp.x, boss.posTmp.y, boss.Radius, leftBottom) == none) {
			 boss.pos.x = boss.posTmp.x;
		 }
		 //通れない
		 else {
			 boss.pos.x = (int((boss.posTmp.x - boss.Radius) / MapchipSize) + 1) * MapchipSize + boss.Radius;
		 }
	 }
	 else {
		 //画面外確認
		 if (boss.posTmp.x <= boss.Radius) {
			 boss.pos.x = boss.Radius;
		 }
		 if (boss.posTmp.x >= WinWidth - boss.Radius) {
			 boss.pos.x = WinWidth - boss.Radius;
		 }
		 //通れる
		 else if (CollisionMap(map, boss.posTmp.x, boss.posTmp.y, boss.Radius, rightTop) == none &&
			 CollisionMap(map, boss.posTmp.x, boss.posTmp.y, boss.Radius, rightBottom) == none) {
			 boss.pos.x = boss.posTmp.x;
		 }
		 //通れない
		 else {
			 boss.pos.x = int((boss.posTmp.x + boss.Radius - 1) / MapchipSize) * MapchipSize - boss.Radius;
		 }
	 }

	 //y座標
	 //仮移動
	 boss.posTmp.x = boss.pos.x;
	 boss.posTmp.y = boss.pos.y + boss.vel.y;
	 if (boss.isRise) {
		 //画面外確認
		 if (boss.posTmp.y <= boss.Radius) {
			 boss.pos.y = boss.Radius;
		 }
		 //通れる
		 else if (CollisionMap(map, boss.posTmp.x, boss.posTmp.y, boss.Radius, leftTop) == none &&
			 CollisionMap(map, boss.posTmp.x, boss.posTmp.y, boss.Radius, rightTop) == none) {
			 boss.pos.y = boss.posTmp.y;
		 }
		 //通れない
		 else {
			 boss.pos.y = (int((boss.posTmp.y - boss.Radius) / MapchipSize) + 1) * MapchipSize + boss.Radius;
			 //boss.vel.y = 0;//頭ぶつけてるので速度0
		 }
	 }
	 else {
		 //画面外確認
		 if (boss.posTmp.y >= WinHeight - boss.Radius) {
			 boss.pos.y = WinHeight - boss.Radius;
		 }
		 //通れる
		 else if (CollisionMap(map, boss.posTmp.x, boss.posTmp.y, boss.Radius, leftBottom) == none &&
			 CollisionMap(map, boss.posTmp.x, boss.posTmp.y, boss.Radius, rightBottom) == none) {
			 boss.pos.y = boss.posTmp.y;
		 }
		 //通れない
		 else {
			 boss.pos.y = int((boss.posTmp.y + boss.Radius - 1) / MapchipSize) * MapchipSize - boss.Radius;

		 }
	 }

	 //地面確認
	 if (CollisionMap(map, boss.posTmp.x, boss.posTmp.y + 1, boss.Radius, leftBottom) == none &&
		 CollisionMap(map, boss.posTmp.x, boss.posTmp.y + 1, boss.Radius, rightBottom) == none) {
		 boss.isGround = false;
	 }
	 else {
		 boss.isGround = true;
	 }
	 BossQuad(boss);

 }
 