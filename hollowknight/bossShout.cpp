#include "stdafx.h"
#include "bossShout.h"

#include "boss.h"
#include "bossIdle.h"
#include "bossTelepoOut.h"

bossStateBase * bossShout::inputHandle(boss * boss)
{
	if (_loopCount >= 12) return new bossTelepoOut;
	return nullptr;
}

void bossShout::update(boss * boss)
{


	_count++;
	if (_count % 7 == 0)
	{
		if (_currentFrameY == 0)
		{
			if (_currentFrameX >= _imgName->getMaxFrameX()) _currentFrameX = 0;
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX++;
			_loopCount++;

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

void bossShout::enter(boss * boss)
{
	_stateName = "boss shout";
	_imgName = IMAGEMANAGER->findImage("boss shout");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;
	_loopCount = 0;

	return;
}

void bossShout::exit(boss * boss)
{
}

void bossShout::getCurrentState(boss * boss)
{
}
