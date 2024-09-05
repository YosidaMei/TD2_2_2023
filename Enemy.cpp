#include "Enemy.h"

//player設定
void EnemySetting(Enemy& enemy) {

	enemy.acc.x = 0;
	enemy.acc.y = Gravity;
	enemy.posTmp.x = 0;
	enemy.posTmp.y = 0;
	enemy.pos.x = 1100;
	enemy.pos.y = -enemy.Radius;
	enemy.vel.x = 0;
	enemy.vel.y = enemy.acc.y;

	enemy.isLeft = false;
	enemy.isRise = false;
	enemy.isAlive = true;
	enemy.isGround = false;
	enemy.isJumping = false;
	enemy.is2jump = false;
	enemy.isAttack = false;
	enemy.Hp = 10;
	enemy.gauge = enemy.GaugeMax;
	enemy.textureHandle[0] = Novice::LoadTexture("./Resouce/Texture/preBoss1_2.png");

	enemy.quad = {};
	enemy.hitQuad = {};

	enemy.transparency = 0xFF;//透明度
}

#include "Bullet.h"

void EnemyQuad(Enemy& boss) {

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


//enemy描画
void DrawEnemy(Enemy &enemy, Vector2& shake) {
	//HPバー
	if (enemy.Hp > 0) {
	Novice::DrawBox(115, 685, 1006, 21, 0.0f, 0xE5E4E3FF, kFillModeSolid);
	Novice::DrawBox(118, 688, 100 * enemy.Hp, 15, 0.0f, 0x00C4A3FF, kFillModeSolid);
	}
	else if (enemy.Hp <= 0) {
		if (enemy.transparency < 0xAA) {
			enemy.transparency -= 0x02;
		}
		else {
			enemy.transparency -= 0x01;
		}
		if (enemy.transparency <= 0x00) {
			enemy.transparency = 0x00;
		}
	}

	Novice::DrawQuad(enemy.pos.x - enemy.Radius + shake.x, enemy.pos.y - enemy.Radius + shake.y,
		enemy.pos.x + enemy.Radius + shake.x, enemy.pos.y - enemy.Radius + shake.y,
		enemy.pos.x - enemy.Radius + shake.x, enemy.pos.y + enemy.Radius + shake.y,
		enemy.pos.x + enemy.Radius + shake.x, enemy.pos.y + enemy.Radius + shake.y,
		enemy.Size * enemy.animationNumber, 0, enemy.Size, enemy.Size, enemy.textureHandle[enemy.textureHandleNumber], 0xFFFFFF00 + enemy.transparency);
	
}

void EnemyHitBoxQuad(Enemy& boss) {

	//左上
	boss.hitQuad.leftTop.x = WinWidth - boss.Size;
	boss.hitQuad.leftTop.y = 0;
	//右上
	boss.hitQuad.rightTop.x = WinWidth;
	boss.hitQuad.rightTop.y = 0;
	//左下
	boss.hitQuad.leftBottom.x = WinWidth - boss.Size;
	boss.hitQuad.leftBottom.y = WinHeight;
	//右下
	boss.hitQuad.rightBottom.x = WinWidth;
	boss.hitQuad.rightBottom.y = WinHeight;

}

//当たり判定
void EnemyHitBox(Player& player, Enemy& enemy) {


	for (int i = 0; i < 5; i++) {

		if (CollisionObj(player.quad, enemy.hitQuad)) {//プレイヤーとボス１の当たり判定
			player.pos.x = enemy.hitQuad.leftTop.x - player.Radius;
		}

		if (CollisionObjRect(player.attack.quad, enemy.quad) && player.attack.isHit && enemy.isAlive) {//プレイヤー攻撃とボス１の判定
			enemy.Hp -= 1;
			player.attack.isHit = false;
			EnemyDamageEffectSetting(enemy,player.attack.Pos.y);
		}
	}
}

void EnemyAnimation(Enemy& enemy) {

	enemy.animationTime++;
	if (enemy.animationTime == enemy.AnimationTimeMax) {
		enemy.animationNumber++;
		enemy.animationTime = 0;
		if (enemy.animationNumber == enemy.AnimationNumberMax) {
			enemy.animationNumber = 0;
		}
	}

}

void EnemyDead(Enemy& enemy,Bullet beam, Bullet bullet[], Bullet& guidedBullet, Scene& scene) {

	if (enemy.Hp <= 0 && enemy.isAlive) {
		enemy.isAlive = false;
		beam.isAlive = false;
		EveryDirectionReset(bullet);
		GuidedBulletReset(guidedBullet);
		enemyChangeEffectRestartSetting();
		StopAudio(bossChange1);
		PlayAudio(bossChange1);
	}
	if (!enemy.isAlive) {
		EnemyChangeEffectSetting(enemy);
		EnemyChangeEffect(enemy,scene);
	}
}

bool EnemyMove(Enemy& enemy,float y) {
	
	enemy.acc.y = 1.0f;

	if (y < enemy.pos.y) {
		enemy.vel.y -= enemy.acc.y;
	}
	else {
		enemy.vel.y += enemy.acc.y;
	}

	enemy.pos.y += enemy.vel.y;

	if ((y <= enemy.pos.y && enemy.vel.y > 0) ||
		(y >= enemy.pos.y && enemy.vel.y < 0)) {
		enemy.pos.y = y;
		enemy.vel.y = 0;
		return true;
	}
	else {
		return false;
	}


}