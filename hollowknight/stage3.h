#pragma once
#include "gameNode.h"

class stage3 : public gameNode
{
	RECT _ground;
public :
	stage3() {};
	~stage3() {};

	HRESULT init();
	void release();
	void update();
	void render();

	RECT getRect() { return _ground; }
};

