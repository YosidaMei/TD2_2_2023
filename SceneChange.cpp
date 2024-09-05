#include "Common.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Bullet.h"
#include "CollsionEffect.h"
#include "SceneChange.h"

int GameoverTransparency = 0;
int GameoverTransparencySpeed = 6;

int GameTitleTransparency = 0xFF;
int GameTitleTransparencySpeed = 6;

int GameclearTransparency = 0;
int GameclearTransparencySpeed = 6;

void Gameover(Player& player, Scene& scene,char key, char preKey, int button, int preButton) {

	if (player.Hp <= 0 && scene != gameover && scene != title) {
		player.isAlive = false;
	}
	if (!player.isAlive && scene != gameover && scene != title) {
		GameoverTransparency += GameoverTransparencySpeed;
		if (GameoverTransparency >= 0xFF) {
			GameoverTransparency = 0xFF;
			scene = gameover;
		}
	}
	if (((key != 0 && preKey == 0) || (button != 0 && preButton == 0)) && scene == gameover) {
		scene = title;
		GameTitleTransparency = 0xFF;
		AllStopAudio();
	}
	if (scene == title && GameoverTransparency > 0x00) {
		GameoverTransparency -= GameoverTransparencySpeed;
		if (GameoverTransparency <= 0x00) {
			GameoverTransparency = 0x00;
		}
	}
}

void DrawGameover(Player& player) {

	if (!player.isAlive) {
		Novice::DrawBox(0, 0, WinWidth, WinHeight, 0, 0x00000000 + GameoverTransparency, kFillModeSolid);
	}

}

void GameTitle(Scene& scene, char keyZ, char preKeyZ, char keyX, char preKeyX, int buttonA, int preButtonA, int buttonB, int preButtonB,
	Player& player, Hp hp[], Enemy& enemy, Boss& boss, Bullet &beam, Bullet &guidedBull, Bullet everyDirectionBullet[],
	int &isPattern, int &nowPattern, int &enemyAttack, Sword &sword, Sword &bossSword) {

	if (scene == title && GameoverTransparency <= 0x00 && GameclearTransparency <= 0x00) {
		if ((keyZ != 0 && preKeyZ == 0) || (buttonA != 0 && preButtonA == 0)) {

			//ここでリセット
			PlayerSetting(player);
			HpSetting(hp);
			EnemySetting(enemy);
			BossSetting(boss);
			BossBeamSet(beam, boss, player);
			BossGuidedBulletSet(guidedBull, boss, player);
			BossEveryDirectionSet(everyDirectionBullet, boss, player);
			isPattern = 0;
			nowPattern = 0;
			enemyAttack = 0;
			SwordSetting(sword);
			BossSwordSetting(bossSword);
			BossActionTableSetting();
			PlayerDamageEffectReset();
			RepelTheSwordEffectReset();
			
			scene = tutorial;
		}
		else if ((keyX != 0 && preKeyX == 0) || (buttonB != 0 && preButtonB == 0)) {

			//ここでリセット
			PlayerSetting(player);
			HpSetting(hp);
			EnemySetting(enemy);
			BossSetting(boss);
			BossBeamSet(beam, boss, player);
			BossGuidedBulletSet(guidedBull, boss, player);
			BossEveryDirectionSet(everyDirectionBullet, boss, player);
			isPattern = 0;
			nowPattern = 0;
			enemyAttack = 0;
			SwordSetting(sword);
			BossSwordSetting(bossSword);
			BossActionTableSetting();
			PlayerDamageEffectReset();
			RepelTheSwordEffectReset();

			scene = gameBoss1;
		}
	}
	if ((scene == gameBoss1 || scene == tutorial) && GameTitleTransparency > 0x00) {
		GameTitleTransparency -= GameTitleTransparencySpeed;
		if (GameTitleTransparency <= 0x00) {
			GameTitleTransparency = 0x00;
		}
	}
}


void TitleSetting(TitleUi& titleUi) {
	titleUi.pos.x = 204.0f;
	titleUi.pos.y = 162.0f;
	titleUi.width = 850;
	titleUi.height = 120;
	titleUi.textureHandle[0] = Novice::LoadTexture("./Resouce/Texture/titleLogo.png");
	titleUi.textureHandle[1] = Novice::LoadTexture("./Resouce/Texture/titleUi.png");

	titleUi.animationNum = 0;
	titleUi.animationCoolTime = 300;

	
	titleUi.animationCoolTime--;
	if (titleUi.animationCoolTime <= 0) {
		titleUi.animationNum++;
		if (titleUi.animationNum >= 5) {
			titleUi.animationNum = 0;
		}
		titleUi.animationCoolTime = 300;
	}
	
}

void TitleAnimation(TitleUi& titleUi) {
		titleUi.animationNum++;
		if (titleUi.animationNum >= 4) {
			titleUi.animationNum = 4;
		}
		if (titleUi.animationNum == 4) {
			titleUi.animationCoolTime--;
		}
	if (titleUi.animationCoolTime <= 0) {

		titleUi.animationCoolTime = 100;
		titleUi.animationNum = 0;
	}
		
}

void DrawGameTitle() {

	Novice::DrawBox(0, 0, WinWidth, WinHeight, 0, 0x24242E00 + GameTitleTransparency, kFillModeSolid);

}
void DrawTitleUi(TitleUi& titleUi) {
	Novice::DrawQuad(
		titleUi.pos.x, titleUi.pos.y,
		titleUi.pos.x + titleUi.width, titleUi.pos.y,
		titleUi.pos.x, titleUi.pos.y + titleUi.height,
		titleUi.pos.x + titleUi.width, titleUi.pos.y + titleUi.height,
		titleUi.width * titleUi.animationNum, 0, titleUi.width, titleUi.height, titleUi.textureHandle[0], 0xFFFFFFFF);

	Novice::DrawSprite(240, 526, titleUi.textureHandle[1], 1, 1, 0.0f, 0xFFFFFFFF);
}


void Gameclear(Scene& scene, char key, char preKey, int button, int preButton) {

	if (scene == gameclear) {
		GameclearTransparency += GameclearTransparencySpeed;
		if (GameclearTransparency >= 0xFF) {
			GameclearTransparency = 0xFF;
		}
	}
	if (((key != 0 && preKey == 0) || (button != 0 && preButton == 0)) && GameclearTransparency == 0xFF) {
		scene = title;
		GameTitleTransparency = 0xFF;
		AllStopAudio();
	}
	if (scene == title && GameclearTransparency > 0x00) {
		GameclearTransparency -= GameclearTransparencySpeed;
		if (GameclearTransparency <= 0x00) {
			GameclearTransparency = 0x00;
		}
	}
}

void DrawGameclear() {

	Novice::DrawBox(0, 0, WinWidth, WinHeight, 0, 0xF0F1F000 + GameclearTransparency, kFillModeSolid);

}