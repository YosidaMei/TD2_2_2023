#include"Bullet.h"
#define _USE_MATH_DEFINES
#include<cmath>
#include "CollsionEffect.h"

Vector2 playerOldPos = { 0 };

void GuidedBullet(Bullet& guidedBull, Enemy& enemy, Player& player, char Keys[256]) {

    //弾が出てる
    if (guidedBull.isAlive) {
        //距離を測る
        guidedBull.posTmp = Guided(playerOldPos, guidedBull.pos);
        //正規化
        guidedBull.normalize = sqrt(guidedBull.posTmp.x * guidedBull.posTmp.x + guidedBull.posTmp.y * guidedBull.posTmp.y);
        //加速度
        guidedBull.acc.x += 0.25f;
        guidedBull.acc.y += 0.25f;
        //攻撃
        if (!guidedBull.isReflection) {
            //プレイヤーの元のｘ座標を超えてない時
            if (guidedBull.posTmp.x > 0) {
                guidedBull.isLeft = false;
                guidedBull.pos.x -= guidedBull.posTmp.x / guidedBull.normalize * (guidedBull.vel.x + guidedBull.acc.x);
                guidedBull.pos.y -= guidedBull.posTmp.y / guidedBull.normalize * (guidedBull.vel.y + guidedBull.acc.y);
                //当たり判定
                if (CollisionObj(player.attack.quad, guidedBull.quad)) {
                    guidedBull.isReflection = true;
                    RepelTheSwordEffectSetting(player);
                }
                else if (CollisionObj(guidedBull.quad, player.quad)) {
                    guidedBull.isHit = true;
                }
            }
            //プレイヤーの元のｘ座標を超えてる時
            else if (guidedBull.posTmp.x < 0) {
                guidedBull.isLeft = true;
                guidedBull.pos.x += guidedBull.posTmp.x / guidedBull.normalize * (guidedBull.vel.x + guidedBull.acc.x);
                guidedBull.pos.y += guidedBull.posTmp.y / guidedBull.normalize * (guidedBull.vel.x + guidedBull.acc.x);
                //当たり判定
                if (CollisionObj(player.attack.quad, guidedBull.quad)) {
                    guidedBull.isReflection = true;
                    RepelTheSwordEffectSetting(player);
                }
                else if (CollisionObj(guidedBull.quad, player.quad)) {
                    guidedBull.isHit = true;
                }
            }
        }
        //攻撃を反射
        else if (guidedBull.isReflection) {
            //ボスより左側
            //プレイヤーの元のｘ座標を超えてない時
            if (guidedBull.posTmp.x > 0) {
                guidedBull.isLeft = false;
                guidedBull.pos.x += guidedBull.posTmp.x / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                guidedBull.pos.y += guidedBull.posTmp.y / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                //当たり判定
                if (CollisionObj(player.attack.quad, guidedBull.quad)) {
                    guidedBull.isReflection = true;
                    RepelTheSwordEffectSetting(player);
                }
                else if (CollisionObj(guidedBull.quad, enemy.quad)) {
                    guidedBull.isBossHit = true;
                }
            }
            //プレイヤーの元のｘ座標を超えてる時
            else if (guidedBull.posTmp.x < 0) {
                guidedBull.isLeft = true;
                guidedBull.pos.x -= guidedBull.posTmp.x / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                guidedBull.pos.y -= guidedBull.posTmp.y / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                //当たり判定
                if (CollisionObj(player.attack.quad, guidedBull.quad)) {
                    guidedBull.isReflection = true;
                    RepelTheSwordEffectSetting(player);
                }
                else if (CollisionObj(guidedBull.quad, enemy.quad)) {
                    guidedBull.isBossHit = true;
                }
            }
        }

        //画面外に行ったとき
        if (guidedBull.pos.x < 0 || guidedBull.pos.x > WinWidth || guidedBull.pos.y < 0 || guidedBull.pos.y > WinHeight) {
            guidedBull.isAlive = false;
            guidedBull.pos.x = -1000;
            guidedBull.pos.y = -1000;
        }
        //当たったフラグがたったら
        if (guidedBull.isHit) {
            player.Hp -= 1;
            PlayerDamageEffectSetting(player,guidedBull.pos.x);
            guidedBull.isAlive = false;
            guidedBull.isHit = false;
        }
        else if (guidedBull.isBossHit) {
            enemy.Hp -= 1;
            EnemyDamageEffectSetting(enemy,guidedBull.pos.y);
            guidedBull.isAlive = false;
            guidedBull.isBossHit = false;
        }

        //移動
        //左上
        guidedBull.quad.leftTop.x = guidedBull.pos.x + (-guidedBull.radius.x) * guidedBull.posTmp.x / guidedBull.normalize - (-guidedBull.radius.y) * guidedBull.posTmp.y / guidedBull.normalize;
        guidedBull.quad.leftTop.y = guidedBull.pos.y + (-guidedBull.radius.x) * guidedBull.posTmp.y / guidedBull.normalize + (-guidedBull.radius.y) * guidedBull.posTmp.x / guidedBull.normalize;
        //右上
        guidedBull.quad.rightTop.x = guidedBull.pos.x + (guidedBull.radius.x) * guidedBull.posTmp.x / guidedBull.normalize - (-guidedBull.radius.y) * guidedBull.posTmp.y / guidedBull.normalize;
        guidedBull.quad.rightTop.y = guidedBull.pos.y + (guidedBull.radius.x) * guidedBull.posTmp.y / guidedBull.normalize + (-guidedBull.radius.y) * guidedBull.posTmp.x / guidedBull.normalize;
        //左下
        guidedBull.quad.leftBottom.x = guidedBull.pos.x + (-guidedBull.radius.x) * guidedBull.posTmp.x / guidedBull.normalize - (guidedBull.radius.y) * guidedBull.posTmp.y / guidedBull.normalize;
        guidedBull.quad.leftBottom.y = guidedBull.pos.y + (-guidedBull.radius.x) * guidedBull.posTmp.y / guidedBull.normalize + (guidedBull.radius.y) * guidedBull.posTmp.x / guidedBull.normalize;
        //右下
        guidedBull.quad.rightBottom.x = guidedBull.pos.x + (guidedBull.radius.x) * guidedBull.posTmp.x / guidedBull.normalize - (guidedBull.radius.y) * guidedBull.posTmp.y / guidedBull.normalize;
        guidedBull.quad.rightBottom.y = guidedBull.pos.y + (guidedBull.radius.x) * guidedBull.posTmp.y / guidedBull.normalize + (guidedBull.radius.y) * guidedBull.posTmp.x / guidedBull.normalize;
    }
    //出てないとき
    else {
        //座標受け取り
        guidedBull.pos = enemy.pos;
        playerOldPos = player.pos;
        guidedBull.vel.x = guidedBull.SpeedMax;
        guidedBull.vel.y = guidedBull.SpeedMax;
        guidedBull.acc = { 0 };
        //弾のフラグオン
        guidedBull.isAlive = true;
        guidedBull.isReflection = false;

        //距離を測る
        guidedBull.posTmp = Guided(playerOldPos, guidedBull.pos);
        //正規化
        guidedBull.normalize = sqrt(guidedBull.posTmp.x * guidedBull.posTmp.x + guidedBull.posTmp.y * guidedBull.posTmp.y);

        //左上
        guidedBull.quad.leftTop.x = guidedBull.pos.x + (-guidedBull.radius.x) * guidedBull.posTmp.x / guidedBull.normalize - (-guidedBull.radius.y) * guidedBull.posTmp.y / guidedBull.normalize;
        guidedBull.quad.leftTop.y = guidedBull.pos.y + (-guidedBull.radius.x) * guidedBull.posTmp.y / guidedBull.normalize + (-guidedBull.radius.y) * guidedBull.posTmp.x / guidedBull.normalize;
        //右上
        guidedBull.quad.rightTop.x = guidedBull.pos.x + (guidedBull.radius.x) * guidedBull.posTmp.x / guidedBull.normalize - (-guidedBull.radius.y) * guidedBull.posTmp.y / guidedBull.normalize;
        guidedBull.quad.rightTop.y = guidedBull.pos.y + (guidedBull.radius.x) * guidedBull.posTmp.y / guidedBull.normalize + (-guidedBull.radius.y) * guidedBull.posTmp.x / guidedBull.normalize;
        //左下
        guidedBull.quad.leftBottom.x = guidedBull.pos.x + (-guidedBull.radius.x) * guidedBull.posTmp.x / guidedBull.normalize - (guidedBull.radius.y) * guidedBull.posTmp.y / guidedBull.normalize;
        guidedBull.quad.leftBottom.y = guidedBull.pos.y + (-guidedBull.radius.x) * guidedBull.posTmp.y / guidedBull.normalize + (guidedBull.radius.y) * guidedBull.posTmp.x / guidedBull.normalize;
        //右下
        guidedBull.quad.rightBottom.x = guidedBull.pos.x + (guidedBull.radius.x) * guidedBull.posTmp.x / guidedBull.normalize - (guidedBull.radius.y) * guidedBull.posTmp.y / guidedBull.normalize;
        guidedBull.quad.rightBottom.y = guidedBull.pos.y + (guidedBull.radius.x) * guidedBull.posTmp.y / guidedBull.normalize + (guidedBull.radius.y) * guidedBull.posTmp.x / guidedBull.normalize;

    }
}

