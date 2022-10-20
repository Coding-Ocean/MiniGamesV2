#include "TITLE.h"
#include "PLAYER.h"
#include "UNKO.h"
#include "MANAGER.h"
namespace GAME28 {

    MANAGER::MANAGER(class GAME* g)
        :Game(g)
    {
        //複数のステートで使用されるオブジェクト
        Player = new PLAYER;
        Unko = new UNKO;
        //しょっぱなのステートをセット
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