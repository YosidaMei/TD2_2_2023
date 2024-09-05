#include <Novice.h>
#include "Common.h"
#include "Map.h"
#include "Player.h"
#include "Collision.h"


static int IsPressButton(int stickNo, PadButton button);

//player設定
void PlayerSetting(Player& player) {

	player.acc.x = 0;
	player.acc.y = Gravity;
	player.posTmp.x = 0;
	player.posTmp.y = 0;
	player.pos.x = 100;
	player.pos.y = 100;
	player.vel.x = 0;
	player.vel.y = player.acc.y;

	player.isLeft = false;
	player.isRise = false;
	player.isAlive = true;
	player.isGround = false;
	player.isJumping = false;
	player.is2jump = false;
	player.isAttack = false;
	player.Hp = 8;
	player.gauge = player.GaugeMax;
	player.textureHandle[0] = Novice::LoadTexture("./Resouce/Texture/prePlayerStand.png");
	player.textureHandle[1] = Novice::LoadTexture("./Resouce/Texture/prePlayerRun.png");
	player.textureHandle[2] = Novice::LoadTexture("./Resouce/Texture/prePlayerJump.png");
	player.textureHandleNumber = 0;

	player.attack.Pos.x = 0;
	player.attack.Pos.y = 0;
	player.attack.Radius.x = player.Radius + player.Radius / 2;
	player.attack.Radius.y = player.Radius + player.Radius / 2;
	player.attack.time = 0;
	player.attack.cooltime = 0;
	player.attack.timeMax = 10;
	player.attack.cooltimeMax = 15;
	player.attack.isLeft = true;
	player.attack.gaugeCost = 0;
	player.attack.textureHandle = Novice::LoadTexture("./Resouce/Texture/prePlayerEffectAttack.png");

	player.attack.quad.leftTop.x = -100;
	player.attack.quad.leftTop.y = -100;
	player.attack.quad.rightTop.x = -100;
	player.attack.quad.rightTop.y = -100;
	player.attack.quad.leftBottom.x = -100;
	player.attack.quad.leftBottom.y = -100;
	player.attack.quad.rightBottom.x = -100;
	player.attack.quad.rightBottom.y = -100;

	player.beam.Pos.x = 0;
	player.beam.Pos.y = 0;
	player.beam.Radius.x = player.Radius;
	player.beam.Radius.y = player.Radius;
	player.beam.time = 0;
	player.beam.cooltime = 0;
	player.beam.timeMax = 30;
	player.beam.cooltimeMax = 30;
	player.beam.isLeft = true;
	player.beam.gaugeCost = 0;

	player.gaugeRecoveryTime = 0;//ゲージ時間
	player.gaugeCooltime = 0;//ゲージクールタイム
	player.gaugeRecoveryTimeMax = 20;//ゲージ時間最大
	player.gaugeCooltimeMax = 180;//ゲージクールタイム最大

	player.animationNumber = 0;//アニメーション番号
	player.animationTime = 0;//アニメーションタイム
	player.AnimationNumberMax = 3;

}

//playerキー入力
void PlayerKeyInput(Player& player, int keyLeft, int keyRight, int stickDir) {

	if (keyLeft && keyRight == 0 || stickDir < 0) {
		player.isLeft = true;
		player.vel.x = -player.SpeedMax;
	}
	else if (keyRight && keyLeft == 0 || stickDir > 0) {
		player.isLeft = false;
		player.vel.x = player.SpeedMax;
	}
	else {
		player.vel.x = 0;
	}
}

//ジャンプや重力
void PlayerJamp(Player& player, int keyJamp, int preKeyJamp, int padJamp, int prePadJamp) {

	player.isLand = false;
	//上昇確認
	if (player.vel.y < 0) {
		player.isRise = true;
	}
	else {
		player.isRise = false;
	}
	//重力
	if (player.isGround == false) {
		player.vel.y += player.acc.y;
	}
	else {
		player.is2jump = false;
		if (player.vel.y != 0) {
			player.isLand = true;
		}
		player.vel.y = 0;
	}

	//ジャンプ
	if (keyJamp && preKeyJamp == 0 && player.isGround) {
		player.isJumping = true;
		player.vel.y = player.JumpPower;
		StopAudio(playerJump);
		PlayAudio(playerJump);
	}
	else if (padJamp && prePadJamp == 0 && player.isGround)
	{
		player.isJumping = true;
		player.vel.y = player.JumpPower;
		StopAudio(playerJump);
		PlayAudio(playerJump);

	}

	//小ジャンプ
	/*if (player.isJumping) {
		if (keyJamp == 0 && padJamp == 0) {
			player.isJumping = false;
			player.vel.y = 0;
		}
		if (player.vel.y > 0) {
			player.isJumping = false;
		}
	}*/
	//2段ジャンプ
	if (keyJamp && preKeyJamp == 0 && player.is2jump == false && player.isGround == false) {
		player.vel.y = player.JumpPower2;
		player.is2jump = true;
		StopAudio(playerJump);
		PlayAudio(playerJump);
	}
	else if (padJamp && prePadJamp == 0 && player.is2jump == false && player.isGround == false)
	{
		player.vel.y = player.JumpPower2;
		player.is2jump = true;
		StopAudio(playerJump);
		PlayAudio(playerJump);
	}



}

