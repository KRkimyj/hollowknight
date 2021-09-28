#pragma once
#include "state.h"

class slide : public state
{
	float _jumpPower;
	float _gravity;

	int _isWay;

public :
	virtual state* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);
	virtual void effecRender(player* player, float x, float y);

	virtual void getCurrentState(player* player);

	virtual int getFramCount() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }
};

