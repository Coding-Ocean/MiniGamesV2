#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "GAME_MANAGER.h"
#include "TITLE.h"
#include "GAME.h"
namespace GAME28 { //�����łȂɂ��t�@�C����ǉ�������include�̌�ɂ��̍s��ǉ����邱�ƁB�@�t�@�C���̍Ō�Ɂg } �h���Y�ꂸ�ɁI

	GAME::GAME(MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		Manager = new GAME_MANAGER(this);
		//�t�F�[�h�C���i�����͂�����Ȃ��ł悢�j
		manager->fade->fadeInTrigger();
	}

	void GAME::destroy()
	{
		delete Manager;
	}

	void GAME::proc()
	{
		Manager->proc();

		manager->fade->draw();
		if (BackToMenuFlag == 1) {
			manager->fade->fadeOutTrigger();
			if (manager->fade->fadeOutEndFlag()) {
				manager->nextState = new MENU(manager);
			}
		}
	}

	void GAME::backToMenu()
	{
		BackToMenuFlag = 1;
	}

}