#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Boss.h"
void BossSwordRotate(Sword& sword, Boss& boss) {

	int speedAttack = 100;
	int speedStand = 20;

	if (boss.isAttack) {
		if (boss.isLeft) {
			if (sword.radian > -315) {
				sword.radian -= speedAttack;
			}
			if (sword.radian < -315) {
				sword.radian = -315;
			}
		}
		else {
			if (sword.radian < 225) {
				sword.radian += speedAttack;
			}
			if (sword.radian > 225) {
				sword.radian = 225;
			}
		}
	}
	else {
		if (sword.radian > -45) {
			sword.radian -= speedStand;
		}
		if (sword.radian < -45) {
			sword.radian += speedStand;
		}
		if (sword.radian >= -45 - speedStand && sword.radian <= -35 + speedStand) {
			sword.radian = -45;
		}

	}
	sword.theta = sword.radian * M_PI / 180.0f;

}
//セッティング
void BossSwordSetting(Sword& sword) {

	sword.Pos.x = 0;//位置
	sword.Pos.y = 0;//位置
	sword.Radius.x = 32;//半径
	sword.Radius.y = 32;//半径
	sword.quad.leftTop.x = -sword.Radius.x;
	sword.quad.rightTop.x = sword.Radius.x;
	sword.quad.leftBottom.x = -sword.Radius.x;
	sword.quad.rightBottom.x = sword.Radius.x;//四点
	sword.quad.leftTop.y = -sword.Radius.y;
	sword.quad.rightTop.y = -sword.Radius.y;
	sword.quad.leftBottom.y = sword.Radius.y;
	sword.quad.rightBottom.y = sword.Radius.y;//四点
	sword.textureHandle = Novice::LoadTexture("./Resouce/Texture/bossSord.png");

	sword.radian = 0;
	sword.theta = 0.0f;
	sword.floating = 0;
	sword.floatinglength = 10;

}

void BossSwordFloating(Sword& sword) {

	int max = 360;
	sword.floating += 3;
	if (sword.floating >= max) {
		sword.floating = 0;
	}

}

//プレイヤーについてく
void BossSwordFollowing(Sword& sword, Boss& boss) {

	int speedAttack = 40;
	int speedStand = 20;
	if (boss.isAttack) {
		if (boss.isLeft) {
			if (sword.Pos.x < boss.attackQuad.leftTop.x + sword.Radius.x) {
				sword.Pos.x += speedAttack;
			}
			if (sword.Pos.x > boss.attackQuad.leftTop.x + sword.Radius.x) {
				sword.Pos.x = boss.attackQuad.leftTop.x + sword.Radius.x;
			}
		}
		else {
			if (sword.Pos.x > boss.attackQuad.rightTop.x - sword.Radius.x) {
				sword.Pos.x -= speedAttack;
			}
			if (sword.Pos.x < boss.attackQuad.rightTop.x - sword.Radius.x) {
				sword.Pos.x = boss.attackQuad.rightTop.x - sword.Radius.x;
			}
		}
		//
		if (sword.Pos.y < boss.attackQuad.leftBottom.y + sword.Radius.y) {
			sword.Pos.y += speedAttack;
		}
		if (sword.Pos.y > boss.attackQuad.leftBottom.y + sword.Radius.y) {
			sword.Pos.y = boss.attackQuad.leftBottom.y + sword.Radius.y;
		}
	}
	else {
		if (boss.isLeft) {
			if (sword.Pos.x < boss.pos.x + boss.Radius + sword.Radius.x) {
				sword.Pos.x += speedStand;
			}
			else {
				sword.Pos.x = boss.pos.x + boss.Radius + sword.Radius.x;
			}
			if (sword.Pos.x >= WinWidth - sword.Radius.x) {
				sword.Pos.x = WinWidth - sword.Radius.x;
			}
		}
		else {
			if (sword.Pos.x > boss.pos.x - boss.Radius - sword.Radius.x) {
				sword.Pos.x -= speedStand;
			}
			else {
				sword.Pos.x = boss.pos.x - boss.Radius - sword.Radius.x;
			}
			if (sword.Pos.x <= sword.Radius.x) {
				sword.Pos.x = sword.Radius.x;
			}
		}
		sword.Pos.y = boss.pos.y - boss.Radius + sword.floatinglength * sinf(sword.floating * M_PI / 180.0f);
	}
}

void BossSwordQuad(Sword& sword) {

	sword.quad.leftTop.x = (-sword.Radius.x * cosf(sword.theta)) - (-sword.Radius.y * sinf(sword.theta)) + sword.Pos.x;
	sword.quad.leftTop.y = (-sword.Radius.x * sinf(sword.theta)) + (-sword.Radius.y * cosf(sword.theta)) + sword.Pos.y;
	sword.quad.rightTop.x = sword.Radius.x * cosf(sword.theta) - (-sword.Radius.y * sinf(sword.theta)) + sword.Pos.x;
	sword.quad.rightTop.y = sword.Radius.x * sinf(sword.theta) + (-sword.Radius.y * cosf(sword.theta)) + sword.Pos.y;
	sword.quad.leftBottom.x = (-sword.Radius.x * cosf(sword.theta)) - sword.Radius.y * sinf(sword.theta) + sword.Pos.x;
	sword.quad.leftBottom.y = (-sword.Radius.x * sinf(sword.theta)) + sword.Radius.y * cosf(sword.theta) + sword.Pos.y;
	sword.quad.rightBottom.x = sword.Radius.x * cosf(sword.theta) - sword.Radius.y * sinf(sword.theta) + sword.Pos.x;//四点
	sword.quad.rightBottom.y = sword.Radius.x * sinf(sword.theta) + sword.Radius.y * cosf(sword.theta) + sword.Pos.y;//四点

}

