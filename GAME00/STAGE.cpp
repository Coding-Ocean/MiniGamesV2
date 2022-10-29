#include"../libOne/inc/graphic.h"
#include "STAGE.h"
namespace GAME00
{
	STAGE::STAGE(GAME* game):ACTOR(game){}
	STAGE::~STAGE(){}

	void STAGE::init()
	{
		setH(1080);
		setW(810);
		setPx((width - w()) / 2);
		setPy((height - h()) / 2);
	}
	void STAGE::draw()
	{
		//Court
		fill(0, 60, 60);
		stroke(200);
		strokeWeight(5);
		rectMode(CORNER);
		rect(px(), py()-5, w(), h()+10);
		//Center line
		stroke(200);
		strokeWeight(2);
		line(px(), h() / 2, px()+w(), h() / 2);
	}
}