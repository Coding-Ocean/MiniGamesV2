#include "TITLE.h"
#include "PLAYER.h"
#include "UNKO.h"
#include "MANAGER.h"
namespace GAME28 {

    MANAGER::MANAGER(class GAME* g)
        :Game(g)
    {
        //�����̃X�e�[�g�Ŏg�p�����I�u�W�F�N�g
        Player = new PLAYER;
        Unko = new UNKO;
        //������ςȂ̃X�e�[�g���Z�b�g
        State = NextState = new TITLE(this);
        State->create();
    }

    MANAGER::~MANAGER() 
    {
        State->destroy();
        delete State;
        delete Player;
        delete Unko;
    }

    void MANAGER::proc() 
    {
        State->proc();
        if (State != NextState) {
            State->destroy();
            delete State;
            State = NextState;
            State->create();
        }
    }

    void MANAGER::setNextState(STATE* nextState)
    {
        NextState = nextState;
    }

}