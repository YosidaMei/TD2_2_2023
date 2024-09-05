#include "Common.h"
#include "Map.h"
#include "Collision.h"

//マップチップとのあたり判定(マップ、x座標、y座標、半径、確認場所)
int CollisionMap(int map[MapHeight][MapWidth],float x, float y, int radius, CollisionDir dir) {

	switch (dir)
	{
	case leftTop:
			return map[int((y - radius) / MapchipSize)][int((x - radius) / MapchipSize)];
		break;
	case rightTop:
		return map[int((y - radius) / MapchipSize)][int((x + radius - 1) / MapchipSize)];
		break;
	case leftBottom:
		return map[int((y + radius - 1) / MapchipSize)][int((x - radius) / MapchipSize)];
		break;
	case rightBottom:
		return map[int((y + radius - 1) / MapchipSize)][int((x + radius - 1) / MapchipSize)];
		break;
	default:
		break;
	}

	return 0;

}

//オブジェクト同士のあたり判定(Quad,Quad)
bool CollisionObj(Quad& quad1, Quad& quad2) {

	if (IntersectionDetection(quad1.leftTop, quad1.rightTop, quad2.leftTop, quad2.rightTop) ||
		IntersectionDetection(quad1.leftTop, quad1.rightTop, quad2.rightTop, quad2.rightBottom) ||
		IntersectionDetection(quad1.leftTop, quad1.rightTop, quad2.rightBottom, quad2.leftBottom) ||
		IntersectionDetection(quad1.leftTop, quad1.rightTop, quad2.leftBottom, quad2.leftTop) ||

		IntersectionDetection(quad1.rightTop, quad1.rightBottom, quad2.leftTop, quad2.rightTop) ||
		IntersectionDetection(quad1.rightTop, quad1.rightBottom, quad2.rightTop, quad2.rightBottom) ||
		IntersectionDetection(quad1.rightTop, quad1.rightBottom, quad2.rightBottom, quad2.leftBottom) ||
		IntersectionDetection(quad1.rightTop, quad1.rightBottom, quad2.leftBottom, quad2.leftTop) ||

		IntersectionDetection(quad1.rightBottom, quad1.leftBottom, quad2.leftTop, quad2.rightTop) ||
		IntersectionDetection(quad1.rightBottom, quad1.leftBottom, quad2.rightTop, quad2.rightBottom) ||
		IntersectionDetection(quad1.rightBottom, quad1.leftBottom, quad2.rightBottom, quad2.leftBottom) ||
		IntersectionDetection(quad1.rightBottom, quad1.leftBottom, quad2.leftBottom, quad2.leftTop) ||

		IntersectionDetection(quad1.leftBottom, quad1.leftTop, quad2.leftTop, quad2.rightTop) ||
		IntersectionDetection(quad1.leftBottom, quad1.leftTop, quad2.rightTop, quad2.rightBottom) ||
		IntersectionDetection(quad1.leftBottom, quad1.leftTop, quad2.rightBottom, quad2.leftBottom) ||
		IntersectionDetection(quad1.leftBottom, quad1.leftTop, quad2.leftBottom, quad2.leftTop)) {

		return true;

	}
	return false;
}

bool IntersectionDetection(Vector2& a, Vector2& b, Vector2& c, Vector2& d) {

	double s = 0;
	double t = 0;
	s = (a.x - b.x) * (c.y - a.y) - (a.y - b.y) * (c.x - a.x);
	t = (a.x - b.x) * (d.y - a.y) - (a.y - b.y) * (d.x - a.x);
	if (s * t > 0) {
		return false;
	}
	s = (c.x - d.x) * (a.y - c.y) - (c.y - d.y) * (a.x - c.x);
	t = (c.x - d.x) * (b.y - c.y) - (c.y - d.y) * (b.x - c.x);
	if (s * t > 0) {
		return false;
	}
	return true;

}
//傾いていない場合
bool CollisionObjRect(Quad& quad1, Quad& quad2) {

	if (( (quad1.leftTop.x >= quad2.leftTop.x &&
		quad1.leftTop.x <= quad2.rightTop.x) ||
		(quad1.rightTop.x >= quad2.leftTop.x &&
		quad1.rightTop.x <= quad2.rightTop.x) || 
		(quad2.leftTop.x >= quad1.leftTop.x &&
			quad2.leftTop.x <= quad1.rightTop.x) ||
		(quad2.rightTop.x >= quad1.leftTop.x &&
			quad2.rightTop.x <= quad1.rightTop.x) ) &&

		( (quad1.leftTop.y >= quad2.leftTop.y &&
			quad1.leftTop.y <= quad2.rightBottom.y) ||
			(quad1.rightBottom.y >= quad2.leftTop.y &&
				quad1.rightBottom.y <= quad2.rightBottom.y) ||
			(quad2.leftTop.y >= quad1.leftTop.y &&
				quad2.leftTop.y <= quad1.rightBottom.y) ||
			(quad2.rightBottom.y >= quad1.leftBottom.y &&
				quad2.rightBottom.y <= quad1.rightBottom.y) ) ) {

		return true;
	}

	return false;

}