#pragma once
namespace MAIN {

    class MANAGER {
    public:
        MANAGER();
        ~MANAGER();
        void proc();
        //各ステートにthisポインタを渡すことによって、以下のオブジェクトが使用可能となる
        class FADE* fade() { return Fade; };
        void backToMenu();
        void setNextState(class STATE* nextState) { NextState = nextState; }
        void setClearFlag(int i) { ClearFlags[i] = 1; }
        //MENUから呼び出す
        char selectIdx() { return SelectIdx; }
        void setSelectIdx(char selectIdx) { SelectIdx = selectIdx; }
        char clearFlags(int i) { return ClearFlags[i]; }
    private:
        class STATE* State;
        class STATE* NextState;
        char SelectIdx; //MENUクラスで選んだゲームインデックスとして使用
        char ClearFlags[30]; //全クラスで使用
        class FADE* Fade;
    };

}