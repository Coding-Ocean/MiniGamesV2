#pragma once
#include"../MAIN/STATE.h"
#include"STAGE.h"
namespace GAME02 { //自分でなにかファイルを追加したらincludeの後にこの行を追加すること。　ファイルの最後に“ } ”も忘れずに！

	class GAME : public MAIN::STATE {
	public:
		GAME(class MAIN::MANAGER* manager);
		~GAME();
		void create(); 
		void destroy();
		void proc();
	private:
		//ここに必要な記憶場所を用意する
		STAGE Stage;
		//以下はいじらないでよい
		int BackToMenuFlag=0;
	};

}

