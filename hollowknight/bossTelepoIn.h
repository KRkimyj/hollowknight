#pragma once
#include "bossStateBase.h"

class boss;

class bossRndTelepo;

class bossTelepoIn : public bossStateBase
{
	bossRndTelepo* rndTelepo;

	float _timerStart, _timerEnd;

	bool _end;
	bool setFrameX;

	int _rnd;
	int _way;

public:
	virtual bossStateBase* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);
	virtual void getCurrentState(boss* boss);
};

