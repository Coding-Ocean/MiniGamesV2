#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "STAGE.h"
#include "AI.h"
#include "PLAYER.h"
#include "BALL.h"
#include "SCORE.h"
#include "GAME.h"
namespace GAME00 {

	GAME::GAME(MAIN::MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		hideCursor();
		angleMode(DEGREES);

		Actors.push_back(Stage = new STAGE(this));
		Actors.push_back(Ai = new AI(this));
		Actors.push_back(Player = new PLAYER(this));
		Actors.push_back(Ball = new BALL(this));
		Actors.push_back(Score = new SCORE(this));

		playSnd = loadSound("assets/GAME00/taikoDon.wav");
		aiSnd = loadSound("assets/GAME00/clappers.wav");
		wallSnd = loadSound("assets/GAME00/woodBlock.wav");
		pointSnd = loadSound("assets/GAME00/pachipachi.wav");
		winSnd = loadSound("assets/GAME00/yahoo.wav");
		loseSnd = loadSound("assets/GAME00/boyoyon.wav");
		playSound(wallSnd);

		Init();
		//フェードイン
		Fade()->fadeInTrigger();
	}

	void GAME::destroy()
	{
		releaseSound(wallSnd);
		releaseSound(winSnd);
		releaseSound(playSnd);
		releaseSound(aiSnd);
		releaseSound(loseSnd);
		for (ACTOR* actor : Actors) { delete actor; }
		Score = Ball = Player = Ai = 0;
		showCursor();
	}

	void GAME::Init()
	{
		for (ACTOR* actor : Actors) { actor->init(); }
		Playing = true;
	}

	void GAME::proc()
	{
		//更新
		if (Playing) {
			for (ACTOR* actor : Actors) { actor->update(); }
		}
		else if (isTrigger(KEY_R)) {
			Init();
		}
		//描画
		clear(60, 0, 0);
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