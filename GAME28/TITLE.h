#pragma once
#include"GAME_STATE.h"
namespace GAME28 {

    class TITLE :
        public GAME_STATE
    {
    public:
        TITLE(class GAME_MANAGER*);
        ~TITLE();
        void create();
        void destroy();
        void proc();
    private:
        void DrawText();
    };

}