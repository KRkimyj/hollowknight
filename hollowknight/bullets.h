#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;		//�Ѿ� �̹��� 
	RECT rc;				//�Ѿ� ��Ʈ
	float x, y;				//�Ѿ� ��ǥ(�ǽð�)
	float angle;			//�Ѿ� ����
	float radius;			//�Ѿ� ������
	float speed;			//�Ѿ� ���ǵ�
	float fireX, fireY;		//�Ѿ� �߻�� ó�� ��ǥ(�߻�� ��ǥ)
	bool isFire;			//�߻�?
	int count;				//�Ѿ� ������ī��Ʈ��
};

class bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;
public:
	bullet() {};
	~bullet() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);

	void move();

	//�Ѿ��� �����޶�� �����ϴ� �Լ�
	void removeBullet(int arrNum);

	
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};