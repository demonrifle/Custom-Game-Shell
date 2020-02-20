/*
Author : w17012919

This AnimationComponent class is an extension of the RenderComponent and uses an array of images to simulate animations.

It controls the position, angle, scale, transparency and the array of images used.
Each parameter can be individually changed, but position and angle are updated every frame based on the parent GameObject it is attached to.

*/

#include "AnimationComponent.h"
#include "GameObject.h"
#include <iostream>

/*
Parameterized constructor using an array of pictures to loop trough,
position and angle
*/
AnimationComponent::AnimationComponent(std::vector<const wchar_t*> mAnimation, Vector2D mPosition, float mAngle)
{
	//Sets Component type
	TypeOfComponent = ComponentType::RENDER;

	//Get singleton MyDrawEngine
	DrawEngine = MyDrawEngine::GetInstance();
	//For each local path to object
	for (const wchar_t* Sprite : mAnimation)
	{
		//Create new PictureIndex
		PictureIndex image = DrawEngine->LoadPicture(Sprite);
		//Add it to animation array
		Animation.push_back(image);
	}
	//Set other parameters
	Position = mPosition;
	Angle = mAngle;

	//Set default values
	AnimationIndex = 0;
	Scale = 1.0f;
	Transparency = 0.0f;

	//The delay has been tested to create a good transition at 1.0f speed
	AnimationDelay = 0.1f;
	AnimationTime = 0.0f;
}

/*
Parameterized constructor using an array of pictures to loop trough,
position, angle, scale and transparency;
*/
AnimationComponent::AnimationComponent(std::vector<const wchar_t*> mAnimation, Vector2D mPosition, float mAngle, float mScale, float mTransparency)
{
	//Get singleton MyDrawEngine
	DrawEngine = MyDrawEngine::GetInstance();
	//For each local path to object
	for (const wchar_t* Sprite : mAnimation)
	{
		//Create new PictureIndex
		PictureIndex image = DrawEngine->LoadPicture(Sprite);
		//Add it to animation array
		Animation.push_back(image);
	}
	//Set other parameters
	Position = mPosition;
	Angle = mAngle;
	Scale = mScale;
	Transparency = mTransparency;

	//Set default values
	AnimationIndex = 0;
	TypeOfComponent = ComponentType::RENDER;

	//The delay has been tested to create a good transition at 1.0f speed
	AnimationDelay = 0.1f;
	AnimationTime = 0.0f;
}

/*
Destructor
*/
AnimationComponent::~AnimationComponent()
{
}

/*
Update of the animation component with the parent GameObject
*/
void AnimationComponent::Update(GameObject* pOwner)
{
	//Set the position to parent
	setPosition(pOwner->getPosition());
	//Set the angle to parent
	setAngle(pOwner->getAngle());
	//Render image at AnimationIndex
	Render(AnimationIndex);

	//Add the frameTime to the active image time,
	AnimationTime += pOwner->getFrameTime();

	//If the current image has been active more than the delay,
	if (AnimationTime > AnimationDelay)
	{
		//Change the image and reset the timer.
		AnimationIndex = (AnimationIndex + 1) % (Animation.size());
		AnimationTime = 0.0f;
	}
}

//Redraw an image on the screen, based on the passed index
void AnimationComponent::Render(int index)
{
	DrawEngine->DrawAt(Position, Animation[index], Scale, Angle, Transparency);
}
