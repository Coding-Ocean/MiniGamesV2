#pragma once

class MANAGER {
public:
    MANAGER();
    ~MANAGER();
    void proc();
    //�e�X�e�[�g��this�|�C���^��n�����Ƃɂ���āA�ȉ��̃I�u�W�F�N�g���g�p�\�ƂȂ�
    char selectIdx; //MENU�N���X�őI�񂾃Q�[���C���f�b�N�X�Ƃ��Ďg�p
    char clearFlags[30]; //�S�N���X�Ŏg�p
    class STATE* state;
    class STATE* nextState;
    class FADE* fade;
};
