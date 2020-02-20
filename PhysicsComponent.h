/*
Author : w17012919

The PhysicsComponent Class holds Velocity and Rotation speeds
and transforms the parent GameObject according to them

*/
#pragma once
#include "Component.h"
#include "vector2D.h"

class GameObject;

class PhysicsComponent :
	 public Component
{
private :

	//Position Velocity and Angle Rotation
	Vector2D Velocity;
	float Rotation;

public :
	//Constructors 
	PhysicsComponent(Vector2D mVelocity, float mRotation);
	PhysicsComponent();
	//Destructor
	virtual ~PhysicsComponent();

	//Update
	virtual void Update(GameObject *pOwner);

	//Gettrs
	Vector2D getVelocity();
	float getRotation();

	//Setters
	void setVelocity(Vector2D mVelocity);
	void setRotation(float mRotation);
};

