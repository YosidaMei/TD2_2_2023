#pragma once
#include <dxgitype.h>
#include"Common.h"
#include"Map.h"

struct Attack {

	Vector2 Pos;//位置
	Vector2 Radius;//半径
	int time;//攻撃時間
	int cooltime;//クールタイム
	int timeMax;//攻撃時間最大
	int cooltimeMax;//クールタイム最大
	bool isLeft;//向き
	Quad quad;//四点
	int textureHandle;

	int gaugeCost = 10;//ゲージ消費量

	bool isHit;

};

struct Afterimage {

	Quad quad = {};//四点
	int animationNumber = 0;
	int textureHandleNumber = 0;//テクスチャハンドルナンバー
	bool isLeft = true;//向き

};

struct Hp {
	Vector2 pos;
	Quad quad = {};//四点
	int textureHandle;
	int AnimationNumberMax = 0;
	int animationNumber = 0;
	const int Size = 64;//サイズ
	const int Radius = Size / 2;//半径
};

struct Player {

	const int Size = 64;//サイズ
	const int Radius = Size / 2;//半径
	const float SpeedMax = 5.0f;//速さ最大
	const float JumpPower = -20.0f;//ジャンプ力
	const float JumpPower2 = -20.0f;//2段ジャンプ力
	const int GaugeMax = 100;//ゲージ最大
	const int BeamSpeed = 20;//ビーム速度

	Vector2 acc;//加速度
	Vector2 posTmp;//仮の位置
	Vector2 pos;//位置
	Vector2 vel;//速度
	Quad quad;//四点
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
	int textureHandle[3];//テクスチャハンドル
	int textureHandleNumber = 0;//テクスチャハンドルナンバー

	Attack attack;//近距離攻撃
	Attack beam;//遠距離攻撃
	
	int animationNumber = 0;
	int AnimationNumberMax = 0;
	int animationTime = 0;
	const int AnimationTimeMax = 5;

	//後でセッティングに入れる
	Afterimage afterimage[5];

	bool isLand	= false;//着地フレーム確認用
};

struct Sword {

	Vector2 Pos;//位置
	Vector2 Radius;//半径
	Quad quad;//四点
	int textureHandle;

	int radian;
	float theta;

	float floating;//yの動いている部分
	float floatinglength;

	//後でセッティングに入れる
	Quad afterimage[5];
	bool afterimageIsLeft[5];
};

struct Smoke {

	bool isAlive = false;
	Vector2 pos = {0,0};//位置
	Vector2 vel = { 0,0 };

	int posSpeed = 0;
	int transparency = 0;//透明度
	int transparencySpeed = 0;//透明度


};

void PlayerSetting(Player &player);
void PlayerKeyInput(Player& player, int keyLeft, int keyRight, int stickDir);
void PlayerJamp(Player& player, int keyJamp, int preKeyJamp, int padJamp, int prePadJamp);
void PlayerMove(Player &player, int map[MapHeight][MapWidth]);
void PlayerAttack(Player &player, int keyAttack, int preKeyAttack, int padAttack, int prePadAttack,int map[MapHeight][MapWidth]);//
//void PlayerGauge(Player& player);
void PlayerAnimation(Player& player);
void PlayerAfterimage(Player& player);
void PlayerQuad(Player& player);
void HpSetting(Hp* hp);
void HpQuad(Hp* hp,Player& player);
void DrawHp(Hp* boss,Player& player, Vector2& shake);
void DrawPlayerUi(int textureHandle);

//---描画---//
void DrawPlayer(Player player, Vector2& shake);

//---剣---//
void SwordSetting(Sword& sword);
void SwordRotate(Sword& sword, Player& player);
void SwordFloating(Sword& sword);
void SwordFollowing(Sword& sword, Player& player);
void SwordQuad(Sword& sword);
void SwordAfterimage(Sword& sword, Player& player);
void SwordFunction(Sword& sword, Player& player);
//描画
void DrowSword(Sword& sword, Player& player, Vector2& shake);
void DrawSwordEffect(Player& player, Vector2& shake);

//---煙---//
void  PlayerLandingSmoke(Player& player);
void PlayerRunSmoke(Player& player);
void PlayerJumpSmoke(Player& player);
void PlayerJumpingSmoke(Player& player);
void Player2JumpSmoke(Player& player);

//---描画---//
void  DrawPlayerLandingSmoke(Vector2& shake, int& textureHandle);
void  DrawPlayerRunSmoke(Vector2& shake, int& textureHandle);
void  DrawPlayerJumpSmoke(Vector2& shake, int& textureHandle);
void  DrawPlayerJumpingSmoke(Vector2& shake, int& textureHandle);
void  DrawPlayer2JumpSmoke(Vector2& shake, int& textureHandle);

//---ダメージ---//
void PlayerDamageEffectSetting(Player& player,float hitPos);
void PlayerDamageEffect();
void  DrawPlayerDamageEffect(Vector2& shake, int& textureHandle);
void PlayerDamageEffectReset();

//音
void PlayerAudio(Player& player);

//void PlayerBeamKeyInput(Player &player);
//void PlayerBeamMove(Player& player,int map[MapHeight][MapWidth]);//
