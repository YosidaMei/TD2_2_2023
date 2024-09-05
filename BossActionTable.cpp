#include "Common.h"
#include "Boss.h"
#include"Bullet.h"
#include<cmath>

Vector2 b2p = { 0,0 };
const int b2pDis = 400;

int bossActionCoolTime = 0;
int maxCoolTime = 30;
int bossActionTime = 60;

int prePattaern = 0;
int oldPrePattern = 0;

bool isBackStep = false;
bool isActionTimeSet = false;
bool isGuidedShot = false;
bool isBeamShot = false;
bool isEveryShot = false;
bool isShot = false;
bool isBeamShotLeft = false;
bool isBeamCancel = false;


int map[MapHeight][MapWidth] = {};

Bullet bullet = {};

Bullet beam = {};

Bullet guidedBull = {};

Bullet everyDirectionBullet[5] = {};

Boss boss = {};

const int bossMaxRight = WinWidth - boss.Radius;
const int bossMaxLeft = 0 + boss.Radius;

bool isPatternSet4810 = false;

void BossActionTable(Boss& boss, Player& player, char keys[256], int actionPattern, int map[MapHeight][MapWidth],
	Bullet& bullet, Bullet& beam, Bullet& guidedBull, Bullet everyDirectionBullet[]) {

	//ボス体力が100↓クールタイム30F
	if (boss.Hp <= 100) {
		maxCoolTime = 30;
	}
	//ボス体力が100↑クールタイム40F
	else {
		maxCoolTime = 40;
	}
	//ボスとプレイヤーの距離
	b2p.x = boss.pos.x - player.pos.x;
	if (b2p.x < 0)
	{
		b2p.x *= -1;
	}

	//ボスの行動
	if (bossActionCoolTime <= 0)
	{

		boss.isAction = true;
		//全方位のセッティング
		if ((actionPattern == 4 || actionPattern == 8 || actionPattern == 10) && !isPatternSet4810) {
			BossEveryDirectionSet(everyDirectionBullet, boss, player);
			//isPatternSet25 = true;
		}

		//テーブル
		switch (actionPattern)
		{
		case 0://初期移動
			if (isActionTimeSet)
			{
				//クールタイムを設定
				bossActionCoolTime = maxCoolTime;
			}
			else
			{
				//ResetMove
				BossResetMoveRight(boss, map);//初期位置に戻る
				bossActionTime--;
				beam.isAlive = false;
				isPatternSet4810 = true;
				if (bossActionTime <= 0)
				{
					isActionTimeSet = true;
				}
			}
			break;
		case 1://画面端ビーム
			if (prePattaern == actionPattern || oldPrePattern == actionPattern)
			{
				bossActionCoolTime = maxCoolTime;
			}
			else {
				if (isShot == false)
				{
					if (boss.pos.x > WinWidth / 2)
					{
						isBeamShotLeft = true;
						isShot = true;
					}
					else
					{
						isBeamShotLeft = false;
						isShot = true;
					}
				}
				if (isBeamShotLeft) {
					//ResetMove
					BossResetMoveLeft(boss, map);//初期位置に戻る
					if (boss.pos.x <= bossMaxLeft + 10)
					{
						//Beam
						BossBeamLeft(beam, boss, player);//敵のビーム攻撃
						if (beam.isAlive == false)
						{
							prePattaern = actionPattern;
							StopAudio(beanCharge);
						}
					}
				}
				else {
					//ResetMove
					BossResetMoveRight(boss, map);//初期位置に戻る
					if (boss.pos.x >= bossMaxRight - 10)
					{
						//Beam
						BossBeamRight(beam, boss, player);//敵のビーム攻撃	
						if (beam.isAlive == false)
						{
							oldPrePattern = prePattaern;
							prePattaern = actionPattern;
							StopAudio(beanCharge);
						}
					}
				}
			}
			break;
		case 2://誘導弾
			if (prePattaern == actionPattern || oldPrePattern == actionPattern)
			{
				bossActionCoolTime = maxCoolTime;
			}
			else
			{
				if (!isBackStep && b2p.x < b2pDis && isShot == false) {

					if (boss.pos.x <= b2pDis) {
						isBackStep = true;
						BossSteppingIn(boss, map, b2pDis * 2, player);
						boss.isLeft = true;
					}
					else if (boss.pos.x >= WinWidth - b2pDis) {
						isBackStep = true;
						BossSteppingIn(boss, map, b2pDis * 2, player);
						boss.isLeft = false;
					}
					else {
						isBackStep = true;
						BossSteppingIn(boss, map, -b2pDis, player);
					}
					StopAudio(teleportation);
					PlayAudio(teleportation);
				}
				else
				{
					isShot = true;
					//Guided
					BossGuidedBullet(guidedBull, boss, player, keys);//敵の誘導弾
				}

				if (guidedBull.isAlive)
				{
					//Run
					BossRun(boss, player, map);
				}
				else
				{
					oldPrePattern = prePattaern;
					prePattaern = actionPattern;
				}
			}
			break;
		case 3://誘導弾
			if (prePattaern == actionPattern || oldPrePattern == actionPattern)
			{
				bossActionCoolTime = maxCoolTime;
			}
			else
			{
				if (!isBackStep && b2p.x < b2pDis && isShot == false) {

					if (boss.pos.x <= b2pDis) {
						isBackStep = true;
						BossSteppingIn(boss, map, b2pDis + player.pos.x, player);
						boss.isLeft = true;
					}
					else if (boss.pos.x >= WinWidth - b2pDis) {
						isBackStep = true;
						BossSteppingIn(boss, map, b2pDis + player.pos.x, player);
						boss.isLeft = false;
					}
					else {
						isBackStep = true;
						BossSteppingIn(boss, map, -b2pDis, player);
					}
					StopAudio(teleportation);
					PlayAudio(teleportation);
				}
				else
				{
					isShot = true;
					//Guided
					BossGuidedBullet(guidedBull, boss, player, keys);//敵の誘導弾
				}

				if (guidedBull.isAlive)
				{
					//Run
					BossRun(boss, player, map);
				}
				else
				{
					oldPrePattern = prePattaern;
					prePattaern = actionPattern;
				}
			}
			break;
		case 4://全方位
			if (prePattaern == actionPattern || oldPrePattern == actionPattern)
			{
				bossActionCoolTime = maxCoolTime;
			}
			else
			{
				if (!isBackStep && b2p.x < b2pDis && isShot == false) {

					if (boss.pos.x <= b2pDis) {
						if (!boss.isLeft)
						{
							isBackStep = true;
							BossSteppingIn(boss, map, b2pDis * 2, player);
							boss.isLeft = true;
						}
						else
						{
							isBackStep = true;
							BossSteppingIn(boss, map, -b2pDis, player);
							boss.isLeft = true;
						}
					}
					else if (boss.pos.x >= WinWidth - b2pDis) {
						if (boss.isLeft)
						{
							isBackStep = true;
							BossSteppingIn(boss, map, b2pDis * 2, player);
							boss.isLeft = false;
						}
						else
						{
							isBackStep = true;
							BossSteppingIn(boss, map, -b2pDis, player);
							boss.isLeft = false;
						}
					}
					else {
						isBackStep = true;
						BossSteppingIn(boss, map, -b2pDis, player);
					}
					StopAudio(teleportation);
					PlayAudio(teleportation);
				}
				else
				{
					isPatternSet4810 = true;
					isShot = true;
					//EveryDir
					BossEveryDirection(everyDirectionBullet, boss, player, keys);//敵の全方位攻撃
					//MapCollisionBossEveryDirection(map, everyDirectionBullet);//全方位攻撃のマップとの当たり判定
				}
				if (boss.isActionEnd == true)
				{
					oldPrePattern = prePattaern;
					prePattaern = actionPattern;
					boss.isActionEnd = false;
				}
			}
			break;
		case 5://その場ビーム
			if (prePattaern == actionPattern || oldPrePattern == actionPattern)
			{
				bossActionCoolTime = maxCoolTime;
			}
			else
			{
				//その場でBeam
				if (isShot == false)
				{
					if (boss.isLeft)
					{
						isBeamShotLeft = true;//向きの固定
						isShot = true;//発射
					}
					else
					{
						isBeamShotLeft = false;
						isShot = true;
					}
				}
				if (isBeamShotLeft)
				{
					BossBeamRight(beam, boss, player);//敵のビーム攻撃
					boss.isLeft = true;//ボスの向きの固定
					if (CollisionObjRect(player.attack.quad, boss.quad) && player.attack.isHit)
					{
						isBeamCancel = true;
					}
					if (beam.isAlive == false || isBeamCancel) {
						prePattaern = actionPattern;
						StopAudio(beanCharge);
					}
				}
				else
				{
					BossBeamLeft(beam, boss, player);//敵のビーム攻撃
					boss.isLeft = false;
					if (CollisionObjRect(player.attack.quad, boss.quad) && player.attack.isHit)
					{
						isBeamCancel = true;
					}
					if (beam.isAlive == false || isBeamCancel)
					{
						oldPrePattern = prePattaern;
						prePattaern = actionPattern;
						StopAudio(beanCharge);
					}
				}
			}
			break;
			/*-----------------ここまでが体力100以上の時-------------------------*/
		case 6://三連撃
			if (prePattaern == actionPattern || oldPrePattern == actionPattern)
			{
				bossActionCoolTime = maxCoolTime;
			}
			else
			{
				BossAttackPattern1(boss, map, player, guidedBull, keys);
				if (guidedBull.isAlive) {
					BossGuidedBullet(guidedBull, boss, player, keys);//敵の誘導弾
				}

				if (boss.isActionEnd)
				{
					guidedBull.isAlive = false;
					boss.isActionEnd = false;
					oldPrePattern = prePattaern;
					prePattaern = actionPattern;
				}
			}
			break;
		case 7://溜め攻撃
			if (prePattaern == actionPattern || oldPrePattern == actionPattern)
			{
				bossActionCoolTime = maxCoolTime;
			}
			else
			{
				//行動時間が0以上なら
				//Attack
				BossAttackPattern2(boss, map, player);

				if (boss.isActionEnd)//行動時間が0になったら
				{
					oldPrePattern = prePattaern;
					prePattaern = actionPattern;
					boss.isActionEnd = false;
				}

			}
			break;
			/*-----------------ここから体力100以下の時-------------------------*/
		case 8://誘導弾＋全方位
			if (prePattaern == actionPattern || oldPrePattern == actionPattern)
			{
				bossActionCoolTime = maxCoolTime;
			}
			else
			{
				if (!isBackStep && b2p.x < b2pDis && isShot == false) {

					if (boss.pos.x <= b2pDis) {
						isBackStep = true;
						BossSteppingIn(boss, map, b2pDis + player.pos.x, player);
						boss.isLeft = true;
					}
					else if (boss.pos.x >= WinWidth - b2pDis) {
						isBackStep = true;
						BossSteppingIn(boss, map, b2pDis + player.pos.x, player);
						boss.isLeft = false;
					}
					else {
						isBackStep = true;
						BossSteppingIn(boss, map, -b2pDis, player);
					}
					StopAudio(teleportation);
					PlayAudio(teleportation);
				}
				else {
					isShot = true;
					isPatternSet4810 = true;

					if (isGuidedShot)
					{
						//Guided
						BossGuidedBullet(guidedBull, boss, player, keys);//敵の誘導弾
					}
					if (isEveryShot)
					{
						//EveryDir
						BossEveryDirection(everyDirectionBullet, boss, player, keys);//敵の全方位攻撃
						//MapCollisionBossEveryDirection(map, everyDirectionBullet);//全方位攻撃のマップとの当たり判定
					}
				}

				if (guidedBull.isAlive == false) {
					isGuidedShot = false;
				}
				if (boss.isActionEnd) {
					isEveryShot = false;
				}
				if (isGuidedShot == false && isEveryShot == false) {
					oldPrePattern = prePattaern;
					prePattaern = actionPattern;
					boss.isActionEnd = false;
				}
			}
			break;
		case 9://画面端ビーム＋誘導弾
			if (prePattaern == actionPattern || oldPrePattern == actionPattern)
			{
				bossActionCoolTime = maxCoolTime;
			}
			else {
				if (isShot == false)
				{
					if (boss.pos.x > WinWidth / 2)
					{
						isBeamShotLeft = true;
						isShot = true;
					}
					else
					{
						isBeamShotLeft = false;
						isShot = true;
					}
				}
				else if (isBeamShotLeft) {
					//ResetMove
					BossResetMoveLeft(boss, map);//初期位置に戻る
					if (boss.pos.x <= bossMaxLeft + 10)
					{
						if (isBeamShot)
						{
							//Beam
							BossBeamLeft(beam, boss, player);//敵のビーム攻撃
						}
						if (isGuidedShot)
						{
							//Guided
							BossGuidedBullet(guidedBull, boss, player, keys);//敵の誘導弾
						}
						if (beam.isAlive == false) {
							isBeamShot = false;
							StopAudio(beanCharge);
						}
						if (guidedBull.isAlive == false) {
							isGuidedShot = false;
						}
						if (isBeamShot == false && isGuidedShot == false)
						{
							prePattaern = actionPattern;
							boss.isActionEnd = false;
						}
					}
				}
				else {
					//ResetMove
					BossResetMoveRight(boss, map);//初期位置に戻る
					if (boss.pos.x >= bossMaxRight - 10)
					{
						if (isBeamShot)
						{
							//Beam
							BossBeamRight(beam, boss, player);//敵のビーム攻撃
						}
						if (isGuidedShot)
						{
							//Guided
							BossGuidedBullet(guidedBull, boss, player, keys);//敵の誘導弾
						}
						if (beam.isAlive == false) {
							isBeamShot = false;
							StopAudio(beanCharge);
						}
						if (guidedBull.isAlive == false) {
							isGuidedShot = false;
						}
						if (isBeamShot == false && isGuidedShot == false)
						{
							oldPrePattern = prePattaern;
							prePattaern = actionPattern;
							boss.isActionEnd = false;
						}
					}
				}
			}
			break;
		case 10://その場ビーム＋全方位
			if (prePattaern == actionPattern || oldPrePattern == actionPattern)
			{
				bossActionCoolTime = maxCoolTime;
			}
			else
			{
				if (!isBackStep && b2p.x < b2pDis && isShot == false) {

					if (boss.pos.x <= b2pDis) {
						if (!boss.isLeft)
						{
							BossSteppingIn(boss, map, b2pDis * 2, player);
							isBackStep = true;
							boss.isLeft = true;
						}
						else
						{
							BossSteppingIn(boss, map, -b2pDis, player);
							isBackStep = true;
							boss.isLeft = true;
						}

					}
					else if (boss.pos.x >= WinWidth - b2pDis) {
						if (boss.isLeft)
						{
							BossSteppingIn(boss, map, b2pDis * 2, player);
							isBackStep = true;
							boss.isLeft = false;
						}
						else
						{
							BossSteppingIn(boss, map, -b2pDis, player);
							isBackStep = true;
							boss.isLeft = false;
						}
					}
					else {
						BossSteppingIn(boss, map, -b2pDis, player);
						isBackStep = true;
					}
					StopAudio(teleportation);
					PlayAudio(teleportation);
				}
				else {
					isPatternSet4810 = true;
					//その場でBeam
					if (isShot == false)
					{
						if (boss.isLeft)
						{
							isBeamShotLeft = true;//向きの固定
							isShot = true;//発射
						}
						else
						{
							isBeamShotLeft = false;
							isShot = true;
						}
					}
					if (!isBeamShotLeft)
					{
						if (isBeamShot) {
							boss.isLeft = false;//ボスの向きの固定
							//Beam
							BossBeamLeft(beam, boss, player);//敵のビーム攻撃

						}
						if (isEveryShot) {
							//EveryDir
							BossEveryDirection(everyDirectionBullet, boss, player, keys);//敵の全方位攻撃
							//MapCollisionBossEveryDirection(map, everyDirectionBullet);//全方位攻撃のマップとの当たり判定
						}
						if (beam.isAlive == false) {
							isBeamShot = false;
							StopAudio(beanCharge);
						}
						if (boss.isActionEnd) {
							isEveryShot = false;
						}
						if (isBeamShot == false && isEveryShot == false) {
							prePattaern = actionPattern;
							boss.isActionEnd = false;
						}
					}
					else
					{
						if (isBeamShot) {
							boss.isLeft = true;//ボスの向きの固定
							//Beam
							BossBeamRight(beam, boss, player);//敵のビーム攻撃
						}
						if (isEveryShot) {
							//EveryDir
							BossEveryDirection(everyDirectionBullet, boss, player, keys);//敵の全方位攻撃
							MapCollisionBossEveryDirection(map, everyDirectionBullet);//全方位攻撃のマップとの当たり判定
						}
						if (beam.isAlive == false) {
							isBeamShot = false;
							StopAudio(beanCharge);
						}
						if (boss.isActionEnd) {
							isEveryShot = false;
						}
						if (isBeamShot == false && isEveryShot == false) {
							oldPrePattern = prePattaern;
							prePattaern = actionPattern;
							boss.isActionEnd = false;
						}
					}
				}
			}
			break;
		default:
			break;
		}
	}
	//クールタイム中
	else {
		if (boss.pos.x > player.pos.x) {
			boss.isLeft = true;
		}
		else {
			boss.isLeft = false;
		}

		BossWalk(boss, player, map);

		boss.isAction = false;
		bossActionCoolTime--;
		isActionTimeSet = false;
		BossBeamSet(beam, boss, player);
		BossGuidedBulletSet(guidedBull, boss, player);
		isPatternSet4810 = false;
		isBackStep = false;
		isBeamShotLeft = false;
		isShot = false;
		isGuidedShot = true;
		isBeamShot = true;
		isEveryShot = true;
		isBeamCancel = false;
	}
}
//テーブルの初期化
void BossActionTableSetting() {

	bossActionCoolTime = 0;
	maxCoolTime = 30;
	bossActionTime = 60;

	prePattaern = 0;

	isBackStep = false;
	isActionTimeSet = false;
	isShot = false;
	isBeamShotLeft = false;
	isPatternSet4810 = false;
}