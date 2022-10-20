#pragma once
namespace GAME28 {

    class MANAGER
    {
    public:
        MANAGER(class GAME* g);
        ~MANAGER();
        void proc();
        void setNextState(class STATE* nextState);
        class GAME* game() { return Game; };
        class PLAYER* player() { return Player; };
        class UNKO* unko() { return Unko; };
    private:
        class STATE* State;
        class STATE* NextState;
        class GAME* Game;
        class PLAYER* Player;
        class UNKO* Unko;
    };

}

