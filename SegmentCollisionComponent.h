/*
Author : w17012919

The SegmentCollisionComponent class is a CollisionComponent class using segments/lines.
*/

#pragma once
#include "CollisionComponent.h"
#include "GameObject.h"

class SegmentCollisionComponent :
	public CollisionComponent
{
private :
	//Shape to use
	Segment2D Shape;
	//Beginning and end point
	Vector2D Start;
	Vector2D End;

public :
	//Constructor
	SegmentCollisionComponent(Vector2D start, Vector2D end);
	//Destructor
	~SegmentCollisionComponent();

	//Return shape, used to detect overlaps
	IShape2D* GetShape() override;

	//Update shape each frame
	void  Update(GameObject* pOwner) override;
};

