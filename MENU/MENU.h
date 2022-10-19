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
    float OfstX;
    float OfstY;
    float RectWidth;
    float RectHeight;
    int NumGames;
    int Yoko;
    int Tate;
    float Hue;
    float Satu;
    float Valu;
    float Angle;
    struct TITLE_LINES {
        std::string lines[3];
    };
    std::vector<TITLE_LINES> Titles;
};
