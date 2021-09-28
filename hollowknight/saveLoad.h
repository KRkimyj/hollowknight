#pragma once
#include "gameNode.h"

class saveLoad : public gameNode
{
public:
	saveLoad() {};
	~saveLoad() {};

	void update();
	void save(int hp, int geo);
	void load();
};



