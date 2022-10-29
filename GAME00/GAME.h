#pragma once
#include <vector>
#include "../MAIN/STATE.h"

namespace GAME00 
{
	class GAME : 
		public MAIN::STATE 
	{
	public: 
		GAME(class MAIN::MANAGER* manager);
		~GAME();
		void create(); 
		void destroy();
		void proc();
		void gameSet() { Playing = false; }
		class ACTOR* stage() { return Stage; }
		class ACTOR* player(){ return Player; };
		class ACTOR* ai() { return Ai; };
		class ACTOR* ball() { return Ball; };
		int playSnd;
		int aiSnd;
		int wallSnd;
		int loseSnd;
		int winSnd;
		int pointSnd;
	private:
		void Init();
		std::vector<ACTOR*>Actors;
		class ACTOR* Stage=0;
		class ACTOR* Player=0;
		class ACTOR* Ai=0;
		class ACTOR* Ball=0;
		class ACTOR* Score=0;
		int BackToMenuFlag = 0;
		bool Playing = true;
	};

}

