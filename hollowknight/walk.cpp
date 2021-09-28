#include "stdafx.h"
#include "walk.h"

#include "player.h"
#include "idle.h"
#include "jump.h"
#include "dash.h"
#include "slash.h"
#include "fall.h"
#include "playerBullet.h"
#include "strun.h"

state * walk::inputHandle(player * player)
{
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		return new idle;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		return new jump;
	}
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		return new dash;
	}
	if (KEYMANAGER->isOnceKeyDown('J')) return new slash;
	if (player->getPlayerRect().right < player->getGroundRect().left || player->getPlayerRect().left > player->getGroundRect().right) return new fall;
	if (KEYMANAGER->isOnceKeyDown('I')) return new playerBullet;

	return nullptr;
}

void walk::update(player* player)
{
	
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->setPlayerX(player->getPlayerX() + 10);
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerX(player->getPlayerX() - 10);
	}
	
	
	_currentFrameY = player->getWay();

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
	return;
}

void walk::enter(player * player)
{
	_stateName = "walk";
	_imgName = IMAGEMANAGER->findImage("walk");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	return;
}

void walk::exit(player * player)
{
}

void walk::effecRender(player * player, float x, float y)
{
}

void walk::getCurrentState(player * player)
{
}
