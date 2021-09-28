#include "stdafx.h"
#include "fall.h"

#include "player.h"
#include "idle.h"
#include "dash.h"
#include "upSlash.h"
#include "downSlash.h"
#include "doubleJump.h"
#include "slide.h"
#include "playerBullet.h"
#include "strun.h"

state * fall::inputHandle(player * player)
{
	if (player->getCollision()/* && player->getPlayerRect().bottom > player->getGroundRect().top*/)
	{
		return new idle();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		return new doubleJump;
	}
	if (KEYMANAGER->isOnceKeyDown('K')) return new dash;
	if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isOnceKeyDown('J')) return new upSlash;
	else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isOnceKeyDown('J')) return new downSlash;
	if (player->getCollisionLR() && KEYMANAGER->isOnceKeyDown('J')) return new slide;
	if (KEYMANAGER->isOnceKeyDown('I')) return new playerBullet;


	//if (KEYMANAGER->isOnceKeyDown('J')) return new slash;

	return nullptr;
}

void fall::update(player * player)
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

	_count++;
	if (_count % 7 == 0)
	{
		if (_currentFrameX >= _imgName->getMaxFrameX()) _currentFrameX = 0;
		_imgName->setFrameX(_currentFrameX);
		_imgName->setFrameY(_currentFrameY);
		_currentFrameX++;

		_count = 0;
	}

	_jumpPower -= _gravity;

	player->setPlayerY(player->getPlayerY() - _jumpPower);

	return;
}

void fall::enter(player * player)
{
	_stateName = "fall";
	_imgName = IMAGEMANAGER->findImage("fall");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	_jumpPower = 0.0f;
	_gravity = 0.4f;


	return;

}

void fall::exit(player * player)
{
}

void fall::effecRender(player * player, float x, float y)
{
}

void fall::getCurrentState(player * player)
{
}
