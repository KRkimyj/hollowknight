#pragma once

#include "bossStateBase.h"

class boss;

class bossGreeting : public bossStateBase
{
	
public:

	virtual bossStateBase* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);
	virtual void getCurrentState(boss* boss);
};

