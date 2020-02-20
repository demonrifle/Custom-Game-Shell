/*
Author : w17012919

The Spawner Class handles the creation of player and enemy characters
*/

#include "Spawner.h"

//Constructor
Spawner::Spawner(ObjectManager* mManager)
{
	//Only sets the manager
	pManager = mManager;
}

//Destructor
Spawner::~Spawner()
{
}

//Handle background tiles and collidable walls spawn
void Spawner::SpawnBackground()
{
	//Create new vector of background choices
	std::vector<const wchar_t*> Backgrounds;
	Backgrounds.push_back(L"Assets/background0.png");
	Backgrounds.push_back(L"Assets/background1.png");
	Backgrounds.push_back(L"Assets/background2.png");

	//Create background components
	Vector2D background = Vector2D(0.0f, 0.0f);
	std::vector<Component*> BackgroundComponents;
	//Choose random background 
	RenderComponent* BackgroundRender = new RenderComponent(Backgrounds[rand() % 3], background, 0.0f, 1.2f, 0.0);

	BackgroundComponents.push_back(BackgroundRender);

	//Create and add background to manager
	GameObject* Background = new GameObject(background, BackgroundComponents, GameObjectType::WALL);
	pManager->AddObject(Background);


	//Create top wall components
	Vector2D mPosition = Vector2D(0.0f, 650.0f);
	std::vector<Component*> TopWallComponents;

	SegmentCollisionComponent* TopWallCollision = new SegmentCollisionComponent(Vector2D(1200.0f, 0.0f), Vector2D(1200.0f, 0.0f));
	RenderComponent* TopWallRender = new RenderComponent(L"Assets/wall0.png", mPosition, 0.0f, 1.2f, 0.1f);

	TopWallComponents.push_back(TopWallRender);
	TopWallComponents.push_back(TopWallCollision);
	
	//Create and add top wall
	GameObject* TopWall = new GameObject(mPosition, TopWallComponents,  GameObjectType::WALL);
	pManager->AddObject(TopWall);

	//Create top wall components
	mPosition = Vector2D(0.0f, -650.0f);
	std::vector<Component*> BottomWallComponents;

	SegmentCollisionComponent* BottomWallCollision = new SegmentCollisionComponent(Vector2D(1200.0f, 0.0f), Vector2D(1200.0f, 0.0f));
	RenderComponent* BottomWallRender = new RenderComponent(L"Assets/wall0.png", mPosition, 0.0f, 1.2f, 0.1f);

	BottomWallComponents.push_back(BottomWallRender);
	BottomWallComponents.push_back(BottomWallCollision);

	//Create, rotate 180 and add top wall
	GameObject* BottomWall = new GameObject(mPosition, BottomWallComponents,   GameObjectType::WALL);
	BottomWall->setAngle(3.14f);
	pManager->AddObject(BottomWall);
	
	//Create left wall components
	mPosition = Vector2D(-1190, 0.0f);
	std::vector<Component*> LeftWallComponents;

	SegmentCollisionComponent* LeftWallCollision = new SegmentCollisionComponent(Vector2D(0.0f, 800.0f), Vector2D(0.0f, 800.0f));
	RenderComponent* LeftWallRender = new RenderComponent(L"Assets/wall1.png", mPosition, 0.0f, 1.2f, 0.1f);

	LeftWallComponents.push_back(LeftWallRender);
	LeftWallComponents.push_back(LeftWallCollision);

	//Create, rotate 180 and add left wall
	GameObject* LeftWall = new GameObject(mPosition, LeftWallComponents,  GameObjectType::WALL);
	LeftWall->setAngle(3.14f);
	pManager->AddObject(LeftWall);

	//Create right wall components
	mPosition = Vector2D(1190, 0.0f);
	std::vector<Component*> RightWallComponents;

	SegmentCollisionComponent* RightWallCollision = new SegmentCollisionComponent(Vector2D(0.0f, 800.0f), Vector2D(0.0f, 800.0f));
	RenderComponent* RightWallRender = new RenderComponent(L"Assets/wall1.png", mPosition, 0.0f, 1.2f, 0.1f);

	RightWallComponents.push_back(RightWallRender);
	RightWallComponents.push_back(RightWallCollision);

	//Create and add right wall
	GameObject* RightWall = new GameObject(mPosition, RightWallComponents,  GameObjectType::WALL);
	pManager->AddObject(RightWall);

}

