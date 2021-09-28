#include "stdafx.h"
#include "bossGreeting.h"

#include "boss.h"
#include "bossIdle.h"
#include "bossShout.h"

bossStateBase * bossGreeting::inputHandle(boss * boss)
{
	if (boss->getHit()) return new bossShout;
	if (_currentFrameX >= _imgName->getMaxFrameX()) return new bossIdle;
	return nullptr;
}

void bossGreeting::update(boss * boss)
{
	_count++;
	if (_count % 7 == 0)
	{
		if (_currentFrameY == 0)
		{
			//if (_currentFrameX >= _imgName->getMaxFrameX()) _currentFrameX = 0;
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX++;

			_count = 0;
		}
		/*else
		{
			if (_currentFrameX == 0) _currentFrameX = _imgName->getMaxFrameX();

			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX--;

			_count = 0;
		}*/
	}

	return;
}

void bossGreeting::enter(boss * boss)
{
	_stateName = "boss greeting";
	_imgName = IMAGEMANAGER->findImage("boss greeting");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	return;
}

void bossGreeting::exit(boss * boss)
{
}

void bossGreeting::getCurrentState(boss * boss)
{
}
