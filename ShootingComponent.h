/*
Author : w17012919

The ShootingComponent is attached to GameObjects, which require the ability to shoot projectiles.

*/
#pragma once
#include "Component.h"

class ObjectManager;

class ShootingComponent :
	public Component
{
private :
		
	//Shooting timers
	float ShootCooldown;
	float ShootReady;
	//Scale of projectile
	float ShootScale;

	//Projectile Image name
	const wchar_t* ProjectileName;
	//Projectile Sound name
	const wchar_t* ProjectileSound;

	//Object to shoot towards to
	GameObject* pEnemy;
	//Manager to add projectile GameObjects to
	ObjectManager* pManager;

public :
	//Constructor
	ShootingComponent(float mShootCooldown, GameObject* mEnemy, ObjectManager* mManager, const wchar_t* mProjectileName, const wchar_t* mProjtileSound);
	//Destructor
	~ShootingComponent();

	//Update
	void Update(GameObject* pOwner) override;
	//Shoot
	void Shoot(GameObject* pOwner);
};

