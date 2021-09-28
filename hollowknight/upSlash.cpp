#include "stdafx.h"
#include "upSlash.h"

#include "player.h"
#include "fall.h"
#include "strun.h"

state * upSlash::inputHandle(player * player)
{
	if (_end) return new fall;

	return nullptr;
}

void upSlash::update(player * player)
{
	//_currentFrameY = player->getWay();

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
			_effectimgName->setFrameY(_currentFrameY);
			_effectFrameX++;

			_count = 0;
		}
		
	}

	return;
}

void upSlash::enter(player * player)
{
	_stateName = "up slash";
	_imgName = IMAGEMANAGER->findImage("up slash");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	_effectimgName = IMAGEMANAGER->findImage("slash effect UD");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;
	setFrameX = false;

	return;
}

void upSlash::exit(player * player)
{
}

void upSlash::effecRender(player * player, float x, float y)
{
}

void upSlash::getCurrentState(player * player)
{
}
