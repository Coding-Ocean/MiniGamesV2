#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "GAME.h"
namespace GAME24 { //自分でなにかファイルを追加したらincludeの後にこの行を追加すること。　ファイルの最後に“ } ”も忘れずに！

	GAME::GAME(MAIN::MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		Img = loadImage("assets/GAME24/unkoWhite.png");

		Diameter = 200;
		Px = -100;
		Py = height / 2;
		Vx = 20;

		//フェードイン（ここはいじらないでよい）
		Fade()->fadeInTrigger();
	}

	void GAME::destroy()
	{

	}

	void GAME::proc()
	{
		//更新
		Px += Vx;

		//描画
		clear(200);
		circle(Px, Py, Diameter);

		//円が右に消えたらゲームオーバーとする
		if (Px > 2100) {
			//うんこ表示
			rectMode(CENTER);
			image(Img, width / 2, height / 2);
			//文字表示
			fill(255, 0, 0);
			textSize(200);
			text("Game Over", 500, 100);
			textSize(60);
			text("Enterでメニューに戻る", 600, 800);
			//メニューに戻る
			if (isTrigger(KEY_ENTER)) {
				BackToMenuFlag = 1;
			}
		}

		//メニューに戻る (基本的に以下はいじらなくてよい)
		Fade()->draw();
		if (BackToMenuFlag == 1) {
			Manager()->backToMenu();
		}
	}

}