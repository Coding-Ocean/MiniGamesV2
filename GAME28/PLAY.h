#pragma once
#include"STATE.h"
namespace GAME28 {

    class PLAY :
        public STATE
    {
    public:
        PLAY(class MANAGER*);
        ~PLAY();
        void create();
        void destroy();
        void proc();
    private:
        void DrawTextInfo();
        void NextState();
    };

}