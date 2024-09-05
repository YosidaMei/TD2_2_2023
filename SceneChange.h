#pragma once

struct TitleUi {
	Vector2 pos;
	int width;
	int height;
	int animationNum;
	int animationCoolTime;
	int textureHandle[2];
};

void Gameover(Player& player, Scene& scene, char key, char preKey, int button, int preButton);
void DrawGameover(Player& player);
void GameTitle(Scene& scene, char keyZ, char preKeyZ, char keyX, char preKeyX, int buttonA, int preButtonA, int buttonB, int preButtonB,
	Player& player, Hp hp[], Enemy& enemy, Boss& boss, Bullet& beam, Bullet& guidedBull, Bullet everyDirectionBullet[],
	int& isPattern, int& nowPattern, int& enemyAttack, Sword& sword, Sword& bossSword);

void DrawGameTitle();
void DrawTitleUi(TitleUi& titleUi);
void TitleSetting(TitleUi& titleUi);
void TitleAnimation(TitleUi& titleUi);

void Gameclear(Scene& scene, char key, char preKey, int button, int preButton);
void DrawGameclear();