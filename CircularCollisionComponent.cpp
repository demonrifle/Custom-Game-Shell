/*
Author : w17012919

The CircularCollisionComponent class is a CollisionComponent derivative using a circular shape.
*/
#include "CircularCollisionComponent.h"

/*
Initialise the component in the Constructor
Set the radius for movement of the component in Update

*/
CircularCollisionComponent::CircularCollisionComponent(Vector2D mPosition, float mRadius)
{
	//Sets Component type
	TypeOfComponent = ComponentType::COLLISION;
	//Set initial shape location and radius
	Shape.PlaceAt(mPosition, mRadius);
	//Set radius for further use
	SetRadius(mRadius);
}

//Destructor
CircularCollisionComponent::~CircularCollisionComponent()
{
}

void CircularCollisionComponent::SetRadius(float mRadius)
{
	Radius = mRadius;
}

/*
Returns the Memory address of the shape for use
*/
IShape2D* CircularCollisionComponent::GetShape()
{
	return &Shape;
}

/*
Update of the component, follows the position of the parent GameObject
*/
void CircularCollisionComponent::Update(GameObject* pOwner)
{
	//Place shape at parent location
	Shape.PlaceAt(pOwner->getPosition(), Radius);
}
