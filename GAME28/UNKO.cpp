#include "../libOne/inc/graphic.h"
#include "UNKO.h"
namespace GAME28 {
	
	void UNKO::create()
	{
		Img = loadImage("assets/GAME28/unkoWhite.png");
		Px = width - 200;;
		Py = height / 2;
		Angle = 0;
	}

	void UNKO::update()
	{
		Angle += 1;
	}

	void UNKO::draw()
	{
		rectMode(CENTER);
		imageColor(255, 128, 0);
		image(Img, Px, Py, Angle);
	}

}