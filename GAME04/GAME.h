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
	private:
		void Init();
		std::vector<class ACTOR*>Actors;
		int BackToMenuFlag=0;
	};

}

