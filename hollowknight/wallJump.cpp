#include "stdafx.h"
#include "wallJump.h"

#include "player.h"
#include "fall.h"
#include "upSlash.h"
#include "downSlash.h"
#include "strun.h"

state * wallJump::inputHandle(player * player)
{
	if (_jumpPower <= 0)return new fall;
	if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isOnceKeyDown('J')) return new upSlash;
	else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isOnceKeyDown('J')) return new downSlash;

	return nullptr;
}

void wallJump::update(player * player)
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_currentFrameY = 1;
		player->setPlayerX(player->getPlayerX() + 10);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_currentFrameY = 0;
		player->setPlayerX(player->getPlayerX() - 10);

	}
	_count++;
	if (_count % 7 == 0)
	{
		if (_currentFrameY == 1)
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

void wallJump::enter(player * player)
{
	_isWay = player->getWay();


	_stateName = "wall jump";
	_imgName = IMAGEMANAGER->findImage("wall jump");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;


	_jumpPower = 15.0f;
	_gravity = 0.4f;

	return;
}

void wallJump::exit(player * player)
{
}

void wallJump::effecRender(player * player, float x, float y)
{
}

void wallJump::getCurrentState(player * player)
{
}
