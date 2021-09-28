#include "stdafx.h"
#include "slash.h"

#include "player.h"
#include "idle.h"
#include "walk.h"
#include "strun.h"

state * slash::inputHandle(player * player)
{
	if (_end && (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D'))) return new walk;
	else if (_end) return new idle;

	return nullptr;
}

void slash::update(player * player)
{
	_currentFrameY = player->getWay();

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->setPlayerX(player->getPlayerX() + 10);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerX(player->getPlayerX() - 10);
	}

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

void slash::enter(player * player)
{
	_stateName = "slash";
	_imgName = IMAGEMANAGER->findImage("slash");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	_effectimgName = IMAGEMANAGER->findImage("slash effect LR");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;
	setFrameX = false;
	//_tagEffect->effectName = "slash effect LR"; //.effectName = imageName;
	//_tagEffect->_imgName = new image;
	//_tagEffect->_imgName = IMAGEMANAGER->findImage("slash effect LR");

	///*_x = x;
	//_y = y;*/
	//_tagEffect->_count = 0;
	//_tagEffect->_currentFrameX, _tagEffect->_currentFrameY = 0;

	return;
}

void slash::exit(player * player)
{
}

void slash::effecRender(player * player, float x, float y)
{
}

void slash::getCurrentState(player * player)
{
}
