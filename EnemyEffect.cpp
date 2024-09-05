#include "Common.h"
#include "Enemy.h"
#define _USE_MATH_DEFINES
#include "math.h"

Vector2 emitter;

const int EnemyEffectMax = 256;
EnemySmoke enemySmoke[EnemyEffectMax];

const int EnemyDamageEffectMax = 128;
EnemySmoke enemyDamageEffect[EnemyEffectMax];

const int EnemyChangeEffectMax = 256;
EnemySmoke enemyChangeEffect[EnemyEffectMax];
bool enemyChangeEffectStop[EnemyChangeEffectMax];
bool enemyChangeEffectRestart = false;

int enemyChangeEffectSize = 0;
const int enemyChangeEffectSizeMax = 160;//カウントの都合で2倍されている

void EnemyEffect(Enemy& enemy) {

	int i = 0;
	int count = 0;
	int countMax = 64;

	for (i = 0; i < EnemyEffectMax; i++) {
		if (enemySmoke[i].isAlive == false) {
			count++;
			enemySmoke[i].isAlive = true;
			enemySmoke[i].transparency = 0xFF;
			//
			enemySmoke[i].pos.x = enemy.pos.x - (rand() % enemy.Radius) + enemy.Radius / 8;
			enemySmoke[i].pos.y = enemy.pos.y + (rand() % enemy.Size) - enemy.Radius + enemy.Radius /2;
			enemySmoke[i].transparencySpeed = (rand() % 11 + 3);
		}
		if (count == countMax) {
			break;
		}
	}


	//smokeの動き
	for (i = 0; i < EnemyEffectMax; i++) {
		if (enemySmoke[i].isAlive) {
			enemySmoke[i].pos.y -= rand() % 11 + 5;
			enemySmoke[i].pos.x += rand() % 11  + 5;
			enemySmoke[i].transparency -= enemySmoke[i].transparencySpeed;
			if (enemySmoke[i].transparency <= 0x00) {
				enemySmoke[i].transparency = 0x00;
				enemySmoke[i].isAlive = false;

			}
		}

	}

}

void  DrawEnemyEffect(Vector2& shake, int& textureHandle) {

	int i = 0;
	int radius = 12;
	for (i = 0; i < EnemyEffectMax; i++) {
		if (enemySmoke[i].isAlive) {
			Novice::DrawQuad(enemySmoke[i].pos.x - radius + shake.x, enemySmoke[i].pos.y - radius + shake.y,
				enemySmoke[i].pos.x + radius + shake.x, enemySmoke[i].pos.y - radius + shake.y,
				enemySmoke[i].pos.x - radius + shake.x, enemySmoke[i].pos.y + radius + shake.y,
				enemySmoke[i].pos.x + radius + shake.x, enemySmoke[i].pos.y + radius + shake.y,
				0, 0, 1, 1, textureHandle, 0x00000000 + enemySmoke[i].transparency);
			//Novice::DrawBox(enemySmoke[i].pos.x - radius + shake.x, enemySmoke[i].pos.y - radius + shake.y, radius * 2, radius * 2, 0, 0x00000000 + enemySmoke[i].transparency, kFillModeSolid);
		}
	}
}

void EnemyDamageEffectSetting(Enemy &enemy, float &y) {

	int i = 0;
	for (i = 0; i < EnemyDamageEffectMax; i++) {
		enemyDamageEffect[i].isAlive = true;
		enemyDamageEffect[i].transparency = 0xDD;
		//
		enemyDamageEffect[i].vel.x = rand() % 16 + 1;
		enemyDamageEffect[i].pos.x = enemy.pos.x - enemy.Radius + rand() % 9 - 4;
		enemyDamageEffect[i].pos.y = y;
		enemyDamageEffect[i].vel.y = rand() % 21 - 21;
		enemyDamageEffect[i].rad = rand() % 8 + 1;
		enemyDamageEffect[i].transparencySpeed = (rand() % 11 + 5);
	}
}

void EnemyDamageEffect() {

	int i = 0;

	//smokeの動き
	for (i = 0; i < EnemyDamageEffectMax; i++) {
		if (enemyDamageEffect[i].isAlive) {
			enemyDamageEffect[i].vel.y += Gravity;
			enemyDamageEffect[i].pos.x += enemyDamageEffect[i].vel.x;
			enemyDamageEffect[i].pos.y += enemyDamageEffect[i].vel.y;
			if (enemyDamageEffect[i].pos.y > 668.0f) {
				enemyDamageEffect[i].pos.y = 668.0f;
				enemyDamageEffect[i].vel.y = -7.5f;
			}
			enemyDamageEffect[i].transparency -= enemyDamageEffect[i].transparencySpeed;
			if (enemyDamageEffect[i].transparency <= 0x00) {
				enemyDamageEffect[i].transparency = 0x00;
				enemyDamageEffect[i].isAlive = false;
			}
		}
	}
}

