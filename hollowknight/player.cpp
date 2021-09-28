#include "stdafx.h"
#include "player.h"
#include "stageManager.h"
#include "enemyManager.h"
#include "fall.h"

HRESULT player::init()
{
	way = 0;
	_save = false;
	_attack = false;
	_isHit = false;

	IMAGEMANAGER->addImage("stage1 front", "stageImage/stage1 front.bmp", 3840, 2160, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("stage2 front", "stageImage/stage2 front.bmp", 3840, 2160, true, RGB(255, 0, 255), false);
	
	initImage();

	if (SCENEMANAGER->getCurrentScene("stage1"))
	{
		_x = 3840 / 2;
		_y = 2160 / 2;
	}
	if (SCENEMANAGER->getCurrentScene("stage2"))
	{
		_x = 2000;
		_y = 50;
	}
	if (SCENEMANAGER->getCurrentScene("stage3") || SCENEMANAGER->getCurrentScene("stage4"))
	{
		_x = 1920 / 2;
		_y = 1080 / 2;
	}
	
	_state = new fall;
	_state->enter(this);
	
	_effectImg = new image;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (KEYMANAGER->isStayKeyDown('D'))  way = 0;
	if (KEYMANAGER->isStayKeyDown('A')) way = 1;
	
	//if (KEYMANAGER->isStayKeyDown('W')) _y -= 10;
	//if (KEYMANAGER->isStayKeyDown('S'))  _y += 10;

	inputHandle();
	_state->update(this);

	effectUpdate();
	save();

	if (_attack)
	{
		_effectRc = RectMake(0, 0, 100, 100);
	}
	_rc = RectMake(_x, _y, 50, 127);
}

void player::render()
{
	//=========== 편의를 위한 렉트 렌더
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _rc);
		Rectangle(getMemDC(), _effectRc);
	}
	//===========

	playerRender();
	effectRender();
	

	/*char str[128];
	sprintf_s(str, "맞? : %d", _isHit);
	TextOut(getMemDC(), _x, _y - 20, str, strlen(str));*/
	//cout << _state->getCurrentStateName() << endl;

	if (KEYMANAGER->isToggleKey('R'))
	{
		frontImageRender();
	}
}

//======================================================

void player::inputHandle()	//상태 호출
{
	state* newState = _state->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->enter(this);
	}
}


// =============================호출용===============================

bool player::getCollision() //스테이지 매니저에서 처리하는 렉트충돌 유무 호출
{
	return _stageM->collisionPlayer();
}

bool player::getCollisionLR()
{
	return _stageM->collisionLRPlayer();
}

int player::getWay()
{
	return way;
}

void player::save()
{
	RECT t;
	RECT _bench = _stageM->getStage1()->getBench();
	if (IntersectRect(&t, &_rc, &_bench))
	{
		_save = true;
	}
	else _save = false;
}

RECT player::getGroundRect()
{
	return _stageM->collisionRect();
}

// =================================================================


void player::playerRender()	//상태에 따른 플레이어 이미지 렌더 위치 조정...
{
	if ((_state->getCurrentStateName() == "slash" || _state->getCurrentStateName() == "jump")&& way == 0)
	{
		_state->getCurrentStateImg()->frameRender(getMemDC(), _x -22, _y, _state->getFrameX(), _state->getFrameY());
	}
	else if (_state->getCurrentStateName() == "down slash" || (_state->getCurrentStateName() == "double jump" && way == 0))
	{
		_state->getCurrentStateImg()->frameRender(getMemDC(), _x - 50, _y, _state->getFrameX(), _state->getFrameY());
	}
	else if (_state->getCurrentStateName() == "fall" && way == 0)
	{
		_state->getCurrentStateImg()->frameRender(getMemDC(), _x - 30, _y, _state->getFrameX(), _state->getFrameY());
	}
	else if (_state->getCurrentStateName() == "idle" && way == 0)
	{
		_state->getCurrentStateImg()->frameRender(getMemDC(), _x - 5, _y, _state->getFrameX(), _state->getFrameY());
	}
	else if (_state->getCurrentStateName() == "wall slide" && way == 1)
	{
		_state->getCurrentStateImg()->frameRender(getMemDC(), _x - 15, _y, _state->getFrameX(), _state->getFrameY());
	}
	else if (_state->getCurrentStateName() == "dash" && way == 0)
	{
		_state->getCurrentStateImg()->frameRender(getMemDC(), _x - 110, _y, _state->getFrameX(), _state->getFrameY());
	}
	else if (_state->getCurrentStateName() == "sit")
	{
		_state->getCurrentStateImg()->frameRender(getMemDC(), _x, _y - 25, _state->getFrameX(), _state->getFrameY());
	}
	else if (_state->getCurrentStateName() == "sit on" || _state->getCurrentStateName() == "sit off")
	{
		_state->getCurrentStateImg()->frameRender(getMemDC(), _x, _y - 15, _state->getFrameX(), _state->getFrameY());
	}
	else if (_state->getCurrentStateName() == "sturn")
	{
		_state->getCurrentStateImg()->alphaFrameRender(getMemDC(), _x, _y, 200);
	}
	else _state->getCurrentStateImg()->frameRender(getMemDC(), _x, _y, _state->getFrameX(), _state->getFrameY());
}

