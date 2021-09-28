#pragma once
#include "gameNode.h"
#include "effect.h"

class player;

class state : public gameNode
{
protected:
	
	string _stateName;

	image* _imgName;
	int _count;
	int _currentFrameX, _currentFrameY;
	
	image* _effectimgName;
	int _effectCount;
	int _effectFrameX, _effectFrameY;

	effect* _effect;

public :

	virtual state* inputHandle(player* player) = 0;
	virtual void update(player* player) = 0;
	virtual void enter(player* player) = 0;
	virtual void exit(player* player) = 0;
	virtual void effecRender(player* player, float x, float y) = 0;

	virtual string getCurrentStateName() { return _stateName; }
	virtual image* getCurrentStateImg() { return _imgName; }
	virtual int getFramCount() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }
	
	virtual image* getCurrentStateEffect() { return _effectimgName; }
	virtual int getEffectFrameX() { return _effectFrameX; }
	virtual int getEffectFrameY() { return _effectFrameY; }

};

