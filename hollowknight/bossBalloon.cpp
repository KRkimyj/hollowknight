#include "stdafx.h"
#include "bossBalloon.h"

#include "boss.h"
#include "bossTelepoOut.h"

bossStateBase * bossBalloon::inputHandle(boss * boss)
{
	if (_end - _start >= 4) return new bossTelepoOut;

	return nullptr;
}

void bossBalloon::update(boss * boss)
{
	if(!_timer)
	{
		_start = TIMEMANAGER->getWorldTime();
		_timer = true;
	}
	_end = TIMEMANAGER->getWorldTime();

	_count++;
	if (_count % 7 == 0)
	{
		
		if (_currentFrameX < _imgName->getMaxFrameX())
		{
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX++;

			_count = 0;
		}

		else _currentFrameX = 1;
	}

	return;
}

void bossBalloon::enter(boss * boss)
{
	_stateName = "boss balloon";
	_imgName = IMAGEMANAGER->findImage("boss balloon");
	_currentFrameX = 0;
	_currentFrameY = 0;
	_count = 0;

	return;
}

void bossBalloon::exit(boss * boss)
{
}

void bossBalloon::getCurrentState(boss * boss)
{
}
