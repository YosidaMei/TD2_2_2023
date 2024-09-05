#include "Boss.h"
#include "math.h"

bool jumpOverConfirm = false;

void BossAttack(Player& player,Boss& boss, int cooltime, int attackWidth, int attackHeight) {

	if (boss.isAttack) {

		//攻撃用クールタイム
		boss.cooltime--;
		//四点消す
		if (boss.cooltime == 0) {
			boss.isAttack = false;
			boss.attackQuad.leftTop.x = -2000;
			boss.attackQuad.rightTop.x = -2000;
			boss.attackQuad.leftBottom.x = -2000;
			boss.attackQuad.rightBottom.x = -2000;
			boss.attackQuad.leftTop.y = -2000;
			boss.attackQuad.rightTop.y = -2000;
			boss.attackQuad.leftBottom.y = -2000;
			boss.attackQuad.rightBottom.y = -2000;
			//クールタイムがゼロになったら次の動作へ
		}

	}
	else {
		boss.isAttack = true;
		//攻撃四点作成

		StopAudio(bossAttack);
		PlayAudio(bossAttack);
		boss.attackQuad.leftTop.y = boss.pos.y - attackHeight / 2.0f;
		boss.attackQuad.rightTop.y = boss.pos.y - attackHeight / 2.0f;
		boss.attackQuad.leftBottom.y = boss.pos.y + attackHeight / 2.0f;
		boss.attackQuad.rightBottom.y = boss.pos.y + attackHeight / 2.0f;

		if (boss.isLeft) {
			boss.attackQuad.leftTop.x = boss.pos.x - boss.Radius - attackWidth;
			boss.attackQuad.rightTop.x = boss.pos.x - boss.Radius;
			boss.attackQuad.leftBottom.x = boss.pos.x - boss.Radius - attackWidth;
			boss.attackQuad.rightBottom.x = boss.pos.x - boss.Radius;
			//atari
			if (CollisionObjRect(player.quad, boss.attackQuad)) {//プレイヤー攻撃とボス１の判定
				player.Hp -= 1;
				PlayerDamageEffectSetting(player,WinWidth + 1);
			}

		}
		else {
			boss.attackQuad.leftTop.x = boss.pos.x + boss.Radius;
			boss.attackQuad.rightTop.x = boss.pos.x + boss.Radius + attackWidth;
			boss.attackQuad.leftBottom.x = boss.pos.x + boss.Radius;
			boss.attackQuad.rightBottom.x = boss.pos.x + boss.Radius + attackWidth;
			//atari
			if (CollisionObjRect(player.quad, boss.attackQuad)) {//プレイヤー攻撃とボス１の判定
				player.Hp -= 1;
				PlayerDamageEffectSetting(player, -1);
			}
		}

		boss.cooltime = cooltime;
		//atari
		//if (CollisionObjRect(player.quad, boss.attackQuad)) {//プレイヤー攻撃とボス１の判定
		//	player.Hp -= 1;
			//PlayerDamageEffectSetting(player, guidedBull.pos.x);
		//}

	}
}


void BossSteppingIn(Boss& boss, int map[MapHeight][MapWidth], float step,Player &player) {

	float tmp = 0;
	if (boss.isLeft) {
		boss.vel.x -= step;
	}
	else {
		boss.vel.x += step;
	}
	BossCheckMap(boss, map);
	if (player.pos.y > WinHeight - boss.Size - MapchipSize * 2 && boss.jumpedOver == false && jumpOverConfirm) {
		if (boss.isLeft) {
			if (boss.pos.x - boss.Radius < player.pos.x + player.Radius) {
				boss.numberInPattern++;
			}
		}
		else {
			if (boss.pos.x + boss.Radius > player.pos.x - player.Radius) {
				boss.numberInPattern++;
			}
		}
		tmp = boss.vel.x;
		boss.vel.x = 0;
		BossCheckMap(boss, map);
		boss.vel.x = tmp;
	}
	if (boss.isLeft) {
		if (boss.pos.x < boss.Radius) {
			boss.pos.x = boss.Radius;
		}
	}
	else {
		if (boss.pos.x > WinWidth - boss.Radius) {
			boss.pos.x = WinWidth - boss.Radius;
		}
	}
}

void BossAttackPattern(Boss& boss, int map[MapHeight][MapWidth], Player& player,Bullet& beam, Bullet& guidedBull, Bullet everyDirectionBullet[]) {




}

