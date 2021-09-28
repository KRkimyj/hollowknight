#include "stdafx.h"
#include "playerBullet.h"

#include "player.h"
#include "fall.h"
#include "strun.h"

state * playerBullet::inputHandle(player * player)
{
	if (_end) return new fall;
	return nullptr;
}

void playerBullet::update(player * player)
{
	_currentFrameY = player->getWay();
	if (_currentFrameY == 1 && !setFrameX)
	{
		setFrameX = true;
		_effectFrameX = _effectimgName->getMaxFrameX();
	}

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

void playerBullet::enter(player * player)
{
	_stateName = "player bullet";
	_imgName = IMAGEMANAGER->findImage("player bullet");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	_effectimgName = IMAGEMANAGER->findImage("player bullet effect");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;
	setFrameX = false;

	return;
}

void playerBullet::exit(player * player)
{
}

void playerBullet::effecRender(player * player, float x, float y)
{
}

void playerBullet::getCurrentState(player * player)
{
}
