#pragma once
#include"../MAIN/STATE.h"
#include"STAGE.h"
namespace GAME02 { //�����łȂɂ��t�@�C����ǉ�������include�̌�ɂ��̍s��ǉ����邱�ƁB�@�t�@�C���̍Ō�Ɂg } �h���Y�ꂸ�ɁI

	class GAME : public MAIN::STATE {
	public:
		GAME(class MAIN::MANAGER* manager);
		~GAME();
		void create(); 
		void destroy();
		void proc();
	private:
		//�����ɕK�v�ȋL���ꏊ��p�ӂ���
		STAGE Stage;
		//�ȉ��͂�����Ȃ��ł悢
		int BackToMenuFlag=0;
	};

}

