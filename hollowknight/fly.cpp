#include "stdafx.h"
#include "fly.h"
#include "flyIdle.h"

HRESULT fly::init()
{
	return S_OK;
}

HRESULT fly::init(const char * imageName, POINT position)
{
	imageInit();

	_state = FLY_IDLE;

	_position.x = position.x;
	_position.y = position.y;

	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;

	_rndFireCount = RND->getFromIntTo(1, 800);

	//_imageName = IMAGEMANAGER->findImage(imageName);

	_rc = RectMake(_position.x, _position.y,
		_vFlyImg[_state]->getFrameWidth(), _vFlyImg[_state]->getFrameHeight());

	_moveRc = RectMakeCenter(_position.x, _position.y,
		_vFlyImg[_state]->getFrameWidth() * 2, _vFlyImg[_state]->getFrameHeight() * 2);

	
	_isTurn = false;
	_end = false;
	_isFollow = false;

	return S_OK;
}

void fly::release()
{
	/*SAFE_RELEASE(_viBullet->bulletImage);
	SAFE_DELETE(_viBullet->bulletImage);
	_viBullet = _vBullet.erase(_viBullet);*/
}

void fly::update()
{
	stateChange();
	if (_state == FLY_IDLE) draw();
	else if (_state == FLY_TURN || _state == FLY_BULLET_READY || _state == FLY_BULLET_FIRE) turnDraw();


	_rc = RectMake(_position.x, _position.y,
		_vFlyImg[_state]->getFrameWidth(), _vFlyImg[_state]->getFrameHeight());

	_moveRc = RectMakeCenter(_position.x + _vFlyImg[_state]->getFrameWidth() /2, _position.y + _vFlyImg[_state]->getFrameHeight() /2,
		_vFlyImg[_state]->getFrameWidth() * 2, _vFlyImg[_state]->getFrameHeight() * 2);
}

void fly::render()
{
	//=========== 편의를 위한 렉트 렌더
	if (KEYMANAGER->isStayKeyDown(VK_F1))
	{
		Rectangle(getMemDC(), _moveRc);
		Rectangle(getMemDC(), _rc);
	}
	//===========

	_vFlyImg[_state]->frameRender(getMemDC(), _position.x, _position.y, _currentFrameX, _currentFrameY);

	//=========편의를 위한 상태 기타등등 텍스트
	/*char str[128];
	sprintf_s(str, "state : %d", _state);
	TextOut(getMemDC(), _position.x, _position.y - 100, str, strlen(str));
	sprintf_s(str, "currentFrameX : %d", _vFlyImg[_state]->getFrameX());
	TextOut(getMemDC(), _position.x, _position.y - 80, str, strlen(str));
	sprintf_s(str, "currentFrameY : %d", _vFlyImg[_state]->getFrameY());
	TextOut(getMemDC(), _position.x, _position.y - 60, str, strlen(str));
	sprintf_s(str, "_end : %d", _end);
	TextOut(getMemDC(), _position.x, _position.y - 40, str, strlen(str));*/
	//=====================
}

void fly::move()
{
	if (_isFollow)
	{
	}
}

void fly::draw()
{
	_count++;

	if (_isTurn) _currentFrameY = 1;
	else _currentFrameY = 0;

	if (_count % 7 == 0)
	{
		if (_currentFrameY == 0)
		{
			if (_currentFrameX >= _vFlyImg[_state]->getMaxFrameX()) _currentFrameX = 0;

			_vFlyImg[_state]->setFrameX(_currentFrameX);
			_vFlyImg[_state]->setFrameY(_currentFrameY);
			_currentFrameX++;

			_count = 0;
		}
		else if (_currentFrameY == 1)
		{
			if (_currentFrameX == 0) _currentFrameX = _vFlyImg[_state]->getMaxFrameX();

			_vFlyImg[_state]->setFrameX(_currentFrameX);
			_vFlyImg[_state]->setFrameY(_currentFrameY);
			_currentFrameX--;

			_count = 0;
		}
	}
}

void fly::imageInit()
{
	for (int i = 0; i < FLY_STATE_END; i++)
		_vFlyImg.push_back(new image);

	_vFlyImg[FLY_IDLE]->init("enemyImage/fly idle.bmp", 572, 270, 4, 2, true, RGB(255, 0, 255), false);
	_vFlyImg[FLY_TURN]->init("enemyImage/fly turn.bmp", 314, 256, 2, 2, true, RGB(255, 0, 255), false);
	_vFlyImg[FLY_BULLET_READY]->init("enemyImage/fly bullet ready.bmp", 696, 278, 4, 2, true, RGB(255, 0, 255), false);
	_vFlyImg[FLY_BULLET_FIRE]->init("enemyImage/fly bullet fire.bmp", 340, 274, 2, 2, true, RGB(255, 0, 255), false);
	_vFlyImg[FLY_DEATH]->init("enemyImage/fly death.bmp", 121, 200, 2, 2, true, RGB(255, 0, 255), false);

}

void fly::stateChange()
{
	if (!_isFollow)
	{
		if (_state == FLY_IDLE && RND->getFromIntTo(0, 100) >= 99)
		{
			if (_currentFrameY == 0) _currentFrameX = 0;
			if (_currentFrameY == 1) _currentFrameX = 1;
			_state = FLY_TURN;
		}
	}
	if (_isFollow)
	{
		if (_state == FLY_IDLE && bulletCountFire())
		{
			if (_currentFrameY == 0) _currentFrameX = 0;
			if (_currentFrameY == 1) _currentFrameX = 3;
			_state = FLY_BULLET_READY;
		}
	}
	
}

void fly::turnDraw()
{
	_count++;

	if (_count % 7 == 0)
	{
		if (_currentFrameY == 0)
		{
			if (_state == FLY_TURN && _currentFrameX >= _vFlyImg[_state]->getMaxFrameX())
			{
				_isTurn = true;
				_state = FLY_IDLE;
			}
			else if (_state == FLY_BULLET_READY && _currentFrameX >= _vFlyImg[_state]->getMaxFrameX())
			{
				_state = FLY_BULLET_FIRE;
				_currentFrameX = 0;
			}
			else if (_state == FLY_BULLET_FIRE && _currentFrameX >= _vFlyImg[_state]->getMaxFrameX()) _state = FLY_IDLE;
			_vFlyImg[_state]->setFrameX(_currentFrameX);
			_vFlyImg[_state]->setFrameY(_currentFrameY);
			_currentFrameX++;

			_count = 0;
		}
		else if (_currentFrameY == 1)
		{
			if (_state == FLY_TURN && _currentFrameX == 0)
			{
				_isTurn = false;
				_state = FLY_IDLE;
				_currentFrameX++;
			}
			else if (_state == FLY_BULLET_READY && _currentFrameX <= 0)
			{
				_state = FLY_BULLET_FIRE;
				_currentFrameX = 1;
			}
			if (_state == FLY_BULLET_FIRE && _currentFrameX <= 0)
			{
				_state = FLY_IDLE;
				_currentFrameX = 3;
			}
			
			_vFlyImg[_state]->setFrameX(_currentFrameX);
			_vFlyImg[_state]->setFrameY(_currentFrameY);
			_currentFrameX--;

			_count = 0;
		}
	}
}

bool fly::bulletCountFire()
{
		_fireCount++;

		if (_fireCount % _rndFireCount == 0)
		{

			_rndFireCount = RND->getFromIntTo(1, 800);
			_fireCount = 0;

			return true;
		}

		return false;
}