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
		//�{�[�����ǂɂԂ�����
		bool hit = false;
		if (px() < r() && vx() < 0) {
			setVx(-vx());
			hit = true;
		}
		else if (px() > game()->stage()->w() - r() && vx() > 0) {
			setVx(-vx());
			hit = true;
		}
		//�R�[�g���Ȃ特��炷
		if (hit && 
			py() >= 0 && 
			py() <= game()->stage()->h()) {
			playSound(game()->wallSnd);
			hit = false;
		}
		//�R�[�g�O�ɏo�Ă��������A�_�����ꂽ�ق�����T�[�u�B
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
		//�p�h���Ƃ̓����蔻��
		Collision();
		//�ړ�
		setPx(px() + vx());
		setPy(py() + vy());
	}

	void BALL::Collision()
	{
		//�ΏۑI��
		ACTOR* paddle;
		if (py() < game()->stage()->h() / 2)
			paddle = game()->ai();
		else
			paddle = game()->player();
		//�p�h���ɂ�������
		if (py() >= paddle->py() - r() &&//��
			py() <= paddle->py() + r() &&//��
			px() >= paddle->px() - r() &&//��
			px() <= paddle->px() + paddle->w() + r()//�E
			) {
			if (PlaySoundOnce == false) {
				if (py() < game()->stage()->h() / 2)
					playSound(game()->aiSnd);
				else
					playSound(game()->playSnd);
				PlaySoundOnce = true;
			}
			//���˕Ԃ�
			//�p�h���̒��S����̃x�N�g��dx
			float half = paddle->w() / 2;
			float dx = px() - (paddle->px() + half);
			//���S����̋����ɂ���Ċp�x�����߂�
			float angle = Map(dx, -half - r(), half + r(), 135, 45);
			setVx(Cos(angle) * sp());
			setVy(-Sin(angle) * sp());
			//�����łԂ�����
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