void BossAttackPattern1(Boss& boss, int map[MapHeight][MapWidth], Player& player, Bullet& guidedBull,char keys[]) {

	jumpOverConfirm = false;

	if (boss.isAttack) {
		BossAttack(player,boss, 0, 0, 0); 
	}
	else if(boss.cooltime > 0) {
		boss.cooltime--;
		BossJumpedOver(boss, player);
	}
	else {
		switch (boss.numberInPattern)
		{
		case 0:
			//プレイヤー側を向く
			if (player.pos.x <= boss.pos.x) {
				boss.isLeft = true;
			}
			else {
				boss.isLeft = false;
			}
			boss.numberInPattern++;
			break;
		case 1:
			//ため
			boss.cooltime = 30;
			BossChargeEffectSet(boss);
			boss.numberInPattern++;
			break;
		case 2:
			//踏み込み
			jumpOverConfirm = true;
			BossSteppingIn(boss, map, 8.0f,player);//とりあえず8
			if (boss.numberInPattern != 2) {
				break;
			}
			BossJumpedOver(boss, player);
			if (fabsf(boss.vel.x) > 32) {
				boss.numberInPattern++;
				boss.vel.x = 0;
				boss.jumpedOver = false;
			}
			break;
		case 3:
			//アタック
			BossAttack(player,boss, 10, boss.Size, boss.Size);//クールタイム10,48,48
			boss.numberInPattern++;
			break;
		case 4:
			//次の行動//プレイヤー側を向く
			if ((player.pos.x <= boss.pos.x && boss.isLeft) ||
				(player.pos.x > boss.pos.x && boss.isLeft == false)) {
				boss.numberInPattern++;
			}
			else {
				if (player.pos.x <= boss.pos.x) {
					boss.isLeft = true;
				}
				else {
					boss.isLeft = false;
				}
				boss.numberInPattern = 13;
			}

		case 5:
			//ため
			boss.cooltime = 30;
			BossChargeEffectSet(boss);
			boss.numberInPattern++;
			StopAudio(bossChage);
			PlayAudio(bossChage);
			break;
		case 6:
			//踏み込み
			jumpOverConfirm = true;
			BossSteppingIn(boss, map, 8.0f, player);//とりあえず8 
			if (boss.numberInPattern != 6) {
				break;
			}
			BossJumpedOver(boss, player);
			if (fabsf(boss.vel.x) > 32) {
				boss.numberInPattern++;
				boss.jumpedOver = false;
				boss.vel.x = 0;
			}
			break;
		case 7:
			//アタック
			BossAttack(player,boss, 10, boss.Size, boss.Size);//クールタイム10,48,48
			boss.numberInPattern++;
			break;
		case 8:
			//次の行動//プレイヤー側を向く
		if ((player.pos.x <= boss.pos.x && boss.isLeft) ||
				(player.pos.x > boss.pos.x && boss.isLeft == false)) {
				boss.numberInPattern++;
			}
			else {
				if (player.pos.x <= boss.pos.x) {
					boss.isLeft = true;
				}
				else {
					boss.isLeft = false;
				}
				boss.numberInPattern = 13;
			}
			break;
		case 9:
			BossSteppingIn(boss, map, -8.0f, player);//とりあえず8
			//ため長め
			boss.cooltime = 60;
			BossChargeEffectSet(boss);
			boss.numberInPattern++;
			StopAudio(bossChage);
			PlayAudio(bossChage);
			break;
		case 10:
			//踏み込み
			jumpOverConfirm = true;
			BossSteppingIn(boss, map, 8.0f, player);//とりあえず8
			if (boss.numberInPattern != 10) {
				break;
			}
			BossJumpedOver(boss, player);
			if (fabsf(boss.vel.x) > 80) {
				boss.numberInPattern++;
				boss.jumpedOver = false;
				boss.vel.x = 0;
			}
			break;
		case 11:
			//アタック
			BossAttack(player,boss, 10, boss.Size, boss.Size);//クールタイム10,48,48
			boss.numberInPattern++;
			break;
		case 13:
			//ため
			boss.cooltime = 30;
			BossChargeEffectSet(boss);
			boss.numberInPattern++;
			StopAudio(bossChage);
			PlayAudio(bossChage);
			break;
		case 14:
			//踏み込み
			jumpOverConfirm = true;
			BossSteppingIn(boss, map, 8.0f, player);//とりあえず8
			if (boss.numberInPattern != 14) {
				break;
			}
			BossJumpedOver(boss, player);
			if (fabsf(boss.vel.x) > 16) {
				boss.numberInPattern++;
				boss.jumpedOver = false;
				boss.vel.x = 0;
			}
			break;
		case 15:
			//アタック
			BossAttack(player,boss, 10, boss.Size, boss.Size);//クールタイム10,48,48
			boss.numberInPattern++;
			break;
		case 16:
			//クールタイム
			boss.cooltime = 40;
			boss.numberInPattern++;
			break;
			//17,18,19削除検討中
		case 17:
			//投剣//修正途中
			//BossGuidedBullet(guidedBull, boss, player, keys);//敵の誘導弾
			boss.numberInPattern++;
			break;
		case 18:
			//踏み込み
			BossSteppingIn(boss, map, -8.0f, player);//とりあえず8
			if (fabsf(boss.vel.x) > 56) {
				boss.numberInPattern++;
				boss.jumpedOver = false;
				boss.vel.x = 0;
			}
			break;
		default:
			//行動終了
			boss.numberInPattern = 0;
			boss.cooltime = 180;

			boss.isActionEnd = true;

			break;
		}

	}

}

