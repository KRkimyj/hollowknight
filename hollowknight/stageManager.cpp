#include "stdafx.h"
#include "stageManager.h"
#include "player.h"
#include "enemyManager.h"

HRESULT stageManager::init()
{
	directionImageInit();

	_stage1 = new stage1;
	_stage1->init();
	_stage2 = new stage2;
	_stage2->init();
	_stage3 = new stage3;
	_stage3->init();
	_stage4 = new stage4;
	_stage4->init();

	SCENEMANAGER->addScene("stage1", new stage1);
	SCENEMANAGER->addScene("stage2", new stage2);
	SCENEMANAGER->addScene("stage3", new stage3);
	SCENEMANAGER->addScene("stage4", new stage4);
	SCENEMANAGER->changeScene("stage1"); //처음 스테이지는 1
	
	CAMERAMANAGER->setBackScreenSize(3840, 2160);

	_start = _end = 0;
	_stop = false;
	alpha = 0;

	return S_OK;
}

void stageManager::release()
{
}

void stageManager::update()
{
	//렉트 뿌리기 위해 잠시 쓰는 씬전환 
	if (KEYMANAGER->isStayKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("stage2");
	}
	if (KEYMANAGER->isStayKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("stage3");
	}
	if (KEYMANAGER->isStayKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene("stage4");
	}


	if (SCENEMANAGER->getCurrentScene("stage1"))
	{
		for (int i = 0; i < _stage1->getVGround().size(); i++)
		{
			if (i != 5) newCollision(_stage1->getVGround()[i].rc);
		}
		if (_pl->getPlayerY() >= 2160)
		{
			SCENEMANAGER->changeScene("stage2");
			_pl->init();
			_em->init();
		}
	}
	if (SCENEMANAGER->getCurrentScene("stage2"))
	{
		for (int i = 0; i < _stage2->getVGround().size(); i++)
		{
			newCollision(_stage2->getVGround()[i].rc);
		}
		if (_pl->getPlayerY() <= 0)
		{
			_em->removeFly();
			SCENEMANAGER->changeScene("stage1");
			_pl->init();
		}
		if(_pl->getPlayerX() >= 3840)
		{
			_em->removeFly();
			SCENEMANAGER->changeScene("stage3");
			_pl->init();
			_em->init();

			_start = TIMEMANAGER->getWorldTime();
			_timer = true;
		}
	}
	if (SCENEMANAGER->getCurrentScene("stage3"))
	{
		if (_timer)
		{
			_end = TIMEMANAGER->getWorldTime();
			//if (_end - _start > 3) //_stop = true;
			if (_end - _start > 2)
			{
				SCENEMANAGER->changeScene("stage4");
				_start = _end = 0; //스테이지 4 바뀌는 연출 해야한단다 못했구나 저런..
			}
		}
	}

	/*if (_stop) alpha += 5;
	if (alpha >= 255)
	{
		_stop = false;
		alpha = 0;
	}*/

	if (SCENEMANAGER->getCurrentScene("stage3") || SCENEMANAGER->getCurrentScene("stage4"))
	{	
		newCollision(_stage3->getRect());
	}


	if (SCENEMANAGER->getCurrentScene("stage3") || SCENEMANAGER->getCurrentScene("stage4"))
	{
		CAMERAMANAGER->setBackScreenSize(1920, 1080);
	}
	else
	{
		CAMERAMANAGER->setBackScreenSize(3840, 2160);
	}


	
}

void stageManager::render()
{
	SCENEMANAGER->render();

	if (SCENEMANAGER->getCurrentScene("stage1"))
	{
		_stage1->render();
	}
	else if (SCENEMANAGER->getCurrentScene("stage2"))
	{
		_stage2->render();
	}
	else if (SCENEMANAGER->getCurrentScene("stage3"))
	{
		_stage3->render();

		/*char str[128];
		sprintf_s(str, "_end : %d", _end);
		TextOut(getMemDC(), 1920 / 2, 1080 / 2, str, strlen(str));
		sprintf_s(str, "_start : %d", _start);
		TextOut(getMemDC(), 1920 / 2, 1080 / 2 + 20, str, strlen(str));*/
	}
	else
	{
		_stage4->render();
		//IMAGEMANAGER->findImage("red image")->alphaRender(getMemDC(), 0, 0, 200);
	}

}

