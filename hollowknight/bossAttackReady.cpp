#include "stdafx.h"
#include "bossAttackReady.h"

#include "boss.h"
#include "bossTelepoOut.h"
#include "bossAttack.h"
bossStateBase * bossAttackReady::inputHandle(boss * boss)
{
	if (_end) return new bossAttack;
	return nullptr;
}

void bossAttackReady::update(boss * boss)
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

void bossAttackReady::enter(boss * boss)
{
	_stateName = "boss attack ready";
	_imgName = IMAGEMANAGER->findImage("boss attack ready");
	_currentFrameY = boss->getWay();
	if (_currentFrameY == 0) _currentFrameX == 0;
	else _currentFrameX = _imgName->getMaxFrameX();

	_count = 0;
	_timer = false;


	return;
}

void bossAttackReady::exit(boss * boss)
{
}

void bossAttackReady::getCurrentState(boss * boss)
{
}
