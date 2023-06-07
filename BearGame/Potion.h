#pragma once
#include "Object.h"

class Potion : public Object
{
public:
	Potion();
	virtual void perform();
	virtual void restore();
private:
	virtual void setAttribute();
};