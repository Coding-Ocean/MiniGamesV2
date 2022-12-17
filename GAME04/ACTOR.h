#pragma once
class ACTOR {
public:
	ACTOR(class GAME* game):Game(game){}
	virtual ~ACTOR(){}
	virtual void create() {};
	virtual void destroy() {};
	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};
	class GAME* game() { return Game; }
private:
	class GAME* Game;
};