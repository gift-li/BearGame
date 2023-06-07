#pragma once
#include "Object.h"

class Honey : public Object
{
public:
	Honey();
	virtual void perform();
	virtual void restore();
private:
	virtual void setAttribute();
};