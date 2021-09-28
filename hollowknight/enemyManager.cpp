#include "stdafx.h"
#include "enemyManager.h"

#include "player.h"
#include "stageManager.h"

HRESULT enemyManager::init()
{
	/*_bullet = new bullet;
	_bullet->init("bullet", 30, 700);
*/
	if (SCENEMANAGER->getCurrentScene("stage2"))
	{
		_bullet = new bullet;
		_bullet->init("fly bullet", 30, 1000);

		setFly();
	}
	else //if (SCENEMANAGER->getCurrentScene("stage3"))
	{
		_boss = new boss;
		_boss->init();
	}

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (int i = 0; i < _vFly.size(); i++) _vFly[i]->update();
	flyMove();
	flyBulletFire();
	if (_bullet != nullptr)	_bullet->update();

	if (_boss != nullptr)
	{
		_boss->update();
	}
	playerBossCollision();
	bossBulletire();

	if (SCENEMANAGER->getCurrentScene("stage4"))
	{
		if (_boss->getBossState()->getCurrentStateName() == "boss shout")
		{
			CAMERAMANAGER->vibrateScreen(_pl->getPlayerX(), _pl->getPlayerY(), 50, 0.01);

		}
		else CAMERAMANAGER->updateScreen(_pl->getPlayerX(), _pl->getPlayerY(), 0.5, 0.5);
	}
	else CAMERAMANAGER->updateScreen(_pl->getPlayerX(), _pl->getPlayerY(), 0.5, 0.5);
	//=========================================
	
}

void enemyManager::render()
{
	if (SCENEMANAGER->getCurrentScene("stage2"))
	{
		for (int i = 0; i < _vFly.size(); i++) _vFly[i]->render();
		//
	}

	_bullet->render();
	if (_boss != nullptr)
	{
		//_bullet->render();
		_boss->render();
	}
}

void enemyManager::setFly()
{
	_fly = new fly;

	//1165 1200
	_fly->init("fly idle", PointMake(1165, 1200));

	_vFly.push_back(_fly);

	_fly = new fly;
	//2500 1145
	_fly->init("fly idle", PointMake(2555, 1145));

	_vFly.push_back(_fly);
	
	_fly = new fly;
	//3520 1115
	_fly->init("fly idle", PointMake(3520, 1115));

	_vFly.push_back(_fly);
}

void enemyManager::flyMove()
{
	RECT t;
	for (int i = 0; i < _vFly.size(); i++)
	{
		if (IntersectRect(&t, &_pl->getPlayerRect(), &_vFly[i]->getMoveRect())) _vFly[i]->setFollow(true);
		if (_vFly[i]->getFollow())
		{
			float angle = getAngle(_pl->getPlayerX(), _pl->getPlayerY(), _vFly[i]->getPoint().x, _vFly[i]->getPoint().y);

			float x = _vFly[i]->getFlyPoint().x;
			float y = _vFly[i]->getFlyPoint().y;
			float distance = getDistance(_pl->getPlayerX(), _pl->getPlayerY(), _vFly[i]->getPoint().x, _vFly[i]->getPoint().y);
			float speed;
			

			if (distance >= 400) _vFly[i]->setFlyPoint(x -= cosf(angle) * 7, y -= -sinf(angle) * 7);
			else if (distance >= 200) _vFly[i]->setFlyPoint(x -= cosf(angle) * 5, y -= -sinf(angle) * 5);
			//else _vFly[i]->setFlyPoint(x += cosf(angle) * 5, y += -sinf(angle) * 5);

			if (angle > PI / 2 && angle < PI * 3 / 2)
			{
				_vFly[i]->setCurrentFrameY(1);
			}
			else
			{
				_vFly[i]->setCurrentFrameY(0);
			}
		}
	}
}

void enemyManager::removeFly()
{
	_vFly.clear();
	_vFly.resize(0);
}

void enemyManager::flyBulletFire()
{
	for (int i = 0; i < _vFly.size(); i++)
	{
		if (_vFly[i]->getFrameCount() == 1 && _vFly[i]->getState() == 3 && ((_vFly[i]->getCurrentFrameY() == 0 && _vFly[i]->getCurrentFrameX() == 1) 
			|| (_vFly[i]->getCurrentFrameY() == 1 && _vFly[i]->getCurrentFrameX() == 0)) )
		{
			float angle = getAngle((_pl->getPlayerRect().right + _pl->getPlayerRect().left) / 2, _pl->getPlayerRect().bottom, 
				_vFly[i]->getPoint().x, _vFly[i]->getPoint().y);

			if (_vFly[i]->getCurrentFrameY() == 0) _bullet->fire(_vFly[i]->getFlyPoint().x, _vFly[i]->getFlyPoint().y + 70, angle, 7.0f);
			if (_vFly[i]->getCurrentFrameY() == 1) _bullet->fire(_vFly[i]->getRect().right, _vFly[i]->getFlyPoint().y + 70, angle, 7.0f);

		}
	}
}

void enemyManager::bossBulletire()
{
	if (SCENEMANAGER->getCurrentScene("stage4") && _boss->getBossState()->getCurrentStateName() == "boss balloon")
	{
		for (int i = 0; i < 50; i++)
		{
			float angle = 0.1 + i * 5;

			_bullet->fire(1920 / 2 + 200, 300, angle, 10.0f);
		}
	}
}

void enemyManager::playerBossCollision()
{
	RECT t;

	if (SCENEMANAGER->getCurrentScene("stage2"))
	{
		for (int i = 0; i < _vFly.size(); i++)
		{
			if (IntersectRect(&t, &_pl->getPlayerRect(), &_vFly[i]->getRect()))
			{
				_pl->setHit(true);
			}
			else _pl->setHit(false);
		}
		for (int i = 0; i < _bullet->getVBullet().size(); i++)
		{
			if (IntersectRect(&t, &_pl->getPlayerRect(), &_bullet->getVBullet()[i].rc) && _pl->getState()->getCurrentStateName() != "dash")
			{
				_pl->setHit(true);
				_bullet->removeBullet(i);
			}
			//else _pl->setHit(false);
		}
	}
	else if (SCENEMANAGER->getCurrentScene("stage4"))
	{
		if (_pl->getState()->getCurrentStateName() == "slash" || _pl->getState()->getCurrentStateName() == "up slash" || _pl->getState()->getCurrentStateName() == "down slash"
			|| _pl->getState()->getCurrentStateName() == "player bullet")
		{
			if (IntersectRect(&t, &_pl->getPlayerEffectRect(), &_boss->getBossRect()) && !_pl->getAttack())
			{
				///*if (!_pl->_attak)*/ _boss->setHit();
				_pl->attack(true);
				_boss->isCollision(true);
				////else _boss->setHit(false);
			}
			//else _pl->_attak = false;
		}
		else _pl->attack(false);


		if (IntersectRect(&t, &_pl->getPlayerRect(), &_boss->getBossRect()) && !_pl->getHit())
		{
			_pl->setHit(true);
		}
		else _pl->setHit(false);
		for (int i = 0; i < _bullet->getVBullet().size(); i++)
		{
			if (IntersectRect(&t, &_pl->getPlayerRect(), &_bullet->getVBullet()[i].rc) && _pl->getState()->getCurrentStateName() != "dash")
			{
				_pl->setHit(true);
				_bullet->removeBullet(i);
			}
			//else _pl->setHit(false);
		}
	}
	

}
