/*
Author : w17012919

The Spawner Class handles the creation of player and enemy characters
*/

#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Spawner
{
private :
	//Pointer to player for other objects to use where required to chase or shoot player
	GameObject* pPlayer;
	//Object manager to add new items to
	ObjectManager* pManager;
public :
	//Constructor
	Spawner(ObjectManager* mManager);
	//Destructor
	~Spawner();

	void SpawnBackground();

	void SpawnPlayer();

	void SpawnImp();
	void SpawnLizard();
	void SpawnWarriorOrc();
	void SpawnMaskedOrc();
	void SpawnNecromancer();

	void SpawnRandom();

	GameObject* getPlayer();
	Vector2D getRandomPosition();
};

