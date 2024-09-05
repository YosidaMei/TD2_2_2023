#include <Novice.h>
#include <stdio.h>
#include "Common.h"
#include "Map.h"

//マップ読み込み
int  MapLoading(int map[MapHeight][MapWidth]) {

	FILE* fp = NULL;
	fopen_s(&fp, "./map.csv", "rt");
	if (fp == NULL) {
		return 0;
	}

	int x = 0;
	int y = 0;
	while ((fscanf_s(fp, "%d,", &map[y][x])) != EOF && y < MapHeight && x < MapWidth) {
		if (x < MapWidth) {
			x++;
			if (x == MapWidth - 1) {
				fscanf_s(fp, "%d\n", &map[y][x]);
				x = 0;
				y++;
			}
		}
	}

	fclose(fp);

	return 0;

}

//マップ描画
void DrawMap(int& textureHandle, int map[MapHeight][MapWidth], Vector2& shake) {

	for (int y = 0; y < MapHeight; y++) {
		for (int x = 0; x < MapWidth; x++) {
			if (map[y][x] == none) {
				Novice::DrawQuad(MapchipSize * x + shake.x, MapchipSize * y + shake.y,
					MapchipSize * (x + 1) + shake.x, MapchipSize * y + shake.y,
					MapchipSize * x + shake.x, MapchipSize * (y + 1) + shake.y,
					MapchipSize * (x + 1) + shake.x, MapchipSize * (y + 1) + shake.y,
					0, 0, MapchipSize, MapchipSize, textureHandle, 0x555555FF);
			}
			else {
				Novice::DrawQuad(MapchipSize * x + shake.x, MapchipSize * y + shake.y,
					MapchipSize * (x + 1) + shake.x, MapchipSize * y + shake.y,
					MapchipSize * x + shake.x, MapchipSize * (y + 1) + shake.y,
					MapchipSize * (x + 1) + shake.x, MapchipSize * (y + 1) + shake.y,
					0, 0, MapchipSize, MapchipSize, textureHandle, 0xFFFFFFFF);
			}
		}
	}
	for (int y = 0; y < MapHeight; y++) {
		if (y < MapHeight - 2) {
			Novice::DrawQuad(MapchipSize * -1 + shake.x, MapchipSize * y + shake.y,
				0 + shake.x, MapchipSize * y + shake.y,
				MapchipSize * -1 + shake.x, MapchipSize * (y + 1) + shake.y,
				0 + shake.x, MapchipSize * (y + 1) + shake.y,
				0, 0, MapchipSize, MapchipSize, textureHandle, 0x555555FF);

			Novice::DrawQuad(MapchipSize * MapWidth + shake.x, MapchipSize * y + shake.y,
				MapchipSize * (MapWidth + 1) + shake.x, MapchipSize * y + shake.y,
				MapchipSize * MapWidth + shake.x, MapchipSize * (y + 1) + shake.y,
				MapchipSize * (MapWidth + 1) + shake.x, MapchipSize * (y + 1) + shake.y,
				0, 0, MapchipSize, MapchipSize, textureHandle, 0x555555FF);
		}
		else {
			Novice::DrawQuad(MapchipSize * -1 + shake.x, MapchipSize * y + shake.y,
				0 + shake.x, MapchipSize * y + shake.y,
				MapchipSize * -1 + shake.x, MapchipSize * (y + 1) + shake.y,
				0 + shake.x, MapchipSize * (y + 1) + shake.y,
				0, 0, MapchipSize, MapchipSize, textureHandle, 0xFFFFFFFF);

			Novice::DrawQuad(MapchipSize * MapWidth + shake.x, MapchipSize * y + shake.y,
				MapchipSize * (MapWidth + 1) + shake.x, MapchipSize * y + shake.y,
				MapchipSize * MapWidth + shake.x, MapchipSize * (y + 1) + shake.y,
				MapchipSize * (MapWidth + 1) + shake.x, MapchipSize * (y + 1) + shake.y,
				0, 0, MapchipSize, MapchipSize, textureHandle, 0xFFFFFFFF);
		}
	}

	for (int x = - 1; x < MapWidth + 1; x++) {
			Novice::DrawQuad(MapchipSize * x + shake.x, MapchipSize * -1 + shake.y,
				MapchipSize * (x + 1) + shake.x, MapchipSize * -1 + shake.y,
				MapchipSize * x + shake.x, 0 + shake.y,
				MapchipSize * (x + 1) + shake.x, 0 + shake.y,
				0, 0, MapchipSize, MapchipSize, textureHandle, 0x555555FF);
	}
}