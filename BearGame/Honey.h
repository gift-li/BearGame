#pragma once
#include "Object.h"

class Honey : public Object
{
public:
	Honey();
	virtual void perform();
private:
	virtual void setAttribute();
};