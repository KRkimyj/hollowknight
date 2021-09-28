#include "stdafx.h"
#include "bossUppercutReady.h"

#include "boss.h"
#include "bossUppercut.h"

bossStateBase * bossUppercutReady::inputHandle(boss * boss)
{
	if (_end) return new bossUppercut;
	return nullptr;
}

void bossUppercutReady::update(boss * boss)
{
	boss->setBossPosition(_x, 925 - _imgName->getFrameHeight());

	_count++;
	if (_count % 10 == 0)
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

void bossUppercutReady::enter(boss * boss)
{
	_stateName = "boss uppercut ready";
	_imgName = IMAGEMANAGER->findImage("boss uppercut ready");

	_currentFrameY = boss->getWay();
	if (_currentFrameY == 0) _currentFrameX == 0;
	else _currentFrameX = _imgName->getMaxFrameX();


	_count = 0;
	_timer = false;

	_x = boss->getBossPosition().x;
	return;
}

void bossUppercutReady::exit(boss * boss)
{
}

void bossUppercutReady::getCurrentState(boss * boss)
{
}
