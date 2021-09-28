#include "stdafx.h"
#include "sitOff.h"

#include "player.h"
#include "idle.h"

state * sitOff::inputHandle(player * player)
{
	if (_end) return new idle;
	return nullptr;
}

void sitOff::update(player * player)
{
	_count++;
	if (_count % 4 == 0)
	{
		if (_currentFrameX == 0) _currentFrameX = _imgName->getMaxFrameX();

		_imgName->setFrameX(_currentFrameX);
		_imgName->setFrameY(_currentFrameY);
		_currentFrameX--;

		if (_currentFrameX == 0) _end = true;

		_count = 0;
	}

	return;
}

void sitOff::enter(player * player)
{
	_stateName = "sit off";
	_imgName = IMAGEMANAGER->findImage("sit on");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;
	_end = false;

	return;
}

void sitOff::exit(player * player)
{
}

void sitOff::effecRender(player * player, float x, float y)
{
}

void sitOff::getCurrentState(player * player)
{
}
