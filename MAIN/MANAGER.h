#pragma once
namespace MAIN {

    class MANAGER {
    public:
        MANAGER();
        ~MANAGER();
        void proc();
        //�e�X�e�[�g��this�|�C���^��n�����Ƃɂ���āA�ȉ��̃I�u�W�F�N�g���g�p�\�ƂȂ�
        class FADE* fade() { return Fade; };
        void backToMenu();
        void setNextState(class STATE* nextState) { NextState = nextState; }
        void setClearFlag(int i) { ClearFlags[i] = 1; }
        //MENU����Ăяo��
        char selectIdx() { return SelectIdx; }
        void setSelectIdx(char selectIdx) { SelectIdx = selectIdx; }
        char clearFlags(int i) { return ClearFlags[i]; }
    private:
        class STATE* State;
        class STATE* NextState;
        char SelectIdx; //MENU�N���X�őI�񂾃Q�[���C���f�b�N�X�Ƃ��Ďg�p
        char ClearFlags[30]; //�S�N���X�Ŏg�p
        class FADE* Fade;
    };

}