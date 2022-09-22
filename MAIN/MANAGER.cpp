#include<stdio.h>
#include"MANAGER.h"
#include"FADE.h"
#include"../MENU/MENU.h"
#include"../GAME23/GAME.h"
MANAGER::MANAGER() {
    //-----------------------------------------------------------------------------------
    //�S�X�e�[�g���ʎg�p�́u�f�[�^�A�܂��́A�I�u�W�F�N�g�v����
    //-----------------------------------------------------------------------------------

    //�N���A�ς݃Q�[���t���b�O��ǂ݂���
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

    //�t�F�[�h�C���A�t�F�[�h�A�E�g����N���X
    fade = new FADE;

    //-----------------------------------------------------------------------------------
    //������ςȂ̃X�e�[�g���Z�b�g
    //-----------------------------------------------------------------------------------
    state = new MENU(this);
    state->create();
    nextState = state;
}

MANAGER::~MANAGER() {
    //�N���A�����Q�[���̏�Ԃ��Z�[�u
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

