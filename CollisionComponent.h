/*
Author : w17012919

The CollisionComponent class serves as am abstract base for all derived Collision classes.
*/
#pragma once
#include "Component.h"
#include "Shapes.h"

//Abstract collision class
class CollisionComponent : 
	public Component
{
public:

	//Constructor and Destructor
	CollisionComponent();
	virtual ~CollisionComponent();
	
	//Abstract method for returning the type of shape each derived class uses
	virtual IShape2D* GetShape() = 0;
	//Update
	virtual void Update(GameObject* pOwner) = 0;
};

