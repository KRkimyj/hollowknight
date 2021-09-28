#include "stdafx.h"
#include "doubleJump.h"
#include "stdafx.h"

#include "player.h"
#include "fall.h"
#include "dash.h"
#include "upSlash.h"
#include "downSlash.h"
#include "slide.h"
#include "strun.h"

state * doubleJump::inputHandle(player * player)
{
	if (_jumpPower <= 0)//_currentFrameX >= _imgName->getMaxFrameX())
	{
		return new fall;
	}
	if (KEYMANAGER->isOnceKeyDown('K')) return new dash;
	if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isOnceKeyDown('J')) return new upSlash;
	else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isOnceKeyDown('J')) return new downSlash;
	if (player->getCollisionLR() && KEYMANAGER->isOnceKeyDown('J')) return new slide;

	return nullptr;
}

void doubleJump::update(player * player)
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

		if (_effectFrameX <= _effectimgName->getMaxFrameX())
		{
			_effectimgName->setFrameX(_effectFrameX);
			_effectimgName->setFrameY(0);
			_effectFrameX++;

			_count = 0;
		}
	}

	player->setPlayerY(player->getPlayerY() - _jumpPower);
	_jumpPower -= _gravity;


	return;
}

void doubleJump::enter(player * player)
{
	_stateName = "double jump";
	_imgName = IMAGEMANAGER->findImage("double jump");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;

	_effectimgName = IMAGEMANAGER->findImage("double jump effect");
	_effectCount = 0;
	_effectFrameX, _effectFrameY = 0;

	_jumpPower = 15.0f;
	_gravity = 0.4f;
	
	return;
}

void doubleJump::exit(player * player)
{
}

void doubleJump::effecRender(player * player, float x, float y)
{
}

void doubleJump::getCurrentState(player * player)
{
}