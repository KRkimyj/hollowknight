#include "stdafx.h"
#include "slide.h"

#include "player.h"
#include "idle.h"
#include "wallJump.h"
#include "strun.h"

state * slide::inputHandle(player * player)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) return new wallJump;
	if (player->getCollision()) return new idle;

	return nullptr;
}

void slide::update(player * player)
{
	_currentFrameY = _isWay;

	_count++;
	if (_count % 5 == 0)
	{
		if (_currentFrameY == 0)
		{
			if (_currentFrameX >= _imgName->getMaxFrameX()) _currentFrameX = 0;
			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX++;

			_count = 0;
		}
		else
		{
			if (_currentFrameX == 0) _currentFrameX = _imgName->getMaxFrameX();

			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX--;

			_count = 0;
		}
	}

	player->setPlayerY(player->getPlayerY() + _gravity);

	return;
}

void slide::enter(player * player)
{
	_stateName = "wall slide";
	_imgName = IMAGEMANAGER->findImage("wall slide");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	_jumpPower = 0.0f;
	_gravity = 0.4f;

	_isWay = player->getWay();

	return;
}

void slide::exit(player * player)
{
}

void slide::effecRender(player * player, float x, float y)
{
}

void slide::getCurrentState(player * player)
{
}
