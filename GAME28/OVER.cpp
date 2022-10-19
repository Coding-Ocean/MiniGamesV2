#include"../libOne/inc/graphic.h"
#include"../libOne/inc/input.h"
#include"GAME_MANAGER.h"
#include"PLAYER.h"
#include"UNKO.h"
#include"PLAY.h"
#include "OVER.h"
namespace GAME28 {
	OVER::OVER(class GAME_MANAGER* manager):GAME_STATE(manager) {}
	OVER::~OVER() {}

	void OVER::create()
	{
	}

	void OVER::destroy()
	{
	}

	void OVER::proc()
	{
		manager->unko->update();

		clear(200);
		manager->player->draw();
		manager->unko->draw();
		DrawText();

		if (isTrigger(KEY_SPACE)) {
			manager->nextState = new PLAY(manager);
		}

		if (isTrigger(KEY_ENTER)) {
			manager->backToMenu();
		}
	}

	void OVER::DrawText()
	{
		fill(0);
		textMode(TOP);
		textSize(100);
		text("OVER", 0, 0);
		textSize(50);
		text("Push space key to replay", 0, 100);
		text("Push enter key to return menu", 0, 150);
	}

}