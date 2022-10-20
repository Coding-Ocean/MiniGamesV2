#include"../libOne/inc/graphic.h"
#include"../libOne/inc/input.h"
#include"GAME.h"
#include"MANAGER.h"
#include"PLAY.h"
#include "TITLE.h"
namespace GAME28 {

	TITLE::TITLE(class MANAGER* manager):STATE(manager){}
	TITLE::~TITLE(){}

	void TITLE::create()
	{
		ToNextState = false;
		Game()->fadeIn();
	}
	
	void TITLE::destroy()
	{
	}

	void TITLE::proc()
	{
		clear(200);
		DrawTextInfo();

		NextState();
	}

	void TITLE::DrawTextInfo()
	{
		fill(0,60,60);
		textMode(TOP);
		textSize(100);
		text("TITLE", 0, 0);
		textSize(50);
		text("Push space key to start.", 0, 100);
	}

	void TITLE::NextState()
	{
		if (isTrigger(KEY_SPACE)) {
			ToNextState = true;
		}
		if (ToNextState) {
			if (Game()->fadeOut()) {
				Manager()->setNextState(new PLAY(Manager()));
			}
		}
	}


}