void player::effectUpdate()
{
	if (_state->getCurrentStateName() == "slash")
	{
		//_attack = false;
		_effectImg = _state->getCurrentStateEffect();

		if (way == 0)
		{
			_effectX = _x + 50;
			_effectY = _y;
		}
		else
		{
			_effectX = _x - _effectImg->getFrameWidth();
			_effectY = _y;
		}
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
		
	}
	else if (_state->getCurrentStateName() == "up slash")
	{
		//_attack = false;
		_effectImg = _state->getCurrentStateEffect();
		_effectX = _x - 35;
		_effectY = _y - _effectImg->getFrameHeight() + 50;
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
	}
	else if (_state->getCurrentStateName() == "down slash")
	{
		//_attack = false;
		_effectImg = _state->getCurrentStateEffect();
		_effectX = _x - 35;
		_effectY = _y + (_rc.bottom - _rc.top) - 20;
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
	}
	else if (_state->getCurrentStateName() == "double jump")
	{
		//_attack = false;
		_effectImg = _state->getCurrentStateEffect();
		_effectX = _x - 50;
		_effectY = _y + (_rc.bottom - _rc.top) - 50;
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
	}
	else if (_state->getCurrentStateName() == "dash")
	{
		//_attack = false;
		_effectImg = _state->getCurrentStateEffect();

		if (way == 0)
		{
			_effectX = _rc.left - _effectImg->getFrameWidth();
			_effectY = _y;
		}
		else
		{
			_effectX = _rc.right;
			_effectY = _y;
		}
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
	}
	else if (_state->getCurrentStateName() == "player bullet")
	{
		//_attack = false;
		_effectImg = _state->getCurrentStateEffect();

		if (way == 0)
		{
			_effectX = _rc.right + 30;
			_effectY = _y;
		}
		else
		{
			_effectX = _rc.left - _effectImg->getFrameWidth() - 30;
			_effectY = _y;
		}
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
	}
	else if (_state->getCurrentStateName() == "sturn")
	{
		_effectImg = _state->getCurrentStateEffect();
		_effectX = _x - 50;
		_effectY = _y - 50;
		_effectWidth = _effectImg->getFrameWidth();
		_effectHeight = _effectImg->getFrameHeight();
	}
	_effectRc = RectMake(_effectX, _effectY, _effectWidth, _effectHeight);
	//else SAFE_DELETE(_effectImg);
}

void player::effectRender()
{
	if (_state->getCurrentStateName() == "slash" || _state->getCurrentStateName() == "up slash"
		|| _state->getCurrentStateName() == "player bullet")
	{
		_effectImg->alphaFrameRender(getMemDC(), _effectX, _effectY, _state->getEffectFrameX(), _state->getFrameY(), 255);
	}
	if (_state->getCurrentStateName() == "down slash")
	{
		_effectImg->alphaFrameRender(getMemDC(), _effectX, _effectY, _state->getEffectFrameX(), 1, 255);
	}
	else if (_state->getCurrentStateName() == "double jump" || _state->getCurrentStateName() == "dash")
	{
		_effectImg->alphaFrameRender(getMemDC(), _effectX, _effectY, _state->getEffectFrameX(), _state->getFrameY(), 200);
	}
	else if (_state->getCurrentStateName() == "sturn")
	{
		_effectImg->alphaFrameRender(getMemDC(), _effectX, _effectY, _state->getEffectFrameX(), _state->getFrameY(), 255);
	}
}

void player::frontImageRender()	//전경 렌더
{
	if (SCENEMANAGER->getCurrentScene("stage1"))
	{
		IMAGEMANAGER->findImage("stage1 front")->render(getMemDC());
	}
	else if (SCENEMANAGER->getCurrentScene("stage2"))
	{
		IMAGEMANAGER->findImage("stage2 front")->render(getMemDC());
	}
}

void player::initImage()	//캐릭터 이미지 초기화
{
	IMAGEMANAGER->addFrameImage("idle", "playerImage/idle.bmp", 360, 254, 6, 2, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addFrameImage("walk", "playerImage/walk.bmp", 420, 254, 7, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("jump", "playerImage/jump.bmp", 474, 258, 6, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("double jump", "playerImage/double jump.bmp", 928, 258, 8, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("dash", "playerImage/dash.bmp", 1204, 228, 7, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("fall", "playerImage/fall.bmp", 522, 258, 6, 2, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addFrameImage("wall slide", "playerImage/wall slide.bmp", 312, 264, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("wall jump", "playerImage/wall jump.bmp", 582, 246, 6, 2, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addFrameImage("slash", "playerImage/slash.bmp", 410, 254, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("sturn", "playerImage/sturn.bmp", 94, 248, true, RGB(255, 0, 255), true);	//피격 연출을 위해 알파블렌더 켜놓기
	IMAGEMANAGER->addFrameImage("up slash", "playerImage/up slash.bmp", 565, 131, 5, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("down slash", "playerImage/down slash.bmp", 615, 124, 5, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("player bullet", "playerImage/player bullet.bmp", 609, 254, 7, 2, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addFrameImage("sit on", "playerImage/sit on.bmp", 320, 127, 4, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("sit", "playerImage/sit.bmp", 380, 129, 5, 1, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addFrameImage("map open", "playerImage/map open.bmp", 207, 254, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("map walk", "playerImage/map walk.bmp", 564, 236, 8, 2, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addFrameImage("up focus", "playerImage/up focus.bmp", 294, 254, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("down focus", "playerImage/down focus.bmp", 338, 254, 5, 2, true, RGB(255, 0, 255), false);


}



