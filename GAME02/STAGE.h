#pragma once
#include "../libOne/inc/graphic.h"
#include "../libOne/inc/input.h"
#include "CELL.h"

namespace GAME02
{
	class STAGE {
	public:
		void create() {
			float w = 800;
			float h = 800;
			Scale = 100;

			OfstX = (width - w) / 2;
			OfstY = (height - h) / 2;
			Cols = w / Scale;
			Rows = h / Scale;
			
			Cell = new CELL*[Cols];
			for (int c = 0; c < Cols; c++) {
				Cell[c] = new CELL[Rows];
			}

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
			for (int c = 0; c < Cols; c++) {
				delete[] Cell[c];
			}
			delete[]Cell;
		}

		void Init() {
			GameOver = 0;
			GameClear = 0;
			NumNotOpen = Cols * Rows;
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
					int numAdjacentBoms = 0;
					for (int i = -1; i <= 1; i++) {
						if (c + i < 0 || c + i >= Cols)continue;
						for (int j = -1; j <= 1; j++) {
							if (r + j < 0 || r + j >= Rows)continue;
							if (Cell[c + i][r + j].bom()) {
								numAdjacentBoms++;
							}
						}
					}
					Cell[c][r].setNumAdjacentBoms(numAdjacentBoms);
				}
			}
		}

		void Open(int c, int r) {
			if (Cell[c][r].close()) {
				Cell[c][r].open();
				NumNotOpen--;
				//隣接ボム数が０の隣接セルを開いてしまう
				if (Cell[c][r].numAdjacentBoms()==0) {
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

		void update() {
			if (isTrigger(KEY_R)) {
				Init();
			}
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
			//操作できる
			int c = int(mouseX - OfstX) / Scale;
			int r = int(mouseY - OfstY) / Scale;
			if (isTrigger(MOUSE_LBUTTON)) {
				Open(c, r);
				if (Cell[c][r].bom()) {
					GameOver = 1;
				}
				else if (NumBoms == NumNotOpen) {
					GameClear = 1;
				}
				if (GameOver || GameClear) {
					for (int c = 0; c < Cols; c++) {
						for (int r = 0; r < Rows; r++) {
							Cell[c][r].open();
						}
					}
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
				fill(255,255,0);
				textSize(100);
				textMode(BOTTOM);
				text("    GameOver", OfstX, OfstY);
			}
			else if (GameClear) {
				fill(255);
				textSize(100);
				textMode(BOTTOM);
				text("   GameClear", OfstX+25, OfstY);
			}
		}
	private:
		class CELL** Cell = 0;
		int Cols = 0;
		int Rows = 0;
		float Scale = 0;
		float OfstX = 0;
		float OfstY = 0;
		//sequence
		int NumBoms = 0;
		int NumNotOpen = 0;
		int GameClear = 0;
		int GameOver = 0;
	};
}