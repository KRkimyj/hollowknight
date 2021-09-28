#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);

	//===전방선언 삽입===
	_sm = new stageManager;
	_sm->init();

	_pl = new player;
	_pl->init();

	_em = new enemyManager;

	_sm->setPlayer(_pl);
	_sm->setEnemyManager(_em);
	_pl->setstageManager(_sm);
	_pl->setEnemyManager(_em);
	_em->setPlayer(_pl);
	_em->setstageManager(_sm);
	//==================

	imageInit();
	_ef->imageInit();

	_cameraRect = RectMakeCenter(_pl->getPlayerX(), _pl->getPlayerY(), WINSIZEX, WINSIZEY);
	_cameraPoint.x = _pl->getPlayerX();
	_cameraPoint.y = _pl->getPlayerY();
	_cameraWidth = WINSIZEX / 2;
	_cameraHeight = WINSIZEY / 2;

	_start = _end = 0;
	_vibe = false;

	//_img = IMAGEMANAGER->addImage("grim bullet", "enemyEffectImage/grim bullet.bmp", 64, 64, true, RGB(255, 0, 255), true);
	
	
	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	_sm->update();
	/*if (!_sm->getStop())*/ _pl->update();
	_em->update();

	//camera();
	
	//진동 한 거 연습했어
	//======================================
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=========================================

	//SCENEMANAGER->render();
	_sm->render();
	if (!SCENEMANAGER->getCurrentScene("stage1")) _em->render();
	_pl->render();
	/*
	char str[100];
	sprintf_s(str, "x : %d, y : %d, 현재 프레임: %d,  ", _pl->getPlayerRect().left, _pl->getPlayerRect().top, _pl->getState()->getFrameX());
	TextOut(getMemDC(), _pl->getPlayerX() - 100, _pl->getPlayerY() - 100, str, strlen(str));*/

	TIMEMANAGER->render(getMemDC());

	//_img->alphaRender(getMemDC(), 2000, 1000, 100);

	//==================================================
	//this->getBackBuffer()->render(getHDC(), 0, 0, _cameraRect.left, _cameraRect.top, WINSIZEX, WINSIZEY);
	CAMERAMANAGER->render(getHDC(), 0, 0, getMemDC());
}

void playGround::imageInit()
{
	IMAGEMANAGER->addImage("fly bullet", "enemyEffectImage/fly bullet.bmp", 50, 50, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("fly bullet remove", "enemyEffectImage/fly bullet remove.bmp", 528, 103, 6, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("fly bullet remove LR", "enemyEffectImage/fly bullet remove LR.bmp", 606, 174, 6, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("hit image", "stageImage/hit image.bmp", 3840, 2160, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("hit image2", "stageImage/hit image2.bmp", 1920, 1080, true, RGB(255, 0, 255), true);
}
