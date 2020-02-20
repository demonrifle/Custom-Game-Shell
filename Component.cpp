/*
Author : w17012919

The Component class serves as a base for all derived Component classes.
*/
#include "Component.h"

Component::Component()
{
}

Component::~Component()
{
}

ComponentType Component::getComponentType()
{
	return TypeOfComponent;
}
