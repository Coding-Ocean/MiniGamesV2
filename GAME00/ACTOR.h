#pragma once
namespace GAME00 
{
	class ACTOR
	{
	public:
		ACTOR(class GAME* game) :Game(game) {}
		~ACTOR() { Game = 0; }
		virtual void init(){}
		virtual void update(){}
		virtual void draw(){}
		//getter setter
		class GAME* game() { return Game; }
		float px() { return Px; }
		float py() { return Py; }
		float sp() { return Sp; }
		float vx() { return Vx; }
		float vy() { return Vy; }
		float r() { return W; }
		float w() { return W; }
		float h() { return H; }
		void setPx(float px) { Px = px; }
		void setPy(float py) { Py = py; }
		void setSp(float sp) { Sp = sp; }
		void setVx(float vx) { Vx = vx; }
		void setVy(float vy) { Vy = vy; }
		void setR(float r) { W = r; }
		void setW(float w) { W = w; }
		void setH(float h) { H = h; }
	private:
		class GAME* Game=0;
		float W = 0;//幅（半径）
		float H = 0;
		float Px=0, Py=0;//位置
		float Sp=0, Vx=0, Vy=0;//スピードとベクトル
	};
}