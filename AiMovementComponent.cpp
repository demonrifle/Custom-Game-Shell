/*
Author : w17012919

This AiMovementComponent is used to control non-player characters with random or chasing behaviour.

*/
#include "AiMovementComponent.h"
#include "GameObject.h"

/* AiMovementComponent constructor

Requires a PhysicsComponent,
how often a change will be made in float seconds,
the maximum speed of the object
and another game object to chase.

*/
AiMovementComponent::AiMovementComponent(PhysicsComponent* mPhysicsComponent, float mChangeCooldown, int mMaxSpeed, GameObject* mOther)
{	
	//Sets Component type
	TypeOfComponent = ComponentType::AIMOVEMENT;
	//Set parameters
	pPhysicsComponent = mPhysicsComponent;
	ChangeCooldown = mChangeCooldown;
	MaxSpeed = mMaxSpeed;
	pOther = mOther;
	//Set default values
	InputAxis = Vector2D(0.0f, 0.0f);
	ChangeReady = 0.0f;
	//Set random initial direction
	ChangeDirection(0.0f);

}

//Destructor
AiMovementComponent::~AiMovementComponent()
{
}

/*
Overridden Update method,
receives a pointer to the
parent GameObject to use 
as a parameter across any functions
and take the game frameTime.
*/
void AiMovementComponent::Update(GameObject* pOwner)
{
	//Get frame time
	float frameTime = pOwner->getFrameTime();
	//If pOther is set, chase it
	if (pOther)
	{
		ChangeDirection(frameTime, pOwner);
	}
	//Else set new random direction
	else
	{
		ChangeDirection(frameTime);
	}

}

/*
Change direction randomly
*/
void AiMovementComponent::ChangeDirection(float frameTime)
{
	//If direction should change
	if (ChangeReady <= 0.0f)
	{
		//If max speed is not set to 0
		if (MaxSpeed != 0)
		{
			//Get new random values between positive and negative max speed
			int x = rand() % MaxSpeed - MaxSpeed / 2;
			int y = rand() % MaxSpeed - MaxSpeed / 2;
			//Set and normalise vector
			InputAxis = Vector2D((float)x, (float)y).unitVector();
			//Multiply by MaxSpeed for vector magnitude
			InputAxis *= MaxSpeed;
			//Set new velocity
			pPhysicsComponent->setVelocity(InputAxis);
		}
		//Set new random change timer 
		ChangeReady = rand() % 5 + ChangeCooldown;
	}
	//Reduce change timer
	else ChangeReady -= frameTime;

}

/*
Change direction to chase pOther GameObject
*/
void AiMovementComponent::ChangeDirection(float frameTime, GameObject* pOwner)
{
	//If direction should change
	if (ChangeReady <= 0.0f)
	{
		//Get direction to pOther
		Vector2D NewVelocity = pOther->getPosition() - pOwner->getPosition();
		//Normalise vector
		NewVelocity = NewVelocity.unitVector();
		//Multiply by MaxSpeed for vector magnitude
		NewVelocity *= MaxSpeed;
		//Set InputAxis
		InputAxis = NewVelocity;
		//Set velocity
		pPhysicsComponent->setVelocity(InputAxis);
		//Reset timer
		ChangeReady = ChangeCooldown;
	}
	//Reduce change timer
	else ChangeReady -= frameTime;
}

