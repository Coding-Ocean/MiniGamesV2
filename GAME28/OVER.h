#pragma once
#include"STATE.h"
namespace GAME28 {

    class OVER :
        public STATE
    {
    public:
        OVER(class MANAGER*);
        ~OVER();
        void create();
        void destroy();
        void proc();
    private:
        void DrawTextInfo();
        void NextState();
        bool ToNextState;
    };

}