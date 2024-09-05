#define _USE_MATH_DEFINES
#include <math.h>
#include"Bullet.h"
#include "Map.h"
#include"Boss.h"
#include "CollsionEffect.h"

bool isLeft = true;

int randomCount = 0;

int actionUp = 0;

void BossEveryDirectionSet(Bullet* bullet, Boss& enemy, Player& player) {
	
	isLeft = enemy.isLeft;
	actionUp = 0;
	actionUp = rand() % 3;

	if (actionUp == 0) {
		for (int i = 0; i < 5; i++) {
			bullet[i].isAlive = true;
			if (isLeft) {
				bullet[i].posTmp.x = enemy.pos.x - enemy.Radius;
			}
			else {
				bullet[i].posTmp.x = enemy.pos.x + enemy.Radius;
			}
			bullet[i].posTmp.y = enemy.pos.y - enemy.Radius;
			bullet[i].pos.x = bullet[i].posTmp.x;
			bullet[i].pos.y = bullet[i].posTmp.y;
			bullet[i].vel.x = bullet[i].SpeedMax;
			bullet[i].vel.y = bullet[i].SpeedMax;
			bullet[i].acc = { 0 };
			bullet[i].isReflection = false;
		}
	}
	if (actionUp == 1) {
		randomCount = 0;
		for (int i = 0; i < 5; i++) {
			bullet[i].isAlive = true;
			if (isLeft) {
				bullet[i].posTmp.x = enemy.pos.x - enemy.Radius;
			}
			else {
				bullet[i].posTmp.x = enemy.pos.x + enemy.Radius;
			}
			bullet[i].posTmp.y = enemy.pos.y - enemy.Radius;
			bullet[i].pos.x = bullet[i].posTmp.x;
			bullet[i].pos.y = bullet[i].posTmp.y;
			bullet[i].vel.x = bullet[i].SpeedMax + randomCount;
			bullet[i].vel.y = bullet[i].SpeedMax + randomCount;
			bullet[i].acc = { 0 };
			bullet[i].isReflection = false;
			randomCount += 1;
		}
	}
	if (actionUp == 2) {
		randomCount = 5;
		for (int i = 0; i < 5; i++) {
			bullet[i].isAlive = true;
			if (isLeft) {
				bullet[i].posTmp.x = enemy.pos.x - enemy.Radius;
			}
			else {
				bullet[i].posTmp.x = enemy.pos.x + enemy.Radius;
			}
			bullet[i].posTmp.y = enemy.pos.y - enemy.Radius;
			bullet[i].pos.x = bullet[i].posTmp.x;
			bullet[i].pos.y = bullet[i].posTmp.y;
			bullet[i].quad.leftTop.x = 0;
			bullet[i].quad.leftTop.y = 0;
			bullet[i].quad.rightTop.x = 0;
			bullet[i].quad.rightTop.y = 0;
			bullet[i].quad.leftBottom.x = 0;
			bullet[i].quad.leftBottom.y = 0;
			bullet[i].quad.rightBottom.x = 0;
			bullet[i].quad.rightBottom.y = 0;

			bullet[i].vel.x = bullet[i].SpeedMax + randomCount;
			bullet[i].vel.y = bullet[i].SpeedMax + randomCount;
			bullet[i].acc = { 0 };
			bullet[i].isReflection = false;
			randomCount -= 1;
		}
	}

}

