/*
Author : w17012919

The ObjectManager contains all GameObjects, tracks active and removes inactive ones, checks for collisions.

*/
#pragma once
#include <list>
#include "GameObject.h"

class ObjectManager
{
private :
	//Active objects
	std::list<GameObject*> pObjectList;
	//Inactive / to-be-removed obejcts
	std::list<GameObject*> pInactiveObjectList;
public :
	//Constructor
	ObjectManager();
	//Destructor
	~ObjectManager();
	//Add new object to the list
	void AddObject(GameObject* pNewObject);
	//Update all objects in the list
	void UpdateAll(float frameTime);
	//Check collisions between all collidable objects
	void CheckCollision();
	//Deletion of objects
	void DeleteAll();
	void DeleteInactive();
	
	//Return collider for a GameObject
	IShape2D* getCollider(GameObject* pOwner);
	//Return the amount of GameObjects of type GameObjectType left
	int ObjectsLeft(GameObjectType type);
};

