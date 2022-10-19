#pragma once
#include"../MAIN/STATE.h"

namespace GAME29 { //�����łȂɂ��t�@�C����ǉ�������include�̌�ɂ��̍s��ǉ����邱�ƁB�@�t�@�C���̍Ō�Ɂg } �h���Y�ꂸ�ɁI

	class GAME : public STATE {
	public:
		GAME(class MANAGER* manager);
		~GAME();
		void create();
		void destroy();
		void proc();
	private:
		//�V�[�P���X�J��
		const int TITLE = 0;
		const int PLAY = 1;
		const int OVER = 2;
		const int CLEAR = 3;
		int State;
		void Init();
		void Title();
		void Play();
		void Over();
		int BackToMenuFlag = 0;
		void BackToMenu();
		//����
		int UnkoImg;
		float UnkoAngle;
		//�~
		float CircleDiameter;//���a
		float CirclePx;
		float CirclePy;
		float CircleVx;
	};

}