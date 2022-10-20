#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "MANAGER.h"
#include "TITLE.h"
#include "GAME.h"
namespace GAME28 { 

	GAME::GAME(MAIN::MANAGER* manager) :MAIN::STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		Manager = new GAME28::MANAGER(this);
	}

	void GAME::destroy()
	{
		delete Manager;
	}

	void GAME::proc()
	{
		Manager->proc();

		MAIN::STATE::Fade()->draw();

		if (BackToMenuFlag == 1) {
			MAIN::STATE::Manager()->backToMenu();
		}
	}

	//以下このGAME内のステートから呼び出される------------------------------

	void GAME::fadeIn()
	{
		MAIN::STATE::Fade()->fadeInTrigger();
	}

	bool GAME::fadeOut()
	{
		MAIN::STATE::Fade()->fadeOutTrigger();
		if (MAIN::STATE::Fade()->fadeOutEndFlag())
			return true;
		else
			return false;
	}

	void GAME::backToMenu()
	{
		BackToMenuFlag = 1;
	}

}