#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "STAGE.h"
#include "FOOD.h"
#include "SNAKE.h"
#include "GAME.h"
namespace GAME01 { //自分でなにかファイルを追加したらincludeの後にこの行を追加すること。　ファイルの最後に“ } ”も忘れずに！

	GAME::GAME(MAIN::MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		hideCursor();

		eatSnd = loadSound("assets/GAME01/peta.wav");
		gameOverSnd = loadSound("assets/GAME01/manuke.wav");

		Actors.push_back(Stage = new STAGE(this));
		Actors.push_back(Food = new FOOD(this));
		Actors.push_back(Snake = new SNAKE(this));
		
		Init();
		
		Fade()->fadeInTrigger();
	}

	void GAME::destroy()
	{
		for (ACTOR* actor : Actors) { delete actor; }
		showCursor();
	}

	void GAME::Init()
	{
		for (ACTOR* actor : Actors) { actor->init(); }
		FrameCnt = 0;
		GameSpeed = 20;
		Playing = true;
	}
	void GAME::proc()
	{
		if (Playing) {
			clear(0, 128, 128);
			Snake->input();
			if ((++FrameCnt %= GameSpeed) == 0) {
				for (ACTOR* actor : Actors) { actor->update(); }
			}
		}
		else{
			clear(128, 0, 0);
			if (isTrigger(KEY_R)) {
				Init();
			}
		}
		for (ACTOR* actor : Actors) { actor->draw(); }

		//メニューに戻る
		if (isTrigger(KEY_ENTER)) {
			BackToMenuFlag = 1;
		}
		Fade()->draw();
		if (BackToMenuFlag == 1) {
			Manager()->backToMenu();
		}
	}
}