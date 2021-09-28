#pragma once
#include"bossStateBase.h"

class boss;

class bossTelepoOut : public bossStateBase
{
	float _timerStart, _timerEnd;

	bool _end;
	bool setFrameX;

	int _rndPattern;

public:
	virtual bossStateBase* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);
	virtual void getCurrentState(boss* boss);

};
