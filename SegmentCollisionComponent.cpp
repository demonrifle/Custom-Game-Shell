/*
Author : w17012919

The SegmentCollisionComponent class is a CollisionComponent class using segments/lines.
*/

#include "SegmentCollisionComponent.h"
  
//Constructor for Segments, takes in two vectors for the distance of the two endpoints, both should be positive
SegmentCollisionComponent::SegmentCollisionComponent(Vector2D mStart, Vector2D mEnd)
{
	//Set component type
	TypeOfComponent = ComponentType::COLLISION;
	//Set Shape
	Shape = Segment2D();
	//Set parameters
	Start = mStart;
	End = mEnd;
}

//Destructor
SegmentCollisionComponent::~SegmentCollisionComponent()
{
}

IShape2D* SegmentCollisionComponent::GetShape()
{
	return &Shape;
}

//Update method
//Takes in the parent GameObject 
void SegmentCollisionComponent::Update(GameObject* pOwner)
{
	//Place	the segment at the position of the owner with an offset of the start and end points 
	Shape.PlaceAt(pOwner->getPosition() - Start, pOwner->getPosition() + End);
}
