#pragma once
#include "Object.h"

class Potion : public Object
{
public:
	Potion();
	virtual void perform();
private:
	virtual void setAttribute();
};