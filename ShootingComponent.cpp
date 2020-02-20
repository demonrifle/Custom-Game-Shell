/*
Author : w17012919

The ShootingComponent is attached to GameObjects, which require the ability to shoot projectiles.

*/

#include "ShootingComponent.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "mysoundengine.h"

//Constructor, takes in shoot cooldown, object to shoot towards 
//and the names of the image and sound to use when firing
ShootingComponent::ShootingComponent(float mShootCooldown, GameObject* mEnemy, ObjectManager* mManager, const wchar_t* mProjectileName, const wchar_t* mProjectileSound)
{
	//Set component type
	TypeOfComponent = ComponentType::SHOOTING;
	//Set parameters
	ShootCooldown = mShootCooldown;
	pEnemy = mEnemy;
	pManager = mManager;
	ProjectileName = mProjectileName;
	ProjectileSound = mProjectileSound;
	//Set initial shoot delay
	ShootReady = (float) (rand() % 3 + 2);
}

//Destructor
ShootingComponent::~ShootingComponent()
{
}

//Update of the component each frame
void ShootingComponent::Update(GameObject* pOwner)
{
	//Get frame time since last update
	float frameTime = pOwner->getFrameTime();
	//If shoot is ready
	if (ShootReady <= 0.0f)
	{
		//Shoot and reset timer
		Shoot(pOwner);
		ShootReady = rand() % 3 + ShootCooldown;
	}
	//Reduce timer
	else ShootReady -= frameTime;
}

//Shoot a projectile towards enemy
void ShootingComponent::Shoot(GameObject* pOwner)
{
	//Play Sound
	MySoundEngine* SoundEngine = MySoundEngine::GetInstance();
	SoundIndex Sound = SoundEngine->LoadWav(ProjectileSound);
	SoundEngine->SetVolume(Sound, -1000);
	SoundEngine->Play(Sound);

	//Calculate new shoot direction
	Vector2D OwnerPosition = pOwner->getPosition();
	Vector2D EnemyPosition = pEnemy->getPosition();
	Vector2D Offset = EnemyPosition - OwnerPosition;
	//Normalise vector
	Offset = Offset.unitVector();

	//Randomise speed 
	float magnitude = (float)(rand() % 200 + 500);
	Offset *= magnitude;

	//Create components for projectile
	std::vector<Component*> ProjectileComponents;
	RenderComponent* ProjectileRender = new RenderComponent(ProjectileName, OwnerPosition, 0.0f, 2.0f, 0.0f);
	CircularCollisionComponent* ProjectileCollision = new CircularCollisionComponent(OwnerPosition, ProjectileRender->getScale() * 12.0f);
	PhysicsComponent* ProjectilePhysics = new PhysicsComponent(Offset, 24.0f);

	ProjectileComponents.push_back(ProjectileRender);
	ProjectileComponents.push_back(ProjectileCollision);
	ProjectileComponents.push_back(ProjectilePhysics);

	//Create Projectile and add to manager
	GameObject* Projectile = new GameObject(OwnerPosition, ProjectileComponents,  GameObjectType::ENEMYPROJECTILE);
	pManager->AddObject(Projectile);
}
