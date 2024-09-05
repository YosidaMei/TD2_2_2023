#include"MapEffect.h"

MapEffect effectTest[MaxEff];

int countEffectTime = 0;

int maxEffect;

int playerHpEffect;

void BackEffSet(int scene) {
	if (scene == 2) {
		maxEffect = 10;
	}
	else if (scene == 3) {
		maxEffect = 20;
	}

	for (int i = 0; i < maxEffect; i++) {
		if (!effectTest[i].isAlive) {
			effectTest[i].isAlive = true;
			effectTest[i].transparency = 0xFF;
			effectTest[i].pos.x = rand() % 1150 + 50;
			effectTest[i].pos.y = WinHeight;
			effectTest[i].vel.y = rand() % 25 + 1;
			effectTest[i].transparencySpeed = rand() % 15 + 1;
			effectTest[i].radius = rand() % 4 + 1;
		}
	}
}

void EffectUpdate(int scene,Boss& boss) {

	if (scene == 2) {
		maxEffect = 10;
	}
	else if (scene == 3) {
		if (boss.Hp <= 100) {
			maxEffect = 20;
		}
		else if (boss.Hp > 100) {
			maxEffect = 25;
		}
	}

	for (int i = 0; i < maxEffect; i++) {
		if (effectTest[i].isAlive) {
			effectTest[i].pos.y -= effectTest[i].vel.y / 3;
			effectTest[i].transparency -= effectTest[i].transparencySpeed;
			if (effectTest[i].transparency <= 0x00) {
				effectTest[i].transparency = 0x00;
				if (i != 0) {
					effectTest[i].isAlive = false;
				}
			}
		}
	}
}

void HpEffectUpdate(Player& player) {
	if (player.Hp >= 6) {
		playerHpEffect = 0x00;
	}
	if (player.Hp < 5) {
		playerHpEffect = 0x08;
	}
	if (player.Hp < 2) {
		playerHpEffect = 0x15;
	}
}

void DrawEffect(int scene, Boss& boss, int &textureHandle) {

	int radius = 4;
	Novice::SetBlendMode(kBlendModeAdd);
	for (int i = 0; i < maxEffect; i++) {
		if (scene == 2) {
			Novice::DrawQuad(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
				effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
				effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
				effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
				0, 0, 1, 1, textureHandle, 0xFFFFFF00 + effectTest[i].transparency);
			//Novice::DrawBox(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
				//effectTest[i].radius * 2, effectTest[i].radius * 2, 0.0f, 0xFFFFFF00 + effectTest[i].transparency, kFillModeSolid);
			Novice::DrawQuad(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
				effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
				effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
				effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
				0, 0, 1, 1, textureHandle, 0x4016DD00 + effectTest[i].transparency);
			//Novice::DrawBox(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
				//effectTest[i].radius * 2, effectTest[i].radius * 2, 0.0f, 0x4016DD00 + effectTest[i].transparency, kFillModeSolid);
		}
		else if (scene == 3) {
			if (boss.Hp > 100) {
				Novice::DrawQuad(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
					effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
					0, 0, 1, 1, textureHandle, 0x4E92AA00 + effectTest[i].transparency);
				//Novice::DrawBox(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					//effectTest[i].radius * 2, effectTest[i].radius * 2, 0.0f, 0x4E92AA00 + effectTest[i].transparency, kFillModeSolid);
				Novice::DrawQuad(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
					effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
					0, 0, 1, 1, textureHandle, 0x88888800 + effectTest[i].transparency);
				//Novice::DrawBox(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					//effectTest[i].radius * 2, effectTest[i].radius * 2, 0.0f, 0x88888800 + effectTest[i].transparency, kFillModeSolid);
			}
			else if (boss.Hp <= 100) {
				Novice::DrawQuad(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
					effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
					0, 0, 1, 1, textureHandle, 0xCC325A00 + effectTest[i].transparency);
				//Novice::DrawBox(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					//effectTest[i].radius * 2, effectTest[i].radius * 2, 0.0f, 0xCC325A00 + effectTest[i].transparency, kFillModeSolid);
				Novice::DrawQuad(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
					effectTest[i].pos.x + effectTest[i].radius, effectTest[i].pos.y + effectTest[i].radius,
					0, 0, 1, 1, textureHandle, 0x88888800 + effectTest[i].transparency);
				//Novice::DrawBox(effectTest[i].pos.x - effectTest[i].radius, effectTest[i].pos.y - effectTest[i].radius,
					//effectTest[i].radius * 2, effectTest[i].radius * 2, 0.0f, 0x88888800 + effectTest[i].transparency, kFillModeSolid);
			}
		}
	}
	Novice::SetBlendMode(kBlendModeNormal);
}

void DrawHpEffect(Player& player, int& textureHandle) {

	Novice::SetBlendMode(kBlendModeAdd);
	Novice::DrawQuad(0, 0, WinWidth, 0, 0, WinHeight, WinWidth, WinHeight,
		0, 0, 1, 1, textureHandle, 0xbb543D00 + playerHpEffect);
	//Novice::DrawBox(0, 0, WinWidth, WinHeight, 0.0f, 0xbb543D00 + playerHpEffect, kFillModeSolid);
	//Novice::DrawBox(50, 50, WinWidth - 100, WinHeight - 100, 0.0f, 0xffffff1A, kFillModeSolid);
	Novice::SetBlendMode(kBlendModeNormal);
}
