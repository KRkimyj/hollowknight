#include "stdafx.h"
#include "bossIdle.h"

#include "boss.h"
#include "bossGreeting.h"

bossStateBase * bossIdle::inputHandle(boss * boss)
{
	if (_end - _start > 3) return new bossGreeting;

	return nullptr;
}

void bossIdle::update(boss * boss)
{//idle은 한방향뿐
	if (!_timer)
	{
		_start = TIMEMANAGER->getWorldTime();
		_timer = true;
	}
	_end = TIMEMANAGER->getWorldTime();
	
	_count++;
	if (_count % 7 == 0)
	{
		if (_currentFrameY == 0)
		{
			if (_currentFrameX >= _imgName->getMaxFrameX()) _currentFrameX = 0;
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX++;

			_count = 0;
		}
	}

	return;
}

void bossIdle::enter(boss * boss)
{
	_stateName = "boss idle";
	_imgName = IMAGEMANAGER->findImage("boss idle");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;
	_timer = false;
	return;
}

void bossIdle::exit(boss * boss)
{
}

void bossIdle::getCurrentState(boss * boss)
{
}
