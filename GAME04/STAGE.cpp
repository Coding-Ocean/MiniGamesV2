#include "../libOne/inc/libOne.h"
#include"GAME.h"
#include "STAGE.h"
namespace GAME04 {

	STAGE::STAGE(GAME* game):ACTOR(game){}

	STAGE::~STAGE(){}

	void STAGE::create()
	{
		Cols = 32;
		Rows = 33;
		Map = new char[Cols * Rows];

		Size = 30;
		OfstX = (width - Size * Cols) / 2;
		OfstY = (height - Size * Rows) / 2;

		Img_a = loadImage("assets\\GAME04\\map_a.png");
		Img_b = loadImage("assets\\GAME04\\map_b.png");
		Img_c = loadImage("assets\\GAME04\\map_c.png");
		Img_d = loadImage("assets\\GAME04\\map_d.png");
		Img_x = loadImage("assets\\GAME04\\map_x.png");
		Img_y = loadImage("assets\\GAME04\\map_y.png");
	}

	void STAGE::destroy()
	{
		delete[] Map;
	}

	void STAGE::init()
	{
		FILE* fp;
		fopen_s(&fp, "assets\\GAME04\\map.txt", "r");
		if (fp) {
			char d[4];
			int i = 0;
			NumFood = 0;
			while (fscanf_s(fp, "%s", d, 2) != EOF) {
				Map[i] = d[0];
				if (d[0] == 'o' || d[0] == 'p') {
					NumFood++;
				}
				i++;
				if (i >= Cols * Rows) {
					break;
				}
			}
			fclose(fp);
		}
	}

	void STAGE::update()
	{
		if (NumFood <= 0) {
			game()->toClear();
		}
	}

	void STAGE::draw()
	{
		for (int c = 1; c < Cols - 1; c++) {
			for (int r = 0; r < Rows; r++) {
				char d = Map[c + r * Cols];
				float px = OfstX + Size * c;
				float py = OfstY + Size * r;
#if 1			
				stroke(0, 0, 40);
				strokeWeight(2);
				if (d == '.' || d == 'o' || d == 'p')
					fill(0, 0, 60);
				else
					fill(0, 0, 0);
				rect(px, py, Size, Size);
#endif
#if 0
				if		(d == 'x')image(Img_x, px, py);
				else if (d == 'y')image(Img_y, px, py);
				else if (d == 'a')image(Img_a, px, py);
				else if (d == 'b')image(Img_b, px, py);
				else if (d == 'c')image(Img_c, px, py);
				else if (d == 'd')image(Img_d, px, py);
				else if (d == 'o') {
					stroke(0, 0, 100);
					strokeWeight(10);
					point(px + Size/2, py + Size/2);
				}
				else if (d == 'p') {
					stroke(0, 0, 100);
					strokeWeight(30);
					point(px + Size/2, py + Size/2);
				}
#endif
			}
		}

		//print((let)"NumFood="+NumFood);
	}

	void STAGE::drawWarpZone()
	{
		//ワープエリアを塗りつぶす
		noStroke();
		fill(0, 0, 0);
		float px = OfstX - Size/2;
		float py = OfstY + 450 - Size/2;
		rect(px, py, 60, 60);
		px = OfstX + 30 * 31 - Size/2;
		rect(px, py, 60, 60);
		//ゴーストの出入口
		stroke(300, 100, 100);
		strokeWeight(8);
		float sx = OfstX + 465 - Size / 2;
		float sy = OfstY + 420 - Size / 2;
		line(sx, sy, sx + 60, sy);
	}

	void STAGE::drawStageClear()
	{
		fill(60, 0, 100);
		textSize(100);
		textMode(BOTTOM);
		float px = OfstX + Size * Cols / 2 - 11 * 25;
		float py = OfstY + Size * Rows / 2;
		text("Stage Clear", px, py);
	}

	int STAGE::pathway(int posx, int posy)
	{
		int c = posx / Size;
		int r = posy / Size;
		int i = c + r * Cols;
		if (Map[i] == '.' || Map[i] == 'o' || Map[i] == 'p')
			return 1;
		return 0;
	}

	void STAGE::eaten(int posx, int posy) {
		int c = posx / Size;
		int r = posy / Size;
		int i = c + r * Cols;
		PowerFoodEaten = 0;
		if (Map[i] == 'o') {
			NumFood--;
			Map[i] = '.';
		}
		else if (Map[i] == 'p') {
			NumFood--;
			Map[i] = '.';
			PowerFoodEaten = 1;
		}
	}

	int STAGE::wall(int c, int r)
	{
		int i = c + r * Cols;
		if (Map[i] == '.' || Map[i] == 'o' || Map[i] == 'p') {
			return 0;
		}
		return 1;
	}
}