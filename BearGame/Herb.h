#pragma once
#include "Object.h"

class Herb : public Object
{
public:
	Herb();
	virtual void perform();
private:
	virtual void setAttribute();
};