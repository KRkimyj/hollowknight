#pragma once

#include "bossStateBase.h"
class boss;

class bossShout : public bossStateBase
{
	int _loopCount;

	public :

	virtual bossStateBase* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);
	virtual void getCurrentState(boss* boss);
};

