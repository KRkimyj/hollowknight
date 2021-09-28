#pragma once
#include "gameNode.h"

class stage4 : public gameNode
{
	RECT _ground;

public :
	stage4() {};
	~stage4() {};

	HRESULT init();
	void release();
	void update();
	void render();

	RECT getRect() { return _ground; }

};

