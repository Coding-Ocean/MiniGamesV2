#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "STAGE.h"
#include "PLAYER.h"
#include "GHOST.h"
#include "GAME.h"
namespace GAME04 { 

	GAME::GAME(MAIN::MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		hideCursor();

		//Actor配列へ登録
		Actors.push_back(Stage = new STAGE(this));
		Actors.push_back(Player = new PLAYER(this));
		Actors.push_back(RedGhost = new GHOST(0, this));
		Actors.push_back(new GHOST(1, this));
		Actors.push_back(new GHOST(2, this));
		Actors.push_back(new GHOST(3, this));

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
		State = PLAY;
	}

	void GAME::proc()
	{
		//リセット
		if (isTrigger(KEY_R)) {
			Init();
		}
		//更新
		colorMode(HSV, 100);
		angleMode(DEGREES);
		if (State == PLAY) {
			for (ACTOR* actor : Actors) {
				actor->update();
			}
		}
		//描画
		clear(0,0,0);
		for (ACTOR* actor : Actors) {
			actor->draw();
		}
		Stage->drawWarpZone();
		if (State == CLEAR) {
			Stage->drawStageClear();
		}
		//フェード
		Fade()->draw();
		//メニューに戻る
		if (isTrigger(KEY_ENTER)) {	BackToMenuFlag = 1;	}
		if (BackToMenuFlag == 1) { Manager()->backToMenu();	}
	}
}