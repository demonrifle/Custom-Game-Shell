/*
Author : w17012919

The ObjectManager contains all GameObjects, tracks active and removes inactive ones, checks for collisions.

*/

#include "ObjectManager.h"

//Constructor
ObjectManager::ObjectManager()
{
}
//Destructor
ObjectManager::~ObjectManager()
{
}

//Add new object to the list
void ObjectManager::AddObject(GameObject* pNewObject)
{
	pObjectList.push_back(pNewObject);
}

//Update all objects
void ObjectManager::UpdateAll(float frameTime)
{
	//For each object in the active list
	for (GameObject* obj : pObjectList)
	{
		//If still active
		if (obj->getActive())
		{
			//Update it
			obj->Update(frameTime);
		}
		//If inactive
		else
		{
			//Add to inactive
			pInactiveObjectList.push_back(obj);
		}

	}
}

//Check if two GameObjects collide
void ObjectManager::CheckCollision()
{
	//Initialise iterators
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;
	//it1 starts at active objects 
	for (it1 = pObjectList.begin(); it1 != pObjectList.end(); it1++)
	{
		//it2 starts at the next item to avoid multiple collisions of the same objects
		for (it2 = std::next(it1); it2 != pObjectList.end(); it2++)
		{
			//If both objects have colliders
			if (getCollider((*it1)) != nullptr && getCollider((*it2)) != nullptr)
			{
				//If shapes intersect
				if (getCollider(*it1)->Intersects(*getCollider(*it2)))
				{
					//Colide with eachother
					//Functionality depends on the type of both objects
					(*it1)->Collide((*it2));
				}
			}
		}
	}
}

//Dete all game objects
void ObjectManager::DeleteAll()
{
	//For each object in the list
	for (GameObject* obj : pObjectList)
	{
		delete obj;
	}
}

void ObjectManager::DeleteInactive()
{
	//Initialise iterator
	std::list<GameObject*>::iterator it1;
	//If there are inactive objects
	if (!pInactiveObjectList.empty())
	{
		//For each inactive object
		for (it1 = pInactiveObjectList.begin(); it1 != pInactiveObjectList.end(); it1++)
		{
			//remove it from the active list to stop updating it
			pObjectList.remove((*it1));
		}

		//For each inactive object in the list
		for (GameObject* obj : pInactiveObjectList)
		{
			//Delete the object
			delete obj;
			//Set the pointer back to nullptr
			obj = nullptr;
		}
		//Clear the list
		pInactiveObjectList.clear();
	}

}

//Return collider if it exists
IShape2D* ObjectManager::getCollider(GameObject* pOwner)
{
	//For each component in the owner list
	for (Component* pNextComponent : pOwner->getComponents())
	{
		//If object type is collision
		if (pNextComponent->getComponentType() == ComponentType::COLLISION)
		{
			//Cast to new CollisionComponent
			CollisionComponent* Collision = (CollisionComponent*)pNextComponent;
			//Return shape
			return Collision->GetShape();
		}
	}
	//Return nullptr if nothing is found
	return nullptr;
}

//Returns objects left of type
int ObjectManager::ObjectsLeft(GameObjectType type)
{
	//Initialise a counter
	int i = 0;
	//For each object in the list
	for (GameObject* obj : pObjectList)
	{
		//If its of the same type
		if(obj->getObjectType()==type)
		{
			//Increment counter
			i++;
		}
	}
	//return counter
	return i;
}

