#include <Novice.h>
#include "Common.h"
#include "Map.h"
#include "Player.h"
#include "Collision.h"

void PlayerBeamKeyInput(Player& player) {
	
	//キーが押されたか
	if (player.gauge == player.GaugeMax && player.beam.cooltime == 0 && player.beam.time == 0) {
		player.beam.time = player.beam.timeMax;
		player.beam.isLeft = player.isLeft;
		player.beam.Pos.x = player.pos.x + player.Radius;
		player.beam.Pos.y = player.pos.y;
		player.gauge -= player.beam.gaugeCost;
		if (player.gauge < 0) {
			player.gauge = 0;
		}
	}

}

void PlayerBeamMove(Player &player,int map[MapHeight][MapWidth]) {

	//攻撃中処理
	if (player.beam.cooltime == 0 && player.beam.time > 0) {
		//向き
		if (player.beam.isLeft) {
			player.beam.Pos.x -= player.BeamSpeed;
			//ブロック衝突
			if (CollisionMap(map, player.beam.Pos.x, player.beam.Pos.y, player.beam.Radius.x, leftBottom) != none ||
				CollisionMap(map, player.beam.Pos.x, player.beam.Pos.y, player.beam.Radius.x, leftBottom) != none) {
				player.beam.time = 0;
			}
		}
		else {
			player.beam.Pos.x += player.BeamSpeed;
			//ブロック衝突
			if (CollisionMap(map, player.beam.Pos.x, player.beam.Pos.y, player.beam.Radius.x, rightTop) != none ||
				CollisionMap(map, player.beam.Pos.x, player.beam.Pos.y, player.beam.Radius.x, rightBottom) != none) {
				player.beam.time = 0;
			}
		}
		//タイム
		if (player.beam.time == 0) {
			player.beam.cooltime = player.beam.cooltimeMax;
		}
		else {
			player.beam.time--;
		}
	}
	else {
		player.beam.Pos.x = -100;
		player.beam.Pos.x = -100;
	}
	//クールタイム
	if (player.beam.cooltime != 0) {
		player.beam.cooltime--;
	}

}