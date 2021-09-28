#include "stdafx.h"
#include "effectClass.h"

HRESULT effectClass::init(const char* imageName, float x, float y)
{
	/*tagEffect effect;

	effect.effectName = imageName;
	effect._imgName = new image;
	effect._imgName = IMAGEMANAGER->findImage(imageName);

	effect._x = x;
	effect._y = y;
	effect._count = 0;
	effect._currentFrameX, effect._currentFrameY = 0;

	effect._effectRc = RectMake(effect._x, effect._y, effect._imgName->getFrameWidth(), effect._imgName->getFrameHeight());

	_vEffect.push_back(effect);*/
	/*tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.radius = bullet.bulletImage->getWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());*/

	return S_OK;
}

void effectClass::release(const char* imageName)
{

}

void effectClass::update(int way)
{
	/*for (int i = 0; _vEffect.size(); i++)
	{
		_vEffect[i]._count++;
		_vEffect[i]._currentFrameY = way;

		if (_vEffect[i]._count % 7 == 0)
		{
			if (_vEffect[i]._currentFrameY == 0)
			{
				if (_vEffect[i]._currentFrameX >= _vEffect[i]._imgName->getMaxFrameX()) _vEffect[i]._currentFrameX = 0;
				_vEffect[i]._imgName->setFrameX(_vEffect[i]._currentFrameX);
				_vEffect[i]._imgName->setFrameY(_vEffect[i]._currentFrameY);
				_vEffect[i]._currentFrameX++;

				_vEffect[i]._count = 0;
			}
			else
			{
				if (_vEffect[i]._currentFrameX == 0) _vEffect[i]._currentFrameX = _vEffect[i]._imgName->getMaxFrameX();

				_vEffect[i]._imgName->setFrameX(_vEffect[i]._currentFrameX);
				_vEffect[i]._imgName->setFrameY(_vEffect[i]._currentFrameY);
				_vEffect[i]._currentFrameX--;

				_vEffect[i]._count = 0;
			}
		}
	}*/
	

//	return;
	//EFFECTMANAGER->update();
}

void effectClass::render(const char* imageName, float x, float y, int alpha)
{
	/*for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]._imgName->alphaFrameRender(getMemDC(), x, y, 
			_vEffect[i]._currentFrameX, _vEffect[i]._currentFrameY, alpha);
	}*/
	//EFFECTMANAGER->play("right slash effect", 2000, 1000);
}

void effectClass::imageInit()
{
	IMAGEMANAGER->addFrameImage("slash effect LR", "playerEffectImage/slash effect LR.bmp", 302, 258, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slash effect UD", "playerEffectImage/slash effect UD.bmp", 258, 302, 2, 2, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("dash effect LR", "playerEffectImage/dash effect LR.bmp", 1156, 292, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("double jump effect", "playerEffectImage/double jump effect.bmp", 584, 289, 4, 1, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("sturn effect", "playerEffectImage/sturn effect.bmp", 242, 153, 2, 1, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("player bullet effect", "playerEffectImage/player bullet effect.bmp", 1016, 216, 4, 2, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("heal effect", "playerEffectImage/heal effect.bmp", 296, 234, 4, 2, true, RGB(255, 0, 255), true);
	
	IMAGEMANAGER->addFrameImage("grim fire", "enemyEffectImage/grim fire.bmp", 708, 345, 6, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("grim bullet", "enemyEffectImage/grim bullet2.bmp", 100, 100, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("spike ready", "bossImage/spike ready.bmp", 201, 151, 3, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("spike up", "bossImage/spike up.bmp", 376, 552, 4, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("spike", "bossImage/spike.bmp", 128, 853, 2, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("spike down", "bossImage/spike down.bmp", 445, 651, 5, 1, true, RGB(255, 0, 255), false);

	//EFFECTMANAGER->addEffect("right slash effec", "playerEffectImage/right slash effect.bmp", 302, 129, 2, 2, 4, 10, 1, true);
}
