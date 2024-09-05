#include"Enemy.h"

//ビームの範囲
int extent = 3;
int count = 0;
bool isMax = false;

//count
int enemyHitCount = 0;

void EnemyBeam(Bullet& beam, Enemy& enemy, Player& player) {

	beam.quad.leftTop.x = beam.pos.x - beam.Radius;
	beam.quad.leftTop.y = beam.pos.y - beam.Radius;
	beam.quad.leftBottom.x = beam.pos.x - beam.Radius;
	beam.quad.leftBottom.y = beam.pos.y + beam.Radius;
	beam.quad.rightTop.x = enemy.pos.x + beam.Radius;
	beam.quad.rightTop.y = beam.pos.y - beam.Radius;
	beam.quad.rightBottom.x = enemy.pos.x + beam.Radius;
	beam.quad.rightBottom.y = beam.pos.y + beam.Radius;

	//ビームが出てる
	if (beam.isAlive)
	{
		//ビームが画面端に届いていない時
		if (beam.pos.x > 0)
		{
			beam.pos.x -= 100;
		}
		//ビームが画面端に届いた時
		else
		{
			if (!isMax) {
				count++;
				if (count >= 45)
				{
					//ビームの太さを変える
					beam.Radius += extent;
				}
				if (count >= 30)
				{
					//ビームの太さを変える
					beam.Radius += extent;
				}
				//ビームが一定の大きさになった時
				if (beam.Radius >= 35)
				{
					count = 30;
					isMax = true;
				}
			}
			else {
				count--;
				
				beam.isHit = CollisionObjRect(player.quad, beam.quad);
				
				if (count <= 0)
				{
					//ビームの太さを変える
					beam.Radius -= extent;
					if (beam.Radius <= 0)
					{
						beam.isAlive = false;
						StopAudio(beanCharge);
					}
				}
			}
		}
		if (beam.isHit)
		{
			enemyHitCount--;
			if (enemyHitCount <= 0)
			{
				PlayerDamageEffectSetting(player, player.pos.x);
				beam.isHit = false;
				player.Hp -= 1;
				enemyHitCount = 25;

			}
		}
	}
	else {
		beam.Radius = 1;
		beam.pos.x = enemy.pos.x;
		beam.pos.y = enemy.pos.y + enemy.Radius - 65;
		beam.isAlive = true;
		extent = 3;
		count = 0;
		enemyHitCount = 0;
		isMax = false;
		if (beam.isHit)
		{
			beam.isHit = false;
		}
		StopAudio(beanCharge);
		PlayAudio(beanCharge);
	}
}

void DrawEnemyBeam(Bullet& beam, Enemy& enemy, Vector2& shake) {

	if (beam.isAlive) {
		Novice::DrawQuad(beam.quad.leftTop.x + shake.x, beam.quad.leftTop.y + shake.y,
			beam.quad.rightTop.x + shake.x, beam.quad.rightTop.y + shake.y,
			beam.quad.leftBottom.x + shake.x, beam.quad.leftBottom.y + shake.y,
			beam.quad.rightBottom.x + shake.x, beam.quad.rightBottom.y + shake.y,
			0, 0, beam.Size, beam.Size * 2, beam.textureHandle, 0xFFFFFFFF);
	}
	//Novice::ScreenPrintf(10,500,"%d",beam.isHit);
}