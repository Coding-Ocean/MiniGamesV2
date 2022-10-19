#pragma once
#include"../MAIN/STATE.h"

namespace GAME29 { //自分でなにかファイルを追加したらincludeの後にこの行を追加すること。　ファイルの最後に“ } ”も忘れずに！

	class GAME : public STATE {
	public:
		GAME(class MANAGER* manager);
		~GAME();
		void create();
		void destroy();
		void proc();
	private:
		//シーケンス遷移
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
		//うんこ
		int UnkoImg;
		float UnkoAngle;
		//円
		float CircleDiameter;//直径
		float CirclePx;
		float CirclePy;
		float CircleVx;
	};

}