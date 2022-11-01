#include "../libOne/inc/libOne.h"
#include "../MAIN/MANAGER.h"
#include "../MAIN/FADE.h"
#include "../MENU/MENU.h"
#include "GAME.h"
namespace GAME02 { //�����łȂɂ��t�@�C����ǉ�������include�̌�ɂ��̍s��ǉ����邱�ƁB�@�t�@�C���̍Ō�Ɂg } �h���Y�ꂸ�ɁI

	GAME::GAME(MAIN::MANAGER* manager) :STATE(manager) {}
	GAME::~GAME() {}

	void GAME::create()
	{
		Field.create();

		Fade()->fadeInTrigger();
	}

	void GAME::destroy()
	{
		Field.destroy();
	}

	void GAME::proc()
	{
		clear(234, 4, 126);
		Field.update();
		Field.draw();

		//�t�F�[�h����
		Fade()->draw();
		//���j���[�ɖ߂�
		if (isTrigger(KEY_ENTER)) {BackToMenuFlag = 1;}
		if (BackToMenuFlag == 1) {Manager()->backToMenu();}
	}
}