#include "stdafx.h"
#include "jump.h"

#include "player.h"
#include "idle.h"
#include "fall.h"
#include "dash.h"
#include "doubleJump.h"
#include "upSlash.h"
#include "downSlash.h"
#include "slide.h"
#include "playerBullet.h"
#include "strun.h"

state * jump::inputHandle(player * player)
{
	if (_jumpPower <= 0)//_currentFrameX >= _imgName->getMaxFrameX())
	{
		return new fall;
	}
	if (KEYMANAGER->isOnceKeyDown('K')) return new dash;
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) return new doubleJump;
	if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isOnceKeyDown('J')) return new upSlash;
	else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isOnceKeyDown('J')) return new downSlash;
	if (player->getCollisionLR() && KEYMANAGER->isOnceKeyDown('J')) return new slide;
	if (KEYMANAGER->isOnceKeyDown('I')) return new playerBullet;

	return nullptr;
}

void jump::update(player * player)
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
	if (_count % 7 == 0)
	{
		if (_currentFrameY == 0)
		{
			//if (_currentFrameX >= _imgName->getMaxFrameX()) _currentFrameX = 0;
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

	_jumpPower -= _gravity;

	player->setPlayerY(player->getPlayerY() - _jumpPower);

	return;
}

void jump::enter(player * player)
{
	_stateName = "jump";
	_imgName = IMAGEMANAGER->findImage("jump");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	
	_jumpPower = 15.0f;
	_gravity = 0.4f;

	return;
}

void jump::exit(player * player)
{
}

void jump::effecRender(player * player, float x, float y)
{
}

void jump::getCurrentState(player * player)
{
}
