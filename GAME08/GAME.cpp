#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "GAME.h"
namespace GAME08 { //�����łȂɂ��t�@�C����ǉ�������include�̌�ɂ��̍s��ǉ����邱�ƁB�@�t�@�C���̍Ō�Ɂg } �h���Y�ꂸ�ɁI

	GAME::GAME(MANAGER* manager) :STATE(manager) {} 
	GAME::~GAME(){}

	void GAME::create()
	{
		Img = loadImage("../game08/assets/unkoWhite.png");

		Diameter = 200;
		Px = -100;
		Py = height / 2;
		Vx = 20;

		//�t�F�[�h�C���i�����͂�����Ȃ��ł悢�j
		manager->fade->fadeInTrigger();
	}

	void GAME::destroy()
	{

	}

	void GAME::proc()
	{
		//�X�V
		Px += Vx;

		//�`��
		clear(200);
		circle(Px, Py, Diameter);
		
		//�~���E�ɏ�������Q�[���I�[�o�[�Ƃ���
		if (Px > 2100) {
			//���񂱕\��
			rectMode(CENTER);
			image(Img, width / 2, height / 2);
			//�����\��
			fill(255, 0, 0);
			textSize(200);
			text("Game Over", 500, 100);
			textSize(60);
			text("Enter�Ń��j���[�ɖ߂�", 600, 800);
			//���j���[�ɖ߂�
			if (isTrigger(KEY_ENTER)) {
				BackToMenuFlag = 1;
			}
		}

		//���j���[�ɖ߂� (��{�I�Ɉȉ��͂�����Ȃ��Ă悢)
		manager->fade->draw();
		if (BackToMenuFlag == 1) {
			manager->fade->fadeOutTrigger();
			if (manager->fade->fadeOutEndFlag()) {
				
				manager->nextState = new MENU(manager);
			}
		}
	}
}