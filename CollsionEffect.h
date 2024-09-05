#pragma once

struct Effect {

	bool isAlive = false;
	Vector2 pos = { 0,0 };//位置
	Vector2 vel = { 0,0 };

	int posSpeed = 0;
	int transparency = 0;//透明度
	int transparencySpeed = 0;//透明度

	float radius = 0;
};

//剣はじく音
struct EffectEllipse {

	bool isAlive = false;
	Vector2 pos = { 0,0 };//位置
	Vector2 vel = { 0,0 };

	int posSpeed = 0;
	int transparency = 0;//透明度
	int transparencySpeed = 0;//透明度

	int radius;
};

void RepelTheSwordEffectSetting(Player& player);
void RepelTheSwordEffect();
void DrawRepelTheSwordEffect(Vector2& shake, int& textureHandle);
void RepelTheSwordEffectReset();