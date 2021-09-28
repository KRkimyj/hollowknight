#include "stdafx.h"
#include "bossBalloonReady.h"

#include "boss.h"
#include "bossBalloon.h"

bossStateBase * bossBalloonReady::inputHandle(boss * boss)
{
	if (_end) return new bossBalloon;
	return nullptr;
}

void bossBalloonReady::update(boss * boss)
{
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
			if (_currentFrameX >= _imgName->getMaxFrameX()) _end = true;
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX++;

			_count = 0;
		}
	}

	return;
}

void bossBalloonReady::enter(boss * boss)
{
	_stateName = "boss balloon ready";
	_imgName = IMAGEMANAGER->findImage("boss balloon ready");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;
	_timer = false;


	return;
}

void bossBalloonReady::exit(boss * boss)
{
}

void bossBalloonReady::getCurrentState(boss * boss)
{
}
