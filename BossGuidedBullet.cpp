#include"Bullet.h"
#include<cmath>
#include"Boss.h"
#include"Player.h"
#include "CollsionEffect.h"

Vector2 playerOld = { 0 };
Vector2 bossOld = { 0 };

bool isPlayer2BulletLeft = 0;
bool isReflectAttack = 0;


void BossGuidedBulletSet(Bullet& guidedBull, Boss& boss, Player& player) {
    //座標受け取り
    guidedBull.pos = boss.pos;
    playerOld.x = player.pos.x;
    playerOld.y = player.pos.y + player.Radius / 2;

    guidedBull.vel.x = guidedBull.SpeedMax;
    guidedBull.vel.y = guidedBull.SpeedMax;
    guidedBull.acc = { 0 };
    bossOld = Guided(playerOld, guidedBull.pos);
    //弾のフラグオン
    guidedBull.isAlive = false;
    guidedBull.isReflection = false;

    //左上
    guidedBull.quad.leftTop.x = 0;
    guidedBull.quad.leftTop.y = 0;
    //右上
    guidedBull.quad.rightTop.x = 0;
    guidedBull.quad.rightTop.y = 0;
    //左下
    guidedBull.quad.leftBottom.x = 0;
    guidedBull.quad.leftBottom.y = 0;
    //右下
    guidedBull.quad.rightBottom.x = 0;
    guidedBull.quad.rightBottom.y = 0;


}