//Spawn Player 
void Spawner::SpawnPlayer()
{
	//Create components

	Vector2D mPosition = Vector2D(0.0f, 0.0f);
	std::vector<Component*> PlayerComponents;

	//Collision
	RectangularCollisionComponent* PlayerCollision = new RectangularCollisionComponent(mPosition, Vector2D(40.0f, 80.0f));
	//Physics
	PhysicsComponent* PlayerPhysics = new PhysicsComponent(Vector2D(0.0f, 0.0f), 0.0f);

	//Animation
	std::vector<const wchar_t*> animator;
	animator.push_back(L"Assets/wizardIdle0.png");
	animator.push_back(L"Assets/wizardIdle1.png");
	animator.push_back(L"Assets/wizardIdle2.png");
	animator.push_back(L"Assets/wizardIdle3.png");
	AnimationComponent* PlayerAnimation = new AnimationComponent(animator, mPosition, 0.0f, 4.0f, 0.0f);

	//Input
	InputComponent* PlayerInput = new InputComponent(PlayerPhysics, pManager, 0.5f, L"Assets/fireball.wav");

	PlayerComponents.push_back(PlayerPhysics);
	PlayerComponents.push_back(PlayerInput);
	PlayerComponents.push_back(PlayerCollision);
	PlayerComponents.push_back(PlayerAnimation);

	//Create and add
	GameObject* Player = new GameObject(mPosition, PlayerComponents, GameObjectType::PLAYER);
	pManager->AddObject(Player);

	//Set member pointer
	pPlayer = Player;

}

void Spawner::SpawnImp()
{
	Vector2D mPosition = getRandomPosition();
	std::vector<Component*> ImpComponents;
	CircularCollisionComponent* ImpCollision = new CircularCollisionComponent(mPosition, 30.0f);

	std::vector<const wchar_t*> animator;
	animator.push_back(L"Assets/impIdle0.png");
	animator.push_back(L"Assets/impIdle1.png");
	animator.push_back(L"Assets/impIdle2.png");
	animator.push_back(L"Assets/impIdle3.png");
	AnimationComponent* ImpAnimation = new AnimationComponent(animator, mPosition, 0.0f, 3.0f, 0.0f);

	PhysicsComponent* ImpPhysics = new PhysicsComponent(Vector2D(0.0f, 0.0f), 0.0f);
	AiMovementComponent* ImpMovement = new AiMovementComponent(ImpPhysics, 3.0f, 500, nullptr);
	ImpComponents.push_back(ImpCollision);
	ImpComponents.push_back(ImpAnimation);
	ImpComponents.push_back(ImpMovement);
	ImpComponents.push_back(ImpPhysics);

	GameObject* Imp = new GameObject(mPosition, ImpComponents,  GameObjectType::ENEMY);

	pManager->AddObject(Imp);
}

void Spawner::SpawnLizard()
{
	Vector2D mPosition = getRandomPosition();
	std::vector<Component*> LizardComponents;
	RectangularCollisionComponent* LizardCollision = new RectangularCollisionComponent(mPosition, Vector2D(50.0f, 90.0f));

	std::vector<const wchar_t*> animator;
	animator.push_back(L"Assets/lizardIdle0.png");
	animator.push_back(L"Assets/lizardIdle1.png");
	animator.push_back(L"Assets/lizardIdle2.png");
	animator.push_back(L"Assets/lizardIdle3.png");
	AnimationComponent* LizardAnimation = new AnimationComponent(animator, mPosition, 0.0f, 3.0f, 0.0f);
	PhysicsComponent* LizardPhysics = new PhysicsComponent(Vector2D(0.0f, 0.0f), 0.0f);
	AiMovementComponent* LizardMovement = new AiMovementComponent(LizardPhysics, 3.0f, 200, nullptr);
	LizardComponents.push_back(LizardCollision);
	LizardComponents.push_back(LizardAnimation);
	LizardComponents.push_back(LizardMovement);
	LizardComponents.push_back(LizardPhysics);
	GameObject* Lizard = new GameObject(mPosition, LizardComponents, GameObjectType::ENEMY);

	pManager->AddObject(Lizard);
}

void Spawner::SpawnWarriorOrc()
{
	Vector2D mPosition = getRandomPosition();
	std::vector<Component*> WarriorOrcComponents;
	RectangularCollisionComponent* WarriorOrcCollision = new RectangularCollisionComponent(mPosition, Vector2D(70.0f, 70.0f));

	std::vector<const wchar_t*> animator;
	animator.push_back(L"Assets/warriorOrcIdle0.png");
	animator.push_back(L"Assets/warriorOrcIdle1.png");
	animator.push_back(L"Assets/warriorOrcIdle2.png");
	animator.push_back(L"Assets/warriorOrcIdle3.png");
	AnimationComponent* WarriorOrcAnimation = new AnimationComponent(animator, mPosition, 0.0f, 4.0f, 0.0f);
	PhysicsComponent* WarriorOrcPhysics = new PhysicsComponent(Vector2D(0.0f, 0.0f), 0.0f);
	AiMovementComponent* WarriorOrcMovement = new AiMovementComponent(WarriorOrcPhysics, 3.0f, 150, pPlayer);
	WarriorOrcComponents.push_back(WarriorOrcCollision);
	WarriorOrcComponents.push_back(WarriorOrcAnimation);
	WarriorOrcComponents.push_back(WarriorOrcMovement);
	WarriorOrcComponents.push_back(WarriorOrcPhysics);
	GameObject* WarriorOrc = new GameObject(mPosition, WarriorOrcComponents,  GameObjectType::ENEMY);

	pManager->AddObject(WarriorOrc);
}

