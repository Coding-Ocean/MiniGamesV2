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
		Stage.create();

		//フェードイン（ここはいじらないでよい）
		Fade()->fadeInTrigger();
	}

	void GAME::destroy()
	{
		Stage.destroy();
	}

	void GAME::proc()
	{
		clear(234, 4, 126);
		Stage.update();
		Stage.draw();

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