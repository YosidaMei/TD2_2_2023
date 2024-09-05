#include "Common.h"
#include "Enemy.h"
#include"Bullet.h"

//ビーム
const int BeamCooltime = 90;//ビームのクールタイム
const int BeamEndHp = 11;//ビームから誘導弾に切り替えるHp

//誘導弾
const int GuidedBullCooltime = 30;//誘導弾のクールタイム
const int GuidedBullEndHp = 11;//誘導弾から誘導弾に切り替えるHp

//全方位弾
const int EveryDirectionBulletCooltime = 30;//全方位弾のクールタイム
const int EveryDirectionBulletEndHp = 11;//全方位誘導弾から誘導弾に切り替えるHp

float MovePosY = 0;//ビームで移動する場所
int enemyCooltime = 0;//行動クールタイム

void EnemyActionTable(Enemy& enemy, Player& player, char keys[256], int &actionPattern, int map[MapHeight][MapWidth],
	Bullet& bullet, Bullet& beam, Bullet& guidedBull, Bullet everyDirectionBullet[]) {

	int i = 0;
	int everyDirectionBulletMax = 5;
	int count = 0;
	int random = 0;

	//パターン
	switch (actionPattern)
	{
	//初期
	case 0:

		if (EnemyMove(enemy, 540)) {
			enemyCooltime++;
			if (enemyCooltime >= 60)
			{
				actionPattern = 9;//全方位弾へ
			}
			StopAudio(BGM1);
			PlayAudio(BGM1);
		}

		break;
	//ビーム準備
	case 1:

		MovePosY = player.pos.y;
		if (MovePosY > 668 - enemy.Radius) {
			MovePosY = 668 - enemy.Radius;
		}
		actionPattern++;

		break;
	//ビーム前移動到着
	case 2:

		if (EnemyMove(enemy, MovePosY)) {
			EnemyBeam(beam, enemy, player);//敵のビーム攻撃
			actionPattern++;
		}

		break;
	//ビーム
	case 3:

		if (beam.isAlive) {
			EnemyBeam(beam, enemy, player);//敵のビーム攻撃
		}
		else {
			actionPattern++;
			enemyCooltime = BeamCooltime;//クールタイム

		}

		break;
	//ビーム待機
	case 4:

		enemyCooltime--;
		if (enemyCooltime == 0) {
			random = rand() % 10;
			if (random < 2) {
				actionPattern = 1;//ビームへ
			}
			else if (random < 6) {
				actionPattern = 5;//誘導弾へ
			}
			else {
				actionPattern = 9;//全方位弾へ
			}
		}

		break;
	//誘導弾準備
	case 5:

		MovePosY = rand() % (668 - enemy.Size) + enemy.Radius;
		if (MovePosY > 668 - enemy.Radius / 2) {
			MovePosY = 668 - enemy.Radius / 2;
		}
		actionPattern++;

		break;
	//誘導弾前移動到着
	case 6:

		if (EnemyMove(enemy, MovePosY)) {

			GuidedBullet(guidedBull, enemy, player, keys);//敵の誘導弾
			actionPattern++;
		}


		break;
	//誘導弾
	case 7:
		
		if (guidedBull.isAlive) {
			GuidedBullet(guidedBull, enemy, player, keys);//敵の誘導弾
		}
		else {
			actionPattern++;
			enemyCooltime = GuidedBullCooltime;//クールタイム
		}

		break;
	//誘導弾待機
	case 8:

		enemyCooltime--;
		if (enemyCooltime == 0) {
			if (enemy.Hp <= 5) {
				random = rand() % 10;
				if (random < 5) {
					actionPattern = 1;//ビームへ
				}
				else if (random < 7) {
					actionPattern = 5;//誘導弾へ
				}
				else {
					actionPattern = 9;//全方位弾へ
				}
			}
			else {
				random = rand() % 10;
				if (random < 8) {
					actionPattern = 9;//全方位弾へ
				}
				else {
					actionPattern = 5;//誘導弾へ
				}
			}
		}
		break;
	//全方位弾準備
	case 9:

		MovePosY = 668 - enemy.Radius;
		actionPattern++;

		break;
	//全方位弾前移動
	case 10:

		if (EnemyMove(enemy, MovePosY)) {
			for (i = 0; i < everyDirectionBulletMax; i++) {
				everyDirectionBullet[i].isAlive = false;
			}

			EveryDirection(everyDirectionBullet, enemy, player, keys);//敵の全方位攻撃
			actionPattern++;
		}

		break;
	//全方位弾
	case 11:

		for (i = 0; i < everyDirectionBulletMax; i++) {
			if (everyDirectionBullet[i].isAlive) {
				count++;
			}
		}
		if (count > 0) {
			EveryDirection(everyDirectionBullet, enemy, player, keys);//敵の全方位攻撃
		}
		else {
			actionPattern++;
			enemyCooltime = EveryDirectionBulletCooltime;//クールタイム
		}

		break;
	//全方位弾待機
	case 12:
		enemyCooltime--;
		if (enemyCooltime == 0) {
			if (enemy.Hp <= 5) {
				random = rand() % 10;
				if (random < 5) {
					actionPattern = 1;//ビームへ
				}
				else if (random < 8) {
					actionPattern = 5;//誘導弾へ
				}
				else {
					actionPattern = 9;//全方位弾へ
				}
			}
			else {
				random = rand() % 10;
				if (random < 3) {
					actionPattern = 9;//全方位弾へ
				}
				else {
					actionPattern = 5;//誘導弾へ
				}
			}
		}
	break;

	default:
		break;
	}
}