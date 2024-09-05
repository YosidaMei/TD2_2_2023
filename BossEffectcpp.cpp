#include "Boss.h"
#define _USE_MATH_DEFINES
#include "math.h"

const int bossEffectMax = 256;
BossEffect bossEffect[bossEffectMax];

const int BossDamageEffectMax = 128;
BossEffect damegeEffect[BossDamageEffectMax];

float bossChargeStartRadius = 0;
float bossChargeRadius = 0;
float bossChargeRadiusMagnification = 0;
float bossChargeRadiusMagnificationTime = 0;
bool bossChargeIsAlive = false;

void BossDeadEffectSetting(Boss &boss) {

	int i = 0;
	for (i = 0; i < bossEffectMax; i++) {

		bossEffect[i].isAlive = true;
		bossEffect[i].pos.x = boss.pos.x;
		bossEffect[i].pos.y = boss.pos.y;

		int radian = rand() % 359;

		bossEffect[i].vel.x = cosf(radian * M_PI / 180.0f) * (rand() % 11 + 1);
		bossEffect[i].vel.y = sinf(radian * M_PI / 180.0f) * (rand() % 11 + 1);

		bossEffect[i].transparency = 0xFF;//透明度
		bossEffect[i].transparencySpeed = (rand() % 11 + 5);

	}

}

void BossDeadEffect(Boss& boss,Scene &scene) {
	
	int i = 0;
	for (i = 0; i < bossEffectMax; i++) {

		bossEffect[i].pos.x += bossEffect[i].vel.x;
		bossEffect[i].pos.y += bossEffect[i].vel.y;

		bossEffect[i].vel.x *= 1.01;
		bossEffect[i].vel.y *= 1.01;

		bossEffect[i].transparency -= bossEffect[i].transparencySpeed;
		if (bossEffect[i].transparency <= 0x00) {
			bossEffect[i].transparency = 0x00;
			bossEffect[i].isAlive = false;
		}
	}

	scene = gameclear;
	for (i = 0; i < bossEffectMax; i++) {
		if (bossEffect[i].isAlive) {
			scene = gameBoss2;
			break;
		}
	}
}

void DrawBossDeadEffect(Boss& boss, Vector2& shake, int& textureHandle) {

	int i = 0;
	int radius = 12;
	for (i = 0; i < bossEffectMax; i++) {
		if (bossEffect[i].isAlive) {
			Novice::DrawQuad(bossEffect[i].pos.x - radius + shake.x, bossEffect[i].pos.y - radius + shake.y,
				bossEffect[i].pos.x + radius + shake.x, bossEffect[i].pos.y - radius + shake.y,
				bossEffect[i].pos.x - radius + shake.x, bossEffect[i].pos.y + radius + shake.y,
				bossEffect[i].pos.x + radius + shake.x, bossEffect[i].pos.y + radius + shake.y,
				0, 0, 1, 1, textureHandle, 0x00000000 + bossEffect[i].transparency);
			//Novice::DrawBox(bossEffect[i].pos.x - radius, bossEffect[i].pos.y - radius, radius * 2, radius * 2, 0, 0x00000000 + bossEffect[i].transparency, kFillModeSolid);
		}
	}

}

void BossDamageEffectSetting(Boss& boss, float hitPos) {

	int i = 0;
	for (i = 0; i < BossDamageEffectMax; i++) {
		damegeEffect[i].isAlive = true;
		damegeEffect[i].transparency = 0x88;
		//
		if (boss.pos.x > hitPos) {
			damegeEffect[i].vel.x = rand() % 46 + 1;
		}
		else {
			damegeEffect[i].vel.x = rand() % 45 - 45;
		}
		damegeEffect[i].pos.x = boss.pos.x;
		damegeEffect[i].pos.y = boss.pos.y;
		damegeEffect[i].vel.y = rand() % 21 - 5;
		damegeEffect[i].transparencySpeed = (rand() % 7 + 3);
	}
	damegeEffect[0].posSpeed = 10;
}

