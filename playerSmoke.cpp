#include <Novice.h>
#include "Common.h"
#include "Map.h"
#include "Player.h"

const int PlayerLandingSmokeMax = 128;
Smoke playerLandingSmoke[PlayerLandingSmokeMax];

const int PlayerRunSmokeMax = 128;
Smoke playerRunSmoke[PlayerRunSmokeMax];

const int PlayerJumpSmokeMax = 128;
Smoke playerJumpSmoke[PlayerJumpSmokeMax];

const int PlayerJumpingSmokeMax = 128;
Smoke playerJumpingSmoke[PlayerJumpingSmokeMax];

const int Player2JumpSmokeMax = 64;
Smoke player2JumpSmoke[Player2JumpSmokeMax];

const int PlayerDamageEffectMax = 128;
Smoke damegeEffect[PlayerDamageEffectMax];

void  PlayerLandingSmoke(Player& player) {


	int i = 0;

	if (player.isLand) {
		for (i = 0; i < PlayerLandingSmokeMax; i++) {
			playerLandingSmoke[i].isAlive = true;
			playerLandingSmoke[i].transparency = 0x88;
			//
			playerLandingSmoke[i].pos.x = player.pos.x + (rand() % (player.Size / 5 * 4) - player.Radius / 5 * 4);
			playerLandingSmoke[i].pos.y = player.pos.y + player.Radius;
			playerLandingSmoke[i].posSpeed = rand() % 5;
			playerLandingSmoke[i].transparencySpeed =(rand() % 20 + 10);
		}
	}

	//smokeの動き
	for (i = 0; i < PlayerLandingSmokeMax; i++) {
		if (playerLandingSmoke[i].isAlive) {
			playerLandingSmoke[i].pos.y -= playerLandingSmoke[i].posSpeed;
			playerLandingSmoke[i].transparency -= playerLandingSmoke[i].transparencySpeed;
			if (playerLandingSmoke[i].transparency <= 0x00) {
				playerLandingSmoke[i].transparency = 0x00;
				playerLandingSmoke[i].isAlive = false;

			}
		}

	}

}

void  DrawPlayerLandingSmoke(Vector2& shake, int &textureHandle) {

	int i = 0;
	int radius = 4;
	for (i = 0; i < PlayerLandingSmokeMax; i++) {
		if (playerLandingSmoke[i].isAlive) {
			Novice::DrawQuad(playerLandingSmoke[i].pos.x - radius + shake.x, playerLandingSmoke[i].pos.y - radius + shake.y,
				playerLandingSmoke[i].pos.x + radius + shake.x, playerLandingSmoke[i].pos.y - radius + shake.y,
				playerLandingSmoke[i].pos.x - radius + shake.x, playerLandingSmoke[i].pos.y + radius + shake.y,
				playerLandingSmoke[i].pos.x + radius + shake.x, playerLandingSmoke[i].pos.y + radius + shake.y,
				0, 0, 1, 1, textureHandle, 0x958D9400 + playerLandingSmoke[i].transparency);
			//Novice::DrawBox(playerLandingSmoke[i].pos.x - radius + shake.x, playerLandingSmoke[i].pos.y - radius + shake.y, radius * 2, radius * 2, 0, 0x958D9400 + playerLandingSmoke[i].transparency, kFillModeSolid);
		}
	}
}

void PlayerRunSmoke(Player& player) {

	int i = 0;
	int count = 0;
	int countMax = 2;

	if (player.isGround && player.vel.x != 0) {
		for (i = 0; i < PlayerRunSmokeMax; i++) {
			if (playerRunSmoke[i].isAlive == false) {
				count++;
				playerRunSmoke[i].isAlive = true;
				playerRunSmoke[i].transparency = 0x88;
				//
				if (player.isLeft) {
					playerRunSmoke[i].pos.x = player.pos.x + (rand() % player.Radius / 2);
				}
				else {
					playerRunSmoke[i].pos.x = player.pos.x - (rand() % player.Radius / 2);
				}
				playerRunSmoke[i].pos.y = player.pos.y + player.Radius;
				playerRunSmoke[i].posSpeed = rand() % 3;
				playerRunSmoke[i].transparencySpeed = (rand() % 10 + 5);
			}
			if (count == countMax) {
				break;
			}
		}
	}

	//smokeの動き
	for (i = 0; i < PlayerRunSmokeMax; i++) {
		if (playerRunSmoke[i].isAlive) {
			playerRunSmoke[i].pos.y -= playerRunSmoke[i].posSpeed;
			playerRunSmoke[i].transparency -= playerRunSmoke[i].transparencySpeed;
			if (playerRunSmoke[i].transparency <= 0x00) {
				playerRunSmoke[i].transparency = 0x00;
				playerRunSmoke[i].isAlive = false;

			}
		}

	}

}

