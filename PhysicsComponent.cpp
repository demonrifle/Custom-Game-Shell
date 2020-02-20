/*
Author : w17012919

The PhysicsComponent Class holds Velocity and Rotation speeds
and transforms the parent GameObject according to them

*/
#include "PhysicsComponent.h"
#include "GameObject.h"

/*
Parameterized constructor
*/
PhysicsComponent::PhysicsComponent(Vector2D mVelocity, float mRotation)
{
	//Set Component type
	TypeOfComponent = ComponentType::PHYSICS;
	//Set parameters
	Velocity = mVelocity;
	Rotation = mRotation;
}

//Default Constructor
PhysicsComponent::PhysicsComponent()
{
	//Set Component type
	TypeOfComponent = ComponentType::PHYSICS;
	//Set defaults
	Velocity = Vector2D(0.0f, 0.0f);
	Rotation = 0.0f;
}

//Destructor
PhysicsComponent::~PhysicsComponent()
{
}

/*
Update takes the position and angle of the parent GameObject
*/
void PhysicsComponent::Update(GameObject* pOwner)
{
	//Calculate new position according to current and velocity
	Vector2D newPosition = pOwner->getPosition() + Velocity * pOwner->getFrameTime();
	//Set new position
	pOwner->setPosition(newPosition);

	//Calculate new angle according to current and rotation
	float newAngle = pOwner->getAngle() + Rotation * pOwner->getFrameTime();
	//Set new rotation
	pOwner->setAngle(newAngle);
}

Vector2D PhysicsComponent::getVelocity()
{
	return Velocity;
}

float PhysicsComponent::getRotation()
{
	return Rotation;
}

void PhysicsComponent::setVelocity(Vector2D mVelocity)
{
	Velocity = mVelocity;
}

void PhysicsComponent::setRotation(float mRotation)
{
	Rotation = mRotation;
}
