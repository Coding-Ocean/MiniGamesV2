#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "GAME.h"
namespace GAME03 { 

	GAME::GAME(MAIN::MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		hideCursor();
		
		Stage = new int* [ROWS];
		for (int y = 0; y < ROWS; y++) {
			Stage[y] = new int[COLS];
		}

		Fade()->fadeInTrigger();
	}

	void GAME::destroy()
	{
		for (int y = 0; y < ROWS; y++) {
			delete[]Stage[y];
		}
		delete[]Stage;

		showCursor();
	}

	void GAME::proc()
	{
		clear(20);
		if (GameState == INIT)init();
		else if (GameState == PLAY)play();
		else if (GameState == OVER)over();

		Fade()->draw();
		//ƒƒjƒ…[‚É–ß‚é
		if (isTrigger(KEY_ENTER)) BackToMenuFlag = 1;
		if (BackToMenuFlag == 1) Manager()->backToMenu();
	}
}