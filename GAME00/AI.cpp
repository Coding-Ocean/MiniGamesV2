#include "../libOne/inc/mathUtil.h"
#include "GAME.h"
#include "STAGE.h"
#include "BALL.h"
#include "AI.h"
namespace GAME00
{
	AI::AI(GAME* game):ACTOR(game){}
	AI::~AI(){}

	void AI::init()
	{
		setW(120);
		setPx(game()->stage()->w() / 2 - w() / 2);
		setPy(game()->stage()->h() / 6);
		setSp(4.5f);
	}

	void AI::update()
	{
		//ƒ{[ƒ‹‚ğ’Ç‚¢‚©‚¯‚é
		float dx = game()->ball()->px() - (px() + w() / 2);
		dx *= 0.25f;
		if (Abs(dx) > sp())
			setVx((dx / Abs(dx)) * sp());
		else
			setVx(dx);
		setPx(px() + vx());
		//ˆÚ“®§ŒÀ
		float lim = 8;
		if (px() < lim) setPx(lim);
		lim = game()->stage()->w() - w() - 8;
		if (px() > lim)	setPx(lim);
	}

	void AI::draw()
	{
		stroke(255);
		strokeWeight(15);
		float x = game()->stage()->px() + px();
		line(x, py(),x + w(), py());
	}

}