#include "stdafx.h"
#include "boss.h"

#include "bossIdle.h"

HRESULT boss::init()
{
	bossImageInit();

	_bossState = new bossIdle;		//처음상태는 idle입니다
	_bossState->enter(this);		

	_isCollisionPlayer = false;
	_isHit = false;
	_hitNum = 0;
	_pattern = 0;
	_patternOn = false;
	_rnd = 0;
	_way = 0;

	_position.x = 1200;
	_position.y = 925 - 398;
	_rc = RectMake(_position.x, _position.y, _bossState->getFrameWidth(), _bossState->getFrameHeight());

	return S_OK;
}

//HRESULT boss::init()
//{
//	return S_OK;
//}

void boss::release()
{
}

void boss::update()
{
	inputHandle();
	_bossState->update(this);

	if (_isHit)
	{
		_hitNum++;
		_isHit = false;
	}
	
	patternRnd();


	if (_patternOn)
	{
		_pattern = RND->getFromIntTo(1, 4);
		_patternOn = false;
	}
	
	
	bossUpdate();
	bossEffectUpdate();

	_rc = RectMake(_position.x, _position.y, _bossState->getFrameWidth(), _bossState->getFrameHeight());
}

void boss::render()
{
	//=========편의를 위한 렉트 렌더
	if (KEYMANAGER->isStayKeyDown(VK_F1))
	{
		Rectangle(getMemDC(), _rc);
		Rectangle(getMemDC(), _effectRc);
		Rectangle(getMemDC(), _effectRc2);
		Rectangle(getMemDC(), _effectRc3);
		Rectangle(getMemDC(), _effectRc4);
	}
	//================================

	/*char str[128];
	sprintf_s(str, "way : %d", _way);
	TextOut(getMemDC(), _position.x, _position.y - 20, str, strlen(str));
	sprintf_s(str, "currentFrameX : %d", _bossState->getFrameX());
	TextOut(getMemDC(), _position.x, _position.y - 40, str, strlen(str));
	sprintf_s(str, "currentFrameY : %d", _bossState->getFrameY());
	TextOut(getMemDC(), _position.x, _position.y - 60, str, strlen(str));
	sprintf_s(str, "isHit : %d", _isHit);
	TextOut(getMemDC(), _position.x, _position.y - 80, str, strlen(str));
	sprintf_s(str, "hitNum : %d", _hitNum);
	TextOut(getMemDC(), _position.x, _position.y - 100, str, strlen(str));
	sprintf_s(str, "_patterOn : %d", _patternOn);
	TextOut(getMemDC(), _position.x, _position.y - 120, str, strlen(str));
	sprintf_s(str, "_rndPattern : %d", _pattern);
	TextOut(getMemDC(), _position.x, _position.y - 140, str, strlen(str));*/

	if (_hitNum < 15)
	{
		bossRender();
		bossEffectRender();
	}

}

//=====================================보스 상태=====
void boss::inputHandle()	//상태 호출
{
	bossStateBase* newState = _bossState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_bossState);
		_bossState = newState;
		_bossState->enter(this);
	}
}
//==================================================

void boss::patternRnd()
{
	if (_bossState->getCurrentStateName() == "boss teleportation out" && _rnd == 0)
	{
		_patternOn = true;
		_rnd = 1;
	}
	else _rnd = 0;
}

void boss::bossUpdate()
{
	if (_bossState->getCurrentStateName() == "boss greeting")
	{
		_position.x  = 1200 - 40;
		_position.y  = 925 - 398 - 5;
	}
	else if (_bossState->getCurrentStateName() == "boss shout")
	{
		_position.x = 1200 - 100;
		_position.y = 925 - 398 + 50;
	}
	else if (_bossState->getCurrentStateName() == "boss spike ready"
		|| _bossState->getCurrentStateName() == "boss spike up" || _bossState->getCurrentStateName() == "boss spike"
		|| _bossState->getCurrentStateName() == "boss spike down")
	{
		_position.x = 1920 / 2 - 100;
		_position.y = 925 - 398;
	}
}

void boss::bossRender()
{
	_bossState->getCurrentStateImg()->frameRender(getMemDC(), _position.x, _position.y, _bossState->getFrameX(), _bossState->getFrameY());
}


