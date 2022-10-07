/*メニューに表示するタイトル
GAME17
*/
#pragma once
#include"../MAIN/STATE.h"

namespace GAME17 { //自分でなにかファイルを追加したらincludeの後にこの行を追加すること。　ファイルの最後に“ } ”も忘れずに！

	class GAME : public STATE {
	public: 
		GAME(class MANAGER* manager);
		~GAME();
		void create(); 
		void destroy();
		void proc();
	private:
		//ここに必要な記憶場所を用意する
		//画像表示用
		int Img;
		//円表示用
		float Diameter;//直径
		float Px;
		float Py;
		float Vx;

		//以下はいじらないでよい
		int BackToMenuFlag=0;
	};

}

