#pragma once
#include<Novice.h>
#include "Common.h"
#include "Player.h"

struct Boss {

	const int Size = 64;//サイズ
	const int Radius = Size / 2;//半径
	const float SpeedMax = 5.0f;//速さ最大
	const float JumpPower = -20.0f;//ジャンプ力
	const float JumpPower2 = -10.0f;//2段ジャンプ力
	const int GaugeMax = 100;//ゲージ最大
	const int BeamSpeed = 20;//ビーム速度

	Vector2 acc;//加速度
	Vector2 posTmp;//仮の位置
	Vector2 pos;//位置
	Vector2 vel;//速度
	bool isLeft;//向き
	bool isRise;//上昇している
	bool isAlive;//生きてるか
	bool isGround;//着地しているか
	bool isJumping;//ジャンプしているか
	bool is2jump;//２段ジャンプしているか
	bool isAttack;//攻撃してるか
	int Hp;//体力
	int gauge;//ゲージ
	int gaugeRecoveryTime;//ゲージ時間
	int gaugeCooltime;//ゲージクールタイム
	int gaugeRecoveryTimeMax;//ゲージ時間最大
	int gaugeCooltimeMax;//ゲージクールタイム最大
	int textureHandle[4];//テクスチャハンドル
	int textureHandleNumber = 0;//テクスチャハンドルナンバー

	int animationNumber = 0;//アニメーション
	int AnimationNumberMax = 0;
	int animationTime = 0;
	const int AnimationTimeMax = 5;


	Quad quad;//四点
	int cooltime = 0;//クールタイム
	Quad attackQuad;//攻撃四点
	
	Attack attack;

	//後でセッティングに入れる
	Afterimage afterimage[5];

	//---パターン用---//
	int numberInPattern = 0;
	int numberInPatternMax = 0;
	bool jumpedOver;
	
	bool isAction;
	bool isActionEnd;

};

#include"Bullet.h"

struct BossEffect {

	bool isAlive = false;
	Vector2 pos = { 0,0 };//位置
	Vector2 vel = { 0,0 };

	int posSpeed = 0;
	int transparency = 0;//透明度
	int transparencySpeed = 0;//透明度


};

void BossSetting(Boss& boss);
void BossFunction(Boss& boss, Player& player, int map[MapHeight][MapWidth]);
void BossCooltime(int& cooltime);
void BossQuad(Boss& boss);
void BossAnimation(Boss& boss);
void DrawBoss(Boss& boss,Vector2 &shake);
void BossHitBox(Player& player, Boss& boss);

void BossDead(Boss& boss, Scene& scene);

void BossWalk(Boss& boss, Player& player, int map[MapHeight][MapWidth]);
void BossRun(Boss& boss,Player& player,int map[MapHeight][MapWidth]);
void BossGravity(Boss& boss);
void BossCheckMap(Boss& boss, int map[MapHeight][MapWidth]);
void BossResetMoveRight(Boss& boss, int map[MapHeight][MapWidth]);
void BossResetMoveLeft(Boss& boss, int map[MapHeight][MapWidth]);

//---攻撃系---//
//ビーム
void BossBeamSet(Bullet& beam, Boss& boss, Player& player);
void BossBeamRight(Bullet& beam, Boss& boss, Player& player);
void BossBeamLeft(Bullet& beam, Boss& boss, Player& player);
void DrawBossBeam(Bullet& beam, Boss& boss,Vector2& shake);
//全方位弾
void BossEveryDirectionSet(Bullet* bullet, Boss& enemy, Player& player);
void BossEveryDirection(Bullet* bullet, Boss& boss, Player& player, char Key[256]);
void DrawBossEveryDirection(Bullet* bullet,Vector2& shake);
void MapCollisionBossEveryDirection(int map[MapHeight][MapWidth], Bullet* bullet);
//誘導弾
void BossGuidedBulletSet(Bullet& guidedBull, Boss& boss, Player& player);
void BossGuidedBullet(Bullet& guidedBull, Boss& boss, Player& player, char Keys[256]);
void DrawBossGuidedBullet(Bullet& guidedBull, Boss& boss, Vector2& shake);

//テーブル
void BossActionTable(Boss& boss, Player& player, char keys[256], int actionPattern, int map[MapHeight][MapWidth], 
	Bullet& bullet, Bullet& beam, Bullet& guidedBull, Bullet everyDirectionBullet[]);
void BossActionTableSetting();

//---行動パターン系---//
void BossAttack(Player& player,Boss& boss, int cooltime, int attackWidth, int attackHeight);
void BossSteppingIn(Boss& boss, int map[MapHeight][MapWidth], float step, Player& player);
void BossJumpedOver(Boss& boss, Player& player);
void BossAttackPattern1(Boss& boss, int map[MapHeight][MapWidth], Player& player, Bullet& guidedBull, char keys[]);
void BossAttackPattern2(Boss& boss, int map[MapHeight][MapWidth], Player& player);
void DrawAttackBoss(Boss& boss);//デバッグ

//---ボスエフェクト---//
void BossDeadEffectSetting(Boss& boss);
void BossDeadEffect(Boss& boss,Scene &scene);
void DrawBossDeadEffect(Boss& boss, Vector2& shake, int& textureHandle);

void BossAfterimage(Boss& boss);

void BossDamageEffectSetting(Boss& boss, float hitPos);
void BossDamageEffect();
void DrawBossDamageEffect(Vector2& shake, int& textureHandle);

void BossChargeEffectSet(Boss& boss);
void BossChargeEffect();
void DrawBossCharge(Boss& boss, int isPattern, Vector2& shake);
void BossChargeEffectDelete();

//---ボスソード---//
void BossSwordRotate(Sword& sword, Boss& boss);
void BossSwordSetting(Sword& sword);
void BossSwordFloating(Sword& sword);
void BossSwordFollowing(Sword& sword, Boss& boss);
void BossSwordQuad(Sword& sword);
void BossSwordAfterimage(Sword& sword, Boss& boss);
void DrowBossSword(Sword& sword, Boss& boss, Vector2& shake);
void DrawBossSwordEffect(Boss& boss, Vector2& shake);
void BossSwordFunction(Sword& sword, Boss& boss);


void BossPositionClamp(Boss& boss);