void BossDamageEffect() {

	int i = 0;

	//smokeの動き
	for (i = 0; i < BossDamageEffectMax; i++) {
		if (damegeEffect[i].isAlive) {
			damegeEffect[i].pos.x += damegeEffect[i].vel.x;
			damegeEffect[i].pos.y += damegeEffect[i].vel.y;
			if (0 > damegeEffect[i].vel.x) {
				damegeEffect[i].vel.x += rand() % 6 + 1;
				if (0 <= damegeEffect[i].vel.x) {
					damegeEffect[i].vel.x = rand() % 5 - 5;
					damegeEffect[i].vel.y = rand() % 15 - 15;
				}
			}
			else {
				damegeEffect[i].vel.x += rand() % 5 - 5;
				if (0 >= damegeEffect[i].vel.x) {
					damegeEffect[i].vel.x = rand() % 6 + 1;;
					damegeEffect[i].vel.y = rand() % 15 - 15;
				}
			}
			damegeEffect[i].transparency -= damegeEffect[i].transparencySpeed;
			if (damegeEffect[i].transparency <= 0x00) {
				damegeEffect[i].transparency = 0x00;
				damegeEffect[i].isAlive = false;
			}
		}
	}
	if (damegeEffect[0].posSpeed > 0) {
		damegeEffect[0].posSpeed--;
	}
}

void  DrawBossDamageEffect(Vector2& shake, int& textureHandle) {

	int i = 0;
	int radius = 4;
	for (i = 0; i < BossDamageEffectMax; i++) {
		if (damegeEffect[i].isAlive) {
			Novice::DrawQuad(damegeEffect[i].pos.x - radius + shake.x, damegeEffect[i].pos.y - radius + shake.y,
				damegeEffect[i].pos.x + radius + shake.x, damegeEffect[i].pos.y - radius + shake.y,
				damegeEffect[i].pos.x - radius + shake.x, damegeEffect[i].pos.y + radius + shake.y,
				damegeEffect[i].pos.x + radius + shake.x, damegeEffect[i].pos.y + radius + shake.y,
				0, 0, 1, 1,textureHandle, 0x6B7FC700 + damegeEffect[i].transparency);

			//Novice::DrawBox(damegeEffect[i].pos.x - radius + shake.x, damegeEffect[i].pos.y - radius + shake.y, radius * 2, radius * 2, 0, 0x6B7FC700 + damegeEffect[i].transparency, kFillModeSolid);
		}
	}

}

void BossChargeEffectSet(Boss &boss) {

	bossChargeStartRadius = boss.Size * 2;
	bossChargeRadiusMagnification = 1.0f / boss.cooltime;
	bossChargeRadiusMagnificationTime = 0;
	bossChargeIsAlive = true;

}

void BossChargeEffect() {

	bossChargeRadius = bossChargeStartRadius * (1.0f - bossChargeRadiusMagnificationTime * bossChargeRadiusMagnificationTime);
	bossChargeRadiusMagnificationTime += bossChargeRadiusMagnification;
	if (bossChargeRadiusMagnificationTime >= 1.0f) {
		bossChargeIsAlive = false;
	}

}
void BossChargeEffectDelete() {
	bossChargeIsAlive = false;
}

void DrawBossCharge(Boss& boss, int isPattern, Vector2& shake) {

	if (bossChargeIsAlive) {

		if (isPattern != 7) {
			Novice::DrawEllipse(boss.pos.x + shake.x, boss.pos.y + shake.y, bossChargeRadius, bossChargeRadius, 0, 0xFFFFFFFF, kFillModeWireFrame);
			Novice::DrawEllipse(boss.pos.x + shake.x, boss.pos.y + shake.y, bossChargeRadius * 1.2f, bossChargeRadius * 1.2f, 0, 0xFFFFFFFF, kFillModeWireFrame);
			Novice::DrawEllipse(boss.pos.x + shake.x, boss.pos.y + shake.y, bossChargeRadius * 1.4f, bossChargeRadius * 1.4f, 0, 0xFFFFFFFF, kFillModeWireFrame);
		}
		else {
			Novice::DrawEllipse(boss.pos.x + shake.x, boss.pos.y + shake.y, bossChargeRadius, bossChargeRadius, 0, 0x00B7C8FF, kFillModeWireFrame);
			Novice::DrawEllipse(boss.pos.x + shake.x, boss.pos.y + shake.y, bossChargeRadius * 1.2f, bossChargeRadius * 1.2f, 0, 0x00B7C8FF, kFillModeWireFrame);
			Novice::DrawEllipse(boss.pos.x + shake.x, boss.pos.y + shake.y, bossChargeRadius * 1.4f, bossChargeRadius * 1.4f, 0, 0x00B7C8FF, kFillModeWireFrame);
			Novice::DrawEllipse(boss.pos.x + shake.x, boss.pos.y + shake.y, 200, 200, 0, 0x00B7C844, kFillModeSolid);
		}

	}

}
