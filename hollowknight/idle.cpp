#include "stdafx.h"
#include "idle.h"

#include "player.h"
#include "walk.h"
#include "jump.h"
#include "dash.h"
#include "slash.h"
#include "fall.h"
#include "upSlash.h"
#include "playerBullet.h"
#include "strun.h"
#include "sitOn.h"

state * idle::inputHandle(player * player)
{
	if ((KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D')))
	{
		return new walk();
	}
	if (player->getSave() && KEYMANAGER->isOnceKeyDown(VK_SPACE)) return new sitOn;
	else if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) return new jump;
	
	if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isOnceKeyDown('J')) return new upSlash;
	else if (KEYMANAGER->isOnceKeyDown('J')) return new slash;
	if (KEYMANAGER->isOnceKeyDown('K')) return new dash;
	if (KEYMANAGER->isOnceKeyDown('I')) return new playerBullet;
	if (player->getHit()) return new strun;

	return nullptr;
}

void idle::update(player* player)
{
	_currentFrameY = player->getWay();

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

void idle::enter(player * player)
{
	_stateName = "idle";
	_imgName = IMAGEMANAGER->findImage("idle");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	//player->setPlayerY(player->getPlayerY() - 126);
	return;
}

void idle::exit(player * player)
{
}

void idle::effecRender(player * player, float x, float y)
{
}

void idle::getCurrentState(player * player)
{
}
