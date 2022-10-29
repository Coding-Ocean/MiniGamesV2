#include "../libOne/inc/mathUtil.h"
#include "../libOne/inc/rand.h"
#include "../libOne/inc/sound.h"
#include "GAME.h"
#include "STAGE.h"
#include "AI.h"
#include "PLAYER.h"
#include "BALL.h"
namespace GAME00
{
	BALL::BALL(GAME* game)
		:ACTOR(game)
	{
	}

	void BALL::init()
	{
		setR(10);
		setSp(8.5f);
		setPx(game()->player()->px() + game()->player()->w() / 2);
		setPy(game()->player()->py() + -r() * 2);
		setVx(0);
		setVy(-sp());

		PlaySoundOnce = false;
	}

	void BALL::update()
	{
		//ボールが壁にぶつかった
		bool hit = false;
		if (px() < r() && vx() < 0) {
			setVx(-vx());
			hit = true;
		}
		else if (px() > game()->stage()->w() - r() && vx() > 0) {
			setVx(-vx());
			hit = true;
		}
		//コート内なら音を鳴らす
		if (hit && 
			py() >= 0 && 
			py() <= game()->stage()->h()) {
			playSound(game()->wallSnd);
			hit = false;
		}
		//コート外に出ていった時、点をいれたほうからサーブ。
		if (py() < -800) {
			setPx(game()->player()->px() + game()->player()->w()/2);
			setPy(game()->player()->py() + -r());
			setVx(-sp());
		}
		else if (py() > game()->stage()->h() + 800) {
			setPx(game()->ai()->px() + game()->ai()->w() / 2);
			setPy(game()->ai()->py() + r());
			setVx(sp());
		}
		//パドルとの当たり判定
		Collision();
		//移動
		setPx(px() + vx());
		setPy(py() + vy());
	}

	void BALL::Collision()
	{
		//対象選択
		ACTOR* paddle;
		if (py() < game()->stage()->h() / 2)
			paddle = game()->ai();
		else
			paddle = game()->player();
		//パドルにあたった
		if (py() >= paddle->py() - r() &&//上
			py() <= paddle->py() + r() &&//下
			px() >= paddle->px() - r() &&//左
			px() <= paddle->px() + paddle->w() + r()//右
			) {
			if (PlaySoundOnce == false) {
				if (py() < game()->stage()->h() / 2)
					playSound(game()->aiSnd);
				else
					playSound(game()->playSnd);
				PlaySoundOnce = true;
			}
			//跳ね返す
			//パドルの中心からのベクトルdx
			float half = paddle->w() / 2;
			float dx = px() - (paddle->px() + half);
			//中心からの距離によって角度を決める
			float angle = Map(dx, -half - r(), half + r(), 135, 45);
			setVx(Cos(angle) * sp());
			setVy(-Sin(angle) * sp());
			//下方でぶつかった
			if (py() > paddle->py()) {
				setVy(-vy());
			}
		}
		else {
			PlaySoundOnce = false;
		}
	}

	void BALL::draw()
	{
		fill(255);
		stroke(0);
		strokeWeight(0);
		circle(game()->stage()->px() + px(), py(), r() * 2);
	}

}