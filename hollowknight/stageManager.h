#pragma once
#include "gameNode.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"

#include <vector>

class player;
class enemyManager;

class stageManager : public gameNode
{
	player* _pl;
	enemyManager* _em;

	stage1* _stage1;
	stage2* _stage2;
	stage3* _stage3;
	stage4* _stage4;

	RECT _collisionRect;

	float _start, _end;
	bool _stop, _timer;
	int alpha;

	int _alpha;
	bool _pade;


public :
	stageManager() {};
	~stageManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	bool collisionPlayer();
	bool collisionLRPlayer();
	void newCollision(RECT stageGround);
	void directionImageInit();
	void changStage4();

	void setPlayer(player* player) { _pl = player; }
	void setEnemyManager(enemyManager* enemyManager) { _em = enemyManager; }
	bool getStop() { return _timer; }

	RECT collisionRect() { return _collisionRect; }
	stage1* getStage1() { return _stage1; }
};

