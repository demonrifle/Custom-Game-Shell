/*
Author : w17012919

The RectangularCollisionComponent class is a CollisionComponent class using a rectangular collision shape.
*/
#pragma once
#include "CollisionComponent.h"
#include "GameObject.h"

class RectangularCollisionComponent :
	public CollisionComponent
{
private:

	//Rectangle shape and dimensions
	Rectangle2D Shape;
	Vector2D Dimensions;

public:

	//Constructor and Destructor
	RectangularCollisionComponent(Vector2D position, Vector2D xy);
	~RectangularCollisionComponent();

	//Settter
	void setDimensions(Vector2D xy);

	//Return shape, used to detect overlaps
	IShape2D* GetShape() override;

	//Update shape each frame
	void  Update(GameObject* pOwner) override;
};

