#pragma once
#include"GAME_STATE.h"
namespace GAME28 {

    class PLAY :
        public GAME_STATE
    {
    public:
        PLAY(class GAME_MANAGER*);
        ~PLAY();
        void create();
        void destroy();
        void proc();
    private:
        void DrawText();
    };

}