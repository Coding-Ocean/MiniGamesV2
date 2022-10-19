#include "TITLE.h"
#include "GAME.h"
#include "PLAYER.h"
#include "UNKO.h"
#include "GAME_MANAGER.h"
namespace GAME28 {

    GAME_MANAGER::GAME_MANAGER(GAME* g)
        :game(g)
    {
        player = new PLAYER;
        unko = new UNKO;
        //しょっぱなのステートをセット
        state = new TITLE(this);
        nextState = state;
        state->create();
    }

    GAME_MANAGER::~GAME_MANAGER() 
    {
        state->destroy();
        delete state;
        delete player;
        delete unko;
    }

    void GAME_MANAGER::proc() 
    {
        state->proc();
        if (state != nextState) {
            state->destroy();
            delete state;
            state = nextState;
            state->create();
        }
    }

    void GAME_MANAGER::backToMenu()
    {
        game->backToMenu();
    }

}