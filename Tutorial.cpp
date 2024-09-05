#include <Novice.h>
#include "Common.h"
#include "Player.h"
#include "Tutorial.h"
#include "Bullet.h"
#include "Collision.h"
#include "CollsionEffect.h"

int tutorialNumber = 0;

Explanation explanation = {};

Bullet tutorialBullet = {};

int tutorial13count = 600;

void ExplanationSetting() {

	explanation.textureHandle[0] = Novice::LoadTexture("./Resouce/Texture/explanationMove.png");//move
	explanation.textureHandle[1] = Novice::LoadTexture("./Resouce/Texture/explanationAttack.png");//attack
	explanation.textureHandle[2] = Novice::LoadTexture("./Resouce/Texture/explanationLongJump.png");//jump
	explanation.textureHandle[3] = Novice::LoadTexture("./Resouce/Texture/explanationJump.png");//2jump
	explanation.textureHandle[4] = Novice::LoadTexture("./Resouce/Texture/explanationSword.png");//sword
	explanation.transparency = 0x00;
	explanation.transparencySpeed = 0x06;
	//移動画像設定
	explanation.textureHandleNumber = 0;
	explanation.size.x = 320.0f;
	explanation.size.y = 32.0f;
	explanation.posision.x = WinWidth / 2.0f;
	explanation.posision.y = WinHeight / 2.0f;

	//チュートリアルバレット
	tutorialBullet.isAlive = false;
	tutorialBullet.isReflection = false;
	tutorialBullet.pos.y = 668 - tutorialBullet.size.y;
	tutorialBullet.pos.x = WinWidth + tutorialBullet.radius.x;
	tutorialBullet.vel.x = -2.0f;
	tutorialBullet.acc.x = -0.05f;
	tutorialBullet.textureHandle = Novice::LoadTexture("./Resouce/Texture/EnemySwrodGuide.png");

}

