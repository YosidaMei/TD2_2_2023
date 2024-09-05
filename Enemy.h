#pragma once
#include<Novice.h>
#include "Common.h"
#include"Player.h"

struct Enemy {

	const int Size = 256;//サイズ
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
	int textureHandle[1];//テクスチャハンドル

	Quad quad;//四点
	Quad hitQuad;//当たり判定四点

	int textureHandleNumber = 0;
	int TextureHandleNumberMax = 1;

	int animationNumber = 0;
	int AnimationNumberMax = 5;
	int animationTime = 0;
	const int AnimationTimeMax = 5;

	int transparency = 0xFF;//透明度

};

#include"Bullet.h"

struct EnemySmoke {

	bool isAlive = false;
	Vector2 pos = { 0,0 };//位置
	Vector2 vel = { 0,0 };

	float rad = 0;

	int posSpeed = 0;
	int transparency = 0;//透明度
	int transparencySpeed = 0;//透明度


};

void EnemySetting(Enemy &enemy);

void DrawEnemy(Enemy& enemy, Vector2& shake);

void EnemyQuad(Enemy& boss);

void EnemyHitBox(Player& player, Enemy& enemy);

void EnemyAnimation(Enemy& enemy);

bool EnemyMove(Enemy& enemy, float y);

void EnemyHitBoxQuad(Enemy& boss);

//エフェクト
void EnemyEffect(Enemy& enemy);
void DrawEnemyEffect(Vector2& shake, int& textureHandle);
void EnemyDamageEffectSetting(Enemy& enemy, float& y);
void EnemyDamageEffect();
void DrawEnemyDamageEffect(Vector2& shake, int& textureHandle);

void enemyChangeEffectRestartSetting();
void EnemyChangeEffectSetting(Enemy& enemy);
void EnemyChangeEffect(Enemy& enemy, Scene& scene);
void DrawEnemyChangeEffect(Enemy& enemy, Vector2& shake, Scene& scene, int& textureHandle);


//エネミーアクションテーブルはBullet.h