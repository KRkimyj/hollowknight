#pragma once
#include "flyState.h"

class flyIdle : public flyState
{
	int _fireCount, _rndFireCount;
	bool _isFire;
	bool _isTurn;

	string _stateName;

	image* _imgName;
	int _count;
	int _currentFrameX, _currentFrameY;
	float speed;
	float angle;

public:
	virtual flyState* inputHandle(fly* player);
	virtual void update(fly* player);
	virtual void enter(fly* player);
	virtual void exit(fly* player);

	virtual string getCurrentStateName() { return _stateName; }
	virtual image* getCurrentStateImg() { return _imgName; }
	virtual int getFramCount() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }
};

