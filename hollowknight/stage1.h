#pragma once
#include "gameNode.h"
#include <vector>

struct tagGround
{
	RECT rc;
	float x, y;
};
class stage1 : public gameNode
{
	RECT _bench;

	vector<tagGround>				_vGround;
	vector<tagGround>::iterator		_viGround;

	

public :
	stage1() {};
	~stage1() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void stage1GroundSet();

	vector<tagGround> getVGround() { return _vGround; }
	vector<tagGround>::iterator	 getViGround() { return	_viGround; }

	int getStage1VectorSize() { return _vGround.size(); }
	RECT getStage1Ground(int i) { return _viGround[i].rc; }
	RECT getBench() { return _bench; }
};

