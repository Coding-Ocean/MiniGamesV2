#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "GAME.h"
namespace GAME29 { //�����łȂɂ��t�@�C����ǉ�������include�̌�ɂ��̍s��ǉ����邱�ƁB�@�t�@�C���̍Ō�Ɂg } �h���Y�ꂸ�ɁI

	GAME::GAME(MAIN::MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		UnkoImg = loadImage("assets/GAME29/unkoWhite.png");
		Init();
		State = TITLE;
		//�t�F�[�h�C��
		manager->fade->fadeInTrigger();
	}

	void GAME::destroy()
	{

	}

	void GAME::proc()
	{
		if (State == TITLE) {
			Title();
		}
		else if (State == PLAY) {
			Play();
		}
		else if (State == OVER) {
			Over();
		}
		BackToMenu();
	}

	void GAME::Init()
	{
		CircleDiameter = 200;
		CirclePx = -400;
		CirclePy = height / 2;
		CircleVx = 20;

		UnkoAngle = 0;
	}

	void GAME::Title()
	{
		clear(200);

		fill(0);
		textMode(TOP);
		textSize(100);
		text("TITLE", 0, 0);
		textSize(50);
		text("Push space key to start.", 0, 100);

		if (isTrigger(KEY_SPACE)) {
			State = PLAY;
		}
	}

	void GAME::Play()
	{
		//�X�V--------------------------------------------
		//�~
		CirclePx += CircleVx;
		//�`��--------------------------------------------
		clear(200);
		//�~
		fill(255);
		circle(CirclePx, CirclePy, CircleDiameter);
		//����
		rectMode(CENTER);
		imageColor(255, 128, 0);
		image(UnkoImg, width - 100, height / 2, UnkoAngle);
		//�e�L�X�g
		fill(0);
		textMode(TOP);
		textSize(100);
		text("PLAY", 0, 0);
		//���̃X�e�[�g-------------------------------------
		if (CirclePx >= width - 100) {
			State = OVER;
		}
	}

	void GAME::Over()
	{
		//�X�V--------------------------------------------
		//����
		UnkoAngle += 1.f;
		//�`��--------------------------------------------
		clear(200);
		//�~
		fill(255);
		circle(CirclePx, CirclePy, CircleDiameter);
		//����
		rectMode(CENTER);
		imageColor(255, 128, 0);
		image(UnkoImg, width - 100, height / 2, UnkoAngle);
		//�����\��
		fill(0);
		textMode(TOP);
		textSize(100);
		text("OVER", 0, 0);
		textSize(50);
		text("Push space key to replay", 0, 100);
		text("Push enter key to return menu", 0, 150);
		//���̃X�e�[�g-------------------------------------
		//���v���C
		if (isTrigger(KEY_SPACE)) {
			Init();
			State = PLAY;
		}
		//���j���[�ɖ߂�
		if (isTrigger(KEY_ENTER)) {
			BackToMenuFlag = 1;
		}
	}

	void GAME::BackToMenu()
	{
		manager->fade->draw();
		if (BackToMenuFlag == 1) {
			manager->fade->fadeOutTrigger();
			if (manager->fade->fadeOutEndFlag()) {
				manager->nextState = new MENU::MENU(manager);
			}
		}
	}

}