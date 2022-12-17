#include "../libOne/inc/libOne.h"
#include "GAME.h"
#include "STAGE.h"
#include "PLAYER.h"
namespace GAME04 {

	PLAYER::PLAYER(GAME* game):ACTOR(game){	}

	PLAYER::~PLAYER(){}

	void PLAYER::create()
	{
		Img[0] = loadImage("assets\\GAME04\\pacman0.png");
		Img[1] = loadImage("assets\\GAME04\\pacman1.png");
		Img[2] = loadImage("assets\\GAME04\\pacman2.png");

		Size = game()->stage()->size();
		OfstX = game()->stage()->ofstX();
		OfstY = game()->stage()->ofstY();
	}

	void PLAYER::destroy()
	{
	}

	void PLAYER::init()
	{
		Pos.set(466, 720);
		//Pos.set(60, 60);
		Speed = 2;
		Dir.set(Speed, Speed);
		AnimCnt = 0;
	}

	int PLAYER::Floor(int pos)
	{
		return pos / Size * Size;
	}
	void PLAYER::update()
	{
		STAGE* stage = game()->stage();
		//一時的な次の位置候補
		INT2 nextPos = Pos;
		if (isPress(KEY_D)) {
			//とりあえず右に進めてみる
			nextPos.x += Dir.x;
			Angle = 180;
			//画像右上の頂点が通り道上にある
			if (stage->pathway(nextPos.x + 29, nextPos.y)) {
				//Sizeの倍数になるように位置を強制的に設定
				nextPos.y = Floor(nextPos.y);
				Pos = nextPos;
			}
			//画像右下の頂点が通り道上にある
			else if (stage->pathway(nextPos.x + 29, nextPos.y + 29)) {
				//Sizeの倍数になるように位置を強制的に設定
				nextPos.y = Floor(nextPos.y + Size);
				Pos = nextPos;
			}
			//餌なら食べる
			stage->eaten(Pos.x, Pos.y);
		}
		//以下各方向で上記と同じ処理を行う
		else if (isPress(KEY_A)) {
			nextPos.x -= Dir.x;
			Angle = 0;
			if (stage->pathway(nextPos.x, nextPos.y)) {
				nextPos.y = Floor(nextPos.y);
				Pos = nextPos;
			}
			else if (stage->pathway(nextPos.x, nextPos.y + 29)) {
				nextPos.y = Floor(nextPos.y + Size);
				Pos = nextPos;
			}
			stage->eaten(Pos.x + 29, Pos.y);
		}
		else if (isPress(KEY_W)) {
			nextPos.y -= Dir.y;
			Angle = 90;
			if (stage->pathway(nextPos.x, nextPos.y)) {
				nextPos.x = Floor(nextPos.x);
				Pos = nextPos;
			}
			else if (stage->pathway(nextPos.x + 29, nextPos.y)) {
				nextPos.x = Floor(nextPos.x + Size);
				Pos = nextPos;
			}
			stage->eaten(Pos.x, Pos.y + 29);
		}
		else if (isPress(KEY_S)) {
			nextPos.y += Dir.y;
			Angle = -90;
			if (stage->pathway(nextPos.x, nextPos.y + 29)) {
				nextPos.x = Floor(nextPos.x);
				Pos = nextPos;
			}
			else if (stage->pathway(nextPos.x + 29, nextPos.y + 29)) {
				nextPos.x = Floor(nextPos.x + Size);
				Pos = nextPos;
			}
			stage->eaten(Pos.x, Pos.y);
		}
		//ワープ
		if (Pos.x < 2)
			Pos.x = 928;
		else if (Pos.x > 928)
			Pos.x = 2;
		//キーを押している間アニメーションする
		if (isPress(KEY_D) || isPress(KEY_A) || isPress(KEY_W) || isPress(KEY_S)) {
			AnimCnt++;
		}
		else {
			AnimCnt = 0;
		}
	}

	void PLAYER::draw()
	{
		float px = OfstX + Pos.x - Size/2;
		float py = OfstY + Pos.y - Size/2;
		int i = AnimCnt / 4 % 3;
		image(Img[i], px, py, Angle);

		//fill(120, 100, 100);
		//print((let)"PlayerPosX=" + Pos.x);
		//print((let)"PlayerPosY=" + Pos.y);
	}
}