void  DrawEnemyDamageEffect(Vector2& shake, int& textureHandle) {

	int i = 0;
	//int enemyDamageEffect[i].rad = 8;
	for (i = 0; i < EnemyDamageEffectMax; i++) {
		if (enemyDamageEffect[i].isAlive) {
			Novice::DrawQuad(enemyDamageEffect[i].pos.x - enemyDamageEffect[i].rad + shake.x, enemyDamageEffect[i].pos.y - enemyDamageEffect[i].rad + shake.y,
				enemyDamageEffect[i].pos.x + enemyDamageEffect[i].rad + shake.x, enemyDamageEffect[i].pos.y - enemyDamageEffect[i].rad + shake.y,
				enemyDamageEffect[i].pos.x - enemyDamageEffect[i].rad + shake.x, enemyDamageEffect[i].pos.y + enemyDamageEffect[i].rad + shake.y,
				enemyDamageEffect[i].pos.x + enemyDamageEffect[i].rad + shake.x, enemyDamageEffect[i].pos.y + enemyDamageEffect[i].rad + shake.y,
				0, 0, 1, 1, textureHandle, 0x9CB6CD00 + enemyDamageEffect[i].transparency);
			//Novice::DrawBox(enemyDamageEffect[i].pos.x - enemyDamageEffect[i].rad + shake.x, enemyDamageEffect[i].pos.y - enemyDamageEffect[i].rad + shake.y,
				//enemyDamageEffect[i].rad * 2, enemyDamageEffect[i].rad * 2, 0, 0x9CB6CD00 + enemyDamageEffect[i].transparency, kFillModeSolid);
		}
	}

}

void enemyChangeEffectRestartSetting() {

	enemyChangeEffectRestart = false;
	enemyChangeEffectSize = 0;

}

void EnemyChangeEffectSetting(Enemy &enemy) {

	int i = 0;
	int count = 0;
	int countMax = 2;

	for (i = 0; i < EnemyChangeEffectMax; i++) {
		if (enemyChangeEffect[i].isAlive == false && !enemyChangeEffectRestart) {
			if (i == 0) {
				enemyChangeEffect[0].posSpeed = 2;
				enemyChangeEffect[1].posSpeed = 0;
			}
			count++;
			enemyChangeEffect[i].isAlive = true;
			enemyChangeEffect[i].transparency = 0x00;
			
			int radian = rand() % 359;

			enemyChangeEffect[i].pos.x = enemy.pos.x + cosf(radian * M_PI / 180.0f) * enemy.Radius + rand() % 61 - 30;
			enemyChangeEffect[i].pos.y = enemy.pos.y + sinf(radian * M_PI / 180.0f) * enemy.Radius + rand() % 61 - 30;

			//距離を測る
			Vector2 posTmp = Guided(enemy.pos, enemyChangeEffect[i].pos);
			//正規化
			float normalize = sqrt(posTmp.x * posTmp.x + posTmp.y * posTmp.y);

			enemyChangeEffect[i].vel.x = posTmp.x / normalize * 0.1f;
			enemyChangeEffect[i].vel.y = posTmp.y / normalize * 0.1f;
			enemyChangeEffect[i].transparencySpeed = (rand() % 10 + 1);
			if (count == countMax) {
				break;
			}
		}
	}
}

