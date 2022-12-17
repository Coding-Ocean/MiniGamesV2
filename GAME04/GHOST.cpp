#include "../libOne/inc/libOne.h"
#include "GAME.h"
#include "STAGE.h"
#include "PLAYER.h"
#include "GHOST.h"
namespace GAME04 {

	GHOST::GHOST(int no, GAME* game)
		:ACTOR(game)
		, No(no)
	{
		DepartureCnt[0] = 0;
		DepartureCnt[1] = 60;
		DepartureCnt[2] = 120;
		DepartureCnt[3] = 240;
		DIR[U].set(0, -1);
		DIR[L].set(-1, 0);
		DIR[D].set(0, 1);
		DIR[R].set(1, 0);
	}

	GHOST::~GHOST()
	{
	}

	void GHOST::create()
	{
		if (No == 0) {
			Imgs[0][0][0] = loadImage("assets\\GAME04\\ghost_red_u0.png");
			Imgs[0][0][1] = loadImage("assets\\GAME04\\ghost_red_u1.png");
			Imgs[0][1][0] = loadImage("assets\\GAME04\\ghost_red_l0.png");
			Imgs[0][1][1] = loadImage("assets\\GAME04\\ghost_red_l1.png");
			Imgs[0][2][0] = loadImage("assets\\GAME04\\ghost_red_d0.png");
			Imgs[0][2][1] = loadImage("assets\\GAME04\\ghost_red_d1.png");
			Imgs[0][3][0] = loadImage("assets\\GAME04\\ghost_red_r0.png");
			Imgs[0][3][1] = loadImage("assets\\GAME04\\ghost_red_r1.png");
		}
		else if (No == 1) {
			Imgs[1][0][0] = loadImage("assets\\GAME04\\ghost_pink_u0.png");
			Imgs[1][0][1] = loadImage("assets\\GAME04\\ghost_pink_u1.png");
			Imgs[1][1][0] = loadImage("assets\\GAME04\\ghost_pink_l0.png");
			Imgs[1][1][1] = loadImage("assets\\GAME04\\ghost_pink_l1.png");
			Imgs[1][2][0] = loadImage("assets\\GAME04\\ghost_pink_d0.png");
			Imgs[1][2][1] = loadImage("assets\\GAME04\\ghost_pink_d1.png");
			Imgs[1][3][0] = loadImage("assets\\GAME04\\ghost_pink_r0.png");
			Imgs[1][3][1] = loadImage("assets\\GAME04\\ghost_pink_r1.png");
		}
		else if (No == 2) {
			Imgs[2][0][0] = loadImage("assets\\GAME04\\ghost_green_u0.png");
			Imgs[2][0][1] = loadImage("assets\\GAME04\\ghost_green_u1.png");
			Imgs[2][1][0] = loadImage("assets\\GAME04\\ghost_green_l0.png");
			Imgs[2][1][1] = loadImage("assets\\GAME04\\ghost_green_l1.png");
			Imgs[2][2][0] = loadImage("assets\\GAME04\\ghost_green_d0.png");
			Imgs[2][2][1] = loadImage("assets\\GAME04\\ghost_green_d1.png");
			Imgs[2][3][0] = loadImage("assets\\GAME04\\ghost_green_r0.png");
			Imgs[2][3][1] = loadImage("assets\\GAME04\\ghost_green_r1.png");
		}
		else if (No == 3) {
			Imgs[3][0][0] = loadImage("assets\\GAME04\\ghost_orange_u0.png");
			Imgs[3][0][1] = loadImage("assets\\GAME04\\ghost_orange_u1.png");
			Imgs[3][1][0] = loadImage("assets\\GAME04\\ghost_orange_l0.png");
			Imgs[3][1][1] = loadImage("assets\\GAME04\\ghost_orange_l1.png");
			Imgs[3][2][0] = loadImage("assets\\GAME04\\ghost_orange_d0.png");
			Imgs[3][2][1] = loadImage("assets\\GAME04\\ghost_orange_d1.png");
			Imgs[3][3][0] = loadImage("assets\\GAME04\\ghost_orange_r0.png");
			Imgs[3][3][1] = loadImage("assets\\GAME04\\ghost_orange_r1.png");
		}

		ImgFrightened[0][0] = loadImage("assets\\GAME04\\ghost_frightened_a0.png");
		ImgFrightened[0][1] = loadImage("assets\\GAME04\\ghost_frightened_a1.png");
		ImgFrightened[1][0] = loadImage("assets\\GAME04\\ghost_frightened_b0.png");
		ImgFrightened[1][1] = loadImage("assets\\GAME04\\ghost_frightened_b1.png");

		ImgEaten[0] = loadImage("assets\\GAME04\\ghost_eaten_u.png");
		ImgEaten[1] = loadImage("assets\\GAME04\\ghost_eaten_l.png");
		ImgEaten[2] = loadImage("assets\\GAME04\\ghost_eaten_d.png");
		ImgEaten[3] = loadImage("assets\\GAME04\\ghost_eaten_r.png");

		Size = game()->stage()->size();
		OfstX = game()->stage()->ofstX();
		OfstY = game()->stage()->ofstY();
	}

