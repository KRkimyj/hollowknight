#pragma once
#include "state.h"

class player;

class fall : public state
{
	float _jumpPower;
	float _gravity;

public :
	virtual state* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);
	virtual void effecRender(player* player, float x, float y);

	virtual void getCurrentState(player* player);
};

