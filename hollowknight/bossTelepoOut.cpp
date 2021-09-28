#include "stdafx.h"
#include "bossTelepoOut.h"

#include "boss.h"
#include "bossTelepoIn.h"
#include "bossIdle.h"

bossStateBase * bossTelepoOut::inputHandle(boss * boss)
{
	if (_end) return new bossTelepoIn;
	return nullptr;
}

void bossTelepoOut::update(boss * boss)
{
	//if (boss->getPattern() == 1) boss->setBossPosition(1920 / 2 + 50, 200);

	_count++;
	if (_count % 4 == 0)
	{
		if (_currentFrameX <= _imgName->getMaxFrameX())
		{
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX++;

			_count = 0;
		}

		if (_currentFrameX >= 4)
		{
			if (_effectFrameX >= _effectimgName->getMaxFrameX()) _end = true;

			_effectimgName->setFrameX(_effectFrameX);
			_effectimgName->setFrameY(_currentFrameY);
			_effectFrameX++;

			_count = 0;
		}
	}

	return;
}

void bossTelepoOut::enter(boss * boss)
{
	_stateName = "boss teleportation out";
	_imgName = IMAGEMANAGER->findImage("boss teleportation out");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	_effectimgName = IMAGEMANAGER->findImage("grim fire");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;
	setFrameX = false;

	return;
}

void bossTelepoOut::exit(boss * boss)
{
}

void bossTelepoOut::getCurrentState(boss * boss)
{
}