void BossGuidedBullet(Bullet& guidedBull, Boss& boss, Player& player, char Key[256]) {

    //弾が出てる
    if (guidedBull.isAlive) {
        //距離を測る
        guidedBull.posTmp = Guided(playerOld, guidedBull.pos);
        //正規化
        guidedBull.normalize = sqrt(guidedBull.posTmp.x * guidedBull.posTmp.x + guidedBull.posTmp.y * guidedBull.posTmp.y);
        guidedBull.acc.x += 0.25f;
        guidedBull.acc.y += 0.25f;
        //移動
        if (!guidedBull.isReflection) {
            //ボスより左側
            if (isPlayer2BulletLeft) {
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
                    guidedBull.pos.y += guidedBull.posTmp.y / guidedBull.normalize * (guidedBull.vel.y + guidedBull.acc.y);
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
            //ボスより右側
            else if (!isPlayer2BulletLeft) {
                //超えてないとき
                if (guidedBull.posTmp.x > 0) {
                    guidedBull.isLeft = false;
                    guidedBull.pos.x += guidedBull.posTmp.x / guidedBull.normalize * (guidedBull.vel.x + guidedBull.acc.x);
                    guidedBull.pos.y += guidedBull.posTmp.y / guidedBull.normalize * (guidedBull.vel.y + guidedBull.acc.y);
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
            }
        }
        else if (guidedBull.isReflection) {

            //ボスより左側
            if (isPlayer2BulletLeft) {
                //プレイヤーの元のｘ座標を超えてない時
                if (guidedBull.posTmp.x > 0) {
                    guidedBull.isLeft = true;
                    guidedBull.pos.x += guidedBull.posTmp.x / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                    guidedBull.pos.y += guidedBull.posTmp.y / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                    //当たり判定
                    if (CollisionObj(guidedBull.quad, boss.quad)) {
                        guidedBull.isBossHit = true;
                    }
                    if (CollisionObj(player.attack.quad, guidedBull.quad)) {
                        guidedBull.isReflection = true;
                        RepelTheSwordEffectSetting(player);
                    }
                }
                //プレイヤーの元のｘ座標を超えてる時
                else if (guidedBull.posTmp.x < 0) {
                    guidedBull.isLeft = true;
                    guidedBull.pos.x -= guidedBull.posTmp.x / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                    guidedBull.pos.y -= guidedBull.posTmp.y / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                    //当たり判定
                    if (CollisionObj(guidedBull.quad, boss.quad)) {
                        guidedBull.isBossHit = true;
                    }
                    if (CollisionObj(player.attack.quad, guidedBull.quad)) {
                        guidedBull.isReflection = true;
                        RepelTheSwordEffectSetting(player);
                    }
                }
            }

            //ボスより右側
            if (!isPlayer2BulletLeft) {
                //越えてないとき
                if (guidedBull.posTmp.x > 0) {
                    guidedBull.isLeft = false;
                    guidedBull.pos.x -= guidedBull.posTmp.x / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                    guidedBull.pos.y -= guidedBull.posTmp.y / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                    //当たり判定
                    if (CollisionObj(guidedBull.quad, boss.quad)) {
                        guidedBull.isBossHit = true;
                    }
                    if (CollisionObj(player.attack.quad, guidedBull.quad)) {
                        guidedBull.isReflection = true;
                        RepelTheSwordEffectSetting(player);
                    }
                }
                //プレイヤーの元のｘ座標を超えてる時
                else if (guidedBull.posTmp.x < 0) {
                    guidedBull.isLeft = true;
                    guidedBull.pos.x += guidedBull.posTmp.x / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                    guidedBull.pos.y += guidedBull.posTmp.y / guidedBull.normalize * guidedBull.SpeedMax * guidedBull.SpeedMax;
                    //当たり判定
                    if (CollisionObj(guidedBull.quad, boss.quad)) {
                        guidedBull.isBossHit = true;
                    }
                    if (CollisionObj(player.attack.quad, guidedBull.quad)) {
                        guidedBull.isReflection = true;
                        RepelTheSwordEffectSetting(player);
                    }
                }
            }
        }
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
        //画面外に行ったとき
        if (guidedBull.pos.x < 0 || guidedBull.pos.x > WinWidth || guidedBull.pos.y < 0 || guidedBull.pos.y > WinHeight) {
            guidedBull.pos.x = -1000;
            guidedBull.pos.y = -1000;
            guidedBull.isAlive = false;
        }
        //当たったフラグがたったら
        if (guidedBull.isHit) {
            player.Hp -= 1;
            PlayerDamageEffectSetting(player, guidedBull.pos.x);
            guidedBull.isAlive = false;
            guidedBull.isHit = false;
        }
        else if (guidedBull.isBossHit) {
            boss.Hp -= 10;
            BossDamageEffectSetting(boss, guidedBull.pos.x);
            guidedBull.isAlive = false;
            guidedBull.isBossHit = false;
        }
    }
    //出てないとき
    else {
        //座標受け取り
        guidedBull.pos = boss.pos;
        playerOld.x = player.pos.x;
        playerOld.y = player.pos.y + player.Radius / 2;

        guidedBull.vel.x = guidedBull.SpeedMax;
        guidedBull.vel.y = guidedBull.SpeedMax;
        guidedBull.acc = { 0 };
        //弾のフラグオン
        guidedBull.isAlive = true;
        guidedBull.isHit = false;
        guidedBull.isBossHit = false;
        guidedBull.isReflection = false;

        bossOld = Guided(playerOld, guidedBull.pos);

        //距離を測る
        guidedBull.posTmp = Guided(playerOld, guidedBull.pos);
        //正規化
        guidedBull.normalize = sqrt(guidedBull.posTmp.x * guidedBull.posTmp.x + guidedBull.posTmp.y * guidedBull.posTmp.y);

        if (bossOld.x < 0) {
            isPlayer2BulletLeft = true;
        }
        else {
            isPlayer2BulletLeft = false;
        }
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

void DrawBossGuidedBullet(Bullet& guidedBull, Boss& boss, Vector2& shake) {
    if (boss.isAlive) {
        if (guidedBull.isAlive) {
            //反射してないときの描画
            if (!guidedBull.isReflection) {
                if (guidedBull.isLeft) {
                    if (isPlayer2BulletLeft) {
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
                else {
                    if (isPlayer2BulletLeft) {
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
            //反射したときの描画
            else if (guidedBull.isReflection) {
                if (guidedBull.isLeft) {
                    if (boss.isLeft) {
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
                else {
                    if (boss.isLeft) {
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
            }
        }
    }
}