void boss::bossImageInit()
{
	IMAGEMANAGER->addFrameImage("boss idle", "bossImage/boss idle.bmp", 2316, 398, 12, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss greeting", "bossImage/boss greeting.bmp", 1701, 405, 7, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss shout", "bossImage/boss shout.bmp", 1492, 353, 4, 1, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addFrameImage("boss teleportation in", "bossImage/boss teleportation in.bmp", 1155, 413, 5, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss teleportation out", "bossImage/boss teleportation out.bmp", 1488, 397, 6, 1, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addFrameImage("boss spike", "bossImage/boss spike.bmp", 3400, 404, 10, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss balloon ready", "bossImage/boss balloon ready.bmp", 243, 299, 1, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss balloon", "bossImage/boss balloon.bmp", 1572, 438, 4, 1, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addFrameImage("boss attack ready", "bossImage/boss attack ready.bmp", 1100, 744, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss attack", "bossImage/boss attack.bmp", 2472, 764, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss attack end", "bossImage/boss attack end.bmp", 470, 744, 2, 2, true, RGB(255, 0, 255), false);
	
	IMAGEMANAGER->addFrameImage("boss uppercut ready", "bossImage/boss uppercut ready.bmp", 1224, 628, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss uppercut", "bossImage/boss uppercut.bmp", 652, 1250, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss uppercut end", "bossImage/boss uppercut end.bmp", 382, 898, 2, 2, true, RGB(255, 0, 255), false);
}

void boss::bossEffectUpdate()
{
	if (_bossState->getCurrentStateName() == "boss teleportation out")
	{
		_effectX = _position.x + 50;
		_effectY = _position.y - 100;
		_effectImg = _bossState->getCurrentStateEffect();
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
	}
	else if (_bossState->getCurrentStateName() == "boss spike ready")
	{
		_effectX = 320;
		_effectY = 925 - 140;
		_effectImg = _bossState->getCurrentStateEffect();
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
	}
	else if (_bossState->getCurrentStateName() == "boss spike up")
	{
		_effectX = 320;
		_effectY = 925 - 532;
		_effectImg = _bossState->getCurrentStateEffect();
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
	}
	else if (_bossState->getCurrentStateName() == "boss spike")
	{
		_effectX = 320;
		_effectY = 925 - 803;
		_effectImg = _bossState->getCurrentStateEffect();
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
	}
	else if (_bossState->getCurrentStateName() == "boss spike down")
	{
		_effectX = 320;
		_effectY = 925 - 621;
		_effectImg = _bossState->getCurrentStateEffect();
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
	}

	if (_bossState->getCurrentStateName() == "boss spike up" || _bossState->getCurrentStateName() == "boss spike"
		|| _bossState->getCurrentStateName() == "boss spike down")
	{
		_effectRc = RectMake(_effectX, _effectY, _effectWidth, _effectHeight);
		_effectRc2 = RectMake(_effectX + 300, _effectY, _effectWidth, _effectHeight);
		_effectRc3 = RectMake(_effectX + 1000, _effectY, _effectWidth, _effectHeight);
		_effectRc4 = RectMake(_effectX + 1300, _effectY, _effectWidth, _effectHeight);
	}
}

void boss::bossEffectRender()
{
	if (_bossState->getCurrentStateName() == "boss teleportation out")
	{
		_effectImg->alphaFrameRender(getMemDC(), _effectX, _effectY, _bossState->getEffectFrameX(), _bossState->getEffectFrameY(), 255);
	}
	else if (_bossState->getCurrentStateName() == "boss spike ready" && _bossState->getFrameX() >= 7)
	{
		_effectImg->frameRender(getMemDC(), _effectX, _effectY, _bossState->getEffectFrameX(), _bossState->getEffectFrameY());
	}
	else if (_bossState->getCurrentStateName() == "boss spike up" || _bossState->getCurrentStateName() == "boss spike"
		|| _bossState->getCurrentStateName() == "boss spike down")
	{
		_effectImg->frameRender(getMemDC(), _effectX, _effectY, _bossState->getEffectFrameX(), _bossState->getEffectFrameY());
		_effectImg->frameRender(getMemDC(), _effectRc2.left, _effectRc2.top, _bossState->getEffectFrameX(), _bossState->getEffectFrameY());
		_effectImg->frameRender(getMemDC(), _effectRc3.left, _effectRc3.top, _bossState->getEffectFrameX(), _bossState->getEffectFrameY());
		_effectImg->frameRender(getMemDC(), _effectRc4.left, _effectRc4.top, _bossState->getEffectFrameX(), _bossState->getEffectFrameY());
	}
}

void boss::playerCollision()
{
	/*_isHit = true;

	if (_isHit)
	{*/
		_hitNum++;
		/*_isHit = false;
	}*/
}

void boss::setHit()
{
	_isHit = true;
	if (_isHit)
	{
		_hitNum++;
		_isHit = false;
	}
}
