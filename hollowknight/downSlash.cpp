#include "stdafx.h"
#include "downSlash.h"

#include "player.h"
#include "fall.h"
#include "strun.h"

state * downSlash::inputHandle(player * player)
{
	/*if (_end && (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D'))) return new walk;
	else */
	if (_end) return new fall;

	return nullptr;
}

void downSlash::update(player * player)
{
	if (!setFrameX)
	{
		_effectFrameX = 1;
		setFrameX = true;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->setPlayerX(player->getPlayerX() + 10);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerX(player->getPlayerX() - 10);
	}


	_count++;
	if (_count % 3 == 0)
	{

		if (_currentFrameX >= _imgName->getMaxFrameX()) _end = true;
		_imgName->setFrameX(_currentFrameX);
		_imgName->setFrameY(_currentFrameY);
		_currentFrameX++;

		_count = 0;

		if (_effectFrameX <= _effectimgName->getMaxFrameX())
		{
			_effectimgName->setFrameX(_effectFrameX);
			_effectimgName->setFrameY(1);
			_effectFrameX--;

			_count = 0;
		}
	}

	return;
}

void downSlash::enter(player * player)
{
	_stateName = "down slash";
	_imgName = IMAGEMANAGER->findImage("down slash");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	_effectimgName = IMAGEMANAGER->findImage("slash effect UD");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;
	setFrameX = false;

	return;
}

void downSlash::exit(player * player)
{
}

void downSlash::effecRender(player * player, float x, float y)
{
}

void downSlash::getCurrentState(player * player)
{
}