void BossAttackPattern2(Boss& boss, int map[MapHeight][MapWidth], Player& player) {


	jumpOverConfirm = false;

	if (boss.isAttack) {
		BossAttack(player,boss, 0, 0, 0);
	}
	else if (boss.cooltime > 0) {
		boss.cooltime--;		
		if (boss.numberInPattern == 2 && boss.cooltime > 0 && boss.cooltime < 40 &&
			fabsf(player.pos.x - boss.pos.x) < 200) {//200ピクセル以内
			BossChargeEffectDelete();
			boss.numberInPattern = 5;
			boss.cooltime = 0;
		}
		BossJumpedOver(boss, player);
	}
	else {
		switch (boss.numberInPattern)
		{
		case 0:
			//プレイヤー側を向く
			if (player.pos.x <= boss.pos.x) {
				boss.isLeft = true;
			}
			else {
				boss.isLeft = false;
			}
			boss.numberInPattern++;
			break;
		case 1:
			//ため
			boss.cooltime = 60;
			BossChargeEffectSet(boss);
			boss.numberInPattern++;
			StopAudio(bossChage);
			PlayAudio(bossChage);
			break;
		case 2:
			//踏み込み
			jumpOverConfirm = true;
			BossSteppingIn(boss, map, 8.0f, player);//とりあえず8
			if (boss.numberInPattern != 2) {
				break;
			}
			BossJumpedOver(boss, player);
			if (fabsf(boss.vel.x) > 80) {
				boss.numberInPattern++;
				boss.jumpedOver = false;
				boss.vel.x = 0;
			}
			break;
		case 3:
			//アタック
			BossAttack(player,boss, 10, boss.Size, boss.Size);//クールタイム10,48,48
			boss.numberInPattern = 99;;
			break;
		case 5:
			//踏み込み
			jumpOverConfirm = true;
			BossSteppingIn(boss, map, 8.0f, player);//とりあえず8
			if (boss.numberInPattern != 5) {
				break;
			}
			BossJumpedOver(boss, player);
			if (fabsf(boss.vel.x) > 24) {
				boss.numberInPattern++;
				boss.jumpedOver = false;
				boss.vel.x = 0;
			}
			break;
		case 6:
			//アタック
			BossAttack(player,boss, 10, boss.Size, boss.Size);//クールタイム10,48,48
			boss.numberInPattern = 99;
			break;
		default:
			//行動終了
			boss.numberInPattern = 0;
			boss.cooltime = 180;

			boss.isActionEnd = true;
			break;
		}
	}

}

void BossJumpedOver(Boss& boss, Player& player) {

	if (!((player.pos.x <= boss.pos.x && boss.isLeft) ||
		(player.pos.x > boss.pos.x && boss.isLeft == false))) {
		boss.jumpedOver = true;
	}
	else {
		boss.jumpedOver = false;
	}

}

void DrawAttackBoss(Boss &boss) {

	int t = Novice::LoadTexture("white1x1.png");

	Novice::DrawQuad(boss.attackQuad.leftTop.x, boss.attackQuad.leftTop.y,
		boss.attackQuad.rightTop.x, boss.attackQuad.rightTop.y,
		boss.attackQuad.leftBottom.x, boss.attackQuad.leftBottom.y,
		boss.attackQuad.rightBottom.x, boss.attackQuad.rightBottom.y,
		0, 0, 1, 1, t, 0x06DDDDFF);
}