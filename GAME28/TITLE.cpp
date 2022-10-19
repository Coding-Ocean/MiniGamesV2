#include"../libOne/inc/graphic.h"
#include"../libOne/inc/input.h"
#include"GAME.h"
#include"GAME_MANAGER.h"
#include"PLAY.h"
#include "TITLE.h"
namespace GAME28 {

	TITLE::TITLE(class GAME_MANAGER* manager):GAME_STATE(manager){}
	TITLE::~TITLE(){}

	void TITLE::create()
	{
	}
	
	void TITLE::destroy()
	{
	}

	void TITLE::proc()
	{
		clear(200);
		DrawText();

		if (isTrigger(KEY_SPACE)) {
			manager->nextState = new PLAY(manager);
		}
	}

	void TITLE::DrawText()
	{
		fill(0);
		textMode(TOP);
		textSize(100);
		text("TITLE", 0, 0);
		textSize(50);
		text("Push space key to start.", 0, 100);
	}


}