void BossEveryDirection(Bullet* bullet, Boss& enemy, Player& player, char Key[256]) {

	const int Max = 5;
	float reflection = 0;
	float rightThetaPuls = 0;
	float reflectionspeed = 0;

	for (int i = 0; i < 5; i++) {
		if (bullet[i].isAlive == false) {
			bullet[i].posTmp.x = enemy.pos.x - enemy.Radius - bullet[i].radius.x;
			bullet[i].posTmp.y = enemy.pos.y;
		}
		else {
			if (bullet[i].isReflection) {
				reflection = M_PI;
				reflectionspeed = bullet[i].SpeedMax;
			}
			else {
				reflection = 0;
				reflectionspeed = 1;
			}
			if (isLeft) {
				rightThetaPuls = 0;
			}
			else {
				rightThetaPuls = M_PI / 12.0f * 8;
			}
			if (bullet[i].acc.x < 1) {
				bullet[i].acc.x += 0.1f;
				bullet[i].acc.y += 0.1f;
			}
			else
			{
				bullet[i].acc.x += 0.15f;
				bullet[i].acc.y += 0.15f;
			}
			bullet[i].pos.x -= cosf(M_PI / 12.0f * i + reflection + rightThetaPuls) * (bullet[i].vel.x + bullet[i].acc.x) * reflectionspeed;
			bullet[i].pos.y -= sinf(M_PI / 12.0f * i + reflection + rightThetaPuls) * (bullet[i].vel.y + bullet[i].acc.y) * reflectionspeed;

		}
		bullet[i].quad.leftTop.x = bullet[i].pos.x + (-bullet[i].radius.x) * cosf(M_PI / 12.0f * i + reflection + rightThetaPuls) - (-bullet[i].radius.y) * sinf(M_PI / 12.0f * i + reflection + rightThetaPuls);
		bullet[i].quad.leftTop.y = bullet[i].pos.y + (-bullet[i].radius.x) * sinf(M_PI / 12.0f * i + reflection + rightThetaPuls) + (-bullet[i].radius.y) * cosf(M_PI / 12.0f * i + reflection + rightThetaPuls);
		bullet[i].quad.rightTop.x = bullet[i].pos.x + (bullet[i].radius.x) * cosf(M_PI / 12.0f * i + reflection + rightThetaPuls) - (-bullet[i].radius.y) * sinf(M_PI / 12.0f * i + reflection + rightThetaPuls);
		bullet[i].quad.rightTop.y = bullet[i].pos.y + (bullet[i].radius.x) * sinf(M_PI / 12.0f * i + reflection + rightThetaPuls) + (-bullet[i].radius.y) * cosf(M_PI / 12.0f * i + reflection + rightThetaPuls);
		bullet[i].quad.leftBottom.x = bullet[i].pos.x + (-bullet[i].radius.x) * cosf(M_PI / 12.0f * i + reflection + rightThetaPuls) - (bullet[i].radius.y) * sinf(M_PI / 12.0f * i + reflection + rightThetaPuls);
		bullet[i].quad.leftBottom.y = bullet[i].pos.y + (-bullet[i].radius.x) * sinf(M_PI / 12.0f * i + reflection + rightThetaPuls) + (bullet[i].radius.y) * cosf(M_PI / 12.0f * i + reflection + rightThetaPuls);
		bullet[i].quad.rightBottom.x = bullet[i].pos.x + (bullet[i].radius.x) * cosf(M_PI / 12.0f * i + reflection + rightThetaPuls) - (bullet[i].radius.y) * sinf(M_PI / 12.0f * i + reflection + rightThetaPuls);
		bullet[i].quad.rightBottom.y = bullet[i].pos.y + (bullet[i].radius.x) * sinf(M_PI / 12.0f * i + reflection + rightThetaPuls) + (bullet[i].radius.y) * cosf(M_PI / 12.0f * i + reflection + rightThetaPuls);
		
		//if (cosf(M_PI / 12.0f * i + reflection + rightThetaPuls) == 0 || sinf(M_PI / 12.0f * i + reflection + rightThetaPuls) == 0) {
		if (M_PI / 12.0f * i + reflection + rightThetaPuls == 0 ||
			M_PI / 12.0f * i + reflection + rightThetaPuls == M_PI ||
			M_PI / 12.0f * i + reflection + rightThetaPuls == M_PI * 2) {
			if (CollisionObjRect(bullet[i].quad, player.quad) && bullet[i].isReflection == false) {
				bullet[i].isHit = true;
			}
			if (CollisionObjRect(player.attack.quad, bullet[i].quad) && bullet[i].isReflection == false &&
				((isLeft && player.pos.x < bullet[i].pos.x) || (!isLeft && player.pos.x > bullet[i].pos.x))) {
				bullet[i].isReflection = true;
				RepelTheSwordEffectSetting(player);
			}
			if (CollisionObjRect(bullet[i].quad, enemy.quad) && bullet[i].isReflection) {
				BossDamageEffectSetting(enemy, bullet[i].pos.x);
				bullet[i].isAlive = false;
				bullet[i].pos.x = -1000;
				bullet[i].pos.y = -1000;
				enemy.Hp -= 5;
			}
		}
		else {
			if (CollisionObj(bullet[i].quad, player.quad)) {
				bullet[i].isHit = true;
			}
			if (CollisionObj(player.attack.quad, bullet[i].quad) && bullet[i].isReflection == false &&
				((isLeft && player.pos.x < bullet[i].pos.x) || (!isLeft && player.pos.x > bullet[i].pos.x))) {
				bullet[i].isReflection = true;
				RepelTheSwordEffectSetting(player);
			}
			if (CollisionObj(bullet[i].quad, enemy.quad) && bullet[i].isReflection) {
				BossDamageEffectSetting(enemy, bullet[i].pos.x);
				bullet[i].isAlive = false;
				bullet[i].pos.x = -1000;
				bullet[i].pos.y = -1000;
				enemy.Hp -= 5;
			}
		}
		if (bullet[i].isHit) {
			bullet[i].isAlive = false;
			bullet[i].isHit = false;
			player.Hp -= 1;
			PlayerDamageEffectSetting(player, bullet[i].pos.x);
			bullet[i].pos.x = -1000;
			bullet[i].pos.y = -1000;
		}
		else if ((bullet[i].quad.leftTop.x < 0 && bullet[i].quad.rightTop.x < 0 && bullet[i].quad.leftBottom.x < 0 && bullet[i].quad.rightBottom.x < 0) ||
			(bullet[i].quad.leftTop.x > WinWidth && bullet[i].quad.rightTop.x > WinWidth && bullet[i].quad.leftBottom.x > WinWidth && bullet[i].quad.rightBottom.x > WinWidth) ||
			(bullet[i].quad.leftTop.y < 0 && bullet[i].quad.rightTop.y < 0 && bullet[i].quad.leftBottom.y < 0 && bullet[i].quad.rightBottom.y < 0) ||
			(bullet[i].quad.leftTop.y > WinHeight && bullet[i].quad.rightTop.y > WinHeight && bullet[i].quad.leftBottom.y > WinHeight && bullet[i].quad.rightBottom.y > WinHeight)) {
			bullet[i].isAlive = false;
			bullet[i].isHit = false;
			bullet[i].pos.x = -1000;
			bullet[i].pos.y = -1000;
		}
	}
	//発生
	if (bullet[0].isAlive == false && bullet[1].isAlive == false &&
		bullet[2].isAlive == false && bullet[3].isAlive == false &&
		bullet[4].isAlive == false) {
		if (player.pos.x <= enemy.pos.x) {
			isLeft = true;
		}
		else {
			isLeft = false;
		}
		for (int i = 0; i < 5; i++) {
			//bullet[i].isAlive = true;
			if (isLeft) {
				bullet[i].posTmp.x = enemy.pos.x + enemy.Radius;
			}
			else {
				bullet[i].posTmp.x = enemy.pos.x - enemy.Radius;
			}
			bullet[i].posTmp.y = enemy.pos.y - enemy.Radius;
			bullet[i].pos.x = bullet[i].posTmp.x;
			bullet[i].pos.y = bullet[i].posTmp.y;
			bullet[i].vel.x = bullet[i].SpeedMax;
			bullet[i].vel.y = bullet[i].SpeedMax;
			bullet[i].acc = { 0 };
			bullet[i].isReflection = false;
		}
		enemy.isActionEnd = true;
	}

	if (enemy.isActionEnd) {
		for (int i = 0; i < 5; i++) {
			bullet[i].isAlive = false;
		}
	}

}

