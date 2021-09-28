#pragma once
#include "state.h"

class palyer;

class downSlash : public state
{
	bool _end;
	bool setFrameX;

public:
	virtual state* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);
	virtual void effecRender(player* player, float x, float y);

	virtual void getCurrentState(player* player);

	virtual int getFramCount() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }

	virtual image* getCurrentStateEffect() { return _effectimgName; }
	virtual int getEffectFrameX() { return _effectFrameX; }
};