void BossSwordAfterimage(Sword& sword, Boss& boss) {
	int i = 0;
	int max = 5;
	for (i = 0; i < max - 1; i++) {
		sword.afterimage[i] = sword.afterimage[i + 1];
		sword.afterimageIsLeft[i] = sword.afterimageIsLeft[i + 1];
	}

	sword.afterimage[max - 1] = sword.quad;
	sword.afterimageIsLeft[max - 1] = boss.isLeft;

}

void DrowBossSword(Sword& sword, Boss& boss, Vector2& shake) {

	if (boss.isLeft) {
		Novice::DrawQuad(sword.quad.leftTop.x + shake.x, sword.quad.leftTop.y + shake.y,
			sword.quad.rightTop.x + shake.x, sword.quad.rightTop.y + shake.y,
			sword.quad.leftBottom.x + shake.x, sword.quad.leftBottom.y + shake.y,
			sword.quad.rightBottom.x + shake.x, sword.quad.rightBottom.y + shake.y,
			0, 0, 64, 64, sword.textureHandle, 0xFFFFFFFF);

	}
	else {
		Novice::DrawQuad(sword.quad.rightBottom.x + shake.x, sword.quad.rightBottom.y + shake.y,
			sword.quad.rightTop.x + shake.x, sword.quad.rightTop.y + shake.y,
			sword.quad.leftBottom.x + shake.x, sword.quad.leftBottom.y + shake.y,
			sword.quad.leftTop.x + shake.x, sword.quad.leftTop.y + shake.y,
			0, 0, 64, 64, sword.textureHandle, 0xFFFFFFFF);
	}
	int i = 0;
	int max = 5;
	for (i = 0; i < max - 1; i++) {
		if (sword.afterimageIsLeft[i]) {
			Novice::DrawQuad(sword.afterimage[i].leftTop.x + shake.x, sword.afterimage[i].leftTop.y + shake.y,
				sword.afterimage[i].rightTop.x + shake.x, sword.afterimage[i].rightTop.y + shake.y,
				sword.afterimage[i].leftBottom.x + shake.x, sword.afterimage[i].leftBottom.y + shake.y,
				sword.afterimage[i].rightBottom.x + shake.x, sword.afterimage[i].rightBottom.y + shake.y,
				0, 0, 64, 64, sword.textureHandle, 0xFFFFFF00 + 0x19 * (i + 1));

		}
		else {
			Novice::DrawQuad(sword.afterimage[i].rightBottom.x + shake.x, sword.afterimage[i].rightBottom.y + shake.y,
				sword.afterimage[i].rightTop.x + shake.x, sword.afterimage[i].rightTop.y + shake.y,
				sword.afterimage[i].leftBottom.x + shake.x, sword.afterimage[i].leftBottom.y + shake.y,
				sword.afterimage[i].leftTop.x + shake.x, sword.afterimage[i].leftTop.y + shake.y,
				0, 0, 64, 64, sword.textureHandle, 0xFFFFFF00 + 0x19 * (i + 1));
		}
	}


}

void DrawBossSwordEffect(Boss& boss, Vector2& shake) {
	if (boss.isLeft) {
		if (boss.isAttack) {
			//攻撃表示
			Novice::DrawQuad(boss.attackQuad.rightTop.x + shake.x+16, boss.attackQuad.rightTop.y + shake.y-16,
				boss.attackQuad.leftTop.x + shake.x-16, boss.attackQuad.leftTop.y + shake.y-16,
				boss.attackQuad.rightBottom.x + shake.x+16, boss.attackQuad.rightBottom.y + shake.y+16,
				boss.attackQuad.leftBottom.x + shake.x-16, boss.attackQuad.leftBottom.y + shake.y+16,
				0, 0, 64, 64, boss.attack.textureHandle, 0x50FFFFFF);
		}
	}
	else {
		if (boss.isAttack) {
			//攻撃表示
			Novice::DrawQuad(boss.attackQuad.leftTop.x-16 + shake.x, boss.attackQuad.leftTop.y + shake.y-16,
				boss.attackQuad.rightTop.x + shake.x+16, boss.attackQuad.rightTop.y + shake.y-16,
				boss.attackQuad.leftBottom.x + shake.x-16, boss.attackQuad.leftBottom.y + shake.y+16,
				boss.attackQuad.rightBottom.x + shake.x+16, boss.attackQuad.rightBottom.y + shake.y+16,
				0, 0, 64, 64, boss.attack.textureHandle, 0x50FFFFFF);
		}
	}


}

void BossSwordFunction(Sword& sword, Boss& boss) {

	BossSwordRotate(sword, boss);
	BossSwordFloating(sword);
	BossSwordFollowing(sword, boss);
	BossSwordQuad(sword);
	BossSwordAfterimage(sword, boss);
}