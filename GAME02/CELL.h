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
			MayBeBom = false;
			Bom = (random() % 10 < 2 );
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
					
					stroke(128,64,0);
					strokeWeight(Scale * 0.04f);
					line(px, py, px + Scale * 0.25f, py - Scale * 0.25f);

					stroke(0);
					strokeWeight(Scale * 0.5f);
					point(px, py);
					
					stroke(255, 0, 0);
					strokeWeight(Scale * 0.08f);
					point(px + Scale * 0.25f, py - Scale * 0.25f);
				}
				else {
					fill(0, 245, 255);
					rect(px, py, scale, scale);
					if (NumNeighborBoms) {
						fill(0, 0, 60);
						textSize(Scale * 0.3f);
						textMode(BCENTER);
						text(NumNeighborBoms, px, py);
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
		void open() { Opened = true; }
		void mayBeBom() { MayBeBom = true; }
		bool notYetOpen() { return !Opened; }
		bool bom() { return Bom; }
		void setNumNeighborBoms(int num) { NumNeighborBoms = num; }
		int numNeighborBoms() { return NumNeighborBoms; }
	private:
		float Px=0, Py=0, Scale=0;
		bool Opened = false;
		bool MayBeBom = false;
		bool Bom = false;
		int NumNeighborBoms = 0;
	};
}