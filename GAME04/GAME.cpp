#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "ACTOR.h"
#include "GAME.h"
namespace GAME04 { 

	GAME::GAME(MAIN::MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		hideCursor();
		colorMode(HSV, 100);
		angleMode(DEGREES);
		//画像読み込みなど
		for (ACTOR* actor : Actors) {
			actor->create();
		}
		//データ初期化
		Init();
		//フェードイン
		Fade()->fadeInTrigger();
	}

	void GAME::destroy()
	{
		for (ACTOR* actor : Actors) {
			actor->destroy();
			delete actor;
		}
		showCursor();
	}

	void GAME::Init()
	{
		for (ACTOR* actor : Actors) {
			actor->init();
		}
	}

	void GAME::proc()
	{
		//リセット
		if (isTrigger(KEY_R)) {
			Init();
		}
		//更新
		for (ACTOR* actor : Actors) {
			actor->update();
		}
		//描画
		clear(200);
		for (ACTOR* actor : Actors) {
			actor->draw();
		}
		//フェード
		Fade()->draw();
		//メニューに戻る
		if (isTrigger(KEY_ENTER)) {	BackToMenuFlag = 1;	}
		if (BackToMenuFlag == 1) { Manager()->backToMenu();	}
	}
}