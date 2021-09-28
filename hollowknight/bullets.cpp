#include "stdafx.h"
#include "bullets.h"


HRESULT bullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	move();
}

void bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			Rectangle(getMemDC(), _viBullet->rc);
		}
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.radius = bullet.bulletImage->getWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());

	_vBullet.push_back(bullet);

}

void bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x -= cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void bullet::removeBullet(int arrNum)
{
	//벡터의 값을 지울떈  erase()
	_vBullet.erase(_vBullet.begin() + arrNum);
}