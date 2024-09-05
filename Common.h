#pragma once
#include<Novice.h>

struct Vector2 {
	float x;
	float y;
};

struct Quad {
	
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftBottom;
	Vector2 rightBottom;

};

enum Scene {

	title,//0
	tutorial,//1
	gameBoss1,//2
	gameBoss2,//3
	gameover,//4
	gameclear,//5

};

enum AudioNumber {

	playerMove,//プレイヤー移動
	playerAttack,//プレイヤーアタック
	playerDamage,//プレイヤーダメージ
	playerJump,//プレイヤージャンプ
	enemyDamage,//エネミーダメージ
	swordRepel,//剣の打ち合い
	teleportation,//瞬間移動
	beanCharge,//ビームチャージ
	bossChange1,//ボス形態変化1
	bossChange2,//ボス形態変化2
	bossChage,//ボスのチャージ
	bossAttack,//ボスアタック
	BGM1,//bgm1

};

const int AudioNumberMax = 16;

const int WinWidth = 1280;//画面幅
const int WinHeight = 720;//画面高さ
const float Gravity = 0.8;//重力

void ScreenChange(int KeyReturn, int preKeyReturn);

Vector2 Guided(Vector2& targetPos, Vector2& fromPos);

bool HpDown(int& hp, int& preHp);

void CameraShake(Vector2& shake, int& shakeTime);

void AudioSetting();
void PlayAudio(AudioNumber num);
void StopAudio(AudioNumber num);
void AllStopAudio();
void LoopBGM();