	void GHOST::destroy()
	{
	}

	void GHOST::init()
	{
		switch (No) {
		case 0:
			Pos.set(390, 360);
			DirIdx = R;
			Mode = SCATTER;
			break;
		case 1:
			Pos.set(466, 450);
			DirIdx = U;
			Mode = DEPARTURE_UPDOWN;
			break;
		case 2:
			Pos.set(466 - 60, 450);
			DirIdx = D;
			Mode = DEPARTURE_UPDOWN;
			break;
		case 3:
			Pos.set(466 + 60, 450);
			DirIdx = D;
			Mode = DEPARTURE_UPDOWN;
			break;
		}

		UpDownCnt = 0;
		ScatterChaseCnt = 0;
		FrightenedCnt = 0;

		FrightenedFlag = 0;

		Speed = 2;
		AnimCnt = 0;
	}
	void GHOST::ModeChange() {
		//中央のホームから出発するまで
		if (Mode == DEPARTURE_UPDOWN) {
			if (Pos.y == 420 || Pos.y == 480) {
				DirIdx = (DirIdx + 2) % 4;
			}
			//時間差で出発
			UpDownCnt++;
			if (UpDownCnt >= DepartureCnt[No]) {
				Mode = DEPARTURE_TOCENTER;
			}
		}
		if (Mode == DEPARTURE_TOCENTER) {
			if (Pos.x < 466) {
				DirIdx = R;
			}
			else if (Pos.x > 466) {
				DirIdx = L;
			}
			else {
				DirIdx = U;
				Mode = DEPARTURE;
			}
		}
		if (Mode == DEPARTURE) {
			if (Pos.y <= 360) {
				Pos.set(466, 360);
				DirIdx = R;
				Mode = SCATTER;
				UpDownCnt = 0;
			}
		}

		//分散モードと追跡モードの切り替え
		++ScatterChaseCnt;
		if (Mode == SCATTER) {
			if (ScatterChaseCnt >= 7 * 60) {
				Mode = CHASE;
			}
		}
		else if (Mode == CHASE) {
			if (ScatterChaseCnt >= 7 * 60 + 20 * 60) {
				Mode = SCATTER;
				ScatterChaseCnt = 0;
			}
		}

		//プレイヤーがパワーフードを食べたのでおびえさせる
		if (game()->stage()->powerFoodEaten()) {
			if (Mode == SCATTER || Mode == CHASE) {
				DirIdx = (DirIdx + 2) % 4;
			}
			ScatterChaseCnt = 0;
			FrightenedCnt = 10 * 60;
			FrightenedFlag = 1;
		}
		if (FrightenedCnt > 0) {
			FrightenedCnt--;
			if (FrightenedCnt == 0) {
				if (FrightenedFlag || Mode == CHASE) {
					FrightenedFlag = 0;
					Mode = SCATTER;
				}
				ScatterChaseCnt = 0;
			}
		}

		if (Pos.x % 30 == 0 && Pos.y % 30 == 0) {
			if (FrightenedFlag) {
				if ((Pos - game()->player()->pos()).sqMag() < 40 * 40) {
					//食べられる
					Mode = EATEN;
					Speed = 10;
					FrightenedFlag = 0;
				}
			}
			//食べられてホームの上まで戻り中
			if (Mode == EATEN) {
				int cx = Pos.x / 30;
				int cy = Pos.y / 30;
				//ホームの上に到着
				if (cx == 450 / 30 && cy == 360 / 30) {
					Pos.x = 466;
					DirIdx = D;
					Mode = EATEN_HOME;
				}
			}
		}
		//ホームのなかに入っていく
		if (Mode == EATEN_HOME) {
			if (Pos.y >= 480) {
				Pos.y = 480;
				DirIdx = U;
				UpDownCnt = 0;
				Mode = DEPARTURE_UPDOWN;
				Speed = 2;
			}
		}
	}
	int pow2(int n) {
		return n * n;
	}
	int GHOST::GetDir()
	{
		//以下のモードはターゲットへの方向Dirを決定する必要がない
		if (Mode == DEPARTURE_UPDOWN ||
			Mode == DEPARTURE_TOCENTER ||
			Mode == DEPARTURE ||
			Mode == EATEN_HOME) {
			return 0;
		}

		//現在の座標current x,y
		int cx = Pos.x / 30;
		int cy = Pos.y / 30;

		//これから進む方向フラッグ
		int dirFlag[4] = { 1,1,1,1 };
		//進んできた方へもどる方向はフラッグを倒す。つまり反転することはしない
		if (DirIdx == D) { dirFlag[U] = 0; }//上から来たので上にいかない
		if (DirIdx == R) { dirFlag[L] = 0; }//左から来たので左にいかない
		if (DirIdx == U) { dirFlag[D] = 0; }//下から来たので下にいかない
		if (DirIdx == L) { dirFlag[R] = 0; }//右から来たので右にいかない
		//残りの方向のうち障害物ならフラッグを倒す
		int cnt = 3;//この時点で候補は３方向
		STAGE* stage = game()->stage();
		if (dirFlag[U]) { if (stage->wall(cx, cy - 1)) { dirFlag[U] = 0; cnt--; } }
		if (dirFlag[L]) { if (stage->wall(cx - 1, cy)) { dirFlag[L] = 0; cnt--; } }
		if (dirFlag[D]) { if (stage->wall(cx, cy + 1)) { dirFlag[D] = 0; cnt--; } }
		if (dirFlag[R]) { if (stage->wall(cx + 1, cy)) { dirFlag[R] = 0; cnt--; } }

		//進める方向が一つならベクトルをセットする
		if (cnt == 1) {
			for (int i = 0; i < 4; i++) {
				if (dirFlag[i]) {
					DirIdx = i;
					break;
				}
			}
			return 0;
		}

		//おびえているときはランダムで方向を決定
		if (FrightenedFlag) {
			int i = 0;
			do {
				i = random() % 4;
			} while (dirFlag[i] == 0);
			DirIdx = i;
			return 0;
		}

		//ターゲットの座標を求める
		int tx = 0;
		int ty = 0;
		if (Mode == SCATTER) {
			if (No == 0) { tx = 33; ty = 0; }
			else if (No == 1) { tx = 0; ty = 0; }
			else if (No == 2) { tx = 1; ty = 29; }
			else if (No == 3) { tx = 30; ty = 29; }
		}
		else if (Mode == CHASE) {
			if (No == 0) {
				tx = game()->player()->pos().x / 30;
				ty = game()->player()->pos().y / 30;
			}
			else if (No == 1) {
				tx = game()->player()->pos().x / 30;
				ty = game()->player()->pos().y / 30;
				if (isPress(KEY_D))tx += 4;
				else if (isPress(KEY_A))tx -= 4;
				else if (isPress(KEY_S))ty += 4;
				else if (isPress(KEY_W)) { tx -= 4; ty -= 4; }
			}
			else if (No == 2) {
				tx = game()->player()->pos().x / 30;
				ty = game()->player()->pos().y / 30;
				if (isPress(KEY_D))tx += 2;
				else if (isPress(KEY_A))tx -= 2;
				else if (isPress(KEY_S))ty += 2;
				else if (isPress(KEY_W)) { tx -= 2; ty -= 2; }
				tx += (tx - game()->redGhost()->pos().x / 30);
				ty += (ty - game()->redGhost()->pos().y / 30);
			}
			if (No == 3) {
				tx = game()->player()->pos().x / 30;
				ty = game()->player()->pos().y / 30;
				if (pow2(tx - cx) + pow2(ty - cx) >= 64) {
					tx = 33; ty = 29;
				}
			}
		}
		else if (Mode == EATEN) {
			tx = 450 / 30;
			ty = 360 / 30;
		}
		//ターゲットに近い方向を求める
		int dist[4] = { 99999,99999,99999,99999 };
		if (dirFlag[U]) { dist[U] = pow2(cx - tx) + pow2((cy - 1) - ty); }
		if (dirFlag[L]) { dist[L] = pow2((cx - 1) - tx) + pow2(cy - ty); }
		if (dirFlag[D]) { dist[D] = pow2(cx - tx) + pow2((cy + 1) - ty); }
		if (dirFlag[R]) { dist[R] = pow2((cx + 1) - tx) + pow2(cy - ty); }
		int min = 99999;
		int i = 0;
		for (int j = 0; j < 4; j++) {
			if (min > dist[j]) {
				min = dist[j];
				i = j;
			}
		}
		DirIdx = i;
	}
	void GHOST::update()
	{
		ModeChange();

		if (Pos.x % 30 == 0 && Pos.y % 30 == 0) {
			GetDir();
		}

		//Move
		Pos += DIR[DirIdx] * Speed;
		if (Pos.x < 2)
			Pos.x = 928;
		else if (Pos.x > 928)
			Pos.x = 2;

		//GameOver
		//おびえておらず、たべられてもない
		if (FrightenedFlag == 0 && Mode != EATEN && Mode != EATEN_HOME) {
			if ((Pos - game()->player()->pos()).sqMag() < 30 * 30) {
				game()->toOver();
			}
		}
	}

	void GHOST::draw()
	{
		float px = OfstX + Pos.x - Size / 2;
		float py = OfstY + Pos.y - Size / 2;
		float scale = 1.f;
		if (game()->playing()) {
			++AnimCnt;
		}

		if (Mode == EATEN || Mode == EATEN_HOME) {
			image(ImgEaten[DirIdx], px, py, 0, scale);
		}
		else if (FrightenedFlag) {
			int i = AnimCnt / 5 % 2;
			if (FrightenedCnt <= 2 * 60) {
				if (FrightenedCnt / 6 % 2) {
					image(ImgFrightened[1][i], px, py, 0, scale);
				}
				else {
					image(ImgFrightened[0][i], px, py, 0, scale);
				}
			}
			else {
				image(ImgFrightened[0][i], px, py, 0, scale);
			}
		}
		else {
			int i = AnimCnt / 5 % 2;
			image(Imgs[No][DirIdx][i], px, py, 0, scale);
		}
		//print(Pos.x);
		//print(Pos.y);
		//print((let)"Cnt=" + ScatterChaseCnt);
		//print(HomeFlag);
	}
}