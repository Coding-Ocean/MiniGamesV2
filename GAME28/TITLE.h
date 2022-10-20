#pragma once
#include"STATE.h"
namespace GAME28 {

    class TITLE :
        public STATE
    {
    public:
        TITLE(class MANAGER*);
        ~TITLE();
        void create();
        void destroy();
        void proc();
    private:
        void DrawTextInfo();
        void NextState();
        bool ToNextState;
    };

}