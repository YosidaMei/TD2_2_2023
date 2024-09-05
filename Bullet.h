#pragma once
#include<Novice.h>
#include"Common.h"
#include"Enemy.h"
#include"Player.h"
#include"Collision.h"
struct Bullet {

    const int Size = 36;//サイズ
    int Radius = Size / 2;//半径
    Vector2 size = { 128,48 };
    Vector2 radius = { 64,24 };
    const float SpeedMax = 5.0f;//速さ最大

    Vector2 acc;//加速度
    Vector2 posTmp;//仮の位置
    Vector2 pos;//位置
    Vector2 vel;//速度
    Quad quad;//四点
    float normalize;//正規化
    float theta;//角度
    bool isAlive;//生きてるか
    bool isHit;//攻撃してるか
    bool isBossHit;//反射した弾が当たってるか
    bool isReflection;//反射しているか
    bool isLeft;//左側にあるか
    int textureHandle;//テクスチャハンドル
};

void EnemyBeam(Bullet& beam, Enemy& enemy, Player& player);
void EveryDirection(Bullet* bullet, Enemy& enemy, Player& player,char Key[256]);
void GuidedBullet(Bullet& guidedBull, Enemy& enemy, Player& player,char Key[256]);

void EveryDirectionReset(Bullet bullet[]);
void GuidedBulletReset(Bullet& guidedBull);

void EnemyDead(Enemy& enemy, Bullet beam, Bullet bullet[], Bullet& guidedBullet, Scene& scene);

void DrawEnemyBeam(Bullet& beam, Enemy& enemy, Vector2& shake);
void DrawEveryDirection(Bullet* bullet, Vector2& shake);
void DrawGuidedBullet(Bullet& guidedBull, Enemy& enemy, Vector2& shake);

void MapCollisionEveryDirection(int map[MapHeight][MapWidth], Bullet* bullet);

//エネミーアクションテーブル
void EnemyActionTable(Enemy& enemy, Player& player, char keys[256], int& actionPattern, int map[MapHeight][MapWidth], Bullet& bullet, Bullet& beam, Bullet& guidedBull, Bullet everyDirectionBullet[]);