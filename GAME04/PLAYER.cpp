#include "../libOne/inc/libOne.h"
#include "GAME.h"
#include "STAGE.h"
#include "PLAYER.h"
namespace GAME04 {

	PLAYER::PLAYER(GAME* game):ACTOR(game){	}

	PLAYER::~PLAYER(){}

	void PLAYER::create()
	{
		Img[0] = loadImage("assets\\GAME04\\pacman0.png");
		Img[1] = loadImage("assets\\GAME04\\pacman1.png");
		Img[2] = loadImage("assets\\GAME04\\pacman2.png");

		Size = game()->stage()->size();
		OfstX = game()->stage()->ofstX();
		OfstY = game()->stage()->ofstY();
	}

	void PLAYER::destroy()
	{
	}

	void PLAYER::init()
	{
		Pos.set(466, 720);
		//Pos.set(60, 60);
		Speed = 2;
		Dir.set(Speed, Speed);
		AnimCnt = 0;
	}

	int PLAYER::Floor(int pos)
	{
		return pos / Size * Size;
	}
	void PLAYER::update()
	{
		STAGE* stage = game()->stage();
		//�ꎞ�I�Ȏ��̈ʒu���
		INT2 nextPos = Pos;
		if (isPress(KEY_D)) {
			//�Ƃ肠�����E�ɐi�߂Ă݂�
			nextPos.x += Dir.x;
			Angle = 180;
			//�摜�E��̒��_���ʂ蓹��ɂ���
			if (stage->pathway(nextPos.x + 29, nextPos.y)) {
				//Size�̔{���ɂȂ�悤�Ɉʒu�������I�ɐݒ�
				nextPos.y = Floor(nextPos.y);
				Pos = nextPos;
			}
			//�摜�E���̒��_���ʂ蓹��ɂ���
			else if (stage->pathway(nextPos.x + 29, nextPos.y + 29)) {
				//Size�̔{���ɂȂ�悤�Ɉʒu�������I�ɐݒ�
				nextPos.y = Floor(nextPos.y + Size);
				Pos = nextPos;
			}
			//�a�Ȃ�H�ׂ�
			stage->eaten(Pos.x, Pos.y);
		}
		//�ȉ��e�����ŏ�L�Ɠ����������s��
		else if (isPress(KEY_A)) {
			nextPos.x -= Dir.x;
			Angle = 0;
			if (stage->pathway(nextPos.x, nextPos.y)) {
				nextPos.y = Floor(nextPos.y);
				Pos = nextPos;
			}
			else if (stage->pathway(nextPos.x, nextPos.y + 29)) {
				nextPos.y = Floor(nextPos.y + Size);
				Pos = nextPos;
			}
			stage->eaten(Pos.x + 29, Pos.y);
		}
		else if (isPress(KEY_W)) {
			nextPos.y -= Dir.y;
			Angle = 90;
			if (stage->pathway(nextPos.x, nextPos.y)) {
				nextPos.x = Floor(nextPos.x);
				Pos = nextPos;
			}
			else if (stage->pathway(nextPos.x + 29, nextPos.y)) {
				nextPos.x = Floor(nextPos.x + Size);
				Pos = nextPos;
			}
			stage->eaten(Pos.x, Pos.y + 29);
		}
		else if (isPress(KEY_S)) {
			nextPos.y += Dir.y;
			Angle = -90;
			if (stage->pathway(nextPos.x, nextPos.y + 29)) {
				nextPos.x = Floor(nextPos.x);
				Pos = nextPos;
			}
			else if (stage->pathway(nextPos.x + 29, nextPos.y + 29)) {
				nextPos.x = Floor(nextPos.x + Size);
				Pos = nextPos;
			}
			stage->eaten(Pos.x, Pos.y);
		}
		//���[�v
		if (Pos.x < 2)
			Pos.x = 928;
		else if (Pos.x > 928)
			Pos.x = 2;
		//�L�[�������Ă���ԃA�j���[�V��������
		if (isPress(KEY_D) || isPress(KEY_A) || isPress(KEY_W) || isPress(KEY_S)) {
			AnimCnt++;
		}
		else {
			AnimCnt = 0;
		}
	}

	void PLAYER::draw()
	{
		float px = OfstX + Pos.x - Size/2;
		float py = OfstY + Pos.y - Size/2;
		int i = AnimCnt / 4 % 3;
		image(Img[i], px, py, Angle);

		//fill(120, 100, 100);
		//print((let)"PlayerPosX=" + Pos.x);
		//print((let)"PlayerPosY=" + Pos.y);
	}
}