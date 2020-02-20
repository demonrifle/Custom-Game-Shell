/*
Author : w17012919

The GameObjectclass is the main object spawned in the game
It contains a list of components, that are largely independent of each other
It updates individual objects and is responsible for collisions depending on object types


*/

#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include <stdlib.h>
#include <time.h>
#include <string>
//Include all headers for components
#include "CircularCollisionComponent.h"
#include "RectangularCollisionComponent.h"
#include "SegmentCollisionComponent.h"
#include "AnimationComponent.h" //Includes render component for single images
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "AiMovementComponent.h"
#include "ShootingComponent.h"

//Declare GameObjecType types
enum class GameObjectType { WALL, PLAYER, PLAYERPROJECTILE, ENEMY, ENEMYPROJECTILE };

class GameObject
{
protected :

	//Type of object
	GameObjectType ObjectType;
	//Transform variables
	Vector2D Position;
	float Angle;
	bool Active;

	//Last elapsed frame time, this is passed to components
	float FrameTime;

	//Vector of all components
	std::vector<Component*> pComponentVector;

public :

	//Constructors
	GameObject();
	GameObject(Vector2D mPosition, std::vector<Component*> mComponentVector, GameObjectType mObjectType);
	//Destructor
	virtual ~GameObject();

	//Getters
	GameObjectType getObjectType();
	std::vector<Component*> getComponents();
	float getFrameTime();

	Component* getComponent(ComponentType mType);
	bool removeComponent(ComponentType mType);
	void addComponent(Component* mComponent);

	Vector2D getPosition();
	float getAngle();
	bool getActive();

	//Setters
	void setPosition(Vector2D mPosition);
	void setAngle(float mAngle);
	void setActive(bool mActive);

	//Update function
	virtual void Update(float mFrameTime);
	//Collision handler
	virtual void Collide(GameObject* pOtherObject);
	
};


