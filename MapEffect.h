#pragma once
#include"Common.h"
#include "Boss.h"

struct MapEffect {
	bool isAlive = false;
	Vector2 pos = { 0,0 };//位置
	Vector2 vel = { 0,0 };

	float radius = 0;

	int posSpeed = 0;
	int transparency = 0;//透明度
	int transparencySpeed = 0;//透明度
};

const int MaxEff = 30;

void BackEffSet(int scene);
void EffectUpdate(int scene, Boss& boss);
void DrawEffect(int scene, Boss& boss, int& textureHandle);

void HpEffectUpdate(Player& player);
void DrawHpEffect(Player& player, int& textureHandle);
