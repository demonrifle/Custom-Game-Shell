/*
Author : w17012919

The RenderComponent Class draws a single image on the screen to represent objects.

It controls the position, angle, scale, transparency and the image used.
Each parameter can be individually changed, but position and angle are updated every frame based on the parent GameObject it is attached to.

*/

#pragma once
#include "Component.h"
#include "mydrawengine.h"
class GameObject;

class RenderComponent :
	public Component
{
protected :

	//Image and MyDrawEngine to use
	MyDrawEngine* DrawEngine;
	PictureIndex image;

	//Image parameters.
	Vector2D Position;
	float Scale;
	//The angle goes from 0.0f to 3.14 for a full 360 loop
	float Angle;
	//Transparency is full at 0.0f and invisible at 1.0f
	float Transparency;

public :

	//Constructors
	RenderComponent();
	RenderComponent(const wchar_t* mImage, Vector2D mPosition, float mAngle);
	RenderComponent(const wchar_t* mImage, Vector2D mPosition, float mAngle, float mScale,  float mTransparency);
	//Destructor
	virtual ~RenderComponent();

	//Update function called each frame
	void Update(GameObject* pOwner);
	//Render
	void Render();

	//Individual setters.
	void setPosition(Vector2D mPosition);
	void setScale(float mScale);
	void setAngle(float mAngle);
	void setTransperancy(float mTransparency);

	//Individual getters
	Vector2D getPosition();
	float getScale();
	float getAngle();
	float getTransparency();
};

