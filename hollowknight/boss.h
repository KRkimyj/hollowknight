#pragma once
#include "gameNode.h"
#include "bossStateBase.h"
#include <vector>
struct tagsumon
{
	image* _sImg;
	RECT _sRc;
	POINT _sPoint;
};
class boss : public gameNode
{


protected:


	//vector<image*>		_vFlyImg;
	bossStateBase* _bossState;

	//image* _imageName;		//에너미 이미지
	RECT _rc;				//히트박스
	POINT _position;

	image* _effectImg;
	RECT _effectRc;
	int _count;
	int _currentFrameX, _currentFrameY;
	float _effectX, _effectY;
	int _effectWidth, _effectHeight;
	bool _attack;

	RECT _effectRc2, _effectRc3, _effectRc4, _effectRc5;

	int _pattern;

	bool _isCollisionPlayer;
	bool _isHit;
	int _hitNum;
	bool _patternOn;
	int _rnd;
	int _way;

	RECT _palyerRect;

public:
	boss() {};
	~boss() {};

	vector<tagsumon> _vS;

	virtual HRESULT init();
	//virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void inputHandle();
	void patternRnd();

	void bossUpdate();
	void bossRender();
	void bossImageInit();
	void bossEffectUpdate();
	void bossEffectRender();

	void playerCollision();

	void setHit();
	void setHitNum(int hitNum) { _hitNum = hitNum; }
	void isCollision(bool isHit) { _isHit = isHit; }
	bool getHit() { return _isHit; }
	int hitNum() { return _hitNum; }
	int getPattern() { return _pattern; }

	void setBossPosition(float x, float y) { _position.x = x; _position.y = y; }
	POINT getBossPosition() { return _position; }
	RECT getBossRect() { return _rc; }
	int getWay() { return _way; }
	void setWay(int way) { _way = way; }
	bossStateBase* getBossState() { return _bossState; }
	vector<tagsumon> getVSumon() { return _vS; }
};

