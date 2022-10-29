#include "../libOne/inc/input.h"
#include "GAME.h"
#include "STAGE.h"
#include "PLAYER.h"
namespace GAME00
{
	PLAYER::PLAYER(GAME* game):ACTOR(game){}
	PLAYER::~PLAYER(){}

	void PLAYER::init()
	{
		setW(120);
		setPx(game()->stage()->w() / 2 - w() / 2);
		setPy(game()->stage()->h() / 6 * 5);
		setSp(5);
	}

	void PLAYER::update()
	{
		//ˆÚ“®
		if (isPress(KEY_D))setPx(px() + sp());
		if (isPress(KEY_A))setPx(px() - sp());
		//ˆÚ“®§ŒÀ
		float lim = 8;
		if (px() < lim) setPx(lim);
		lim = game()->stage()->w() - w() - 8;
		if (px() > lim)	setPx(lim);
	}

	void PLAYER::draw()
	{
		stroke(255);
		strokeWeight(15);
		float x = game()->stage()->px() + px();
		line(x, py(), x + w(), py());
	}
}