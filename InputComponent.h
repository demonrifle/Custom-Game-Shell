/*
Author : w17012919

This InputComponent is used to control player characters with movement and shooting behaviour.

*/
#pragma once
#include "PhysicsComponent.h"
#include "myinputs.h"

class ObjectManager;

class InputComponent :
	public Component
{
private: 
	//The physics component to transform
	PhysicsComponent* pPhysicsComponent;
	//An object manager to add objects to when shooting
	ObjectManager* pManager;
	//Input engine 
	MyInputs* pInputs;
	//Movement axis
	Vector2D InputAxis;

	//Shooting axis
	Vector2D ShootAxis;
	//Cooldown delay for shooting
	float ShootCooldown;
	//Cooldown timer
	float ShootReady;
	//Sound played when shooting
	const wchar_t* ShootSound;
public:
	//Constructor
	InputComponent(PhysicsComponent* mPhysicsComponent, ObjectManager* mManager, float mShootCooldown, const wchar_t* mShootSound);
	//Destructor
	~InputComponent();

	//Update
	void Update(GameObject* pOwner) override;
	//Movement
	void Move();
	//Shooting
	void Shoot(float frameTime, GameObject* pOwner);
};