void EnemyChangeEffect(Enemy& enemy, Scene& scene) {

	int i = 0;
	int radius = 12;
	//smokeの動き
	for (i = 0; i < EnemyChangeEffectMax; i++) {
		if (enemyChangeEffect[i].isAlive && !enemyChangeEffectStop[i]) {

			enemyChangeEffect[i].pos.x += enemyChangeEffect[i].vel.x;
			enemyChangeEffect[i].pos.y += enemyChangeEffect[i].vel.y;

			if ((enemyChangeEffect[i].vel.x < 0 && enemyChangeEffect[i].pos.x < enemy.pos.x) ||
				(enemyChangeEffect[i].vel.x > 0 && enemyChangeEffect[i].pos.x > enemy.pos.x)) {
				enemyChangeEffect[i].vel.x *= -1;
				if (!enemyChangeEffectRestart) {
					enemyChangeEffectStop[i] = true;
					enemyChangeEffectSize++;
				}
			}
			if ((enemyChangeEffect[i].vel.y < 0 && enemyChangeEffect[i].pos.y < enemy.pos.y) ||
				(enemyChangeEffect[i].vel.y > 0 && enemyChangeEffect[i].pos.y > enemy.pos.y)) {
				enemyChangeEffect[i].vel.y *= -1;
				if (!enemyChangeEffectRestart) {
					enemyChangeEffectStop[i] = true;
					enemyChangeEffectSize++;
				}
			}

			if (!enemyChangeEffectRestart) {
				enemyChangeEffect[i].vel.x *= 1.05;
				enemyChangeEffect[i].vel.y *= 1.05;
			}
			else {
				enemyChangeEffect[i].vel.x *= 1.25;
				enemyChangeEffect[i].vel.y *= 1.25;
			}

			if (!enemyChangeEffectRestart) {
				enemyChangeEffect[i].transparency += enemyChangeEffect[i].transparencySpeed;
				if (enemyChangeEffect[i].transparency >= 0xFF) {
					enemyChangeEffect[i].transparency = 0xFF;
				}
			}
			else {
				enemyChangeEffect[i].transparency -= enemyChangeEffect[i].transparencySpeed;
				if (enemyChangeEffect[i].transparency <= 0x00) {
					enemyChangeEffect[i].transparency = 0x00;
					enemyChangeEffect[i].isAlive = false;
				}
			}
		}
	}

	//はじける前
	if (!enemyChangeEffectRestart) {
		enemyChangeEffectRestart = true;

		//吸収
		for (i = 0; i < EnemyChangeEffectMax; i++) {
			if (!enemyChangeEffectStop[i]) {
				enemyChangeEffectRestart = false;
				break;
			}
		}
		//小さくなる
		if (enemyChangeEffectRestart && enemyChangeEffectSize > enemyChangeEffectSizeMax) {
			if (enemy.transparency != 0x00) {
				enemy.transparency = 0x00;
			}
			enemyChangeEffectSize -= enemyChangeEffect[0].posSpeed;
			enemyChangeEffect[0].posSpeed *= 1.5f;
			if (enemyChangeEffectSize <= enemyChangeEffectSizeMax) {
				enemyChangeEffectSize = enemyChangeEffectSizeMax;
			}
			enemyChangeEffectRestart = false;
		}
		//いったんストップ
		if (enemyChangeEffectRestart && enemyChangeEffect[1].posSpeed < 60) {
			enemyChangeEffect[1].posSpeed++;
			enemyChangeEffectRestart = false;
		}
		//リスタート
		if (enemyChangeEffectRestart) {
			for (i = 0; i < EnemyChangeEffectMax; i++) {
				enemyChangeEffectStop[i] = false;
			}
			scene = gameBoss2;
			StopAudio(bossChange2);
			PlayAudio(bossChange2);
		}
	}
}

void DrawEnemyChangeEffect(Enemy &enemy, Vector2& shake,Scene &scene, int& textureHandle) {

	int i = 0;
	int radius = 12;

	Novice::SetBlendMode(kBlendModeAdd);
	for (i = 0; i < EnemyChangeEffectMax; i++) {
		if (enemyChangeEffect[i].isAlive && !enemyChangeEffectStop[i]) {
			Novice::DrawQuad(enemyChangeEffect[i].pos.x - radius + shake.x, enemyChangeEffect[i].pos.y - radius + shake.y,
				enemyChangeEffect[i].pos.x + radius + shake.x, enemyChangeEffect[i].pos.y - radius + shake.y,
				enemyChangeEffect[i].pos.x - radius + shake.x, enemyChangeEffect[i].pos.y + radius + shake.y,
				enemyChangeEffect[i].pos.x + radius + shake.x, enemyChangeEffect[i].pos.y + radius + shake.y,
				0, 0, 1, 1, textureHandle, 0x01759F00 + enemyChangeEffect[i].transparency);
			//Novice::DrawBox(enemyChangeEffect[i].pos.x - radius + shake.x, enemyChangeEffect[i].pos.y - radius + shake.y,
				//radius * 2, radius * 2, 0, 0x01759F00 + enemyChangeEffect[i].transparency, kFillModeSolid);
		}
	}
	Novice::SetBlendMode(kBlendModeNormal);

	if (!enemyChangeEffectRestart && scene == gameBoss1) {
		Novice::SetBlendMode(kBlendModeSubtract);
		Novice::DrawEllipse(enemy.pos.x + shake.x, enemy.pos.y + shake.y,
			enemyChangeEffectSize / 4, enemyChangeEffectSize / 4, 0, 0x01759FED, kFillModeSolid);
		Novice::DrawEllipse(enemy.pos.x + shake.x, enemy.pos.y + shake.y,
			enemyChangeEffectSize / 4, enemyChangeEffectSize / 4, 0, 0xBBBBBBBB, kFillModeSolid);
		Novice::SetBlendMode(kBlendModeNormal);
	}
}