void GuidedBulletReset(Bullet& guidedBull) {
    guidedBull.isAlive = false;
    guidedBull.isHit = false;
    guidedBull.isReflection = false;
    guidedBull.isBossHit = false;
    guidedBull.pos.x = -1000;
    guidedBull.pos.y = -1000;
}

void DrawGuidedBullet(Bullet& guidedBull, Enemy& enemy, Vector2& shake) {
    if (enemy.isAlive) {
        if (guidedBull.isAlive) {
            //反射してないときの描画
            if (!guidedBull.isReflection) {
                if (guidedBull.isLeft) {
                    Novice::DrawQuad(guidedBull.quad.rightTop.x + shake.x, guidedBull.quad.rightTop.y + shake.y,
                        guidedBull.quad.leftTop.x + shake.x, guidedBull.quad.leftTop.y + shake.y,
                        guidedBull.quad.rightBottom.x + shake.x, guidedBull.quad.rightBottom.y + shake.y,
                        guidedBull.quad.leftBottom.x + shake.x, guidedBull.quad.leftBottom.y + shake.y,
                        0, 0, guidedBull.size.x, guidedBull.size.y, guidedBull.textureHandle, 0xFFFFFFFF);
                }
                else {
                    Novice::DrawQuad(guidedBull.quad.leftTop.x + shake.x, guidedBull.quad.leftTop.y + shake.y,
                        guidedBull.quad.rightTop.x + shake.x, guidedBull.quad.rightTop.y + shake.y,
                        guidedBull.quad.leftBottom.x + shake.x, guidedBull.quad.leftBottom.y + shake.y,
                        guidedBull.quad.rightBottom.x + shake.x, guidedBull.quad.rightBottom.y + shake.y,
                        0, 0, guidedBull.size.x, guidedBull.size.y, guidedBull.textureHandle, 0xFFFFFFFF);
                }
            }
            //反射したときの描画
            else if (guidedBull.isReflection) {
                if (guidedBull.isLeft) {
                    Novice::DrawQuad(guidedBull.quad.leftTop.x + shake.x, guidedBull.quad.leftTop.y + shake.y,
                        guidedBull.quad.rightTop.x + shake.x, guidedBull.quad.rightTop.y + shake.y,
                        guidedBull.quad.leftBottom.x + shake.x, guidedBull.quad.leftBottom.y + shake.y,
                        guidedBull.quad.rightBottom.x + shake.x, guidedBull.quad.rightBottom.y + shake.y,
                        0, 0, guidedBull.size.x, guidedBull.size.y, guidedBull.textureHandle, 0xFFFFFFFF);
                }
                else {
                    Novice::DrawQuad(guidedBull.quad.rightTop.x + shake.x, guidedBull.quad.rightTop.y + shake.y,
                        guidedBull.quad.leftTop.x + shake.x, guidedBull.quad.leftTop.y + shake.y,
                        guidedBull.quad.rightBottom.x + shake.x, guidedBull.quad.rightBottom.y + shake.y,
                        guidedBull.quad.leftBottom.x + shake.x, guidedBull.quad.leftBottom.y + shake.y,
                        0, 0, guidedBull.size.x, guidedBull.size.y, guidedBull.textureHandle, 0xFFFFFFFF);

                }
            }
        }
    }
    //Novice::ScreenPrintf(0, 0, "%f %f %d", guidedBull.pos.x, guidedBull.pos.y, guidedBull.isAlive);
}