#pragma once
#include "gameNode.h"
#include "effectClass.h"

class boss;

class bossStateBase : public gameNode
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
	virtual bossStateBase* inputHandle(boss* boss) = 0;
	virtual void update(boss* boss) = 0;
	virtual void enter(boss* boss) = 0;
	virtual void exit(boss* boss) = 0;

	virtual string getCurrentStateName() { return _stateName; }
	virtual image* getCurrentStateImg() { return _imgName; }
	virtual int getFramCount() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }
	virtual int getFrameWidth() { return _imgName->getFrameWidth(); }
	virtual int getFrameHeight() { return _imgName->getFrameHeight(); }

	virtual image* getCurrentStateEffect() { return _effectimgName; }
	virtual int getEffectFrameX() { return _effectFrameX; }
	virtual int getEffectFrameY() { return _effectFrameY; }
};
