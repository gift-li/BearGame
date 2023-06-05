#include "Object.h"
#include "Eagle.h"
#include "Tree.h"
#include "Herb.h"
#include "Honey.h"
#include "Potion.h"

Object* Object::random()
{
	switch (rand() % Object::LAST)
	{
	case Object::EAGLE:
		return new Eagle();
	case Object::TREE:
		return new Tree();
	case Object::HERB:
		return new Herb();
	case Object::HONEY:
		return new Honey();
	case Object::POTION:
		return new Potion();
	default:
		return new Eagle();
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