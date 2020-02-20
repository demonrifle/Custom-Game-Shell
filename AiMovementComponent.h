/*
Author : w17012919

This AiMovementComponent is used to control non-player characters with random or chasing behaviour.

*/
#pragma once
#include "PhysicsComponent.h"
#include <stdlib.h>
#include <time.h>

class ObjectManager;

class AiMovementComponent :
	public Component
{
private :
	//A PhysicsComponent to control
	PhysicsComponent* pPhysicsComponent;
	//The direction axis to head to
	Vector2D InputAxis;
	//How often speed is changed
	float ChangeCooldown;
	float ChangeReady;
	//The maximum speed of an object
	int MaxSpeed;

	//Another game object that can be set to be chased
	GameObject* pOther;

public :
	//Constructor 
	AiMovementComponent(PhysicsComponent* mPhysicsComponent, float mChangeCooldown, int mMaxSpeed, GameObject* mOther);
	//Destructor
	~AiMovementComponent();
	//Each frame update
	void Update(GameObject* pOwner) override;
	//Change direction to new random
	void ChangeDirection(float frameTime);
	//Change direction to chase other object
	void ChangeDirection(float frameTime, GameObject* pOwner);

};

