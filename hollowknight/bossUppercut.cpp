#include "stdafx.h"
#include "bossUppercut.h"

#include "boss.h"
#include "bossTelepoOut.h"

bossStateBase * bossUppercut::inputHandle(boss * boss)
{
	if (_end) return new bossTelepoOut;
	return nullptr;
}

void bossUppercut::update(boss * boss)
{
	_y -= 30;

	boss->setBossPosition(boss->getBossPosition().x, _y);

	_count++;
	if (_count % 4 == 0)
	{
		if (_currentFrameY == 0)
		{
			if (_currentFrameX >= _imgName->getMaxFrameX()) _end = true;
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX++;

			_count = 0;
		}
		else
		{
			if (_currentFrameX <= 0) _end = true;
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX--;

			_count = 0;
		}
	}

	return;
}

void bossUppercut::enter(boss * boss)
{
	_stateName = "boss uppercut";
	_imgName = IMAGEMANAGER->findImage("boss uppercut");

	_currentFrameY = boss->getWay();
	if (_currentFrameY == 0) _currentFrameX == 0;
	else _currentFrameX = _imgName->getMaxFrameX();


	_count = 0;
	_timer = false;

	_y = 925 - _imgName->getFrameHeight();
	return;
}

void bossUppercut::exit(boss * boss)
{
}

void bossUppercut::getCurrentState(boss * boss)
{
}
