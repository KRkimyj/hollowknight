#pragma once
#include "gameNode.h"
#include "fly.h"
#include "bullets.h"
#include "boss.h"

#include <vector>

//상호참조를 위한 클라스 전방선언
class player;
class stageManager;

class enemyManager : public gameNode
{
private:
	/*typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;*/

	typedef vector<fly*>				vFly;
	typedef vector<fly*>::iterator		viFly;


private:
	vFly _vFly;
	viFly _viFly;

	fly* _fly;
	boss* _boss;

	bullet* _bullet;

	float _start, _end;
	bool _vibe;

	//==전방선언 빈 포인터==

	player* _pl;
	stageManager* _stageM;

	//===========
	

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setstageManager(stageManager* stage) { _stageM = stage; }
	void setPlayer(player* player) { _pl = player; }

	void setFly();
	void flyMove();
	void removeFly();
	void flyBulletFire();
	void bossBulletire();

	void playerBossCollision();


	player* getPlayer() { return _pl; }
	vector<fly*> getVMinion() { return _vFly; }
	vector<fly*>::iterator getVIMinion() { return _viFly; }
};