void  DrawPlayerRunSmoke(Vector2& shake, int& textureHandle) {

	int i = 0;
	int radius = 4;
	for (i = 0; i < PlayerRunSmokeMax; i++) {
		if (playerRunSmoke[i].isAlive) {
			Novice::DrawQuad(playerRunSmoke[i].pos.x - radius + shake.x, playerRunSmoke[i].pos.y - radius + shake.y,
				playerRunSmoke[i].pos.x + radius + shake.x, playerRunSmoke[i].pos.y - radius + shake.y,
				playerRunSmoke[i].pos.x - radius + shake.x, playerRunSmoke[i].pos.y + radius + shake.y,
				playerRunSmoke[i].pos.x + radius + shake.x, playerRunSmoke[i].pos.y + radius + shake.y,
				0, 0, 1, 1, textureHandle, 0x958D9400 + playerRunSmoke[i].transparency);
			//Novice::DrawBox(playerRunSmoke[i].pos.x - radius + shake.x, playerRunSmoke[i].pos.y - radius + shake.y, radius * 2, radius * 2, 0, 0x958D9400 + playerRunSmoke[i].transparency, kFillModeSolid);
		}
	}
}

void PlayerJumpSmoke(Player & player) {


	int i = 0;

	if (player.isJumping && playerJumpSmoke[0].isAlive == false) {
		for (i = 0; i < PlayerJumpSmokeMax; i++) {
			playerJumpSmoke[i].isAlive = true;
			playerJumpSmoke[i].transparency = 0x88;
			//
			playerJumpSmoke[i].pos.x = player.pos.x + (rand() % (player.Size) - player.Radius);
			playerJumpSmoke[i].pos.y = 668.0;
			playerJumpSmoke[i].posSpeed = rand() % 5;
			playerJumpSmoke[i].transparencySpeed = (rand() % 20 + 10);
		}
	}
	if(!player.isJumping) {
		playerJumpSmoke[0].isAlive = false;
	}

	//smokeの動き
	for (i = 0; i < PlayerJumpSmokeMax; i++) {
		if (playerJumpSmoke[i].isAlive) {
			playerJumpSmoke[i].pos.y -= playerJumpSmoke[i].posSpeed;
			playerJumpSmoke[i].transparency -= playerJumpSmoke[i].transparencySpeed;
			if (playerJumpSmoke[i].transparency <= 0x00) {
				playerJumpSmoke[i].transparency = 0x00;
				if (i != 0) {
					playerJumpSmoke[i].isAlive = false;
				}
			}
		}
	}

}

void  DrawPlayerJumpSmoke(Vector2& shake, int& textureHandle) {

	int i = 0;
	int radius = 4;
	for (i = 0; i < PlayerJumpSmokeMax; i++) {
		if (playerJumpSmoke[i].isAlive) {
			Novice::DrawQuad(playerJumpSmoke[i].pos.x - radius + shake.x, playerJumpSmoke[i].pos.y - radius + shake.y,
				playerJumpSmoke[i].pos.x + radius + shake.x, playerJumpSmoke[i].pos.y - radius + shake.y,
				playerJumpSmoke[i].pos.x - radius + shake.x, playerJumpSmoke[i].pos.y + radius + shake.y,
				playerJumpSmoke[i].pos.x + radius + shake.x, playerJumpSmoke[i].pos.y + radius + shake.y,
				0, 0, 1, 1, textureHandle, 0x958D9400 + playerJumpSmoke[i].transparency);
			//Novice::DrawBox(playerJumpSmoke[i].pos.x - radius + shake.x, playerJumpSmoke[i].pos.y - radius + shake.y, radius * 2, radius * 2, 0, 0x958D9400 + playerJumpSmoke[i].transparency, kFillModeSolid);
		}
	}
}