//playerの移動
void PlayerMove(Player& player, int map[MapHeight][MapWidth]) {

	//x座標
	//仮移動
	player.posTmp.x = player.pos.x + player.vel.x;
	player.posTmp.y = player.pos.y;
	if (player.isLeft) {
		//画面外確認
		if (player.posTmp.x <= player.Radius) {
			player.pos.x = player.Radius;
		}
		//通れる
		else if (CollisionMap(map, player.posTmp.x, player.posTmp.y, player.Radius, leftTop) == none &&
			CollisionMap(map, player.posTmp.x, player.posTmp.y, player.Radius, leftBottom) == none) {
			player.pos.x = player.posTmp.x;
		}
		//通れない
		else {
			player.pos.x = (int((player.posTmp.x - player.Radius) / MapchipSize) + 1) * MapchipSize + player.Radius;
		}
	}
	else {
		//画面外確認
		if (player.posTmp.x >= WinWidth - player.Radius) {
			player.pos.x = WinWidth - player.Radius;
		}
		//通れる
		else if (CollisionMap(map, player.posTmp.x, player.posTmp.y, player.Radius, rightTop) == none &&
			CollisionMap(map, player.posTmp.x, player.posTmp.y, player.Radius, rightBottom) == none) {
			player.pos.x = player.posTmp.x;
		}
		//通れない
		else {
			player.pos.x = int((player.posTmp.x + player.Radius - 1) / MapchipSize) * MapchipSize - player.Radius;
		}
	}

	//y座標
	//仮移動
	player.posTmp.x = player.pos.x;
	player.posTmp.y = player.pos.y + player.vel.y;
	if (player.isRise) {
		//画面外確認
		if (player.posTmp.y <= player.Radius) {
			player.pos.y = player.Radius;
		}
		//通れる
		else if (CollisionMap(map, player.posTmp.x, player.posTmp.y, player.Radius, leftTop) == none &&
			CollisionMap(map, player.posTmp.x, player.posTmp.y, player.Radius, rightTop) == none) {
			player.pos.y = player.posTmp.y;
		}
		//通れない
		else {
			player.pos.y = (int((player.posTmp.y - player.Radius) / MapchipSize) + 1) * MapchipSize + player.Radius;
			player.vel.y = 0;//頭ぶつけてるので速度0
		}
	}
	else {
		//画面外確認
		if (player.posTmp.y >= WinHeight - player.Radius) {
			player.pos.y = WinHeight - player.Radius;
		}
		//通れる
		else if (CollisionMap(map, player.posTmp.x, player.posTmp.y, player.Radius, leftBottom) == none &&
			CollisionMap(map, player.posTmp.x, player.posTmp.y, player.Radius, rightBottom) == none) {
			player.pos.y = player.posTmp.y;
		}
		//通れない
		else {
			player.pos.y = int((player.posTmp.y + player.Radius - 1) / MapchipSize) * MapchipSize - player.Radius;

		}
	}

	//地面確認
	if (CollisionMap(map, player.posTmp.x, player.posTmp.y + 1, player.Radius, leftBottom) == none &&
		CollisionMap(map, player.posTmp.x, player.posTmp.y + 1, player.Radius, rightBottom) == none) {
		player.isGround = false;
	}
	else {
		player.isGround = true;
	}


}

void PlayerQuad(Player& player) {
	//左上
	player.quad.leftTop.x = player.pos.x - player.Radius;
	player.quad.leftTop.y = player.pos.y - player.Radius;
	//右上
	player.quad.rightTop.x = player.pos.x + player.Radius;
	player.quad.rightTop.y = player.pos.y - player.Radius;
	//左下
	player.quad.leftBottom.x = player.pos.x - player.Radius;
	player.quad.leftBottom.y = player.pos.y + player.Radius;
	//右下
	player.quad.rightBottom.x = player.pos.x + player.Radius;
	player.quad.rightBottom.y = player.pos.y + player.Radius;

}

