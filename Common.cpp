#include"Common.h"


//---音---//
const int audioMax = 13;
int audioHandle[audioMax] = { };
int playHandle[audioMax] = { };
float volume[audioMax] = {};
int BGMCountMAX = 3600 + 679;
int bgmCount = 0;

void ScreenChange(int KeyReturn,int preKeyReturn) {
	static bool screenmode = false;

	if (KeyReturn && !preKeyReturn)
	{
		if (screenmode == false)
		{
			screenmode = true;
		}
		else
		{
			screenmode = false;
		}
	}

	if (screenmode == false)
	{
		//Novice::SetWindowMode(kFullscreen);
		//マウスカーソル非表示
		Novice::SetMouseCursorVisibility(0);
	}
	else if (screenmode == true)
	{
		//Novice::SetWindowMode(kWindowed);
		//マウスカーソル表示
		Novice::SetMouseCursorVisibility(1);
	}

}

Vector2 Guided(Vector2& targetPos, Vector2& fromPos) {
	Vector2 result;

	result.x = (targetPos.x - fromPos.x);
	result.y = (targetPos.y - fromPos.y);

	return result;
}

//ヒットストップ用
bool HpDown(int &hp, int &preHp) {

	if (hp < preHp) {
		preHp = hp;
		return true;
	}
	else {
		preHp = hp;
		return false;
	}

}

//カメラシェイク
void CameraShake(Vector2 &shake, int &shakeTime) {

	//シェイクタイムが大きいほどシェイク
	int shakeMax = shakeTime / 10 + 1;
	if (shakeTime > 0) {
		shake.x = rand() % (shakeMax * 2 + 1) - shakeMax;
		shake.y = rand() % (shakeMax * 2 + 1) - shakeMax;
		//シェイクタイムを減らす
		shakeTime--;
	}

}

void AudioSetting() {

	audioHandle[playerMove] = Novice::LoadAudio("./Resouce/Audio/kutu.mp3");
	volume[playerMove] = 2.0f;

	audioHandle[swordRepel] = Novice::LoadAudio("./Resouce/Audio/ken.mp3");
	volume[swordRepel] = 1.5f;

	audioHandle[teleportation] = Novice::LoadAudio("./Resouce/Audio/move.mp3");
	volume[teleportation] = 2.0f;

	audioHandle[beanCharge] = Novice::LoadAudio("./Resouce/Audio/bimu.mp3"); 
	volume[beanCharge] = 2.0f;

	audioHandle[playerAttack] = Novice::LoadAudio("./Resouce/Audio/p_atack.mp3");
	volume[playerAttack] = 2.0f;

	audioHandle[playerDamage] = Novice::LoadAudio("./Resouce/Audio/p_dame.mp3");
	volume[playerDamage] = 2.0f;

	audioHandle[playerJump] = Novice::LoadAudio("./Resouce/Audio/p_jamp.mp3");
	volume[playerJump] = 2.0f;

	audioHandle[enemyDamage] = Novice::LoadAudio("./Resouce/Audio/enemy_dame.mp3");
	volume[enemyDamage] = 2.0f;

	audioHandle[bossChange1] = Novice::LoadAudio("./Resouce/Audio/boss_a.mp3");
	volume[bossChange1] = 3.0f;

	audioHandle[bossChange2] = Novice::LoadAudio("./Resouce/Audio/boss_b.mp3");
	volume[bossChange2] = 3.0f;

	audioHandle[bossChage] = Novice::LoadAudio("./Resouce/Audio/boss_cha.mp3");
	volume[bossChage] = 2.0f;

	audioHandle[bossAttack] = Novice::LoadAudio("./Resouce/Audio/p_atack2.mp3");
	volume[bossAttack] = 2.0f;

	audioHandle[BGM1] = Novice::LoadAudio("./Resouce/Audio/BGM1.mp3");
	volume[BGM1] = 1.0f;

	for (int i = 0; i < audioMax; i++) {
		playHandle[i] = -1;
	}

}

void PlayAudio(AudioNumber num) {
	if (playHandle[num] == -1 or not Novice::IsPlayingAudio(playHandle[num])) {
		if (num != BGM1) {
			playHandle[num] = Novice::PlayAudio(audioHandle[num], 0, volume[num]);
		}
		else {
			playHandle[num] = Novice::PlayAudio(audioHandle[num], 1, volume[num]);
			bgmCount = 0;
		}
	}
}

void StopAudio(AudioNumber num) {
	if(playHandle[num] == -1){
		return;
	}
	Novice::StopAudio(playHandle[num]);
}

void AllStopAudio() {

	for (int i = 0; i < audioMax; i++) {
		Novice::StopAudio(playHandle[i]);
	}

}
void LoopBGM() {

	bgmCount++;
	if (bgmCount == BGMCountMAX) {
		bgmCount = 1;
		Novice::StopAudio(playHandle[BGM1]);
		playHandle[BGM1] = Novice::PlayAudio(audioHandle[BGM1], 1, volume[BGM1]);
	}

}