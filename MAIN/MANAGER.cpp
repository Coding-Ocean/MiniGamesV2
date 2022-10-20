#include<stdio.h>
#include"../MENU/MENU.h"
#include"MANAGER.h"
#include"FADE.h"
namespace MAIN {

    MANAGER::MANAGER() {
        //-----------------------------------------------------------------------------------
        //�S�X�e�[�g���ʎg�p�́u�f�[�^�A�܂��́A�I�u�W�F�N�g�v����
        //-----------------------------------------------------------------------------------

        //�N���A�ς݃Q�[���t���b�O��ǂ݂���
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

        //�t�F�[�h�C���A�t�F�[�h�A�E�g����N���X
        Fade = new FADE;

        //-----------------------------------------------------------------------------------
        //������ςȂ̃X�e�[�g���Z�b�g
        //-----------------------------------------------------------------------------------
        State = NextState = new MENU::MENU(this);
        State->create();
    }

    MANAGER::~MANAGER() {
        //�N���A�����Q�[���̏�Ԃ��Z�[�u
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