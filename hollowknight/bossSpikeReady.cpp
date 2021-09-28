#include "stdafx.h"
#include "bossSpikeReady.h"

#include "boss.h"
#include "bossIdle.h"
#include "bossSpikeUp.h"

bossStateBase * bossSpikeReady::inputHandle(boss * boss)
{
	if (_end) return new bossSpikeUp;
	return nullptr;
}

void bossSpikeReady::update(boss * boss)
{
	_count++;
	if (_count % 7 == 0)
	{
		if (_currentFrameX <= _imgName->getMaxFrameX())
		{
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX++;

			_count = 0;
		}

		if (_currentFrameX >= 7)
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

void bossSpikeReady::enter(boss * boss)
{
	_stateName = "boss spike ready";
	_imgName = IMAGEMANAGER->findImage("boss spike");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	_effectimgName = IMAGEMANAGER->findImage("spike ready");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;
	setFrameX = false;

	return;
}

void bossSpikeReady::exit(boss * boss)
{
}

void bossSpikeReady::getCurrentState(boss * boss)
{
}
