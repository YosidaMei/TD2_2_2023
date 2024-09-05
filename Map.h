#pragma once

const int MapchipSize = 32;//マップチップサイズ
const int MapWidth = WinWidth / MapchipSize;//マップ幅
const int MapHeight = WinHeight / MapchipSize + 1;//マップ高さ（割り切れないので+1）

//マップの種類
enum MapType {

	none,//0
	block//1
};

int  MapLoading(int map[MapHeight][MapWidth]);
void DrawMap(int& textureHandle, int map[MapHeight][MapWidth], Vector2& shake);