void PlayerJumpingSmoke(Player& player) {

	int i = 0;
	int count = 0;
	int countMax = 2;

	if (player.isRise && player.vel.y < -10) {
		for (i = 0; i < PlayerJumpingSmokeMax; i++) {
			if (playerJumpingSmoke[i].isAlive == false) {
				count++;
				playerJumpingSmoke[i].isAlive = true;
				playerJumpingSmoke[i].transparency = 0x88;
				//
				playerJumpingSmoke[i].pos.x = player.pos.x + (rand() % player.Radius / 2 - player.Radius / 4);
				playerJumpingSmoke[i].pos.y = player.pos.y + player.Radius;
				playerJumpingSmoke[i].posSpeed = 0;
				playerJumpingSmoke[i].transparencySpeed = (rand() % 10 + 5);
			}
			if (count == countMax) {
				break;
			}
		}
	}

	//smokeの動き
	for (i = 0; i < PlayerJumpingSmokeMax; i++) {
		if (playerJumpingSmoke[i].isAlive) {
			playerJumpingSmoke[i].pos.y -= playerJumpingSmoke[i].posSpeed;
			playerJumpingSmoke[i].transparency -= playerJumpingSmoke[i].transparencySpeed;
			if (playerJumpingSmoke[i].transparency <= 0x00) {
				playerJumpingSmoke[i].transparency = 0x00;
				playerJumpingSmoke[i].isAlive = false;

			}
		}

	}

}

void  DrawPlayerJumpingSmoke(Vector2& shake, int& textureHandle) {

	int i = 0;
	int radius = 4;
	for (i = 0; i < PlayerJumpingSmokeMax; i++) {
		if (playerJumpingSmoke[i].isAlive) {
			Novice::DrawQuad(playerJumpingSmoke[i].pos.x - radius + shake.x, playerJumpingSmoke[i].pos.y - radius + shake.y,
				playerJumpingSmoke[i].pos.x + radius + shake.x, playerJumpingSmoke[i].pos.y - radius + shake.y,
				playerJumpingSmoke[i].pos.x - radius + shake.x, playerJumpingSmoke[i].pos.y + radius + shake.y,
				playerJumpingSmoke[i].pos.x + radius + shake.x, playerJumpingSmoke[i].pos.y + radius + shake.y,
				0, 0, 1, 1, textureHandle, 0x958D9400 + playerJumpingSmoke[i].transparency);
			//Novice::DrawBox(playerJumpingSmoke[i].pos.x - radius + shake.x, playerJumpingSmoke[i].pos.y - radius + shake.y, radius * 2, radius * 2, 0, 0x958D9400 + playerJumpingSmoke[i].transparency, kFillModeSolid);
		}
	}
}

void Player2JumpSmoke(Player& player) {


	int i = 0;

	if (player.is2jump && player2JumpSmoke[0].isAlive == false) {
		for (i = 0; i < Player2JumpSmokeMax; i++) {
			player2JumpSmoke[i].isAlive = true;
			player2JumpSmoke[i].transparency = 0x88;
			//
			player2JumpSmoke[i].pos.x = player.pos.x;
			player2JumpSmoke[i].pos.y = player.pos.y + player.Radius;
			player2JumpSmoke[i].vel.x = rand() % 10 - 5;
			player2JumpSmoke[i].vel.y = rand() % 10 - 5;
			player2JumpSmoke[i].transparencySpeed = (rand() % 20 + 10);
		}
	}
	if (!player.is2jump) {
		player2JumpSmoke[0].isAlive = false;
	}

	//smokeの動き
	for (i = 0; i < Player2JumpSmokeMax; i++) {
		if (player2JumpSmoke[i].isAlive) {
			player2JumpSmoke[i].pos.x += player2JumpSmoke[i].vel.x;
			player2JumpSmoke[i].pos.y += player2JumpSmoke[i].vel.y;
			player2JumpSmoke[i].transparency -= player2JumpSmoke[i].transparencySpeed;
			if (player2JumpSmoke[i].transparency <= 0x00) {
				player2JumpSmoke[i].transparency = 0x00;
				if (i != 0) {
					player2JumpSmoke[i].isAlive = false;
				}
			}
		}
	}

}

