#include"../libOne/inc/graphic.h"
#include"../libOne/inc/input.h"
#include"GAME.h"
#include"PLAYER.h"
#include"UNKO.h"
#include"GAME_MANAGER.h"
#include"OVER.h"
#include"PLAY.h"
namespace GAME28 {

	PLAY::PLAY(class GAME_MANAGER* manager):GAME_STATE(manager)	{}
	PLAY::~PLAY(){}

	void PLAY::create()
	{
		manager->player->create();
		manager->unko->create();
	}

	void PLAY::destroy()
	{
	}

	void PLAY::proc()
	{
		manager->player->update();

		clear(200);
		manager->player->draw();
		manager->unko->draw();
		DrawText();

		if (manager->player->px() >= width - 200) {
			manager->nextState = new OVER(manager);
		}
	}

	void PLAY::DrawText()
	{
		fill(0);
		textMode(TOP);
		textSize(100);
		text("PLAY", 0, 0);
	}
}