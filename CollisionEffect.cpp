#include "Common.h"
#include "Player.h"
#include "CollsionEffect.h"


const int RepelTheSwordEffecteMax = 128;

Effect repelTheSwordEffect[RepelTheSwordEffecteMax];

EffectEllipse repelTheSwordEffectEllipse;

void RepelTheSwordEffectSetting(Player &player) {

	int i = 0;
	for (i = 0; i < RepelTheSwordEffecteMax; i++) {
		repelTheSwordEffect[i].isAlive = true;
		repelTheSwordEffect[i].transparency = 0x88;
		//
		repelTheSwordEffect[i].pos.x = player.attack.Pos.x;
		repelTheSwordEffect[i].pos.y = player.attack.Pos.y;
		if (player.isLeft) {
			repelTheSwordEffect[i].vel.x = rand() % 31 - 25;
		}
		else {
			repelTheSwordEffect[i].vel.x = rand() % 31 + 1;
		}
		repelTheSwordEffect[i].vel.y = rand() % 31 - 15;
		repelTheSwordEffect[i].transparencySpeed = (rand() % 11 + 5);
		repelTheSwordEffect[i].radius = rand() % 6 + 1;
	}
	repelTheSwordEffectEllipse.radius = 0;
	repelTheSwordEffectEllipse.isAlive = true;
	repelTheSwordEffect[i].transparency = 0xAA;
	repelTheSwordEffectEllipse.pos.x = player.attack.Pos.x;
	repelTheSwordEffectEllipse.pos.y = player.attack.Pos.y;
	repelTheSwordEffectEllipse.transparencySpeed = 8/*(rand() % 11 + 5)*/;
	repelTheSwordEffectEllipse.posSpeed = 2;
	StopAudio(swordRepel);
	PlayAudio(swordRepel);
}

void RepelTheSwordEffect() {
	
	int i = 0;

	//smokeの動き
	for (i = 0; i < RepelTheSwordEffecteMax; i++) {
		if (repelTheSwordEffect[i].isAlive) {
			repelTheSwordEffect[i].pos.x += repelTheSwordEffect[i].vel.x;
			repelTheSwordEffect[i].pos.y += repelTheSwordEffect[i].vel.y;
			repelTheSwordEffect[i].transparency -= repelTheSwordEffect[i].transparencySpeed;
			if (repelTheSwordEffect[i].transparency <= 0x00) {
				repelTheSwordEffect[i].transparency = 0x00;
				if (i != 0) {
					repelTheSwordEffect[i].isAlive = false;
				}
			}
		}
	}
	repelTheSwordEffectEllipse.radius += repelTheSwordEffectEllipse.posSpeed;
	repelTheSwordEffectEllipse.transparency -= repelTheSwordEffectEllipse.transparencySpeed;
	if (repelTheSwordEffectEllipse.transparency <= 0x00) {
		repelTheSwordEffectEllipse.transparency = 0x00;
		repelTheSwordEffectEllipse.isAlive = false;
	}
}

void  DrawRepelTheSwordEffect(Vector2& shake, int& textureHandle) {

	int i = 0;
	for (i = 0; i < RepelTheSwordEffecteMax; i++) {
		if (repelTheSwordEffect[i].isAlive) {
			Novice::DrawQuad(repelTheSwordEffect[i].pos.x - repelTheSwordEffect[i].radius + shake.x, repelTheSwordEffect[i].pos.y - repelTheSwordEffect[i].radius + shake.y,
				repelTheSwordEffect[i].pos.x + repelTheSwordEffect[i].radius + shake.x, repelTheSwordEffect[i].pos.y - repelTheSwordEffect[i].radius + shake.y,
				repelTheSwordEffect[i].pos.x - repelTheSwordEffect[i].radius + shake.x, repelTheSwordEffect[i].pos.y + repelTheSwordEffect[i].radius + shake.y,
				repelTheSwordEffect[i].pos.x + repelTheSwordEffect[i].radius + shake.x, repelTheSwordEffect[i].pos.y + repelTheSwordEffect[i].radius + shake.y,
				0, 0, 1, 1, textureHandle, 0xE3EAD900 + repelTheSwordEffect[i].transparency);
			//Novice::DrawBox(repelTheSwordEffect[i].pos.x - repelTheSwordEffect[i].radius + shake.x, repelTheSwordEffect[i].pos.y - repelTheSwordEffect[i].radius + shake.y,
				//repelTheSwordEffect[i].radius * 2, repelTheSwordEffect[i].radius * 2, 0, 0xE3EAD900 + repelTheSwordEffect[i].transparency, kFillModeSolid);
		}
	}
	if (repelTheSwordEffectEllipse.isAlive == false) {
		Novice::DrawEllipse(repelTheSwordEffectEllipse.pos.x + shake.x, repelTheSwordEffectEllipse.pos.y + shake.y,
			repelTheSwordEffectEllipse.radius, repelTheSwordEffectEllipse.radius,
			0.0f, 0xFFFFEE00 + repelTheSwordEffectEllipse.transparency, kFillModeWireFrame);
	}
}

void RepelTheSwordEffectReset() {

	int i = 0;
	for (i = 0; i < RepelTheSwordEffecteMax; i++) {
		repelTheSwordEffect[i].isAlive = false;
	}
	repelTheSwordEffectEllipse.isAlive = false;
}