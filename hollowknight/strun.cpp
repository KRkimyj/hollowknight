#include "stdafx.h"
#include "strun.h"

#include "player.h"
#include "fall.h"

state * strun::inputHandle(player * player)
{
	if (_loop >= 6/*!player->getHit()*/) return new fall;

	return nullptr;
}

void strun::update(player * player)
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

	/*if (_currentFrameY == 1 && !setFrameX)
	{
		setFrameX = true;
		_effectFrameX = _effectimgName->getMaxFrameX();
	}*/

	_count++;
	if (_count % 10 == 0)
	{
		//if (_currentFrameY == 0)
		//{
		//	/*if (_currentFrameX >= _imgName->getMaxFrameX())
		//	{
		//		_currentFrameX = 0;
		//	}*/
		//	_imgName->setFrameX(0);
		//	_imgName->setFrameY(_currentFrameY);
		//	_currentFrameX++;

		//	_count = 0;
		//}
		//else
		//{
		//	if (_currentFrameX == 0)
		//	{
		//		_currentFrameX = _imgName->getMaxFrameX();
		//	}

		//	_imgName->setFrameX(_currentFrameX);
		//	_imgName->setFrameY(_currentFrameY);
		//	_currentFrameX--;

		//	_count = 0;
		//}

		if (_effectFrameX <= _effectimgName->getMaxFrameX()) _effectFrameX = 0;
		
		_effectimgName->setFrameX(_effectFrameX);
		_effectimgName->setFrameY(0);
		_effectFrameX++;

		_count = 0;
		
	
	}
	_loop++;

	return;
}

void strun::enter(player * player)
{
	_stateName = "sturn";
	_imgName = IMAGEMANAGER->findImage("sturn");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	_effectimgName = IMAGEMANAGER->findImage("sturn effect");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;
	setFrameX = false;

	_loop = 0;

	return;
}

void strun::exit(player * player)
{
}

void strun::effecRender(player * player, float x, float y)
{
}

void strun::getCurrentState(player * player)
{
}