void DrawBossEveryDirection(Bullet* bullet, Vector2& shake) {

	for (int i = 0; i < 5; i++) {
		if (bullet[i].isAlive) {
			Novice::DrawQuad(bullet[i].quad.leftTop.x + shake.x, bullet[i].quad.leftTop.y + shake.y,
				bullet[i].quad.rightTop.x + shake.x, bullet[i].quad.rightTop.y + shake.y,
				bullet[i].quad.leftBottom.x + shake.x, bullet[i].quad.leftBottom.y + shake.y,
				bullet[i].quad.rightBottom.x + shake.x, bullet[i].quad.rightBottom.y + shake.y,
				0, 0, bullet[i].size.x, bullet[i].size.y, bullet[i].textureHandle, 0xFFFFFFFF);
		}
	}

}

void MapCollisionBossEveryDirection(int map[MapHeight][MapWidth], Bullet* bullet) {

	for (int i = 0; i < 5; i++) {

		if (CollisionMap(map, bullet[i].quad.leftTop.x, bullet[i].quad.leftTop.y, 0, leftTop) == block ||
			CollisionMap(map, bullet[i].quad.rightTop.x, bullet[i].quad.rightTop.y, 0, rightTop) == block ||
			CollisionMap(map, bullet[i].quad.leftBottom.x, bullet[i].quad.leftBottom.y, 0, leftBottom) == block ||
			CollisionMap(map, bullet[i].quad.rightBottom.x, bullet[i].quad.rightBottom.y, 0, rightBottom) == block) {
			bullet[i].isAlive = false;
			bullet[i].pos.x = -1000;
			bullet[i].pos.y = -1000;
		};

	}

}