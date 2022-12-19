#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "STAGE.h"
#include "PLAYER.h"
#include "GHOST.h"
#include "GAME.h"
namespace GAME04 { 

	GAME::GAME(MAIN::MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		hideCursor();

		//Actor�z��֓o�^
		Actors.push_back(Stage = new STAGE(this));
		Actors.push_back(Player = new PLAYER(this));
		Actors.push_back(RedGhost = new GHOST(0, this));
		Actors.push_back(new GHOST(1, this));
		Actors.push_back(new GHOST(2, this));
		Actors.push_back(new GHOST(3, this));

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
		State = PLAY;
	}

	void GAME::proc()
	{
		//���Z�b�g
		if (isTrigger(KEY_R)) {
			Init();
		}
		//�X�V
		colorMode(HSV, 100);
		angleMode(DEGREES);
		if (State == PLAY) {
			for (ACTOR* actor : Actors) {
				actor->update();
			}
		}
		//�`��
		clear(0,0,0);
		for (ACTOR* actor : Actors) {
			actor->draw();
		}
		Stage->drawWarpZone();
		if (State == CLEAR) {
			Stage->drawStageClear();
		}
		//�t�F�[�h
		Fade()->draw();
		//���j���[�ɖ߂�
		if (isTrigger(KEY_ENTER)) {	BackToMenuFlag = 1;	}
		if (BackToMenuFlag == 1) { Manager()->backToMenu();	}
	}
}