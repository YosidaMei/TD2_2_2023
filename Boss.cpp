#include "Boss.h"

//ボス初期設定
void BossSetting(Boss& boss) {

	boss.acc = { 0,Gravity };//加速度
	boss.posTmp = {};//仮の位置
	boss.pos = { 1000,600 };//位置
	boss.vel = {};//速度
	boss.isLeft = true;//向き
	boss.isRise = false;//上昇している
	boss.isAlive = true;//生きてるか
	boss.isGround = false;//着地しているか
	boss.isJumping = false;//ジャンプしているか
	boss.is2jump = false;//２段ジャンプしているか
	boss.isAttack = false;//攻撃してるか
	boss.Hp = 300;//体力
	boss.gauge = 0;//ゲージ
	boss.gaugeRecoveryTime = 0;//ゲージ時間
	boss.gaugeCooltime = 0;//ゲージクールタイム
	boss.gaugeRecoveryTimeMax = 0;//ゲージ時間最大
	boss.gaugeCooltimeMax = 0;//ゲージクールタイム最大
	//boss.textureHandle = Novice::LoadTexture("./Resouce/Texture/preBoss2.png");
	boss.textureHandle[0] = Novice::LoadTexture("./Resouce/Texture/preBoss2_2.png");//テクスチャハンドル
	boss.textureHandle[1] = Novice::LoadTexture("./Resouce/Texture/preBossLeft.png");
	boss.textureHandle[2] = Novice::LoadTexture("./Resouce/Texture/preBossRight.png");
	boss.textureHandle[3] = Novice::LoadTexture("./Resouce/Texture/preBossTame.png");
	boss.textureHandleNumber = 0;

	boss.attack.textureHandle = Novice::LoadTexture("./Resouce/Texture/prePlayerEffectAttack.png");
	boss.attack.Pos.x = -100;
	boss.attack.Pos.y = -100;

	boss.animationNumber = 0;//アニメーション番号
	boss.animationTime = 0;//アニメーションタイム
	boss.AnimationNumberMax = 3;

	boss.quad = {};
	boss.attackQuad = {};

	boss.numberInPattern = 0;
	boss.numberInPatternMax = 0;
	boss.jumpedOver = false;

	boss.isAction = false;
}

//ボス関数まとめ
void BossFunction(Boss& boss, Player& player, int map[MapHeight][MapWidth]) {

	if (boss.cooltime == 0) {
		BossWalk(boss, player, map);
	}
	else {
		BossCooltime(boss.cooltime);
	}

	BossGravity(boss);

}

void BossCooltime(int& cooltime) {

	cooltime--;

}

void BossQuad(Boss& boss) {

	//左上
	boss.quad.leftTop.x = boss.pos.x - boss.Radius;
	boss.quad.leftTop.y = boss.pos.y - boss.Radius;
	//右上
	boss.quad.rightTop.x = boss.pos.x + boss.Radius;
	boss.quad.rightTop.y = boss.pos.y - boss.Radius;
	//左下
	boss.quad.leftBottom.x = boss.pos.x - boss.Radius;
	boss.quad.leftBottom.y = boss.pos.y + boss.Radius;
	//右下
	boss.quad.rightBottom.x = boss.pos.x + boss.Radius;
	boss.quad.rightBottom.y = boss.pos.y + boss.Radius;

}

void BossAnimation(Boss& boss) {

	//Stand
	if (boss.vel.x == 0) {
		if (boss.textureHandleNumber != 0) {
			boss.textureHandleNumber = 0;
			boss.AnimationNumberMax = 4;
			boss.animationTime = 0;
			boss.animationNumber = 0;
		}
		//溜め
		if (boss.cooltime >= 0 && boss.cooltime <= 30) {
			if (boss.textureHandleNumber != 3) {
				boss.textureHandleNumber = 3;
				boss.AnimationNumberMax = 5;
				boss.animationTime = 0;
				boss.animationNumber = 0;
			}
		}
	}
	//Front
	else if (boss.vel.x != 0 && boss.isLeft) {
		if (boss.textureHandleNumber != 1) {
			boss.textureHandleNumber = 1;
			boss.AnimationNumberMax = 4;
			boss.animationTime = 0;
			boss.animationNumber = 0;
		}
	}
	//Back
	else if (boss.vel.x != 0 && boss.isLeft) {
		if (boss.textureHandleNumber != 2) {
			boss.textureHandleNumber = 2;
			boss.AnimationNumberMax = 4;
			boss.animationTime = 0;
			boss.animationNumber = 0;
		}
	}

	boss.animationTime++;
	if (boss.animationTime == boss.AnimationTimeMax) {
		boss.animationNumber++;
		boss.animationTime = 0;
		if (boss.animationNumber == boss.AnimationNumberMax) {
			boss.animationNumber = 0;
		}
	}

}

