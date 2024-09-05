#pragma once

//確認場所
enum CollisionDir {
	leftTop,//0
	rightTop,//1
	leftBottom,//2
	rightBottom//3
};

int CollisionMap(int map[MapHeight][MapWidth], float x, float y, int radius, CollisionDir dir);
bool CollisionObj(Quad& quad1, Quad& quad2);
bool IntersectionDetection(Vector2& a, Vector2& b, Vector2& c, Vector2& d);
bool CollisionObjRect(Quad& quad1, Quad& quad2);