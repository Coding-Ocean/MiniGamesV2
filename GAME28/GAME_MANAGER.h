#pragma once
namespace GAME28 {

    class GAME_MANAGER
    {
    public:
        GAME_MANAGER(class GAME* g);
        ~GAME_MANAGER();
        void proc();
        void backToMenu();
        class GAME_STATE* state;
        class GAME_STATE* nextState;
        class GAME* game;
        class PLAYER* player;
        class UNKO* unko;
    };

}

