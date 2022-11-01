#pragma once
#include "../libOne/inc/graphic.h"
#include "../libOne/inc/input.h"
#include "CELL.h"

namespace GAME02
{
	class FIELD {
		//1�̃Z���̑傫��
		float Scale = 0;
		//�X�e�[�W�̕��ƍ���
		float W = 0;
		float H = 0;
		//�X�e�[�W�̉E��̍��W
		float OfstX = 0;
		float OfstY = 0;
		//�Z��2�����z��
		class CELL** Cell = 0;
		int Cols = 0;
		int Rows = 0;
		//�Q�[���I�[�o�[�t���b�O
		int GameOver = 0;
		//�Q�[���N���A����ɕK�v�ȕϐ�
		int GameClear = 0;
		int NumCells = 0;
		int NumRevealed = 0;
		int NumBoms = 0;
		//���ʉ�
		int GameClearSnd = 0;
		int GameOverSnd = 0;
	public:
		void create() {
			GameClearSnd = loadSound("assets/game02/levelup.wav");
			GameOverSnd = loadSound("assets/game02/bomb3.wav");

			Scale = 100;
			W = 800;
			H = 800;
			//�X�e�[�W�E��̍��W
			OfstX = (width - W) / 2;
			OfstY = (height - H) / 2;
			//�񐔁A�s��
			Cols = W / Scale;
			Rows = H / Scale;
			//2�����z�񓮓I�m��
			Cell = new CELL*[Cols];
			for (int c = 0; c < Cols; c++) {
				Cell[c] = new CELL[Rows];
			}
			//�e�Z���̕`��ʒu��ݒ�
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
			//���Z�b�g
			if (isTrigger(KEY_R)) {
				Init();
			}
			//�I�����Ă���
			if (GameOver || GameClear) {
				return;
			}
			//mouse���X�e�[�W��ɂȂ�
			if (mouseX<OfstX || 
				mouseY<OfstY ||
				mouseX>OfstX + Cols * Scale ||
				mouseY>OfstY + Rows * Scale) {
				return;
			}
			//mouse���X�e�[�W��ɂ���
			int c = int(mouseX - OfstX) / Scale;
			int r = int(mouseY - OfstY) / Scale;
			if (isTrigger(MOUSE_LBUTTON)) {
				Reveal(c, r);
				//�Q�[���I�[�o�[
				if (Cell[c][r].bom()) {
					GameOver = 1;
					RevealAll();
					playSound(GameOverSnd);
				}
				//�Q�[���N���A
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
		//create����Ăяo�����
		void Init() {
			GameOver = 0;
			GameClear = 0;
			NumRevealed = 0;
			NumCells = Cols * Rows;
			//�Z�������������A�{���𐔂���
			NumBoms = 0;
			for (int c = 0; c < Cols; c++) {
				for (int r = 0; r < Rows; r++) {
					Cell[c][r].init();
					if (Cell[c][r].bom()) {
						NumBoms++;
					}
				}
			}
			//�e�Z���ɗאڂ���{�����𐔂���
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
		//update����Ăяo�����
		void Reveal(int c, int r) {
			if (Cell[c][r].revealed())
				return;
			Cell[c][r].reveal();
			NumRevealed++;
			//�u�אڃ{�������O�̗אڃZ���v���J���Ă��܂�
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
		//draw����Ăяo�����
		void DrawMessage(const char* msg,float size, float r, float g, float b) {
			fill(r, g, b);
			textSize(size * 2);
			textMode(BOTTOM);
			float px = OfstX + (W - size * strlen(msg)) / 2;
			text(msg, px, OfstY);
		}
	};
}