#pragma once

class MANAGER {
public:
    MANAGER();
    ~MANAGER();
    void proc();
    //各ステートにthisポインタを渡すことによって、以下のオブジェクトが使用可能となる
    char selectIdx; //MENUクラスで選んだゲームインデックスとして使用
    char clearFlags[30]; //全クラスで使用
    class STATE* state;
    class STATE* nextState;
    class FADE* fade;
};