void Tutorial(Player &player, Scene &scene) {

	switch (tutorialNumber)
	{
	//スタート
	case 0:
		
		ExplanationSetting();
		tutorialNumber++;
		break;

	//移動説明表示
	case 1:

		explanation.transparency += explanation.transparencySpeed;
		if (explanation.transparency >= 0xFF) {
			explanation.transparency = 0xFF;
			tutorialNumber++;
		}
		break;

	//移動説明確認
	case 2:

		if (player.vel.x != 0) {
			tutorialNumber++;
		}
		break;

	//移動説明終了
	case 3:

		explanation.transparency -= explanation.transparencySpeed;
		if (explanation.transparency <= 0x00) {
			explanation.transparency = 0x00;
			//攻撃画像の設定
			explanation.size.x = 352.0f;
			explanation.size.y = 32.0f;
			explanation.posision.x = WinWidth / 2.0f;
			explanation.posision.y = WinHeight / 2.0f;
			explanation.textureHandleNumber++;
			tutorialNumber++;
		}
		break;

	//攻撃説明表示
	case 4:

		explanation.transparency += explanation.transparencySpeed;
		if (explanation.transparency >= 0xFF) {
			explanation.transparency = 0xFF;
			tutorialNumber++;
		}
		break;

	//攻撃説明確認
	case 5:

		if (player.isAttack) {
			tutorialNumber++;
		}
		break;

	//攻撃説明終了
	case 6:

		explanation.transparency -= explanation.transparencySpeed;
		if (explanation.transparency <= 0x00) {
			explanation.transparency = 0x00;
			//ジャンプ画像の設定
			explanation.size.x = 288.0f;//
			explanation.size.y = 32.0f;//
			explanation.posision.x = WinWidth / 2.0f;
			explanation.posision.y = WinHeight / 2.0f;

			explanation.textureHandleNumber++;
			tutorialNumber++;
		}
		break;


		//ロングジャンプ説明表示
	case 7:

		explanation.transparency += explanation.transparencySpeed;
		if (explanation.transparency >= 0xFF) {
			explanation.transparency = 0xFF;
			tutorialNumber++;
		}
		break;

		//ロングジャンプ説明確認
	case 8:

		if (!player.isGround) {
			tutorialNumber++;
		}

		break;

		//ロングジャンプ説明終了
	case 9:

		explanation.transparency -= explanation.transparencySpeed;
		if (explanation.transparency <= 0x00) {
			explanation.transparency = 0x00;
			//ジャンプ画像の設定
			explanation.size.x = 640.0f;
			explanation.size.y = 32.0f;
			explanation.posision.x = WinWidth / 2.0f;
			explanation.posision.y = WinHeight / 2.0f;
			explanation.textureHandleNumber++;
			tutorialNumber++;
		}
		break;

	//ジャンプ説明表示
	case 10:

		explanation.transparency += explanation.transparencySpeed;
		if (explanation.transparency >= 0xFF) {
			explanation.transparency = 0xFF;
			tutorialNumber++;
		}
		break;

	//ジャンプ説明確認(2段ジャンプまで)
	case 11:

		if (player.is2jump) {
			tutorialNumber++;
		}
		break;

	//ジャンプ説明終了、シーンをボス1へ
	case 12:

		explanation.transparency -= explanation.transparencySpeed;
		if (explanation.transparency <= 0x00) {
			explanation.transparency = 0x00;
			explanation.textureHandleNumber++;
			tutorialNumber++;
			tutorialBullet.isAlive = true;
			explanation.size.x = 192.0f;
			explanation.size.y = 64.0f;

			tutorial13count = 600;
		}
		break;

	case 13:

		tutorialBullet.pos.x += tutorialBullet.vel.x;
		if (tutorialBullet.isReflection) {
			tutorialBullet.vel.x -= tutorialBullet.acc.x;
		}
		else {
			tutorialBullet.vel.x += tutorialBullet.acc.x;
		}
		if (tutorialBullet.pos.x <= -tutorialBullet.radius.x) {
			tutorialBullet.pos.x = WinWidth + tutorialBullet.radius.x;
			tutorialBullet.vel.x = -2.0f;
		}
		if (tutorialBullet.isReflection && tutorialBullet.pos.x >= WinWidth + tutorialBullet.radius.x) {
			explanation.transparency -= explanation.transparencySpeed * 4;
			if (explanation.transparency <= 0x00) {
				//シーン切り替え
				scene = gameBoss1;
				tutorialBullet.isAlive = false;
				tutorialNumber = 0;
				if (player.pos.x >= WinWidth - 256) {
					player.pos.x = WinWidth - 256;
				}
				explanation.transparency = 0x00;
			}
		}
		else if (tutorial13count == 0) {
			explanation.transparency += explanation.transparencySpeed * 4;
			if (explanation.transparency >= 0xFF) {
				explanation.transparency = 0xFF;
			}
		}
		else {
			tutorial13count--;
		}

		//左上
		tutorialBullet.quad.leftTop.x = tutorialBullet.pos.x + (-tutorialBullet.radius.x);
		tutorialBullet.quad.leftTop.y = tutorialBullet.pos.y + (-tutorialBullet.radius.x);
		//右上
		tutorialBullet.quad.rightTop.x = tutorialBullet.pos.x + (tutorialBullet.radius.x);
		tutorialBullet.quad.rightTop.y = tutorialBullet.pos.y + (-tutorialBullet.radius.x);
		//左下
		tutorialBullet.quad.leftBottom.x = tutorialBullet.pos.x + (-tutorialBullet.radius.x);
		tutorialBullet.quad.leftBottom.y = tutorialBullet.pos.y + (-tutorialBullet.radius.x);
		//右下
		tutorialBullet.quad.rightBottom.x = tutorialBullet.pos.x + (tutorialBullet.radius.x);
		tutorialBullet.quad.rightBottom.y = tutorialBullet.pos.y + (tutorialBullet.radius.y);


		if (CollisionObjRect(tutorialBullet.quad, player.attack.quad) && !tutorialBullet.isReflection) {
			tutorialBullet.vel.x *= -1;
			tutorialBullet.isReflection = true;
			RepelTheSwordEffectSetting(player);
		}

		break;

	default:

		tutorialNumber = 0;
		break;
	}

	RepelTheSwordEffect();

}

