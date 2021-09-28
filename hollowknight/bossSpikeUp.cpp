#include "stdafx.h"
#include "bossSpikeUp.h"

#include "boss.h"
#include "bossIdle.h"
#include "bossSpike.h"

bossStateBase * bossSpikeUp::inputHandle(boss * boss)
{
	if (_end) return new bossSpike;
	return nullptr;
}

void bossSpikeUp::update(boss * boss)
{
	_count++;
	if (_count % 6 == 0)
	{
		if (_currentFrameX >= _imgName->getMaxFrameX())
		{
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX++;

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

void bossSpikeUp::enter(boss * boss)
{
	_stateName = "boss spike up";
	_imgName = IMAGEMANAGER->findImage("boss spike");
	_currentFrameX = 7;
	_currentFrameY = 0;
	_count = 0;

	_effectimgName = IMAGEMANAGER->findImage("spike up");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;
	setFrameX = false;

	return;
}

void bossSpikeUp::exit(boss * boss)
{
}

void bossSpikeUp::getCurrentState(boss * boss)
{
}
