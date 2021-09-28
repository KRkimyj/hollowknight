#pragma once
#include "gameNode.h"
#include "player.h"
#include "stageManager.h"
#include "enemyManager.h"
#include "effectClass.h"


class playGround : public gameNode
{
private:

	stageManager* _sm;
	player* _pl;
	enemyManager* _em;

	effectClass* _ef;

	RECT _cameraRect;
	POINT _cameraPoint;
	float _cameraWidth, _cameraHeight;

	float _start, _end;
	bool _vibe;

	image* _img;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imageInit();

	//void camera();
};

