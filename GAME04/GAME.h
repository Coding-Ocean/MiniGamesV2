#pragma once
#include"../MAIN/STATE.h"
#include<vector>
namespace GAME04 { 

	class GAME : public MAIN::STATE {
	public: 
		GAME(class MAIN::MANAGER* manager);
		~GAME();
		void create(); 
		void destroy();
		void proc();

		void toOver() { State = OVER; }
		void toClear() { State = CLEAR; }
		int playing() { return State == PLAY; }

		class STAGE* stage() { return Stage; }
		class PLAYER* player() { return Player; }
	private:
		void Init();
		
		std::vector<class ACTOR*>Actors;
		class STAGE* Stage = nullptr;
		class PLAYER* Player = nullptr;

		const int PLAY = 0;
		const int OVER = 1;
		const int CLEAR = 2;
		int State = PLAY;

		int BackToMenuFlag=0;
	};

}

