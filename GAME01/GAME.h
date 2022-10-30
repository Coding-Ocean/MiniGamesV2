#pragma once
#include <vector>
#include"../MAIN/STATE.h"

namespace GAME01 { //自分でなにかファイルを追加したらincludeの後にこの行を追加すること。　ファイルの最後に“ } ”も忘れずに！

	class GAME : public MAIN::STATE {
	public:
		GAME(class MAIN::MANAGER* manager);
		~GAME();
		void create();
		void destroy();
		void proc();
		class STAGE* stage() { return Stage; }
		class FOOD* food() { return Food; }
		class SNAKE* snake() { return Snake; }
		void toGameOver() { Playing = false; }
		bool gameOver() { return Playing == false; }
		//sounds
		int eatSnd = 0;
		int gameOverSnd = 0;
	private:
		void Init();
		//ここに必要な記憶場所を用意する
		std::vector<class ACTOR*>Actors;
		class STAGE* Stage = 0;
		class FOOD* Food = 0;
		class SNAKE* Snake = 0;
		int FrameCnt = 0;
		int GameSpeed = 0;
		//sequence
		bool Playing = true;
		//back to menu
		int BackToMenuFlag = 0;
	};

}
