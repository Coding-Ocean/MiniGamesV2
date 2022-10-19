#include<vector>
#include<string>
#include"../MAIN/STATE.h"
namespace MENU {

    class MENU : public MAIN::STATE {
    public:
        MENU(class MAIN::MANAGER* manager);
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

}