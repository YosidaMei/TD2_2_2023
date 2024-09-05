#include"Boss.h"

//ビームの範囲
int BossExtent = 3;
int BossCount = 0;
bool isBossMax = false;

//count
int hitCount = 0;

void BossBeamSet(Bullet& beam, Boss& boss, Player& player) {
	beam.isAlive = false;
	beam.pos = boss.pos;
	beam.Radius = 1;
	beam.vel.x = 10;
	BossExtent = 3;
	BossCount = 0;
	hitCount = 0;
	isBossMax = false;
	if (beam.isHit)
	{
		beam.isHit = false;
	}
}
void BossBeamRight(Bullet& beam, Boss& boss, Player& player) {

	beam.quad.leftTop.x = beam.pos.x - beam.Radius;
	beam.quad.leftTop.y = beam.pos.y - beam.Radius;
	beam.quad.leftBottom.x = beam.pos.x - beam.Radius;
	beam.quad.leftBottom.y = beam.pos.y + beam.Radius;
	beam.quad.rightTop.x = boss.pos.x - boss.Radius;
	beam.quad.rightTop.y = boss.pos.y - beam.Radius;
	beam.quad.rightBottom.x = boss.pos.x - boss.Radius;
	beam.quad.rightBottom.y = boss.pos.y + beam.Radius;

	//ビームが出てる
	if (beam.isAlive)
	{
		//ビームが画面端に届いていない時
		if (beam.pos.x > 0)
		{
			beam.pos.x -= beam.vel.x;
			beam.vel.x += 10;
		}
		//ビームが画面端に届いた時
		else
		{
			if (!isBossMax) {
				BossCount++;
				if (BossCount >= 30)
				{
					//ビームの太さを変える
					beam.Radius += BossExtent;
				}
				//ビームが一定の大きさになった時
				if (beam.Radius >= 35)
				{
					BossCount = 30;
					isBossMax = true;
				}
			}
			else {

				beam.isHit = CollisionObjRect(player.quad, beam.quad);

				BossCount--;
				if (BossCount <= 0)
				{
					//ビームの太さを変える
					beam.Radius -= BossExtent;
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
			hitCount--;
			if (hitCount <= 0)
			{
				PlayerDamageEffectSetting(player, boss.pos.x);
				beam.isHit = false;
				player.Hp -= 1;
				hitCount = 25;

			}
		}
	}
	else {
		beam.pos = boss.pos;
		beam.Radius = 1;
		beam.isAlive = true;
		BossExtent = 3;
		BossCount = 0;
		hitCount = 0;
		isBossMax = false;
		StopAudio(beanCharge);
		PlayAudio(beanCharge);
		if (beam.isHit)
		{
			beam.isHit = false;
		}
	}
}

void BossBeamLeft(Bullet& beam, Boss& boss, Player& player) {

	beam.quad.leftTop.x = boss.pos.x + boss.Radius;
	beam.quad.leftTop.y = boss.pos.y - beam.Radius;
	beam.quad.leftBottom.x = boss.pos.x + boss.Radius;
	beam.quad.leftBottom.y = boss.pos.y + beam.Radius;
	beam.quad.rightTop.x = beam.pos.x + beam.Radius;
	beam.quad.rightTop.y = beam.pos.y - beam.Radius;
	beam.quad.rightBottom.x = beam.pos.x + beam.Radius;
	beam.quad.rightBottom.y = beam.pos.y + beam.Radius;

	//ビームが出てる
	if (beam.isAlive)
	{
		//ビームが画面端に届いていない時
		if (beam.pos.x < 1280)
		{
			beam.pos.x += beam.vel.x;
			beam.vel.x += 10;
		
		}
		//ビームが画面端に届いた時
		else
		{
			if (!isBossMax) {
				BossCount++;
				if (BossCount >= 30)
				{
					//ビームの太さを変える
					beam.Radius += BossExtent;
				}
				//ビームが一定の大きさになった時
				if (beam.Radius >= 42)
				{
					BossCount = 30;
					isBossMax = true;
				}
			}
			else {

				beam.isHit = CollisionObjRect(player.quad, beam.quad);

				BossCount--;

				if (BossCount <= 0)
				{
					//ビームの太さを変える
					beam.Radius -= BossExtent;
					if (beam.Radius <= 0)
					{
						beam.isAlive = false;
					}
				}
			}
		}
		if (beam.isHit)
		{
			hitCount--;
			if (hitCount <= 0)
			{
				PlayerDamageEffectSetting(player, boss.pos.x);
				beam.isHit = false;
				player.Hp -= 1;
				hitCount = 25;

			}
		}
	}
	else {
		beam.pos = boss.pos;
		beam.Radius = 1;
		beam.isAlive = true;
		hitCount = 0;
		BossExtent = 3;
		BossCount = 0;
		isBossMax = false;
		StopAudio(beanCharge);
		PlayAudio(beanCharge);
		if (beam.isHit)
		{
			beam.isHit = false;
		}
	}
}

void DrawBossBeam(Bullet& beam, Boss& boss, Vector2& shake) {
	if (beam.isAlive)
	{
		Novice::DrawQuad(beam.quad.leftTop.x + shake.x, beam.quad.leftTop.y + shake.y,
			beam.quad.rightTop.x + shake.x, beam.quad.rightTop.y + shake.y,
			beam.quad.leftBottom.x + shake.x, beam.quad.leftBottom.y + shake.y,
			beam.quad.rightBottom.x + shake.x, beam.quad.rightBottom.y + shake.y,
			0, 0, beam.Size, beam.Size * 2, beam.textureHandle, 0xFFFFFFFF);
	}
	//Novice::ScreenPrintf(360, 120, "%d", hitCount);
}