void DrawTutorial() {

	int pulsSize = 16;

	if (!tutorialBullet.isAlive) {
		Novice::DrawBox(explanation.posision.x - (explanation.size.x + pulsSize) / 2, explanation.posision.y - (explanation.size.y + pulsSize) / 2, explanation.size.x + pulsSize, explanation.size.y + pulsSize, 0, 0x88888800 + explanation.transparency / 2, kFillModeSolid);

		Novice::DrawQuad(explanation.posision.x - explanation.size.x / 2, explanation.posision.y - explanation.size.y / 2,
			explanation.posision.x + explanation.size.x / 2, explanation.posision.y - explanation.size.y / 2,
			explanation.posision.x - explanation.size.x / 2, explanation.posision.y + explanation.size.y / 2,
			explanation.posision.x + explanation.size.x / 2, explanation.posision.y + explanation.size.y / 2,
			0, 0, explanation.size.x, explanation.size.y,
			explanation.textureHandle[explanation.textureHandleNumber], 0xFFFFFF00 + explanation.transparency);
	}

	if (tutorialBullet.isAlive) {
		if (tutorialBullet.isReflection) {
			Novice::DrawQuad(tutorialBullet.pos.x + tutorialBullet.radius.x, tutorialBullet.pos.y - tutorialBullet.radius.y,
				tutorialBullet.pos.x - tutorialBullet.radius.x, tutorialBullet.pos.y - tutorialBullet.radius.y,
				tutorialBullet.pos.x + tutorialBullet.radius.x, tutorialBullet.pos.y + tutorialBullet.radius.y,
				tutorialBullet.pos.x - tutorialBullet.radius.x, tutorialBullet.pos.y + tutorialBullet.radius.y,
				0, 0, tutorialBullet.size.x, tutorialBullet.size.y, tutorialBullet.textureHandle, 0xFFFFFFFF);
		}
		else {
			Novice::DrawQuad(tutorialBullet.pos.x - tutorialBullet.radius.x, tutorialBullet.pos.y - tutorialBullet.radius.y,
				tutorialBullet.pos.x + tutorialBullet.radius.x, tutorialBullet.pos.y - tutorialBullet.radius.y,
				tutorialBullet.pos.x - tutorialBullet.radius.x, tutorialBullet.pos.y + tutorialBullet.radius.y,
				tutorialBullet.pos.x + tutorialBullet.radius.x, tutorialBullet.pos.y + tutorialBullet.radius.y,
				0, 0, tutorialBullet.size.x, tutorialBullet.size.y, tutorialBullet.textureHandle, 0xFFFFFFFF);

			Novice::DrawQuad(tutorialBullet.pos.x - tutorialBullet.radius.x, tutorialBullet.pos.y - tutorialBullet.radius.y - 64,
				tutorialBullet.pos.x + tutorialBullet.radius.x, tutorialBullet.pos.y - tutorialBullet.radius.y - 64,
				tutorialBullet.pos.x - tutorialBullet.radius.x, tutorialBullet.pos.y + tutorialBullet.radius.y - 64,
				tutorialBullet.pos.x + tutorialBullet.radius.x, tutorialBullet.pos.y + tutorialBullet.radius.y - 64,
				0, 0, explanation.size.x, explanation.size.y, explanation.textureHandle[explanation.textureHandleNumber], 0xFFFFFFFF);
		}
		if (tutorial13count == 0) {
			
			Novice::DrawBox(explanation.posision.x - (352 + pulsSize) / 2, explanation.posision.y - (32 + pulsSize) / 2, 352 + pulsSize, 32 + pulsSize, 0, 0x88888800 + explanation.transparency / 2, kFillModeSolid);

			Novice::DrawQuad(explanation.posision.x - 352 / 2, explanation.posision.y - 32 / 2,
				explanation.posision.x + 352 / 2, explanation.posision.y - 32 / 2,
				explanation.posision.x - 352 / 2, explanation.posision.y + 32 / 2,
				explanation.posision.x + 352 / 2, explanation.posision.y + 32 / 2,
				0, 0, 352, 32, explanation.textureHandle[1], 0xFFFFFF00 + explanation.transparency);

		}
	}

}