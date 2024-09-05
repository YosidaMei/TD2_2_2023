#pragma once

struct Explanation {

	int textureHandle[5] = {};//テクスチャハンドル
	int textureHandleNumber = 0;//テクスチャハンドル番号
	int transparency = 0;//透明度
	int transparencySpeed = 0;//透明度

	Vector2 size = {};
	Vector2 posision = {};

};


void Tutorial(Player& player, Scene& scene);
void DrawTutorial();