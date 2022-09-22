#include<stdio.h>
#include"MANAGER.h"
#include"FADE.h"
#include"../MENU/MENU.h"
#include"../GAME23/GAME.h"
MANAGER::MANAGER() {
    //-----------------------------------------------------------------------------------
    //全ステート共通使用の「データ、または、オブジェクト」準備
    //-----------------------------------------------------------------------------------

    //クリア済みゲームフラッグを読みこむ
    FILE* fp = 0;
    fopen_s(&fp, "data/data.txt", "rb");
    if (fp) {
        fread(clearFlags, 1, 30, fp);
        fread(&selectIdx, 1, 1, fp);
        fclose(fp);
    }
    else {
        for (int i = 0; i < 30; i++) {
            clearFlags[i] = 0;
            selectIdx = 0;
        }
    }

    //フェードイン、フェードアウト制御クラス
    fade = new FADE;

    //-----------------------------------------------------------------------------------
    //しょっぱなのステートをセット
    //-----------------------------------------------------------------------------------
    state = new MENU(this);
    state->create();
    nextState = state;
}

MANAGER::~MANAGER() {
    //クリアしたゲームの状態をセーブ
    FILE* fp = 0;
    fopen_s(&fp, "data/data.txt", "wb");
    if (fp) {
        fwrite(clearFlags, 1, 30, fp);
        fwrite(&selectIdx, 1, 1, fp);
        fclose(fp);
    }
    state->destroy();
    delete state;
    delete fade;
}

void MANAGER::proc() {
    state->proc();
    if (state != nextState) {
        state->destroy();
        delete state;
        state = nextState;
        state->create();
    }
}

