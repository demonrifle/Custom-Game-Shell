/*
Author : w17012919

The GameObjectclass is the main object spawned in the game
It contains a list of components, that are largely independent of each other
It updates individual objects and is responsible for collisions depending on object types


*/

#include "GameObject.h"

//Default constructor
GameObject::GameObject()
{
	Position = Vector2D(0.0f, 0.0f);
	Angle = 0.0f;
	Active = true;
}

//Parameterized constructor
GameObject::GameObject(Vector2D mPosition, std::vector<Component*> mComponentVector, GameObjectType mObjectType)
{
	//Set parameters
	Position = mPosition;
	pComponentVector = mComponentVector;
	ObjectType = mObjectType;
	//Sets default values
	Angle = 0.0f;
	Active = true;
}

//destructor
GameObject::~GameObject()
{

}

//Return component vector
std::vector<Component*> GameObject::getComponents()
{
	return pComponentVector;
}

//Update GameObject
void GameObject::Update(float mFrameTime)
{
	//If the object is active
	if (Active)
	{	
		//Set new frame time
		FrameTime = mFrameTime;

		//For each component in the vector
		for (Component* pComponent : pComponentVector)
		{
			//Update with this as a parameter
			pComponent->Update(this);
		}
	}

}

//Collision handler function
//Plays sound effect on particular collisions
//Handles collisions between two objects
//Behaviour changes depending on the two types
void GameObject::Collide(GameObject* pOtherObject)
{
	//Load sound for death collisions
	MySoundEngine* SoundEngine = MySoundEngine::GetInstance();
	SoundIndex CollisionSound = SoundEngine->LoadWav(L"Assets/fireburst.wav");
	SoundEngine->SetVolume(CollisionSound, -2000);

	//Nested Switcch statements depending on this and other GameObject type
	//Get type of this
	switch (getObjectType())
	{	
	//If this is wall,
	case GameObjectType::WALL:
	{
		//Get other object type
		switch (pOtherObject->getObjectType())
		{
			//If other is player, launch back to stop walking over walls
		case GameObjectType::PLAYER:
		{
			Vector2D newDirection = -pOtherObject->getPosition();
			PhysicsComponent* temp = (PhysicsComponent*) pOtherObject->getComponent(ComponentType::PHYSICS);
			if (temp) temp->setVelocity(newDirection);
		}
		break;
		//If other is enemy change direction to stop walking over walls
		case GameObjectType::ENEMY:
		{
			Vector2D newDirection = -pOtherObject->getPosition();
			newDirection = newDirection.unitVector();
			newDirection *= 200.0f;
			PhysicsComponent* temp = (PhysicsComponent*)pOtherObject->getComponent(ComponentType::PHYSICS);
			if (temp) temp->setVelocity(newDirection);
		}
		break;
		//If other is projectile, destroy it
		case GameObjectType::PLAYERPROJECTILE:
		{
			pOtherObject->setActive(false);
		}
		break;
		//If other is projectile, destroy it
		case GameObjectType::ENEMYPROJECTILE:
		{
			pOtherObject->setActive(false);
		}
		break;
		}
	}
	break;
	// if this is of type Player
	case GameObjectType::PLAYER:
	{
		switch (pOtherObject->getObjectType())
		{
			//If other is wall, push self back
		case GameObjectType::WALL:
		{
			Vector2D newDirection = -this->getPosition() * 0.2f;
			PhysicsComponent* temp = (PhysicsComponent*)getComponent(ComponentType::PHYSICS);
			if (temp) temp->setVelocity(newDirection);
			temp->setVelocity(newDirection);
		}
		break;
		//If other is enemy, destroy both and play sound
		case GameObjectType::ENEMY:
		{

			this->setActive(false);
			pOtherObject->setActive(false);
			SoundEngine->Play(CollisionSound);

		}
		break;
		//If other is enemy projectile, destroy both and play sound
		case GameObjectType::ENEMYPROJECTILE:
		{
			SoundEngine->Play(CollisionSound);
			this->setActive(false);
		}
		break;
		}
	}
	break;
	// if this is of type PlayerProjectile
	case GameObjectType::PLAYERPROJECTILE:
	{
		switch (pOtherObject->getObjectType())
		{
			//If other is wall, destroy self
		case GameObjectType::WALL:
		{
			this->setActive(false);
		}
		break;
		//If other is enemy, destroy both and play sound
		case GameObjectType::ENEMY:
		{
			SoundEngine->Play(CollisionSound);
			this->setActive(false);
			pOtherObject->setActive(false);
		}
		break;
		}
	}
	break;
	// if this is of type Enemy
	case GameObjectType::ENEMY:
	{
		switch (pOtherObject->getObjectType())
		{
		case GameObjectType::WALL:
		{
			//If other is wall, change self velocity
			Vector2D newDirection = -getPosition();
			newDirection = newDirection.unitVector();
			newDirection *= 200.0f;
			PhysicsComponent* temp = (PhysicsComponent*) getComponent(ComponentType::PHYSICS);
			if (temp) temp->setVelocity(newDirection);
			temp->setVelocity(newDirection);
		}
		break;
		//If other is player, destroy both and play sound
		case GameObjectType::PLAYER:
		{
			SoundEngine->Play(CollisionSound);
			pOtherObject->setActive(false);
			this->setActive(false);

		}
		break;
		//If other is enemy, change velocity for both
		case GameObjectType::ENEMY:
		{
			PhysicsComponent* temp = (PhysicsComponent*) getComponent(ComponentType::PHYSICS);
			PhysicsComponent* other = (PhysicsComponent*)pOtherObject->getComponent(ComponentType::PHYSICS);
			Vector2D BounceOff = pOtherObject->getPosition() - getPosition();
			if (BounceOff * temp->getVelocity() > 0)
			{
				Vector2D SecondBounce = -BounceOff;
				SecondBounce = SecondBounce.unitVector();
				Vector2D newVelocity = temp->getVelocity() - 2 * (temp->getVelocity() * SecondBounce) * SecondBounce;
				temp->setVelocity(newVelocity);
				other->setVelocity(-newVelocity);
			}
		}
		break;
		//If other is player projectile, destroy both and play sound
		case GameObjectType::PLAYERPROJECTILE:
		{

			SoundEngine->Play(CollisionSound);
			this->setActive(false);
			pOtherObject->setActive(false);
		}
		break;
		}
	}
	break;
	// if this is of type EnemyProjectile
	case GameObjectType::ENEMYPROJECTILE:
	{
		switch (pOtherObject->getObjectType())
		{

			//If other is wall, disable self
		case GameObjectType::WALL:
		{
			this->setActive(false);
		}
		break;
		case GameObjectType::PLAYER:
		{
			//If other is player, destroy both and play sound
			SoundEngine->Play(CollisionSound);
			this->setActive(false);
			pOtherObject->setActive(false);

		}
		break;
		}
	}
	break;
	}

}

