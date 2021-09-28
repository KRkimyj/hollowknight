#pragma once
#include "gameNode.h"
#include "flyState.h"
#include <vector>

enum FLYSTATE
{
	FLY_IDLE,
	FLY_TURN,
	FLY_BULLET_READY,
	FLY_BULLET_FIRE,
	FLY_DEATH,
	FLY_STATE_END
};
class fly : public gameNode
{
protected:

	vector<image*>		_vFlyImg;

	image* _imageName;		//���ʹ� �̹���
	RECT _rc;				//��Ʈ�ڽ�
	RECT _moveRc;			//�̵����� �� ���� ���� ��Ʈ
	POINT _position;

	float _setAngle;
	float _speed;

	bool _isTurn;		// ������ �� ������
	int _state;			// ������Ʈ ����
	bool _end;
	bool _isFollow;

	int _currentFrameX;
	int _currentFrameY;

	int _count;				//�����ӷ����� ��
	int _fireCount;			//�߻� ī��Ʈ ��
	int _rndFireCount;		//���� �߻� ī��Ʈ ��

public:
	fly() {};
	~fly() {};

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void move();
	void draw();
	void imageInit();
	void stateChange();
	void turnDraw();

	bool bulletCountFire();

	inline POINT getFlyPoint() { return _position; }
	inline void setFlyPoint(float x, float y) { _position.x = x; _position.y = y; }
	inline RECT getRect() { return _rc; }
	inline RECT getMoveRect() { return _moveRc; }
	inline bool getFollow() { return _isFollow; }
	inline void setFollow(bool follow) { _isFollow = follow; }
	inline POINT getPoint() { return PointMake((_rc.left + _rc.right) / 2, (_rc.bottom + _rc.top) / 2); }
	inline void setState(int state) { _state = state; }
	inline int getState() { return _state; }
	inline void setCurrentFrameX(int frameX) { _currentFrameX = frameX; }
	inline int getCurrentFrameX() { return _currentFrameX; }
	inline void setCurrentFrameY(int frameY) { _currentFrameY = frameY; }
	inline int getCurrentFrameY() { return _currentFrameY; }
	inline int getFrameCount() { return _count; }
};

