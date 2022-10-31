#pragma once
#include "../libOne/inc/graphic.h"
#include "../libOne/inc/input.h"
#include "CELL.h"

namespace GAME02
{
	class STAGE {
	public:
		void create() {
			clearSnd = loadSound("assets/game02/levelup.wav");
			overSnd = loadSound("assets/game02/bomb3.wav");

			Scale = 100;
			W = 800;
			H = 800;
			//ステージ右上の座標
			OfstX = (width - W) / 2;
			OfstY = (height - H) / 2;
			//列数、行数
			Cols = W / Scale;
			Rows = H / Scale;
			//2次元配列動的確保
			Cell = new CELL*[Cols];
			for (int c = 0; c < Cols; c++) {
				Cell[c] = new CELL[Rows];
			}
			//各セルの描画位置を設定
			for (int c = 0; c < Cols; c++) {
				float px = OfstX + Scale * c;
				for (int r = 0; r < Rows; r++) {
					float py = OfstY + Scale * r;
					Cell[c][r].create(px, py, Scale);
				}
			}

			Init();
		}

		void destroy() {
			releaseSound(clearSnd);
			releaseSound(overSnd);

			for (int c = 0; c < Cols; c++) {
				delete[] Cell[c];
			}
			delete[]Cell;
		}

		void update() {
			//リセット
			if (isTrigger(KEY_R)) {
				Init();
			}
			//終了している
			if (GameOver || GameClear) {
				return;
			}
			//mouseがステージ上にない
			if (mouseX<OfstX || 
				mouseY<OfstY ||
				mouseX>OfstX + Cols * Scale ||
				mouseY>OfstY + Rows * Scale) {
				return;
			}
			//mouseがステージ上にある
			int c = int(mouseX - OfstX) / Scale;
			int r = int(mouseY - OfstY) / Scale;
			if (isTrigger(MOUSE_LBUTTON)) {
				Open(c, r);
				//ゲームオーバーorクリア
				if (Cell[c][r].bom()) {
					GameOver = 1;
					playSound(overSnd);
				}
				else if (NumBoms == NumNotOpen) {
					GameClear = 1;
					playSound(clearSnd);
				}
				//すべてのセルを開く
				if (GameOver || GameClear) {
					OpenAll();
				}
			}
			else if (isTrigger(MOUSE_RBUTTON)) {
				Cell[c][r].mayBeBom();
			}
		}

		void draw() {
			for (int c = 0; c < Cols; c++) {
				for (int r = 0; r < Rows; r++) {
					Cell[c][r].draw();
				}
			}
			if (GameOver) {
				DrawMessage("You are dead!",45, 255,255,0);
			}
			else if (GameClear) {
				DrawMessage("You did it!", 45, 0, 255, 255);
			}
		}

	private:
		void DrawMessage(const char* msg,float size, float r, float g, float b) {
			fill(r, g, b);
			textSize(size * 2);
			textMode(BOTTOM);
			float px = OfstX + (W - size * strlen(msg)) / 2;
			text(msg, px, OfstY);
		}

		void Init() {
			GameOver = 0;
			GameClear = 0;
			NumNotOpen = Cols * Rows;
			//セルを初期化し、ボムを数える
			NumBoms = 0;
			for (int c = 0; c < Cols; c++) {
				for (int r = 0; r < Rows; r++) {
					Cell[c][r].init();
					if (Cell[c][r].bom()) {
						NumBoms++;
					}
				}
			}
			//各セルに隣接するボム数を数える
			for (int c = 0; c < Cols; c++) {
				for (int r = 0; r < Rows; r++) {
					int numNeighborBoms = 0;
					for (int i = -1; i <= 1; i++) {
						if (c + i < 0 || c + i >= Cols)continue;
						for (int j = -1; j <= 1; j++) {
							if (r + j < 0 || r + j >= Rows)continue;
							if (Cell[c + i][r + j].bom()) {
								numNeighborBoms++;
							}
						}
					}
					Cell[c][r].setNumNeighborBoms(numNeighborBoms);
				}
			}
		}

		void Open(int c, int r) {
			if (Cell[c][r].notYetOpen()) {
				Cell[c][r].open();
				NumNotOpen--;
				//「隣接ボム数が０の隣接セル」を開いてしまう
				if (Cell[c][r].numNeighborBoms() == 0) {
					for (int i = -1; i <= 1; i++) {
						if (c + i < 0 || c + i >= Cols)continue;
						for (int j = -1; j <= 1; j++) {
							if (r + j < 0 || r + j >= Rows)continue;
							Open(c + i, r + j);
						}
					}
				}
			}
		}

		void OpenAll() {
			for (int c = 0; c < Cols; c++) {
				for (int r = 0; r < Rows; r++) {
					Cell[c][r].open();
				}
			}
		}

		//1つのセルの大きさ
		float Scale = 0;
		//ステージの幅と高さ
		float W = 0;
		float H = 0;
		//ステージの右上の座標
		float OfstX = 0;
		float OfstY = 0;
		//セル
		class CELL** Cell = 0;
		int Cols = 0;
		int Rows = 0;
		//ゲームオーバーフラッグ
		int GameOver = 0;
		//ゲームクリア判定に必要な変数
		int GameClear = 0;
		int NumBoms = 0;
		int NumNotOpen = 0;
		//sound
		int clearSnd = 0;
		int overSnd = 0;
	};
}