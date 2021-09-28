#include "stdafx.h"
#include "dash.h"

#include "player.h"
#include "idle.h"
#include "fall.h"
#include "strun.h"

state * dash::inputHandle(player * player)
{
	/*if (player->getCollision())
	{
		return new idle();
	}*/
	if (_end)
	{
		return new fall;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//return new jump;
	}
	return nullptr;
}

void dash::update(player * player)
{
	_currentFrameY = player->getWay();
	if (_currentFrameY == 1 && !setFrameX)
	{
		setFrameX = true;
		_effectFrameX = _effectimgName->getMaxFrameX();
	}

	if (_currentFrameY == 0) player->setPlayerX(player->getPlayerX() + 25);
	if (_currentFrameY == 1) player->setPlayerX(player->getPlayerX() - 25);

	_count++;
	if (_count % 3 == 0)
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
			if (_currentFrameX == 0) _currentFrameX = _imgName->getMaxFrameX();

			_imgName->setFrameX(_currentFrameX);
			_imgName->setFrameY(_currentFrameY);
			_currentFrameX--;

			if (_currentFrameX == 0) _end = true;

			_count = 0;
		}
		if (_currentFrameY == 0)
		{
			if (_effectFrameX <= _effectimgName->getMaxFrameX())
			{
				_effectimgName->setFrameX(_effectFrameX);
				_effectimgName->setFrameY(_currentFrameY);
				_effectFrameX++;

				_count = 0;
			}
		}
		else
		{
			if (_effectFrameX >= 0)
			{
				_effectimgName->setFrameX(_effectFrameX);
				_effectimgName->setFrameY(_currentFrameY);
				_effectFrameX--;

				_count = 0;
			}
		}
	}

	return;
}

void dash::enter(player * player)
{
	_stateName = "dash";
	_imgName = IMAGEMANAGER->findImage("dash");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;
	_end = false;

	_effectimgName = IMAGEMANAGER->findImage("dash effect LR");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;
	setFrameX = false;
	return;
}

void dash::exit(player * player)
{
}

void dash::getCurrentState(player * player)
{
}

void dash::effecRender(player * player, float x, float y)
{
}
