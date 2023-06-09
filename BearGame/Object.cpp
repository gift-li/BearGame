#include "Object.h"
#include "Eagle.h"
#include "Tree.h"
#include "Herb.h"
#include "Honey.h"
#include "Potion.h"

Object* Object::random()
{
    int randomNumber = rand() % 100;

    if (randomNumber < 40)
    {
        return new Tree(); // 40% chance for Tree
    }
    else if (randomNumber < 80)
    {
        return new Eagle(); // 40% chance for Eagle
    }
    else if (randomNumber < 85)
    {
        return new Potion(); // 5% chance for Potion
    }
    else if (randomNumber < 95)
    {
        return new Herb(); // 10% chance for Herb
    }
    else
    {
        return new Honey(); // 5% chance for Honey
    }
}


bool Object::isItem()
{
	switch (this->type)
	{
	case Object::HERB:
	case Object::HONEY:
	case Object::POTION:
		return true;
	default:
		return false;
	}
}