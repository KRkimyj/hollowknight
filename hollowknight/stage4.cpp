#include "stdafx.h"
#include "stage4.h"

HRESULT stage4::init()
{
	IMAGEMANAGER->addImage("stageBoss", "stageImage/stage3 boss.bmp", 1920, 1080, true, RGB(255, 0, 255), false);

	_ground = RectMake(0, 925, 1920, 50);

	return S_OK;
}

void stage4::release()
{
}

void stage4::update()
{
}

void stage4::render()
{
	IMAGEMANAGER->findImage("stageBoss")->render(getMemDC());

	if (KEYMANAGER->isStayKeyDown(VK_F1))
	{
		Rectangle(getMemDC(), _ground);
	}
}
