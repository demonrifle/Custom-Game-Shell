/*
Author : w17012919

The CircularCollisionComponent class is a CollisionComponent derivative using a circular shape.
*/
#pragma once
#include "CollisionComponent.h"
#include "GameObject.h"
class CircularCollisionComponent :
	public CollisionComponent
{
private:

	//Circle shape
	Circle2D Shape;
	//Radius
	float Radius;

public:

	//Constructor 
	CircularCollisionComponent(Vector2D mPosition, float mRadius);
	//Destructor
	~CircularCollisionComponent();

	//Setter
	void SetRadius(float mRadius);

	//Return shape, used to detect overlaps
	IShape2D* GetShape() override;
	
	//Update shape each frame
	void  Update(GameObject* pOwner) override;
};

