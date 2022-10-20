#pragma once
#include"../MAIN/STATE.h"

namespace GAME28 { 

	class GAME : public MAIN::STATE {
	public:
		GAME(class MAIN::MANAGER* manager);
		~GAME();
		void create();
		void destroy();
		void proc();
		//このGAME内の各ステートで使用
		void fadeIn();
		bool fadeOut();
		void backToMenu();
	private:
		class MANAGER* Manager;
		int BackToMenuFlag = 0;
	};

}