Component* GameObject::getComponent(ComponentType mType)
{
	//For each component in the vector
	for (Component* pNextComponent : pComponentVector)
	{
		//If it is of type PHYSICS
		if (pNextComponent->getComponentType() == mType)
		{
			return pNextComponent;
		}
	}
	//else return nullptr
	return nullptr;
}

void GameObject::addComponent(Component* mComponent)
{
	pComponentVector.push_back(mComponent);
}

bool GameObject::removeComponent(ComponentType mType)
{
	Component* temp = getComponent(mType);
	if (temp)
	{
		std::vector<Component*>::iterator it1;
		for (it1 = pComponentVector.begin(); it1 != pComponentVector.end(); it1++)
		{
			if ((*it1) == temp)
			{
				delete* it1;
				*it1 = nullptr;
				pComponentVector.erase(it1);
				return true;
			}
		}
	}
	return false;
}

Vector2D GameObject::getPosition()
{
	return Position;
}

void GameObject::setPosition(Vector2D mPosition)
{
	Position = mPosition;
}

float GameObject::getAngle()
{
	return Angle;
}

void GameObject::setAngle(float mAngle)
{
	Angle = mAngle;
}

float GameObject::getFrameTime()
{
	return FrameTime;
}

bool GameObject::getActive()
{
	return Active;
}

void GameObject::setActive(bool mActive)
{
	Active = mActive;
}

GameObjectType GameObject::getObjectType()
{
	return ObjectType;
}