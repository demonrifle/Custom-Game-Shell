/*
Author : w17012919

This RenderComponent class draws a single image on the screen to represent objects.

It controls the position, angle, scale, transparency and the image used.
Each parameter can be individually changed, but position and angle are updated every frame based on the parent GameObject it is attached to.

*/

#pragma once
#include "RenderComponent.h"
#include "GameObject.h"

/*
Default Constructor.
*/
RenderComponent::RenderComponent()
{
	DrawEngine = MyDrawEngine::GetInstance();
	image = NULL;
	setPosition(Vector2D(0.0f,0.0f));
	setAngle(0.0f);
	setScale(1.0f);
	setTransperancy(0.0f);
}


/*
Constructor for the RenderComponent for any images.
Takes in the initial image and variables to set
*/
RenderComponent::RenderComponent(const wchar_t* mImage, Vector2D mPosition, float mAngle, float mScale,  float mTransparency)
{
	//Get MyDrawEngine singleton
	DrawEngine = MyDrawEngine::GetInstance();
	//Load image
	image = DrawEngine->LoadPicture(mImage);
	//Load other parameters
	setPosition(mPosition);
	setAngle(mAngle);
	setScale(mScale);
	setTransperancy(mTransparency);
	TypeOfComponent = ComponentType::RENDER;
}


/*
Constructor for the RenderComponent using default values for scale 1.0f and transparency 0.0f.
Takes in the initial image and variables to set.
*/
RenderComponent::RenderComponent(const wchar_t* mImage, Vector2D mPosition, float mAngle)
{
	//Get MyDrawEngine singleton
	DrawEngine = MyDrawEngine::GetInstance();
	//Load image
	image = DrawEngine->LoadPicture(mImage);
	//Load other parameters
	setPosition(mPosition);
	setAngle(mAngle);
	//Set default values
	Scale = 1.0f;
	Transparency = 0.0f;
	TypeOfComponent = ComponentType::RENDER;
}

/*
Destructor
*/
RenderComponent::~RenderComponent()
{
}

/*
Update of the image, GameObject to get position and angle for next frame update.
*/
void RenderComponent::Update(GameObject* pOwner)
{
	//Set new position according to owner
	setPosition(pOwner->getPosition());
	//Set new angle according to owner
	setAngle(pOwner->getAngle());
	//Redraw image
	Render();
}

/*
Render redraws the image every time it is called.
*/
void RenderComponent::Render()
{
	DrawEngine->DrawAt(Position, image, Scale, Angle, Transparency);
}


void RenderComponent::setPosition(Vector2D mPosition)
{
	Position = mPosition;
}

void RenderComponent::setScale(float mScale)
{
	Scale = mScale;
}

void RenderComponent::setAngle(float mAngle)
{
	Angle = mAngle;
}

void RenderComponent::setTransperancy(float mTransparency)
{
	Transparency = mTransparency;
}

Vector2D RenderComponent::getPosition()
{
	return Position;
}

float RenderComponent::getScale()
{
	return Scale;
}

float RenderComponent::getAngle()
{
	return Angle;
}

float RenderComponent::getTransparency()
{
	return Transparency;
}
