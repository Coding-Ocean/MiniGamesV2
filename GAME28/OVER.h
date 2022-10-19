#pragma once
#include"GAME_STATE.h"
namespace GAME28 {

    class OVER :
        public GAME_STATE
    {
    public:
        OVER(class GAME_MANAGER*);
        ~OVER();
        void create();
        void destroy();
        void proc();
    private:
        void DrawText();
    };

}