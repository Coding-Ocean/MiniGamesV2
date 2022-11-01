#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "GAME.h"
namespace GAME02 { //自分でなにかファイルを追加したらincludeの後にこの行を追加すること。　ファイルの最後に“ } ”も忘れずに！

	GAME::GAME(MAIN::MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		Field.create();

		Fade()->fadeInTrigger();
	}

	void GAME::destroy()
	{
		Field.destroy();
	}

	void GAME::proc()
	{
		clear(234, 4, 126);
		Field.update();
		Field.draw();

		//フェード処理
		Fade()->draw();
		//メニューに戻る
		if (isTrigger(KEY_ENTER)) {BackToMenuFlag = 1;}
		if (BackToMenuFlag == 1) {Manager()->backToMenu();}
	}
}