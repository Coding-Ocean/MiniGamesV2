#include"../libOne/inc/graphic.h"
#include"../libOne/inc/input.h"
#include"GAME.h"
#include"MANAGER.h"
#include"PLAYER.h"
#include"UNKO.h"
#include"PLAY.h"
#include "OVER.h"
namespace GAME28 {
	OVER::OVER(class MANAGER* manager):STATE(manager) {}
	OVER::~OVER() {}

	void OVER::create()
	{
		ToNextState = false;
	}

	void OVER::destroy()
	{
	}

	void OVER::proc()
	{
		Manager()->unko()->update();

		clear(200);
		Manager()->player()->draw();
		Manager()->unko()->draw();
		DrawTextInfo();

		NextState();
	}

	void OVER::DrawTextInfo()
	{
		fill(0);
		textMode(TOP);
		textSize(100);
		text("OVER", 0, 0);
		textSize(50);
		text("Push space key to replay", 0, 100);
		text("Push enter key to return menu", 0, 150);
	}

	void OVER::NextState()
	{
		if (isTrigger(KEY_SPACE)) {
			ToNextState = true;
		}
		if (ToNextState) {
			if (Game()->fadeOut()) {
				Manager()->setNextState(new PLAY(Manager()));
			}
		}

		if (isTrigger(KEY_ENTER)) {
			Manager()->game()->backToMenu();
		}
	}

}