//player攻撃
void PlayerAttack(Player& player, int keyAttack, int preKeyAttack, int padAttack, int prePadAttack, int map[MapHeight][MapWidth]) {

	//キーが押されたか
	if (keyAttack && preKeyAttack == 0 && player.isAttack == false && player.attack.cooltime == 0 && player.gauge > 0) {
		player.isAttack = true;
		player.attack.isHit = true;
		player.attack.time = player.attack.timeMax;
		player.attack.isLeft = player.isLeft;
		//PlayerBeamKeyInput(player);
		player.gauge -= player.attack.gaugeCost;
		if (player.gauge < 0) {
			player.gauge = 0;
		}
		StopAudio(playerAttack);
		PlayAudio(playerAttack);
	}
	else if (padAttack && prePadAttack == 0 && player.isAttack == false && player.attack.cooltime == 0 && player.gauge > 0) {
		player.isAttack = true;
		player.attack.isHit = true;
		player.attack.time = player.attack.timeMax;
		player.attack.isLeft = player.isLeft;
		//PlayerBeamKeyInput(player);
		player.gauge -= player.attack.gaugeCost;
		if (player.gauge < 0) {
			player.gauge = 0;
		}
		StopAudio(playerAttack);
		PlayAudio(playerAttack);
	}

	//攻撃中処理
	if (player.isAttack) {
		//向き
		if (player.attack.isLeft) {
			player.attack.Pos.x = player.pos.x - player.Radius - player.attack.Radius.x;
		}
		else {
			player.attack.Pos.x = player.pos.x + player.Radius + player.attack.Radius.x;
		}
		player.attack.Pos.y = player.pos.y;
		
		player.vel.y = 0;   //空中攻撃中に落下しなくなる
		
		player.attack.quad.leftTop.x = player.attack.Pos.x - player.attack.Radius.x;
		player.attack.quad.leftTop.y = player.attack.Pos.y - player.attack.Radius.y;
		player.attack.quad.rightTop.x = player.attack.Pos.x + player.attack.Radius.x;
		player.attack.quad.rightTop.y = player.attack.Pos.y - player.attack.Radius.y;
		player.attack.quad.leftBottom.x = player.attack.Pos.x - player.attack.Radius.x;
		player.attack.quad.leftBottom.y = player.attack.Pos.y + player.attack.Radius.y;
		player.attack.quad.rightBottom.x = player.attack.Pos.x + player.attack.Radius.x;
		player.attack.quad.rightBottom.y = player.attack.Pos.y + player.attack.Radius.y;

		//タイム
		if (player.attack.time == 0) {
			player.isAttack = false;
			player.attack.cooltime = player.attack.cooltimeMax;
		}
		else {
			player.attack.time--;
		}
	}
	else {
		player.attack.Pos.x = -100;
		player.attack.Pos.x = -100;
		player.attack.quad.leftTop.x = -100;
		player.attack.quad.leftTop.y = -100;
		player.attack.quad.rightTop.x = -100;
		player.attack.quad.rightTop.y = -100;
		player.attack.quad.leftBottom.x = -100;
		player.attack.quad.leftBottom.y = -100;
		player.attack.quad.rightBottom.x = -100;
		player.attack.quad.rightBottom.y = -100;
	}
	//クールタイム
	if (player.attack.cooltime != 0) {
		player.attack.cooltime--;
	}
	//ビーム
	//PlayerBeamMove(player,map);

}


void PlayerAnimation(Player& player) {

	//Jump
	if (!player.isGround) {
		if (player.textureHandleNumber != 2) {
			player.textureHandleNumber = 2;
			player.AnimationNumberMax = 1;
			player.animationTime = 0;
			player.animationNumber = 0;
		}
	}
	//Stand
	else if (player.vel.x == 0) {
		if (player.textureHandleNumber != 0) {
			player.textureHandleNumber = 0;
			player.AnimationNumberMax = 5;
			player.animationTime = 0;
			player.animationNumber = 0;
		}
	}
	//Run
	else if (player.vel.x != 0) {
		if (player.textureHandleNumber != 1) {
			player.textureHandleNumber = 1;
			player.AnimationNumberMax = 9;
			player.animationTime = 0;
			player.animationNumber = 0;
		}
	}

	player.animationTime++;
	if (player.animationTime == player.AnimationTimeMax) {
		player.animationNumber++;
		player.animationTime = 0;
		if (player.animationNumber == player.AnimationNumberMax) {
			player.animationNumber = 0;
		}
	}

}

