#include "stdafx.h"
#include "bossTelepoIn.h"

#include "boss.h"
#include "bossIdle.h"
#include "bossSpikeReady.h"
#include "bossTelepoOut.h"
#include "bossBalloonReady.h"
#include "bossAttackReady.h"

bossStateBase * bossTelepoIn::inputHandle(boss * boss)
{
	if (_end && _rnd == 3) return new bossSpikeReady;
	else if (_end && _rnd == 2) return new bossAttackReady;
	else if (_end && _rnd == 1) return new bossBalloonReady;
	else if (_end) return new bossTelepoOut;
	return nullptr;
}

void bossTelepoIn::update(boss * boss)
{
	if (_rnd == 1) boss->setBossPosition(1920 / 2, 200);
	else if (_rnd == 2 && _way == 0) boss->setBossPosition(1920 / 2 + 500, 925 - 372);
	else if (_rnd == 2 && _way == 1) boss->setBossPosition(1920 / 2 - 600, 925 - 372);
	else if (_rnd == 3) boss->setBossPosition(1920 / 2 - 100, 925 - _imgName->getFrameHeight());

	_count++;
	if (_count % 4 == 0)
	{
		if (_currentFrameX <= _imgName->getMaxFrameX())  _end = true;
			
		_imgName->setFrameX(_currentFrameX);
		_imgName->setFrameY(_currentFrameY);
		_currentFrameX++;

		_count = 0;


		if (_effectFrameX <= _effectimgName->getMaxFrameX())
		{
			_effectimgName->setFrameX(_effectFrameX);
			_effectimgName->setFrameY(_currentFrameY);
			_effectFrameX++;

			_count = 0;
		}
	}

	return;
}

void bossTelepoIn::enter(boss * boss)
{
	_stateName = "boss teleportation in";
	_imgName = IMAGEMANAGER->findImage("boss teleportation in");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	_effectimgName = IMAGEMANAGER->findImage("grim fire");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;
	setFrameX = false;

	_rnd = boss->getPattern();
	_way = RND->getInt(2);

	boss->setWay(_way);

	return;
}

void bossTelepoIn::exit(boss * boss)
{
}

void bossTelepoIn::getCurrentState(boss * boss)
{
}
