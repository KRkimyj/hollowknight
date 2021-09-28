#include "stdafx.h"
#include "bossAttackEnd.h"

#include "boss.h"
#include "bossUppercutReady.h"

bossStateBase * bossAttackEnd::inputHandle(boss * boss)
{
	if (_end) return new bossUppercutReady;
	return nullptr;
}

void bossAttackEnd::update(boss * boss)
{
	boss->setBossPosition(boss->getBossPosition().x, 925 - _imgName->getFrameHeight());

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

void bossAttackEnd::enter(boss * boss)
{
	_stateName = "boss attack end";
	_imgName = IMAGEMANAGER->findImage("boss attack end");
	_currentFrameY = boss->getWay();
	if (_currentFrameY == 0) _currentFrameX == 0;
	else _currentFrameX = _imgName->getMaxFrameX();

	_count = 0;
	_timer = false;


	return;
}

void bossAttackEnd::exit(boss * boss)
{
}

void bossAttackEnd::getCurrentState(boss * boss)
{
}
