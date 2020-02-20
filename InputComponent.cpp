/*
Author : w17012919

This InputComponent is used to control player characters with movement and shooting behaviour.

*/
#include "InputComponent.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "mysoundengine.h"

/*
Constructor for the InputComponent
*/
InputComponent::InputComponent(PhysicsComponent* mPhysicsComponent, ObjectManager* mManager, float mShootCooldown, const wchar_t* mShootSound)
{
	//Sets Component type
	TypeOfComponent = ComponentType::PLAYERINPUT;
	//Get MyInputs singleton
	pInputs = MyInputs::GetInstance();
	//Set parameters
	pPhysicsComponent = mPhysicsComponent;
	pManager = mManager;
	ShootSound = mShootSound;
	ShootCooldown = mShootCooldown;
	//Set default values
	InputAxis = Vector2D(0.0f, 0.0f);
	//Initial shooting direction to the right
	ShootAxis = Vector2D(500.0f, 0.0f);
	ShootReady = 0.0f;
}

//Destructor
InputComponent::~InputComponent()
{
}

/*
Update of the component called every frame update,
takes in the parent GameObject for data
*/
void InputComponent::Update(GameObject* pOwner)
{
	//Get frameTime
	float frameTime = pOwner->getFrameTime();
	//Move according to input
	Move();
	//Set new velocity to the physicsComponent
	pPhysicsComponent->setVelocity(InputAxis);
	//Shoot
	Shoot(frameTime, pOwner);

}

/*
Move sets the InputAxis according to player input
*/
void InputComponent::Move()
{
	//Check Keyboard presses since last frame
	pInputs->SampleKeyboard();
	//Set input and shooting axis
	//Walk up
	if (pInputs->KeyPressed(DIK_W))
	{
		InputAxis.YValue = 500.0f;
		ShootAxis.YValue = 500.0f;
	}
	//Walk down
	else if (pInputs->KeyPressed(DIK_S))
	{
		InputAxis.YValue = -500.0f;
		ShootAxis.YValue = -500.0f;
	}
	else
	{
		InputAxis.YValue = 0.0f;
		//Check InputAxis to not shoot a bullet with 0 velocity
		if (InputAxis.XValue != 0.0f)
		{
			ShootAxis.YValue = 0.0f;
		}
	}
	//Walk left
	if (pInputs->KeyPressed(DIK_A))
	{
		InputAxis.XValue = -500.0f;
		ShootAxis.XValue = -500.0f;
	}
	//Walk right
	else if (pInputs->KeyPressed(DIK_D))
	{
		InputAxis.XValue = 500.0f;
		ShootAxis.XValue = 500.0f;
	}
	else
	{
		//Check InputAxis to not shoot a bullet with 0 velocity
		InputAxis.XValue = 0.0f;
		if (InputAxis.YValue != 0.0f)
		{
			ShootAxis.XValue = 0.0f;
		}
	}
}

/*
The shoot function checks mouse input and cooldown,
creates a new projectile GameObject and adds it to the manager
*/
void InputComponent::Shoot(float frameTime, GameObject* pOwner)
{
	//Check mouse input since last frame
	pInputs->SampleMouse();
	//If left mouse button is clicked and cooldown is over
	if (pInputs->IfMouseLeftDown() && ShootReady <= 0.0f)
	{
		//Play ShootSound
		MySoundEngine* SoundEngine = MySoundEngine::GetInstance();
		SoundIndex Sound = SoundEngine->LoadWav(ShootSound);
		SoundEngine->SetVolume(Sound, -1000);
		SoundEngine->Play(Sound);

		//Spawn from player position + 
		//an offset of 50.0f towards the shooting direction
		Vector2D mPosition = pOwner->getPosition() + ShootAxis.unitVector()*50.0f;
		//Create components for the projectile
		std::vector<Component*> ShootComponents;

		RenderComponent* ShootRender = new RenderComponent(L"Assets/fireball.png", mPosition, 0.0f, 2.0f, 0.0f);
		CircularCollisionComponent* ShootCollision = new CircularCollisionComponent(mPosition, ShootRender->getScale()*15.0f);
		PhysicsComponent* ShootPhysics = new PhysicsComponent(ShootAxis * 2, 24.0f);
	
		ShootComponents.push_back(ShootRender);
		ShootComponents.push_back(ShootCollision);
		ShootComponents.push_back(ShootPhysics);

		//Create and add object
		GameObject* Projectile = new GameObject(mPosition, ShootComponents, GameObjectType::PLAYERPROJECTILE);
		pManager->AddObject(Projectile);

		//Reset timer
		ShootReady = ShootCooldown;
	}
	//Reduce timer by frame time
	else ShootReady -= frameTime;
}



