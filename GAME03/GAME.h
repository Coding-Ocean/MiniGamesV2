#pragma once
#include"../MAIN/STATE.h"

namespace GAME03 { //自分でなにかファイルを追加したらincludeの後にこの行を追加すること。　ファイルの最後に“ } ”も忘れずに！

	class GAME : public MAIN::STATE {
	public: 
		GAME(class MAIN::MANAGER* manager);
		~GAME();
		void create(); 
		void destroy();
		void proc();
	private:
        int BackToMenuFlag = 0;
        //シーケンス
        const int INIT = 0;
        const int PLAY = 1;
        const int OVER = 2;
        int GameState = INIT;
        //色データ
        float Satu = 200;
        float Value = 255;
        float Alpha = 255;
        struct COLOR Color[9] = {
            COLOR(0,Satu,Value,Alpha),
            COLOR(30,Satu,Value,Alpha),
            COLOR(60,Satu,Value,Alpha),
            COLOR(120,Satu,Value,Alpha),
            COLOR(180,Satu,Value,Alpha),
            COLOR(220,Satu,Value,Alpha),
            COLOR(300,Satu,Value,Alpha),
            COLOR(200,44,88,Alpha),
            COLOR(0,0,20,Alpha),
        };
        //壁と背景の色番号
        const int WALL = 7;
        const int BACK = 8;
        //ステージ（色番号を記憶する２次元配列）
        int** Stage = 0;
        const int ROWS = 20;
        const int COLS = 12;
        float Size = 45;
        float OfstX = (width - Size * COLS) / 2;
        float OfstY = (height - Size * ROWS) / 2;
        //基準ブロック位置と回転数
        int X, Y, R;
        //ブロックパターンの位置
        int Px[4], Py[4];
        //ブロック移動制御
        int FallFlag = 0;
        int LoopCnt = 0;
        //ブロックパターン番号  ※ 兼色番号 ※
        int PtnNo;
        //ブロックパターンオフセット
        int PtnOffsets[7][3][2] = {
            //■□■■...0
            -1,0,   1,0,  2,0,
            //■
            //■□■....1
            -1,-1, -1,0,  1,0,
            //  ■
            //■□■....2
            -1,0,   1,-1, 1,0,
            //■□
            // ■■....3
            -1,0,   0,1,  1,1,
            // □■
            //■■  ....4
             1,0,   0,1, -1,1,
             //  ■
             //■□■....5
             -1,0,   0,-1, 1,0,
             //□■
             //■■......6
              1,0,   0,1,  1,1,
        };
        void drawStage() {
            angleMode(DEGREES);
            colorMode(HSV);
            strokeWeight(Size*0.4f);
            rectMode(CENTER);
            for (int y = 0; y < ROWS; y++) {
                for (int x = 0; x < COLS; x++) {
                    int no = Stage[y][x];
                    stroke(Color[no]);
                    fill(0, 0, 100);
                    float px = OfstX + Size / 2 + Size * x;
                    float py = OfstY + Size / 2 + Size * y;
                    rect(px, py, Size / 2, Size / 2);
                }
            }
        }
        void setPtnPosition() {
            //基準ブロック位置
            Px[0] = X;
            Py[0] = Y;
            //回転数
            int r = R % 4;
            for (int i = 0; i < 3; i++) {
                //現在のブロックパターンのオフセット値を取得
                int ofsX = PtnOffsets[PtnNo][i][0];
                int ofsY = PtnOffsets[PtnNo][i][1];
                //回転数に応じて９０度ずつ回転させる
                for (int j = 0; j < r; j++) {
                    int w = ofsX;
                    ofsX = -ofsY;
                    ofsY = w;
                }
                //位置決定
                Px[i + 1] = X + ofsX;
                Py[i + 1] = Y + ofsY;
            }
        }
        void setPtnNoToStage() {
            setPtnPosition();
            for (int i = 0; i < 4; i++) {
                int x = Px[i];
                int y = Py[i];
                Stage[y][x] = PtnNo;
            }
        }
        void delPtnNoFromStage() {
            for (int i = 0; i < 4; i++) {
                int x = Px[i];
                int y = Py[i];
                Stage[y][x] = BACK;
            }
        }
        int collision() {
            setPtnPosition();
            int flag = 0;
            for (int i = 0; i < 4; i++) {
                int x = Px[i];
                int y = Py[i];
                if (Stage[y][x] != BACK) {
                    flag = 1;
                }
            }
            return flag;
        }
        void complete() {
            for (int y = 1; y < ROWS - 1; y++) {
                int flag = 1;
                for (int x = 1; x < COLS - 1; x++) {
                    if (Stage[y][x] == BACK) {
                        flag = 0;
                    }
                }
                if (flag) {
                    //そろったのでスライド
                    for (int upy = y - 1; upy >= 0; upy--) {
                        for (int x = 1; x < COLS - 1; x++) {
                            Stage[upy + 1][x] = Stage[upy][x];
                        }
                    }
                }
            }
        }

        void init() {
            //壁と背景の色番号をStage2次元配列にセット
            for (int y = 0; y < ROWS; y++) {
                Stage[y][0] = Stage[y][COLS - 1] = WALL;
                for (int x = 1; x < COLS - 1; x++) {
                    Stage[y][x] = BACK;
                    if (y == ROWS - 1) {
                        Stage[y][x] = WALL;
                    }
                }
            }
            //ブロック初期値
            X = 5;
            Y = 1;
            R = 0;
            PtnNo = random() % 7;
            setPtnPosition();
            //次のシーケンス
            GameState = PLAY;
        }
        void play() {
            //現在のパターン番号（色番号）をステージから消す
            delPtnNoFromStage();
            //移動、回転
            int dy = 0, dx = 0, dr = 0;;
            if ((++LoopCnt %= 15) == 0)dy = 1;
            if (isTrigger(KEY_D))dx = 1;
            if (isTrigger(KEY_A))dx = -1;
            if (isTrigger(KEY_W))dr = 1;
            if (isTrigger(KEY_S))FallFlag = 1;
            if (FallFlag)dy = 1;
            Y += dy;
            X += dx;
            R += dr;
            if (collision()) {
                //元の位置、回転に戻す
                Y -= dy;
                X -= dx;
                R -= dr;
                FallFlag = 0;
                if (dy == 1 && dx == 0 && dr == 0) {
                    //積もらせる
                    setPtnNoToStage();
                    //行がそろっていたらスライドさせる
                    complete();
                    //新しいブロック誕生
                    X = 5;
                    Y = 1;
                    R = 0;
                    PtnNo = random() % 7;
                    if (collision()) {
                        GameState = OVER;
                    }
                }
            }
            //パターン番号（色番号）をステージにセット
            setPtnNoToStage();
            //描画
            drawStage();
        }
        void over() {
            drawStage();
            //ゲームオーバーテキスト
            fill(0, 0, 255);
            textSize(Size);
            text("ＧａｍｅＯｖｅｒ", (width - Size * 8) / 2, Size);
            if (isTrigger(KEY_R)) {
                GameState = INIT;
            }
        }
	};

}

