#include "stdafx.h"
#include "flyIdle.h"

flyState * flyIdle::inputHandle(fly * fly)
{
	if (_isFire) //return new fireReady;
	return nullptr;
}

void flyIdle::update(fly * fly)
{
	/*if (!_isFire)
	{
		_fireCount++;

		if (_fireCount % _rndFireCount == 0)
		{
			_rndFireCount = RND->getFromIntTo(1, 800);
			_fireCount = 0;

			_isFire = true;
		}
		else _isFire = false;
		if (_fireCount % _rndFireCount == 1) _isTurn = true;
		else _isTurn = false;
	}*/


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

void flyIdle::enter(fly * fly)
{
	_fireCount, _rndFireCount = 0;
	_isFire = false;
	_isTurn = false;

	_stateName = "fly idle";
	_imgName = IMAGEMANAGER->findImage("fly idle");
	_currentFrameX, _currentFrameY = 0;
	_count = 0;
	
	return;
}

void flyIdle::exit(fly * fly)
{
}
