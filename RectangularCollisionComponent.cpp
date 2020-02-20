/*
Author : w17012919

The RectangularCollisionComponent class is a CollisionComponent class using a circular collision shape.
*/
#include "RectangularCollisionComponent.h"

/*
Initialise the component in the Constructor
Set the dimensions for movement of the component in Update
*/
RectangularCollisionComponent::RectangularCollisionComponent(Vector2D mPosition, Vector2D xy)
{
	//Sets Component type
	TypeOfComponent = ComponentType::COLLISION;
	//Place rectangle collider at the Parent center, with an offset equal to dimensions.
	Shape.PlaceAt(	mPosition.YValue + xy.YValue / 2,	//Top
					mPosition.XValue - xy.XValue / 2,	//Left
					mPosition.YValue - xy.YValue / 2,	//Bottom
					mPosition.XValue + xy.XValue / 2);	//Right
	//Set dimensions for further use
	setDimensions(xy);
}

//Destructor
RectangularCollisionComponent::~RectangularCollisionComponent()
{
}


void RectangularCollisionComponent::setDimensions(Vector2D xy)
{
	Dimensions = xy;
}


IShape2D* RectangularCollisionComponent::GetShape()
{
	return &Shape;
}


//Updates the Component position according to the GameObject parent
void RectangularCollisionComponent::Update(GameObject* pOwner)
{
	//Get parent position
	Vector2D mPosition = pOwner->getPosition();
	//Place rectangle collider at the parent center, with an offset equal to dimensions.
	Shape.PlaceAt(mPosition.YValue + Dimensions.YValue / 2,		//Top
		mPosition.XValue - Dimensions.XValue / 2,				//Left
		mPosition.YValue - Dimensions.YValue / 2,				//Bottom
		mPosition.XValue + Dimensions.XValue / 2);				//Right
}