void PlayerAfterimage(Player& player) {

	int i = 0;
	int max = 5;
	for (i = 0; i < max - 1; i++) {
		player.afterimage[i].quad = player.afterimage[i + 1].quad;
		player.afterimage[i].animationNumber = player.afterimage[i + 1].animationNumber;
		player.afterimage[i].textureHandleNumber = player.afterimage[i + 1].textureHandleNumber;
		player.afterimage[i].isLeft = player.afterimage[i + 1].isLeft;

	}
	if (player.vel.x != 0 || player.vel.y != 0) {
		player.afterimage[max - 1].quad = player.quad;
		player.afterimage[max - 1].animationNumber = player.animationNumber;
		player.afterimage[max - 1].textureHandleNumber = player.textureHandleNumber;
		player.afterimage[max - 1].isLeft = player.isLeft;
	}
	else {
		player.afterimage[max - 1].quad = { 0 };
		player.afterimage[max - 1].animationNumber = player.animationNumber;
		player.afterimage[max - 1].textureHandleNumber = player.textureHandleNumber;
		player.afterimage[max - 1].isLeft = player.isLeft;
	}
}

//playerゲージ
void PlayerGauge(Player& player) {

	if (player.gauge == 0) {
		player.gaugeCooltime++;
		if (player.gaugeCooltime == player.gaugeCooltimeMax) {
			player.gaugeCooltime = 0;
			player.gauge++;
		}
	}
	else if (player.gauge < player.GaugeMax) {
		player.gaugeRecoveryTime++;
		if (player.gaugeRecoveryTime == player.gaugeRecoveryTimeMax) {
			player.gaugeRecoveryTime = 0;
			player.gauge++;
		}
	}

}

//player描画
void DrawPlayer(Player player, Vector2& shake) {

	if (player.isLeft) {
		Novice::DrawQuad(
			player.quad.rightTop.x + shake.x, player.quad.rightTop.y + shake.y,
			player.quad.leftTop.x + shake.x, player.quad.leftTop.y + shake.y,
			player.quad.rightBottom.x + shake.x, player.quad.rightBottom.y + shake.y,
			player.quad.leftBottom.x + shake.x, player.quad.leftBottom.y + shake.y,
			player.Size * player.animationNumber, 0, player.Size, player.Size, player.textureHandle[player.textureHandleNumber], 0xFFFFFFFF);
	}
	else {
		Novice::DrawQuad(player.quad.leftTop.x + shake.x, player.quad.leftTop.y + shake.y,
			player.quad.rightTop.x + shake.x, player.quad.rightTop.y + shake.y,
			player.quad.leftBottom.x + shake.x, player.quad.leftBottom.y + shake.y,
			player.quad.rightBottom.x + shake.x, player.quad.rightBottom.y + shake.y,
			player.Size * player.animationNumber, 0, player.Size, player.Size, player.textureHandle[player.textureHandleNumber], 0xFFFFFFFF);
	}

	int i = 0;
	int max = 5;
	for (i = 0; i < max; i++) {
		if (player.afterimage[i].isLeft) {
			Novice::DrawQuad(player.afterimage[i].quad.rightTop.x + shake.x, player.afterimage[i].quad.rightTop.y + shake.y,
				player.afterimage[i].quad.leftTop.x + shake.x, player.afterimage[i].quad.leftTop.y + shake.y,
				player.afterimage[i].quad.rightBottom.x + shake.x, player.afterimage[i].quad.rightBottom.y + shake.y,
				player.afterimage[i].quad.leftBottom.x + shake.x, player.afterimage[i].quad.leftBottom.y + shake.y,
				player.Size * player.afterimage[i].animationNumber, 0, player.Size, player.Size, player.textureHandle[player.afterimage[i].textureHandleNumber], 0xFFFFFF00 + 0x19 * (i + 1));

		}
		else {
			Novice::DrawQuad(player.afterimage[i].quad.leftTop.x + shake.x, player.afterimage[i].quad.leftTop.y + shake.y,
				player.afterimage[i].quad.rightTop.x + shake.x, player.afterimage[i].quad.rightTop.y + shake.y,
				player.afterimage[i].quad.leftBottom.x + shake.x, player.afterimage[i].quad.leftBottom.y + shake.y,
				player.afterimage[i].quad.rightBottom.x + shake.x, player.afterimage[i].quad.rightBottom.y + shake.y,
				player.Size * player.afterimage[i].animationNumber, 0, player.Size, player.Size, player.textureHandle[player.afterimage[i].textureHandleNumber], 0xFFFFFF00 + 0x19 * (i + 1));

		}

	}

	/*
	Novice::DrawBox(40, 40, 400, 100, 0, 0x00000088, kFillModeSolid);
	Novice::ScreenPrintf(40, 40, "player.isLeft %d", player.isLeft);
	Novice::ScreenPrintf(40, 60, "player.attack.time %d", player.attack.time);
	Novice::ScreenPrintf(40, 80, "player.attack.cooltime %d", player.attack.cooltime);
	Novice::ScreenPrintf(40, 100, "Move: LeftKey,RightKey   Jamp: Z   Attack: X");

	Novice::ScreenPrintf(40, 120, "player.gauge %d", player.gauge);
	Novice::ScreenPrintf(180, 40, "player.HP %d", player.Hp);
	*/

}

