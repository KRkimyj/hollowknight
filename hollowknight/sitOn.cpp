#include "stdafx.h"
#include "sitOn.h"

#include "player.h"
#include "sit.h"
state * sitOn::inputHandle(player * player)
{
	if (_end) return new sit;

	return nullptr;
}

void sitOn::update(player * player)
{
	_count++;
	if (_count % 4 == 0)
	{

		if (_currentFrameX >= _imgName->getMaxFrameX()) _end = true;
		_imgName->setFrameX(_currentFrameX);
		_imgName->setFrameY(_currentFrameY);
		_currentFrameX++;

		_count = 0;
	}

	return;
}

void sitOn::enter(player * player)
{
	_stateName = "sit on";
	_imgName = IMAGEMANAGER->findImage("sit on");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;
	_end = false;
}

void sitOn::exit(player * player)
{
}

void sitOn::effecRender(player * player, float x, float y)
{
}

void sitOn::getCurrentState(player * player)
{
}
