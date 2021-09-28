#pragma once
#include "gameNode.h"
#include "state.h"

class stageManager;
class enemyManager;

//struct tagplayer
//{
//	image* img;
//	RECT rc;
//	float x, y;
//	float speed;
//};
class player : public gameNode
{
	RECT _rc;
	float _x, _y;
	state* _state;

	image* _effectImg;
	RECT _effectRc;
	int _count;
	int _currentFrameX, _currentFrameY;
	float _effectX, _effectY;
	int _effectWidth, _effectHeight;
	bool _attack;

	bool _isHit;

	stageManager* _stageM;
	enemyManager* _em;

	int _life;

	int way;
	bool _save;

public:
	player() {};
	~player() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void inputHandle();

	void setstageManager(stageManager* stage) { _stageM = stage; }
	void setEnemyManager(enemyManager* enemyManager) { _em = enemyManager; }

	bool  getCollision();
	bool getCollisionLR();

	void playerRender();
	void effectUpdate();
	void effectRender();
	void frontImageRender();
	void initImage();
	int getWay();
	void save();
	void attack(bool isattack) { _attack = isattack; }
	bool getAttack() { return _attack; }
	RECT getGroundRect();

	void setPlayerX(float x) { _x = x; }
	void setPlayerY(float y) { _y = y; }
	float getPlayerX() { return _x; }
	float getPlayerY() { return _y; }
	void setHit(bool hit) { _isHit = hit; }
	bool getHit() { return _isHit; }

	RECT getPlayerRect() { return _rc; }
	state* getState() { return _state; }
	RECT getPlayerEffectRect() { return _effectRc; }
	bool getSave() { return _save; }

};

