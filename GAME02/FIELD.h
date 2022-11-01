#pragma once
#include "../libOne/inc/graphic.h"
#include "../libOne/inc/input.h"
#include "CELL.h"

namespace GAME02
{
	class FIELD {
		//1つのセルの大きさ
		float Scale = 0;
		//ステージの幅と高さ
		float W = 0;
		float H = 0;
		//ステージの右上の座標
		float OfstX = 0;
		float OfstY = 0;
		//セル2次元配列
		class CELL** Cell = 0;
		int Cols = 0;
		int Rows = 0;
		//ゲームオーバーフラッグ
		int GameOver = 0;
		//ゲームクリア判定に必要な変数
		int GameClear = 0;
		int NumCells = 0;
		int NumRevealed = 0;
		int NumBoms = 0;
		//効果音
		int GameClearSnd = 0;
		int GameOverSnd = 0;
	public:
		void create() {
			GameClearSnd = loadSound("assets/game02/levelup.wav");
			GameOverSnd = loadSound("assets/game02/bomb3.wav");

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
			releaseSound(GameClearSnd);
			releaseSound(GameOverSnd);

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
				Reveal(c, r);
				//ゲームオーバー
				if (Cell[c][r].bom()) {
					GameOver = 1;
					RevealAll();
					playSound(GameOverSnd);
				}
				//ゲームクリア
				else if (NumBoms == NumCells - NumRevealed) {
					GameClear = 1;
					RevealAll();
					playSound(GameClearSnd);
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
		//createから呼び出される
		void Init() {
			GameOver = 0;
			GameClear = 0;
			NumRevealed = 0;
			NumCells = Cols * Rows;
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
					CountNeighborBoms(c, r);
				}
			}
		}
		void CountNeighborBoms(int c, int r) {
			for (int i = -1; i <= 1; i++) {
				if (c + i < 0 || c + i >= Cols)continue;
				for (int j = -1; j <= 1; j++) {
					if (r + j < 0 || r + j >= Rows)continue;
					if (Cell[c + i][r + j].bom()) {
						Cell[c][r].countNeighborBoms();
					}
				}
			}
		}
		//updateから呼び出される
		void Reveal(int c, int r) {
			if (Cell[c][r].revealed())
				return;
			Cell[c][r].reveal();
			NumRevealed++;
			//「隣接ボム数が０の隣接セル」を開いてしまう
			if (Cell[c][r].numNeighborBoms() == 0) {
				for (int i = -1; i <= 1; i++) {
					if (c + i < 0 || c + i >= Cols)continue;
					for (int j = -1; j <= 1; j++) {
						if (r + j < 0 || r + j >= Rows)continue;
						Reveal(c + i, r + j);
					}
				}
			}
		}
		void RevealAll() {
			for (int c = 0; c < Cols; c++) {
				for (int r = 0; r < Rows; r++) {
					Cell[c][r].reveal();
				}
			}
		}
		//drawから呼び出される
		void DrawMessage(const char* msg,float size, float r, float g, float b) {
			fill(r, g, b);
			textSize(size * 2);
			textMode(BOTTOM);
			float px = OfstX + (W - size * strlen(msg)) / 2;
			text(msg, px, OfstY);
		}
	};
}