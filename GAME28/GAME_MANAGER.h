#pragma once
namespace GAME28 {

    class GAME_MANAGER
    {
    public:
        GAME_MANAGER(class GAME* g);
        ~GAME_MANAGER();
        void proc();
        class GAME_STATE* state;
        class GAME_STATE* nextState;
        class PLAYER* player;
        class UNKO* unko;
        class GAME* game;
    };

}