bool stageManager::collisionPlayer()
{
	RECT t;
	
	if (SCENEMANAGER->getCurrentScene("stage1"))
	{
		for (int i = 0; i < _stage1->getVGround().size(); i++)
		{
			if (IntersectRect(&t, &_pl->getPlayerRect(), &_stage1->getVGround()[i].rc))
			{
				if (i == 5) return false;
				else if (t.right - t.left >= t.bottom - t.top)
				{
					if (_pl->getPlayerRect().top <= _stage1->getVGround()[i].rc.bottom)
					{
						return true;
					}
					else if (_pl->getPlayerRect().top >= _stage1->getVGround()[i].rc.top)
					{
						return false;
					}
				}
			}
		}
		return false;
	}
	else if (SCENEMANAGER->getCurrentScene("stage2"))
	{
		for (int i = 0; i < _stage2->getVGround().size(); i++)
		{
			if (IntersectRect(&t, &_pl->getPlayerRect(), &_stage2->getVGround()[i].rc))
			{
				if (t.right - t.left >= t.bottom - t.top)
				{
					if (_pl->getPlayerRect().top <= _stage2->getVGround()[i].rc.bottom)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			
		}
		return false;
	}
	else if (SCENEMANAGER->getCurrentScene("stage3"))
	{
		if (IntersectRect(&t, &_pl->getPlayerRect(), &_stage3->getRect()))
		{
			return true;
			/*_pl->setPlayerY(_stage3->getRect().top - 127);*/
		}
		else return false;
	}
	else
	{
		if (IntersectRect(&t, &_pl->getPlayerRect(), &_stage4->getRect()))
		{
			return true;
		}
		else return false;
	}
}


bool stageManager::collisionLRPlayer()
{
	RECT t;

	if (SCENEMANAGER->getCurrentScene("stage1"))
	{
		for (int i = 0; i < _stage1->getVGround().size(); i++)
		{
			if (IntersectRect(&t, &_pl->getPlayerRect(), &_stage1->getVGround()[i].rc))
			{
				float width = t.right - t.left;
				float height = t.bottom - t.top;

				if (width <= height) return true;
				else return false;
			}
		}
	}
	if (SCENEMANAGER->getCurrentScene("stage2"))
	{
		for (int i = 0; i < _stage2->getVGround().size(); i++)
		{
			if (IntersectRect(&t, &_pl->getPlayerRect(), &_stage2->getVGround()[i].rc))
			{
				float width = t.right - t.left;
				float height = t.bottom - t.top;

				if (width <= height) return true;
				else return false;
			}
		}
	}
}

void stageManager::newCollision(RECT stageGround)
{
	RECT temp;
	if (IntersectRect(&temp, &_pl->getPlayerRect(), &stageGround) && _pl->getState()->getCurrentStateName() != "idle") /*&& !_chk && _pm->getPlayer().state != JUMP*/
	{

		float width = (temp.right - temp.left);
		float height = (temp.bottom - temp.top);

		float playerX = _pl->getPlayerX();
		float playerY = _pl->getPlayerY();

		bool _pt;
		
		//수직 수평
		(width > height) ? _pt = false : _pt = true;

		//cout << "플레이어 y : " << _pm->getPlayer().y << "네모 탑: " << _nemo[2].rc.top << endl;

		if (_pt) // 수평
		{
			//왼쪽에 있나
			if (_pl->getPlayerRect().left < stageGround.left) _pl->setPlayerX(playerX -= width);//_pm->getPlayer().x -= width;
			//오른쪽에 있나
			if (_pl->getPlayerRect().right > stageGround.right) _pl->setPlayerX(playerX += width);//_pm->getPlayer().x += width;
		}
		else if (!_pt) //수직
		{
			//위에 있나
			if (_pl->getPlayerRect().top < stageGround.top)
			{
				_pl->setPlayerY(playerY -= height);//_pm->getPlayer().y -= height;
				_collisionRect = stageGround;//_pm->getPlayer().gravity = 0;
			}
			//아래에 있나
			if ((_pl->getPlayerRect().bottom > stageGround.bottom)) _pl->setPlayerY(playerY += height); //_pm->getPlayer().y += height;
		}
	}
	//}
}

void stageManager::directionImageInit()
{
	IMAGEMANAGER->addImage("black image", "stageImage/black image.bmp", 3840, 2160, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("whithe image", "stageImage/white image.bmp", 3840, 2160, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("red image", "stageImage/red image.bmp", 1920, 1080, true, RGB(255, 0, 255), true);
}

void stageManager::changStage4()
{
	
	

}
