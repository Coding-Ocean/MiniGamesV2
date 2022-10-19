#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "GAME_MANAGER.h"
#include "TITLE.h"
#include "GAME.h"
namespace GAME28 { //自分でなにかファイルを追加したらincludeの後にこの行を追加すること。　ファイルの最後に“ } ”も忘れずに！

	GAME::GAME(MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		Manager = new GAME_MANAGER(this);
		//フェードイン（ここはいじらないでよい）
		manager->fade->fadeInTrigger();
	}

	void GAME::destroy()
	{
		delete Manager;
	}

	void GAME::proc()
	{
		Manager->proc();

		manager->fade->draw();
		if (BackToMenuFlag == 1) {
			manager->fade->fadeOutTrigger();
			if (manager->fade->fadeOutEndFlag()) {
				manager->nextState = new MENU(manager);
			}
		}
	}

	void GAME::backToMenu()
	{
		BackToMenuFlag = 1;
	}

}