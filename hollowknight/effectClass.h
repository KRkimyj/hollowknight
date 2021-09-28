#pragma once
#include "gameNode.h"
#include <vector>
//
//struct tagEffect
//{
//	RECT _effectRc;
//	float _x, _y;
//
//	string effectName;
//
//	image* _imgName;
//	int _count;
//	int _currentFrameX, _currentFrameY;
//};
class effectClass : public gameNode
{
	//vector<tagEffect>		_vEffect;


public :
	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void release(const char* imageName);
	virtual void update(int way);
	virtual void render(const char* imageName, float x, float y, int alpha);

	void imageInit();

	//vector<tagEffect> getEffect() { return _vEffect; }
};