void Spawner::SpawnMaskedOrc()
{
	Vector2D mPosition = getRandomPosition();
	std::vector<Component*> MaskedOrcComponents;
	RectangularCollisionComponent* MaskedOrcCollision = new RectangularCollisionComponent(mPosition, Vector2D(70.0f, 70.0f));
	std::vector<const wchar_t*> animator;
	animator.push_back(L"Assets/maskedOrcIdle0.png");
	animator.push_back(L"Assets/maskedOrcIdle1.png");
	animator.push_back(L"Assets/maskedOrcIdle2.png");
	animator.push_back(L"Assets/maskedOrcIdle3.png");
	AnimationComponent* MaskedOrcAnimation = new AnimationComponent(animator, mPosition, 0.0f, 4.0f, 0.0f);
	PhysicsComponent* MaskedOrcPhysics = new PhysicsComponent(Vector2D(0.0f, 0.0f), 0.0f);
	AiMovementComponent* MaskedOrcMovement = new AiMovementComponent(MaskedOrcPhysics, 3.0f, 300, pPlayer);
	ShootingComponent* MaskedOrcShooting = new ShootingComponent(3.0f, pPlayer, pManager, L"Assets/axe.png", L"Assets/fireball.wav");
	MaskedOrcComponents.push_back(MaskedOrcCollision);
	MaskedOrcComponents.push_back(MaskedOrcAnimation);
	MaskedOrcComponents.push_back(MaskedOrcMovement);
	MaskedOrcComponents.push_back(MaskedOrcShooting);
	MaskedOrcComponents.push_back(MaskedOrcPhysics);
	GameObject* MaskedOrc = new GameObject(mPosition, MaskedOrcComponents, GameObjectType::ENEMY);

	pManager->AddObject(MaskedOrc);
}

void Spawner::SpawnNecromancer()
{
	Vector2D mPosition = getRandomPosition();
	std::vector<Component*> NecromancerComponents;
	RectangularCollisionComponent* NecromancerCollision = new RectangularCollisionComponent(mPosition, Vector2D(60.0f, 80.0f));
	std::vector<const wchar_t*> animator;
	animator.push_back(L"Assets/necromancerIdle0.png");
	animator.push_back(L"Assets/necromancerIdle1.png");
	animator.push_back(L"Assets/necromancerIdle2.png");
	animator.push_back(L"Assets/necromancerIdle3.png");
	AnimationComponent* NecromancerAnimation = new AnimationComponent(animator, mPosition, 0.0f, 3.0f, 0.0f);
	PhysicsComponent* NecromancerPhysics = new PhysicsComponent(Vector2D(0.0f, 0.0f), 0.0f);
	AiMovementComponent* NecromancerMovement = new AiMovementComponent(NecromancerPhysics, 3.0f, 50, nullptr);
	ShootingComponent* NecromancerShooting = new ShootingComponent(3.0f, pPlayer, pManager, L"Assets/fireball1.png", L"Assets/fireball.wav");
	NecromancerComponents.push_back(NecromancerCollision);
	NecromancerComponents.push_back(NecromancerAnimation);
	NecromancerComponents.push_back(NecromancerMovement);
	NecromancerComponents.push_back(NecromancerShooting);
	NecromancerComponents.push_back(NecromancerPhysics);
	GameObject* Necromancer = new GameObject(mPosition, NecromancerComponents, GameObjectType::ENEMY);

	pManager->AddObject(Necromancer);
}

//Spawn random enemy using a switch statement
void Spawner::SpawnRandom()
{
	switch (rand() % 5)
	{
	case 0:
		SpawnImp();
		break;
	case 1:
		SpawnWarriorOrc();
		break;
	case 2:
		SpawnMaskedOrc();
	case 3:
		SpawnLizard();
	case 4:
		SpawnNecromancer();
	default:
		break;
	}
}

GameObject* Spawner::getPlayer()
{
	return pPlayer;
}

//Get random position, usually to spawn something at
Vector2D Spawner::getRandomPosition()
{
	//Get a new random position
	Vector2D Position = Vector2D((float)(rand() % 2000 - 1000), (float)(rand() % 1000 - 500));
	//If the player pointer is set / player exists
	if (pPlayer)
	{
		//While the position of the player is at least 200 units away from the random position
		while (abs((Position - pPlayer->getPosition()).XValue) < 200.0f ||
			abs((Position - pPlayer->getPosition()).YValue) < 200.0f)
		{
			//Get new position
			Position = Vector2D((float)(rand() % 2000 - 1000), (float)(rand() % 1000 - 500));
		}
	}
	return Position;
}

