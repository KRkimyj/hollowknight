#include "stdafx.h"
#include "bossAttack.h"

#include "boss.h"
#include "bossAttackEnd.h"

bossStateBase * bossAttack::inputHandle(boss * boss)
{
	if (_end) return new bossAttackEnd;

	return nullptr;
}

void bossAttack::update(boss * boss)
{
	if (_currentFrameY == 0) _x -= 20;
	else _x += 20;
	boss->setBossPosition(_x, 925 - _imgName->getFrameHeight());

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

void bossAttack::enter(boss * boss)
{
	_stateName = "boss attack";
	_imgName = IMAGEMANAGER->findImage("boss attack");
	
	_currentFrameY = boss->getWay();
	if (_currentFrameY == 0) _currentFrameX == 0;
	else _currentFrameX = _imgName->getMaxFrameX();
	

	_count = 0;
	_timer = false;

	_x = boss->getBossPosition().x;
	return;
}

void bossAttack::exit(boss * boss)
{
}

void bossAttack::getCurrentState(boss * boss)
{
}
