#pragma once
#include "state.h"

class player;

class dash : public state
{
	bool _end;
	bool setFrameX;

public :
	virtual state* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);
	virtual void getCurrentState(player* player);
	virtual void effecRender(player* player, float x, float y);

	virtual image* getCurrentStateEffect() { return _effectimgName; }
	virtual int getEffectFrameX() { return _effectFrameX; }
};