//HP
void HpSetting(Hp* hp) {
	hp[0].pos.x = 120;
	hp[0].pos.y = 50;
	hp[0].AnimationNumberMax = 4;
	hp[0].animationNumber = 0;
	hp[0].textureHandle = Novice::LoadTexture("./Resouce/Texture/playerHp.png");
	hp[1].pos.x = 50;
	hp[1].pos.y = 50;
	hp[1].AnimationNumberMax = 4;
	hp[1].animationNumber = 0;
}


void HpQuad(Hp* hp, Player& player) {
	for (int i = 0; i < 2; i++) {

	//左上
	hp[i].quad.leftTop.x = hp[i].pos.x - hp[i].Radius;
	hp[i].quad.leftTop.y = hp[i].pos.y - hp[i].Radius;
	//右上
	hp[i].quad.rightTop.x = hp[i].pos.x + hp[i].Radius;
	hp[i].quad.rightTop.y = hp[i].pos.y - hp[i].Radius;
	//左下
	hp[i].quad.leftBottom.x = hp[i].pos.x - hp[i].Radius;
	hp[i].quad.leftBottom.y = hp[i].pos.y + hp[i] .Radius;
	//右下
	hp[i].quad.rightBottom.x = hp[i].pos.x + hp[i].Radius;
	hp[i].quad.rightBottom.y = hp[i].pos.y + hp[i].Radius;

	}

	if (player.Hp == 8) {
		hp[0].animationNumber = 0;
	}
	else if (player.Hp == 7) {
		hp[0].animationNumber = 1;
	}
	else if (player.Hp == 6) {
		hp[0].animationNumber = 2;
	}
	else if (player.Hp == 5) {
		hp[0].animationNumber = 3;
	}
	if (player.Hp == 4) {
		hp[1].animationNumber = 0;
	}
	else if (player.Hp == 3) {
		hp[1].animationNumber = 1;
	}
	else if (player.Hp == 2) {
		hp[1].animationNumber = 2;
	}
	else if (player.Hp == 1) {
		hp[1].animationNumber = 3;
	}
}
void DrawHp(Hp* hp, Player& player, Vector2& shake) {
	if (player.Hp > 4) {
		Novice::DrawQuad(
			hp[0].quad.leftTop.x + shake.x, hp[0].quad.leftTop.y + shake.y,
			hp[0].quad.rightTop.x + shake.x, hp[0].quad.rightTop.y + shake.y,
			hp[0].quad.leftBottom.x + shake.x, hp[0].quad.leftBottom.y + shake.y,
			hp[0].quad.rightBottom.x + shake.x, hp[0].quad.rightBottom.y + shake.y,
			hp[0].Size * hp[0].animationNumber, 0, hp[0].Size, hp[0].Size, hp[0].textureHandle, 0xFFFFFFFF);
	}
	if (player.Hp > 0) {
		Novice::DrawQuad(
			hp[1].quad.leftTop.x + shake.x, hp[1].quad.leftTop.y + shake.y,
			hp[1].quad.rightTop.x + shake.x, hp[1].quad.rightTop.y + shake.y,
			hp[1].quad.leftBottom.x + shake.x, hp[1].quad.leftBottom.y + shake.y,
			hp[1].quad.rightBottom.x + shake.x, hp[1].quad.rightBottom.y + shake.y,
			hp[0].Size * hp[1].animationNumber, 0, hp[0].Size, hp[0].Size, hp[0].textureHandle, 0xFFFFFFFF);
	}
}

void DrawPlayerUi(int textureHandle) {
	Novice::DrawSprite(20, 100, textureHandle, 0.7f, 0.7f, 0.0f, 0xFFFFFFFF);
}

void PlayerAudio(Player &player) {

	if (player.isGround && player.vel.x != 0) {
		PlayAudio(playerMove);
	}
	else {
		StopAudio(playerMove);
	}
}