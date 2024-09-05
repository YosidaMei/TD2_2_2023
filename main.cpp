#include <Novice.h>
#include"Common.h"
#include "Map.h"
#include"Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Boss.h"
#include<time.h>
#include "CollsionEffect.h"
#include "SceneChange.h"
#include "Tutorial.h"
#include "MapEffect.h"

static int IsPressButton(int stickNo, PadButton button);

int IsPressButton(int stickNo, PadButton button)
{
	enum PadButton {

		kPadButton10,//Aボタン
		kPadButton11//Bボタン
	};
}

const char kWindowTitle[] = "LC1A_ディスコ老人会";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WinWidth, WinHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//マップ設定
	int map[MapHeight][MapWidth] = {};
	MapLoading(map);
	int mapTextureHandle = Novice::LoadTexture("./Resouce/Texture/mapChip.png");

	//ゲームパッドスティック入力
	int inputStickX;
	int inputStickY;

	//ゲームパッドボタン入力
	int jumpBottun = 0;
	int preJumpBottun = 0;

	int attackBottan = 0;
	int preAttackBottan = 0;

	//タイトル
	TitleUi titleUi = {};
	TitleSetting(titleUi);

	int overClearUiGh = Novice::LoadTexture("./Resouce/Texture/overClearUi.png");
	int gameOverGh = Novice::LoadTexture("./Resouce/Texture/gameOver.png");
	int gameClearGh = Novice::LoadTexture("./Resouce/Texture/gameClear.png");
	int clearUiGh= Novice::LoadTexture("./Resouce/Texture/ClearUi.png");

	//プレイヤー設定
	Player player = {};
	PlayerSetting(player);

	
	Hp hp[2] = {};//プレイヤーHPのUI
	HpSetting(hp);

	//プレイヤーUI
	int playerUiGh = Novice::LoadTexture("./Resouce/Texture/controlUi2.png");

	//エネミー設定
	Enemy enemy = {};
	EnemySetting(enemy);


	Bullet bullet = {};

	Bullet beam = {};
	beam.textureHandle= Novice::LoadTexture("./Resouce/Texture/bossBeam.png");

	Bullet guidedBull = {};
	guidedBull.textureHandle = Novice::LoadTexture("./Resouce/Texture/EnemySwrodGuide.png");

	Bullet everyDirectionBullet[5] = {};
	for (int i = 0; i < 5; i++) {
		everyDirectionBullet[i].textureHandle = Novice::LoadTexture("./Resouce/Texture/Enemyswrod.png");
	}

	Boss boss = {};
	BossSetting(boss);

	//攻撃パターン
	int isPattern = 0;
	int nowPatten = 0;
	int enemyAttack = 0;

	BossBeamSet(beam, boss, player);
	BossGuidedBulletSet(guidedBull, boss, player);
	BossEveryDirectionSet(everyDirectionBullet, boss, player);

	//乱数
	unsigned int currentTime = time(nullptr);
	srand(currentTime);

	Sword sword = {};
	SwordSetting(sword);

	Sword bossSword = {};
	BossSwordSetting(bossSword);

	Scene scene = title;

	//---ヒットストップ---//
	int hitStoptime = 0;
	int prePlayerHp = player.Hp;
	int preEnemyHp = enemy.Hp;
	int preBossHp = boss.Hp;

	//---カメラシェイク---//
	Vector2 shake = { 0,0 };
	int shakeTime = 0;

	//音
	AudioSetting();

	//マウスカーソル非表示
	Novice::SetMouseCursorVisibility(0);

	//エフェクト
	int effectTextureHandle = Novice::LoadTexture("white1x1.png");

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();


		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//---フルスクリーン切り替え---//
		ScreenChange(keys[DIK_F4], preKeys[DIK_F4]);

		//padのジャンプ入力処理

		preJumpBottun = jumpBottun;
		
		if (Novice::IsPressButton(0, kPadButton10)) {

			jumpBottun = 1;

		}
		else {
			jumpBottun = 0;
		}

		//タイトルアニメ
		TitleAnimation(titleUi);

		//padのアタック入力処理
		preAttackBottan = attackBottan;
		if (Novice::IsPressButton(0, kPadButton11)) {
			attackBottan = true;
		}
		else {
			attackBottan = false;
		}

		if (hitStoptime == 0) {

			//---チュートリアル---//
			if (scene == tutorial) {
				Tutorial(player, scene);
			}

			//---プレイヤー関係---//
			if (scene == gameBoss1 || scene == gameBoss2 || scene == tutorial) {

				Novice::GetAnalogInputLeft(0, &inputStickX, &inputStickY);

				if (player.isAlive) {
					PlayerKeyInput(player, keys[DIK_LEFT], keys[DIK_RIGHT], inputStickX);//プレイヤーキー入力移動
					PlayerJamp(player, keys[DIK_Z], preKeys[DIK_Z], jumpBottun, preJumpBottun);//プレイヤーキー入力ジャンプ
					PlayerMove(player, map);//プレイヤー移動
					PlayerAttack(player, keys[DIK_X], preKeys[DIK_X], attackBottan, preAttackBottan, map);//プレイヤー攻撃
				}

				PlayerAnimation(player);
				PlayerQuad(player);//プレイヤーの四角
				PlayerAfterimage(player);

				//---プレイヤーの剣---//
				SwordFunction(sword, player);

				//---プレイヤー煙---//
				PlayerLandingSmoke(player);
				PlayerRunSmoke(player);
				PlayerJumpSmoke(player);
				PlayerJumpingSmoke(player);
				Player2JumpSmoke(player);

				//---プレイヤーHP---//
				HpQuad(hp, player);
				HpEffectUpdate(player);

				//プレイヤー音
				PlayerAudio(player);

			}

			if (scene == gameBoss1 || scene == gameBoss2) {
				BackEffSet(scene);
				EffectUpdate(scene, boss);
			}

			//---ボス1関係---//
			if (scene == gameBoss1) {

				if (enemy.isAlive) {

					//ボスの攻撃選択用


					EnemyActionTable(enemy, player, keys, enemyAttack, map, bullet, beam, guidedBull, everyDirectionBullet);

				}
				else {
					enemyAttack = 999;
				}

				//四角の読み取り
				EnemyQuad(enemy);

				EnemyHitBoxQuad(enemy);

				//ボスの当たり判定
				EnemyHitBox(player, enemy);//第一段階

				//アニメーション
				EnemyAnimation(enemy);

				//---エネミーエフェクト---//
				//EnemyEffect(enemy);

				//---ボス2への準備---//
				boss.pos.x = enemy.pos.x;
				boss.pos.y = enemy.pos.y;
				bossSword.Pos.x = enemy.pos.x;
				bossSword.Pos.y = -50;
			}

			if (scene == gameBoss1 || scene == gameBoss2) {
				EnemyDead(enemy,beam, everyDirectionBullet, guidedBull, scene);
			}

			if (scene == gameBoss2 || scene == gameclear) {
				BossDead(boss, scene);
			}

			//---ボス2関係---//
			if (scene == gameBoss2) {

				if (boss.isAlive) {
					//ボスのテーブル
					BossActionTable(boss, player, keys, isPattern, map, bullet, beam, guidedBull, everyDirectionBullet);

					nowPatten = isPattern;

					//ボスの行動切り替え
					if (boss.isAction == false && isPattern == nowPatten)
					{
						if (boss.Hp > 100)
						{
							isPattern = rand() % 7 + 1;
						}
						else
						{
							isPattern = rand() % 5 + 6;
						}

					}

					//はみ出し確認
					BossPositionClamp(boss);
				}

				//---剣---//
				BossSwordFunction(bossSword, boss);

				//四角の読み取り
				BossQuad(boss);

				//残像
				BossAfterimage(boss);

				//ボスの当たり判定
				BossHitBox(player, boss);//第二段階

				BossAnimation(boss);//アニメーション

				//---エフェクト---//
				BossChargeEffect();

			}

			//---あたり判定取得後のエフェクト---//
			if (scene == gameBoss1 || scene == gameBoss2) {
				//---剣はじく---//
				RepelTheSwordEffect();

				//---ダメージエフェクト---//
				PlayerDamageEffect();//プレイヤーダメージエフェクト
				EnemyDamageEffect();//エネミーダメージエフェクト
				BossDamageEffect();//ボスダメージエフェクト
			}

			if (scene == gameBoss1 || scene == gameBoss2 || scene == gameover || scene == title) {
				Gameover(player, scene, keys[DIK_Z], preKeys[DIK_Z], jumpBottun, preJumpBottun);
			}

			if (scene == gameBoss1 || scene == gameBoss2 || scene == gameclear || scene == title) {
				Gameclear(scene, keys[DIK_Z], preKeys[DIK_Z], jumpBottun, preJumpBottun);
			}

			//カメラシェイク
			CameraShake(shake, shakeTime);

			//ヒットストップ
			//プレイヤー
			if (HpDown(player.Hp, prePlayerHp)) {
				hitStoptime = 2;
				shakeTime = 30;
				StopAudio(playerDamage);
				PlayAudio(playerDamage);
			}
			//エネミー
			if (HpDown(enemy.Hp, preEnemyHp)) {
				hitStoptime = 2;
				StopAudio(enemyDamage);
				PlayAudio(enemyDamage);
			}
			//ボス
			if (HpDown(boss.Hp, preBossHp)) {
				hitStoptime = 2;
				StopAudio(enemyDamage);
				PlayAudio(enemyDamage);
			}

		}
		//ヒットストップ中
		else {
			hitStoptime--;
		}
		
		if (scene == title || scene == gameover || scene == gameclear || scene == tutorial || scene == gameBoss1) {
			GameTitle(scene, keys[DIK_Z], preKeys[DIK_Z], keys[DIK_X], preKeys[DIK_X], jumpBottun, preJumpBottun,attackBottan,preAttackBottan,
				player,hp,enemy,boss,beam,guidedBull,everyDirectionBullet,
				isPattern, nowPatten, enemyAttack, sword, bossSword);
		}

		if (scene != title && scene != tutorial) {
			LoopBGM();
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		if (scene == gameBoss1 || scene == gameBoss2 || scene == tutorial || scene == gameclear) {

			DrawMap(mapTextureHandle, map, shake);//マップ描画

		}
		if (scene == gameBoss1 || scene == gameBoss2) {
			DrawEffect(scene,boss, effectTextureHandle);
		}

		//---ボス1関係---//
		if (scene == gameBoss1) {
			//攻撃描画
				switch (enemyAttack)
				{
				case 0:

					break;
				case 3:
					DrawEnemyBeam(beam, enemy, shake);//ビーム描画
					break;
				case 7:
					DrawGuidedBullet(guidedBull, enemy, shake);//誘導弾描画

					break;
				case 11:
					DrawEveryDirection(everyDirectionBullet, shake);//全方位弾

					break;
				}

			//DrawEnemyEffect(shake);
			DrawEnemy(enemy, shake);//エネミー描画
			DrawEnemyDamageEffect(shake, effectTextureHandle);//エネミーダメージエフェクト

		}

		if (scene == gameBoss1 || scene == gameBoss2) {
			DrawEnemyChangeEffect(enemy, shake,scene, effectTextureHandle);
		}
		//---ボス2関係---//
		if (scene == gameBoss2) {
			

			if (boss.isAlive) {
				//---剣---//
				DrowBossSword(bossSword, boss, shake);
				DrawBossSwordEffect(boss, shake);

				DrawBoss(boss, shake);//ボス描画

				//ボス攻撃
				DrawBossBeam(beam, boss, shake);//ビーム描画
				DrawBossEveryDirection(everyDirectionBullet, shake);//全方位弾
				DrawBossGuidedBullet(guidedBull, boss, shake);//誘導弾描画
			}
			//DrawAttackBoss(boss);//デバッグ

			DrawBossDamageEffect(shake, effectTextureHandle);

			DrawBossDeadEffect(boss, shake, effectTextureHandle);

			//---エフェクト---//
			DrawBossCharge(boss,isPattern, shake);

		}

		if (scene == gameBoss1 || scene == gameBoss2 || scene == tutorial || scene == gameclear) {


			//剣の軌跡のエフェクト
			DrawSwordEffect(player, shake);

			DrowSword(sword, player, shake);
			//---パーティクル・エフェクト---//
			//---剣はじく---//
			DrawRepelTheSwordEffect(shake, effectTextureHandle);
			
			//---プレイヤー煙---//
			DrawPlayerLandingSmoke(shake, effectTextureHandle);
			DrawPlayerRunSmoke(shake, effectTextureHandle);
			DrawPlayerJumpSmoke(shake, effectTextureHandle);
			DrawPlayerJumpingSmoke(shake, effectTextureHandle);
			DrawPlayer2JumpSmoke(shake, effectTextureHandle);
			//---プレイヤーHP---//
			DrawHp(hp, player, shake);
			DrawPlayerUi(playerUiGh);

			//---プレイヤー関係---//
			DrawPlayer(player, shake);//プレイヤー描画
			DrawPlayerDamageEffect(shake, effectTextureHandle);//ダメージ

		}

		//チュートリアル
		if (scene == tutorial) {
			DrawTutorial();
		}

		if (scene == title || scene == gameover || scene == gameclear || scene == tutorial || scene == gameBoss1) {
			DrawGameTitle();
		}

		if (scene == gameBoss1 || scene == gameBoss2 || scene == gameover || scene == title) {
			DrawGameover(player);
		}

		if (scene == gameBoss1 || scene == gameBoss2 || scene == gameclear || scene == title) {
			DrawGameclear();
		}
		
		//UI
		if (scene == title) {
			DrawTitleUi(titleUi);
		}
		if (scene == gameover) {
			Novice::DrawSprite(190, 162, gameOverGh, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(300, 526, overClearUiGh, 1, 1, 0.0f, 0xFFFFFFFF);
		}
		if (scene == gameclear) {
			Novice::DrawSprite(190, 162, gameClearGh, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(300, 526, clearUiGh, 1, 1, 0.0f, 0xFFFFFFFF);
		}

		if (scene == gameBoss1 || scene == gameBoss2) {
			DrawHpEffect(player, effectTextureHandle);
		}


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