void  DrawPlayer2JumpSmoke(Vector2& shake, int& textureHandle) {

	int i = 0;
	int radius = 4;
	for (i = 0; i < Player2JumpSmokeMax; i++) {
		if (player2JumpSmoke[i].isAlive) {
			Novice::DrawQuad(player2JumpSmoke[i].pos.x - radius + shake.x, player2JumpSmoke[i].pos.y - radius + shake.y,
				player2JumpSmoke[i].pos.x + radius + shake.x, player2JumpSmoke[i].pos.y - radius + shake.y,
				player2JumpSmoke[i].pos.x - radius + shake.x, player2JumpSmoke[i].pos.y + radius + shake.y,
				player2JumpSmoke[i].pos.x + radius + shake.x, player2JumpSmoke[i].pos.y + radius + shake.y,
				0, 0, 1, 1, textureHandle, 0x958D9400 + player2JumpSmoke[i].transparency);
			//Novice::DrawBox(player2JumpSmoke[i].pos.x - radius + shake.x, player2JumpSmoke[i].pos.y - radius + shake.y, radius * 2, radius * 2, 0, 0x958D9400 + player2JumpSmoke[i].transparency, kFillModeSolid);
		}
	}
}


void PlayerDamageEffectSetting(Player& player,float hitPos) {

	int i = 0;
	for (i = 0; i < PlayerDamageEffectMax; i++) {
		damegeEffect[i].isAlive = true;
		damegeEffect[i].transparency = 0x88;
		//
		if (player.pos.x > hitPos) {
			damegeEffect[i].vel.x = rand() % 31 + 1;
		}
		else {
			damegeEffect[i].vel.x = rand() % 30 - 30;
		}
		damegeEffect[i].pos.x = player.pos.x;
		damegeEffect[i].pos.y = player.pos.y;
		damegeEffect[i].vel.y = rand() % 31 - 15;
		damegeEffect[i].transparencySpeed = (rand() % 11 + 5);
	}
	damegeEffect[0].posSpeed = 10;
	damegeEffect[1].posSpeed = 2;
}

void PlayerDamageEffect() {

	int i = 0;

	//smokeの動き
	for (i = 0; i < PlayerDamageEffectMax; i++) {
		if (damegeEffect[i].isAlive) {
			damegeEffect[i].pos.x += damegeEffect[i].vel.x;
			damegeEffect[i].pos.y += damegeEffect[i].vel.y;
			damegeEffect[i].transparency -= damegeEffect[i].transparencySpeed;
			if (damegeEffect[i].transparency <= 0x00) {
				damegeEffect[i].transparency = 0x00;
				damegeEffect[i].isAlive = false;
			}
		}
	}
}

void  DrawPlayerDamageEffect(Vector2& shake, int& textureHandle) {

	int i = 0;
	int radius = 4;
	for (i = 0; i < PlayerDamageEffectMax; i++) {
		if (damegeEffect[i].isAlive) {
			Novice::DrawQuad(damegeEffect[i].pos.x - radius + shake.x, damegeEffect[i].pos.y - radius + shake.y,
				damegeEffect[i].pos.x + radius + shake.x, damegeEffect[i].pos.y - radius + shake.y,
				damegeEffect[i].pos.x - radius + shake.x, damegeEffect[i].pos.y + radius + shake.y,
				damegeEffect[i].pos.x + radius + shake.x, damegeEffect[i].pos.y + radius + shake.y,
				0, 0, 1, 1, textureHandle, 0xE83E4E00 + damegeEffect[i].transparency);
			//Novice::DrawBox(damegeEffect[i].pos.x - radius + shake.x, damegeEffect[i].pos.y - radius + shake.y, radius * 2, radius * 2, 0, 0xE83E4E00 + damegeEffect[i].transparency, kFillModeSolid);
		}
	}

}

void PlayerDamageEffectReset() {
	
	int i = 0;
	for (i = 0; i < PlayerDamageEffectMax; i++) {
		damegeEffect[i].isAlive = false;

	}
}