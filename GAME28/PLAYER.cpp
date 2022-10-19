#include"../libOne/inc/graphic.h"
#include "PLAYER.h"
namespace GAME28 {

	void PLAYER::create()
	{
		Px = -200;
		Py = height / 2;
		Vx = 20;
	}

	void PLAYER::update()
	{
		Px += Vx;
		if (Px >= width + 200) {
			Px = -200;
		}
	}

	void PLAYER::draw()
	{
		fill(255);
		circle(Px, Py, 200);
	}

}