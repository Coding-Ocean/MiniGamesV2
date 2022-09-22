#include<vector>
#include<string>
#include"../MAIN/STATE.h"

class MENU : public STATE{
public:
    MENU(class MANAGER* manager);
    ~MENU();
    void create(); 
    void destroy();
    void proc();
private:
    int ClearImg;
    float RectX;
    float RectY;
    float RectWidth;
    float RectHeight;
    int NumGames;
    int Yoko;
    int Tate;
    float Hue;
    float Satu;
    float Valu;
    float Angle;
    std::vector<std::string> Titles;
};
