#include "stdafx.h"
#include "stage2.h"

HRESULT stage2::init()
{
	IMAGEMANAGER->addImage("stage2", "stageImage/stage2 basic.bmp", 3840, 2160, true, RGB(255, 0, 255), false);
	stage2GroundSet();

	return S_OK;
}

void stage2::release()
{
}

void stage2::update()
{
}

void stage2::render()
{
	IMAGEMANAGER->findImage("stage2")->render(getMemDC());
	//IMAGEMANAGER->findImage("stage2 front")->render(getMemDC());

	if (KEYMANAGER->isStayKeyDown(VK_F1))
	{
		for (int i = 0; i < _vGround2.size(); i++)
		{
			Rectangle(getMemDC(), _vGround2[i].rc);
		}
	}
}

void stage2::stage2GroundSet()
{
	tagGround2 ground2;
	ground2.x = 1610;
	ground2.y = 0;

	ground2.rc = RectMake(ground2.x, ground2.y, 240, 1170);
	_vGround2.push_back(ground2);

	
	ground2.x = 2065;
	ground2.y = 0;

	ground2.rc = RectMake(ground2.x, ground2.y, 225, 1170);
	_vGround2.push_back(ground2);

	
	ground2.x = 0;
	ground2.y = 990;

	ground2.rc = RectMake(ground2.x, ground2.y, 1610, 50);
	_vGround2.push_back(ground2);

	ground2.x = 2290;
	ground2.y = 990;

	ground2.rc = RectMake(ground2.x, ground2.y, 1550, 50);
	_vGround2.push_back(ground2);

	ground2.x = 0;
	ground2.y = 1710;

	ground2.rc = RectMake(ground2.x, ground2.y, 420, 50);
	_vGround2.push_back(ground2);

	ground2.x = 420;
	ground2.y = 1630;

	ground2.rc = RectMake(ground2.x, ground2.y, 70, 80);
	_vGround2.push_back(ground2);

	ground2.x = 490;
	ground2.y = 1470;

	ground2.rc = RectMake(ground2.x, ground2.y, 760, 200);
	_vGround2.push_back(ground2);

	ground2.x = 1250;
	ground2.y = 1630;

	ground2.rc = RectMake(ground2.x, ground2.y, 80, 160);
	_vGround2.push_back(ground2);

	ground2.x = 1330;
	ground2.y = 1790;

	ground2.rc = RectMake(ground2.x, ground2.y, 470, 50);
	_vGround2.push_back(ground2);

	ground2.x = 1440;
	ground2.y = 1430;

	ground2.rc = RectMake(ground2.x, ground2.y, 940, 160);
	_vGround2.push_back(ground2);

	ground2.x = 2380;
	ground2.y = 1590;

	ground2.rc = RectMake(ground2.x, ground2.y, 450, 80);
	_vGround2.push_back(ground2);

	ground2.x = 2830;
	ground2.y = 1670;

	ground2.rc = RectMake(ground2.x, ground2.y, 730, 50);
	_vGround2.push_back(ground2);

	ground2.x = 1800;
	ground2.y = 1590;

	ground2.rc = RectMake(ground2.x, ground2.y, 50, 250);
	_vGround2.push_back(ground2);

	ground2.x = 3560;
	ground2.y = 1345;

	ground2.rc = RectMake(ground2.x, ground2.y, 400, 325);
	_vGround2.push_back(ground2);

	ground2.x = 55;
	ground2.y = 1430;

	ground2.rc = RectMake(ground2.x, ground2.y, 245, 85);
	_vGround2.push_back(ground2);

	ground2.x = 2565;
	ground2.y = 1430;

	ground2.rc = RectMake(ground2.x, ground2.y, 100, 15);
	_vGround2.push_back(ground2);

	ground2.x = 2890;
	ground2.y = 1395;

	ground2.rc = RectMake(ground2.x, ground2.y, 170, 30);
	_vGround2.push_back(ground2);

	ground2.x = 3255;
	ground2.y = 1375;

	ground2.rc = RectMake(ground2.x, ground2.y, 105, 20);
	_vGround2.push_back(ground2);
}
