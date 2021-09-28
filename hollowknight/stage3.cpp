#include "stdafx.h"
#include "stage3.h"

HRESULT stage3::init()
{
	IMAGEMANAGER->addImage("stage3", "stageImage/stage3 basic.bmp", 1920, 1080, true, RGB(255, 0, 255), false);

	_ground = RectMake(0, 925, 1920, 50);

	return S_OK;
}

void stage3::release()
{
}

void stage3::update()
{
}

void stage3::render()
{
	IMAGEMANAGER->findImage("stage3")->render(getMemDC());

	if (KEYMANAGER->isStayKeyDown(VK_F1))
	{
		Rectangle(getMemDC(), _ground);
	}
}
