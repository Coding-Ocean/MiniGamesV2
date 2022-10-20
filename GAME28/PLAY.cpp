#include"../libOne/inc/graphic.h"
#include"../libOne/inc/input.h"
#include"GAME.h"
#include"PLAYER.h"
#include"UNKO.h"
#include"MANAGER.h"
#include"OVER.h"
#include"PLAY.h"
namespace GAME28 {

	PLAY::PLAY(class MANAGER* manager):STATE(manager)	{}
	PLAY::~PLAY(){}

	void PLAY::create()
	{
		Manager()->player()->create();
		Manager()->unko()->create();
		Game()->fadeIn();
	}

	void PLAY::destroy()
	{
	}

	void PLAY::proc()
	{
		Manager()->player()->update();

		clear(200);
		Manager()->player()->draw();
		Manager()->unko()->draw();
		DrawTextInfo();

		NextState();
	}

	void PLAY::DrawTextInfo()
	{
		fill(0);
		textMode(TOP);
		textSize(100);
		text("PLAY", 0, 0);
	}

	void PLAY::NextState()
	{
		if (Manager()->player()->px() >= width - 200) {
			Manager()->setNextState(new OVER(Manager()));
		}
	}

}