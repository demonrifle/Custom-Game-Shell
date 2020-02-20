/*
Author : w17012919

The Component class serves as a base for all derived Component classes.
*/
#pragma once
class GameObject;

enum class ComponentType {RENDER, COLLISION, PHYSICS, PLAYERINPUT, AIMOVEMENT, SHOOTING};

class Component
{
protected :
	ComponentType TypeOfComponent;
public:
	//Constructor
	Component();
	//Destructor
	virtual ~Component();


	ComponentType getComponentType();

	virtual void Update(GameObject* pOwner) = 0;
};

