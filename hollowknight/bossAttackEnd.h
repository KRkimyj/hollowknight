#pragma once
#include "bossStateBase.h"

class boss;

class bossAttackEnd : public bossStateBase
{
	float _start, _end;
	bool _timer;

	float _x;

public:

	virtual bossStateBase* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);
	virtual void getCurrentState(boss* boss);
};

