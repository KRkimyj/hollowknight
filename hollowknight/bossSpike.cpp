#include "stdafx.h"
#include "bossSpike.h"

#include "boss.h"
#include "bossSpikeDown.h"
bossStateBase * bossSpike::inputHandle(boss * boss)
{
	if (_end) return new bossSpikeDown;
	return nullptr;
}

void bossSpike::update(boss * boss)
{
	/*if (!_timer)
	{
		_start = TIMEMANAGER->getWorldTime();
		_timer = true;
	}
	_end = TIMEMANAGER->getWorldTime();*/

	_count++;
	if (_count % 7 == 0)
	{
		if (_currentFrameX >= _imgName->getMaxFrameX())
		{
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX++;

			//_count = 0;
		}
		else _currentFrameX = 7;


		if (_effectFrameX >= _effectimgName->getMaxFrameX()) _end = true;

		_effectimgName->setFrameX(_effectFrameX);
		_effectimgName->setFrameY(_currentFrameY);
		_effectFrameX++;

		_count = 0;
	}

	return;
}

void bossSpike::enter(boss * boss)
{
	_stateName = "boss spike";
	_imgName = IMAGEMANAGER->findImage("boss spike");
	_currentFrameX = 7;
	_currentFrameY = 0;
	_count = 0;

	_effectimgName = IMAGEMANAGER->findImage("spike");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;
	setFrameX = false;

	_end = false;

	return;
}

void bossSpike::exit(boss * boss)
{
}

void bossSpike::getCurrentState(boss * boss)
{
}
