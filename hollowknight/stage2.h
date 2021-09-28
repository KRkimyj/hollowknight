#pragma once
#include "gameNode.h"

struct tagGround2
{
	RECT rc;
	float x, y;
};
class stage2 : public gameNode
{

	vector<tagGround2>				_vGround2;
	vector<tagGround2>::iterator	_viGround2;

public :
	stage2() {};
	~stage2() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void stage2GroundSet();

	vector<tagGround2> getVGround() { return _vGround2; }
	vector<tagGround2>::iterator getViGround() { return _viGround2; }
};

