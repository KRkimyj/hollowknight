#include "stdafx.h"
#include "stage1.h"

HRESULT stage1::init()
{
	IMAGEMANAGER->addImage("stage1", "stageImage/stage1 basic.bmp", 3840, 2160, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addImage("bench", "stageImage/bench.bmp", 200, 98, true, RGB(255, 0, 255), false);
	
	stage1GroundSet();

	_bench = RectMake(1330, 1450, 200, 98);

	return S_OK;
}

void stage1::release()
{
	
}

void stage1::update()
{
}

void stage1::render()
{

	IMAGEMANAGER->findImage("stage1")->render(getMemDC());
	IMAGEMANAGER->findImage("bench")->render(getMemDC(), _bench.left, _bench.top);

	//IMAGEMANAGER->findImage("stage1 front")->render(getMemDC());

	if (KEYMANAGER->isStayKeyDown(VK_F1))
	{
		Rectangle(getMemDC(), _bench);

		for (int i = 0; i < _vGround.size(); i++)
		{
			Rectangle(getMemDC(), _vGround[i].rc);
		}
	}

}

void stage1::stage1GroundSet()
{
	tagGround ground;
	ground.x = 0;
	ground.y = 1540;

	ground.rc = RectMake(ground.x, ground.y, 2835, 50);
	_vGround.push_back(ground);

	
	ground.x = 2835;
	ground.y = 1590;

	ground.rc = RectMake(ground.x, ground.y, 175, 50);
	_vGround.push_back(ground);

	
	ground.x = 3010;
	ground.y = 1635;

	ground.rc = RectMake(ground.x, ground.y, 175, 50);
	_vGround.push_back(ground);


	ground.x = 3185;
	ground.y = 1675;

	ground.rc = RectMake(ground.x, ground.y, 300, 485);
	_vGround.push_back(ground);

	
	ground.x = 3675;
	ground.y = 1675;

	ground.rc = RectMake(ground.x, ground.y, 165, 485);
	_vGround.push_back(ground);

	//1735, 820
	ground.x = 3485;
	ground.y = 1635;

	ground.rc = RectMake(ground.x, ground.y, 185, 50);
	_vGround.push_back(ground);
}

