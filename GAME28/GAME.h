#pragma once
#include"../MAIN/STATE.h"

namespace GAME28 { 

	class GAME : 
		public STATE {
	public:
		GAME(class MANAGER* manager);
		~GAME();
		void create();
		void destroy();
		void proc();
		void backToMenu();
	private:
		class GAME_MANAGER* Manager;
		int BackToMenuFlag = 0;
	};

}