#include<stdio.h>
#include"../MENU/MENU.h"
#include"MANAGER.h"
#include"FADE.h"
namespace MAIN {

    MANAGER::MANAGER() {
        //-----------------------------------------------------------------------------------
        //全ステート共通使用の「データ、または、オブジェクト」準備
        //-----------------------------------------------------------------------------------

        //クリア済みゲームフラッグを読みこむ
        FILE* fp = 0;
        fopen_s(&fp, "assets/MANAGER/data.txt", "rb");
        if (fp) {
            fread(ClearFlags, 1, 30, fp);
            fread(&SelectIdx, 1, 1, fp);
            fclose(fp);
        }
        else {
            for (int i = 0; i < 30; i++) {
                ClearFlags[i] = 0;
            }
            SelectIdx = 0;
        }

        //フェードイン、フェードアウト制御クラス
        Fade = new FADE;

        //-----------------------------------------------------------------------------------
        //しょっぱなのステートをセット
        //-----------------------------------------------------------------------------------
        State = NextState = new MENU::MENU(this);
        State->create();
    }

    MANAGER::~MANAGER() {
        //クリアしたゲームの状態をセーブ
        FILE* fp = 0;
        fopen_s(&fp, "assets/MANAGER/data.txt", "wb");
        if (fp) {
            fwrite(ClearFlags, 1, 30, fp);
            fwrite(&SelectIdx, 1, 1, fp);
            fclose(fp);
        }
        State->destroy();
        delete State;
        delete Fade;
    }

    void MANAGER::proc() {
        State->proc();
        if (State != NextState) {
            State->destroy();
            delete State;
            State = NextState;
            State->create();
        }
    }

    void MANAGER::backToMenu()
    {
        Fade->fadeOutTrigger();
        if (Fade->fadeOutEndFlag()) {
            NextState = new MENU::MENU(this);
        }
    }

}