void BossAfterimage(Boss& boss) {

	int i = 0;
	int max = 5;
	for (i = 0; i < max - 1; i++) {
		boss.afterimage[i].quad = boss.afterimage[i + 1].quad;
		boss.afterimage[i].animationNumber = boss.afterimage[i + 1].animationNumber;
		boss.afterimage[i].textureHandleNumber = boss.afterimage[i + 1].textureHandleNumber;
		boss.afterimage[i].isLeft = boss.afterimage[i + 1].isLeft;

	}
	if (boss.vel.x != 0) {
		boss.afterimage[max - 1].quad = boss.quad;
		boss.afterimage[max - 1].animationNumber = boss.animationNumber;
		boss.afterimage[max - 1].textureHandleNumber = boss.textureHandleNumber;
		boss.afterimage[max - 1].isLeft = boss.isLeft;
	}
	else {
		boss.afterimage[max - 1].quad = { 0 };
		boss.afterimage[max - 1].animationNumber = boss.animationNumber;
		boss.afterimage[max - 1].textureHandleNumber = boss.textureHandleNumber;
		boss.afterimage[max - 1].isLeft = boss.isLeft;
	}
}

//ボス描画
void DrawBoss(Boss& boss, Vector2& shake) {

	//HPバー
	if (boss.Hp > 0) {
		Novice::DrawBox(37, 685, 1206, 21, 0.0f, 0xE5E4E3FF, kFillModeSolid);
		if (boss.Hp > 100)
		{
			Novice::DrawBox(40, 688, 4 * boss.Hp, 15, 0.0f, 0x00C4A3FF, kFillModeSolid);
		}
		else
		{
			Novice::DrawBox(40, 688, 4 * boss.Hp, 15, 0.0f, 0xDC143CFF, kFillModeSolid);
		}
	}
	if (boss.isLeft) {
		Novice::DrawQuad(
			boss.quad.leftTop.x + shake.x, boss.quad.leftTop.y + shake.y,
			boss.quad.rightTop.x + shake.x, boss.quad.rightTop.y + shake.y,
			boss.quad.leftBottom.x + shake.x, boss.quad.leftBottom.y + shake.y,
			boss.quad.rightBottom.x + shake.x, boss.quad.rightBottom.y + shake.y,
			boss.Size * boss.animationNumber, 0, boss.Size, boss.Size, boss.textureHandle[boss.textureHandleNumber], 0xFFFFFFFF);
	}
	else {
		Novice::DrawQuad(boss.quad.rightTop.x + shake.x, boss.quad.rightTop.y + shake.y,
			boss.quad.leftTop.x + shake.x, boss.quad.leftTop.y + shake.y,
			boss.quad.rightBottom.x + shake.x, boss.quad.rightBottom.y + shake.y,
			boss.quad.leftBottom.x + shake.x, boss.quad.leftBottom.y + shake.y,
			boss.Size * boss.animationNumber, 0, boss.Size, boss.Size, boss.textureHandle[boss.textureHandleNumber], 0xFFFFFFFF);
	}
	int i = 0;
	int max = 5;
	for (i = 0; i < max; i++) {
		if (boss.afterimage[i].isLeft) {
			Novice::DrawQuad(boss.afterimage[i].quad.leftTop.x + shake.x, boss.afterimage[i].quad.leftTop.y + shake.y,
				boss.afterimage[i].quad.rightTop.x + shake.x, boss.afterimage[i].quad.rightTop.y + shake.y,
				boss.afterimage[i].quad.leftBottom.x + shake.x, boss.afterimage[i].quad.leftBottom.y + shake.y,
				boss.afterimage[i].quad.rightBottom.x + shake.x, boss.afterimage[i].quad.rightBottom.y + shake.y,
				boss.Size * boss.afterimage[i].animationNumber, 0, boss.Size, boss.Size, boss.textureHandle[boss.afterimage[i].textureHandleNumber], 0xFFFFFF00 + 0x19 * (i + 1));

		}
		else {
			Novice::DrawQuad(boss.afterimage[i].quad.rightTop.x + shake.x, boss.afterimage[i].quad.rightTop.y + shake.y,
				boss.afterimage[i].quad.leftTop.x + shake.x, boss.afterimage[i].quad.leftTop.y + shake.y,
				boss.afterimage[i].quad.rightBottom.x + shake.x, boss.afterimage[i].quad.rightBottom.y + shake.y,
				boss.afterimage[i].quad.leftBottom.x + shake.x, boss.afterimage[i].quad.leftBottom.y + shake.y,
				boss.Size * boss.afterimage[i].animationNumber, 0, boss.Size, boss.Size, boss.textureHandle[boss.afterimage[i].textureHandleNumber], 0xFFFFFF00 + 0x19 * (i + 1));

		}

	}

}



//当たり判定
void BossHitBox(Player& player, Boss& boss) {

	if (CollisionObjRect(player.attack.quad, boss.quad) && player.attack.isHit) {//プレイヤー攻撃とボス１の判定
		boss.Hp -= 20;
		player.attack.isHit = false;
		BossDamageEffectSetting(boss, player.pos.x);
	}
}

void BossDead(Boss& boss, Scene& scene) {

	if (boss.Hp <= 0 && boss.isAlive) {
		boss.isAlive = false;
		BossDeadEffectSetting(boss);
	}
	if (!boss.isAlive) {
		//死亡演出
		BossDeadEffect(boss, scene);

	}
}

void BossPositionClamp(Boss& boss) {

	if (boss.pos.x < boss.Radius) {
		boss.pos.x = boss.Radius;
	}
	if (boss.pos.x > WinWidth - boss.Radius) {
		boss.pos.x = WinWidth - boss.Radius;
	}

}