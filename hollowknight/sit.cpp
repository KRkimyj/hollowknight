#include "stdafx.h"
#include "sit.h"

#include "player.h"
#include "sitOff.h"
state * sit::inputHandle(player * player)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) return new sitOff;

	return nullptr;
}

void sit::update(player * player)
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

			_count = 0;
		}
	}

	return;
}

void sit::enter(player * player)
{
	_stateName = "sit";
	_imgName = IMAGEMANAGER->findImage("sit");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;
}

void sit::exit(player * player)
{
}

void sit::effecRender(player * player, float x, float y)
{
}

void sit::getCurrentState(player * player)
{
}
