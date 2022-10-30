#pragma once
#include "../libOne/inc/graphic.h"
#include "STAGE.h"
namespace GAME02
{
	class CELL {
	public:
		void create(float px, float py, float scale) {
			Px = px;
			Py = py;
			Scale = scale;
		}

		void init() {
			Opened = false;
			Bom = (random() % 10 < 2 );
			MayBeBom = false;
		}

		void draw() {
			float px = Px + Scale / 2;
			float py = Py + Scale / 2;
			float scale = Scale * 0.8f;
			rectMode(CENTER);
			stroke(255, 109, 40);
			strokeWeight(Scale * 0.15f);
			if (Opened) {
				if (Bom) {
					fill(252, 231, 0);
					rect(px, py, scale, scale);
					fill(0, 0, 0);
					stroke(0);
					strokeWeight(Scale * 0.5f);
					point(px, py);
					strokeWeight(Scale * 0.06f);
					line(px, py, px + 20, py - 20);
					stroke(255, 0, 0);
					strokeWeight(Scale*0.1f);
					point(px + 22, py - 22);
				}
				else {
					fill(0, 245, 255);
					rect(px, py, scale, scale);
					if (NumAdjacentBoms) {
						fill(0, 0, 60);
						textSize(Scale * 0.3f);
						textMode(BCENTER);
						text(NumAdjacentBoms, px, py);
					}
				}
			}
			else if (MayBeBom) {
				fill(234, 4, 126);
				rect(px, py, scale, scale);
			}
			else {
				fill(252, 231, 0);
				rect(px,py, scale, scale);
			}
		}
		bool bom() { return Bom; }
		void open() { Opened = true; }
		bool close() { return !Opened; }
		void mayBeBom() { MayBeBom = true; }
		void setNumAdjacentBoms(int num) { NumAdjacentBoms = num; }
		int numAdjacentBoms() { return NumAdjacentBoms; }
	private:
		float Px=0, Py=0, Scale=0;
		bool Bom = false;
		bool Opened = false;
		bool MayBeBom = false;
		int NumAdjacentBoms = 0;
	};
}