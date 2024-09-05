#define _USE_MATH_DEFINES
#include <math.h>
#include"Bullet.h"
#include "Map.h"
#include "CollsionEffect.h"

const int Max = 5;

void EveryDirection(Bullet* bullet, Enemy& enemy, Player& player, char Key[256]) {

	//発生
	if (bullet[0].isAlive == false && bullet[1].isAlive == false &&
		bullet[2].isAlive == false && bullet[3].isAlive == false &&
		bullet[4].isAlive == false) {
		for (int i = 0; i < 5; i++) {
			bullet[i].posTmp.x = enemy.pos.x - enemy.Radius / 2;
			bullet[i].posTmp.y = enemy.pos.y + enemy.Radius * 3 / 4;
			bullet[i].vel.x = bullet[i].SpeedMax;
			bullet[i].vel.y = bullet[i].SpeedMax;
			bullet[i].acc = { 0 };
			bullet[i].isAlive = true;
			bullet[i].pos.x = bullet[i].posTmp.x;
			bullet[i].pos.y = bullet[i].posTmp.y;
			bullet[i].isReflection = false;
			bullet[i].isHit = false;
			bullet[i].isBossHit = false;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (bullet[i].isAlive) {
			if (!bullet[i].isReflection) {

				bullet[i].acc.x += 0.1f;
				bullet[i].acc.y += 0.1f;

				bullet[i].pos.x -= cosf(M_PI / 12.0f * i) * (bullet[i].vel.x + bullet[i].acc.x);
				bullet[i].pos.y -= sinf(M_PI / 12.0f * i) * (bullet[i].vel.y + bullet[i].acc.y);

				bullet[i].quad.leftTop.x = bullet[i].pos.x + (-bullet[i].radius.x) * cosf(M_PI / 12.0f * i) - (-bullet[i].radius.y) * sinf(M_PI / 12.0f * i);
				bullet[i].quad.leftTop.y = bullet[i].pos.y + (-bullet[i].radius.x) * sinf(M_PI / 12.0f * i) + (-bullet[i].radius.y) * cosf(M_PI / 12.0f * i);
				bullet[i].quad.rightTop.x = bullet[i].pos.x + (bullet[i].radius.x) * cosf(M_PI / 12.0f * i) - (-bullet[i].radius.y) * sinf(M_PI / 12.0f * i);
				bullet[i].quad.rightTop.y = bullet[i].pos.y + (bullet[i].radius.x) * sinf(M_PI / 12.0f * i) + (-bullet[i].radius.y) * cosf(M_PI / 12.0f * i);
				bullet[i].quad.leftBottom.x = bullet[i].pos.x + (-bullet[i].radius.x) * cosf(M_PI / 12.0f * i) - (bullet[i].radius.y) * sinf(M_PI / 12.0f * i);
				bullet[i].quad.leftBottom.y = bullet[i].pos.y + (-bullet[i].radius.x) * sinf(M_PI / 12.0f * i) + (bullet[i].radius.y) * cosf(M_PI / 12.0f * i);
				bullet[i].quad.rightBottom.x = bullet[i].pos.x + (bullet[i].radius.x) * cosf(M_PI / 12.0f * i) - (bullet[i].radius.y) * sinf(M_PI / 12.0f * i);
				bullet[i].quad.rightBottom.y = bullet[i].pos.y + (bullet[i].radius.x) * sinf(M_PI / 12.0f * i) + (bullet[i].radius.y) * cosf(M_PI / 12.0f * i);
					
				//if (cosf(M_PI / 12.0f * i) == 0 || sinf(M_PI / 12.0f * i) == 0) {
				if(M_PI / 12.0f * i == 0 || M_PI / 12.0f * i == M_PI || M_PI / 12.0f * i == M_PI * 2){
					if (CollisionObjRect(bullet[i].quad, player.quad)) {
						bullet[i].isHit = true;
					}
					if (CollisionObjRect(player.attack.quad, bullet[i].quad) && bullet[i].isReflection == false && bullet[i].pos.x > player.pos.x) {
						bullet[i].isReflection = true;
						RepelTheSwordEffectSetting(player);
					}
				}
				else {
					if (CollisionObj(bullet[i].quad, player.quad)) {
						bullet[i].isHit = true;
					}
					if (CollisionObj(player.attack.quad, bullet[i].quad) && bullet[i].isReflection == false && bullet[i].pos.x > player.pos.x) {
						bullet[i].isReflection = true;
						RepelTheSwordEffectSetting(player);
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
			}
			else if (bullet[i].isReflection) {

				bullet[i].pos.x -= cosf(M_PI / 12.0f * i + M_PI) * bullet[i].SpeedMax * bullet[i].SpeedMax;
				bullet[i].pos.y -= sinf(M_PI / 12.0f * i + M_PI) * bullet[i].SpeedMax * bullet[i].SpeedMax;

				bullet[i].quad.leftTop.x = bullet[i].pos.x + (-bullet[i].radius.x) * cosf(M_PI / 12.0f * i + M_PI) - (-bullet[i].radius.y) * sinf(M_PI / 12.0f * i + M_PI);
				bullet[i].quad.leftTop.y = bullet[i].pos.y + (-bullet[i].radius.x) * sinf(M_PI / 12.0f * i + M_PI) + (-bullet[i].radius.y) * cosf(M_PI / 12.0f * i + M_PI);
				bullet[i].quad.rightTop.x = bullet[i].pos.x + (bullet[i].radius.x) * cosf(M_PI / 12.0f * i + M_PI) - (-bullet[i].radius.y) * sinf(M_PI / 12.0f * i + M_PI);
				bullet[i].quad.rightTop.y = bullet[i].pos.y + (bullet[i].radius.x) * sinf(M_PI / 12.0f * i + M_PI) + (-bullet[i].radius.y) * cosf(M_PI / 12.0f * i + M_PI);
				bullet[i].quad.leftBottom.x = bullet[i].pos.x + (-bullet[i].radius.x) * cosf(M_PI / 12.0f * i + M_PI) - (bullet[i].radius.y) * sinf(M_PI / 12.0f * i + M_PI);
				bullet[i].quad.leftBottom.y = bullet[i].pos.y + (-bullet[i].radius.x) * sinf(M_PI / 12.0f * i + M_PI) + (bullet[i].radius.y) * cosf(M_PI / 12.0f * i + M_PI);
				bullet[i].quad.rightBottom.x = bullet[i].pos.x + (bullet[i].radius.x) * cosf(M_PI / 12.0f * i + M_PI) - (bullet[i].radius.y) * sinf(M_PI / 12.0f * i + M_PI);
				bullet[i].quad.rightBottom.y = bullet[i].pos.y + (bullet[i].radius.x) * sinf(M_PI / 12.0f * i + M_PI) + (bullet[i].radius.y) * cosf(M_PI / 12.0f * i + M_PI);

				//if (cosf(M_PI / 12.0f * i + M_PI) == 0 || sinf(M_PI / 12.0f * i + M_PI) == 0) {
				if (M_PI / 12.0f * i == 0 || M_PI / 12.0f * i == M_PI || M_PI / 12.0f * i == M_PI * 2) {

					if (CollisionObjRect(bullet[i].quad, enemy.quad)) {
						bullet[i].isBossHit = true;
					}
				}
				else {
					if (CollisionObj(bullet[i].quad, enemy.quad)) {
						bullet[i].isBossHit = true;
					}
				}
				if (bullet[i].isBossHit) {
					EnemyDamageEffectSetting(enemy, bullet[i].pos.y);
					bullet[i].isAlive = false;
					bullet[i].pos.x = -1000;
					bullet[i].pos.y = -1000;
					enemy.Hp -= 1;
				}
			}
			if ((bullet[i].quad.leftTop.x < 0 && bullet[i].quad.rightTop.x < 0 && bullet[i].quad.leftBottom.x < 0 && bullet[i].quad.rightBottom.x < 0) ||
				(bullet[i].quad.leftTop.x > WinWidth && bullet[i].quad.rightTop.x > WinWidth && bullet[i].quad.leftBottom.x > WinWidth && bullet[i].quad.rightBottom.x > WinWidth) ||
				(bullet[i].quad.leftTop.y < 0 && bullet[i].quad.rightTop.y < 0 && bullet[i].quad.leftBottom.y < 0 && bullet[i].quad.rightBottom.y < 0) ||
				(bullet[i].quad.leftTop.y > WinHeight && bullet[i].quad.rightTop.y > WinHeight && bullet[i].quad.leftBottom.y > WinHeight && bullet[i].quad.rightBottom.y > WinHeight)) {
				bullet[i].isAlive = false;
				bullet[i].isHit = false;
				bullet[i].pos.x = -1000;
				bullet[i].pos.y = -1000;
			}
		}
	}
	/*
		if (Key[DIK_P]) {
			for (int i = 0; i < 5; i++) {
				if (CollisionObj(player.attack.quad, bullet[i].quad) && bullet[i].isReflection == false) {
					bullet[i].isReflection = true;
				}
			}
		}
		else {
			for (int i = 0; i < 5; i++)
			{
				bullet[i].isReflection = false;
			}
		}
		*/
}

void EveryDirectionReset(Bullet bullet[]) {
	for (int i = 0; i < Max; i++) {
		bullet[i].isAlive = false;
		bullet[i].isReflection = false;
		bullet[i].isHit = false;
		bullet[i].isBossHit = false;
		bullet[i].pos.x = -1000;
		bullet[i].pos.y = -1000;
	}
}

void DrawEveryDirection(Bullet* bullet, Vector2& shake) {

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

void MapCollisionEveryDirection(int map[MapHeight][MapWidth], Bullet* bullet) {

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