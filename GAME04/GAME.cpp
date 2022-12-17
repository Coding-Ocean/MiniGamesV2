#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "STAGE.h"
#include "GAME.h"
namespace GAME04 { 

	GAME::GAME(MAIN::MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		hideCursor();

		//Actor�z��֓o�^
		Actors.push_back(Stage = new STAGE(this));

		//�摜�ǂݍ��݂Ȃ�
		for (ACTOR* actor : Actors) {
			actor->create();
		}
		//�f�[�^������
		Init();
		//�t�F�[�h�C��
		Fade()->fadeInTrigger();
	}

	void GAME::destroy()
	{
		for (ACTOR* actor : Actors) {
			actor->destroy();
			delete actor;
		}
		showCursor();
	}

	void GAME::Init()
	{
		for (ACTOR* actor : Actors) {
			actor->init();
		}
	}

	void GAME::proc()
	{
		//���Z�b�g
		if (isTrigger(KEY_R)) {
			Init();
		}
		colorMode(HSV, 100);
		angleMode(DEGREES);
		//�X�V
		for (ACTOR* actor : Actors) {
			actor->update();
		}
		//�`��
		clear(0,0,0);
		for (ACTOR* actor : Actors) {
			actor->draw();
		}
		//�t�F�[�h
		Fade()->draw();
		//���j���[�ɖ߂�
		if (isTrigger(KEY_ENTER)) {	BackToMenuFlag = 1;	}
		if (BackToMenuFlag == 1) { Manager()->backToMenu();	}
	}
}