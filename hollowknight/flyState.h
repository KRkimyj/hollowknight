#pragma once
#include "gameNode.h"

class fly;

class flyState : public gameNode
{
protected:
	string _stateName;

	image* _imgName;
	int _count;
	int _currentFrameX, _currentFrameY;
	float speed;
	float angle;

public :
	virtual flyState* inputHandle(fly* player) = 0;
	virtual void update(fly* player) = 0;
	virtual void enter(fly* player) = 0;
	virtual void exit(fly* player) = 0;

	virtual string getCurrentStateName() { return _stateName; }
	virtual image* getCurrentStateImg() { return _imgName; }
	virtual int getFramCount() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }
};