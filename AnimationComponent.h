/*
Author : w17012919

This AnimationComponent class is an extension of the RenderComponent and uses an array of images to simulate animations.

It controls the position, angle, scale, transparency and the array of images used.
Each parameter can be individually changed, but position and angle are updated every frame based on the parent GameObject it is attached to.

*/

#pragma once
#include "RenderComponent.h"
class AnimationComponent :
	public RenderComponent
{
private :

	//Animation vector array and index.
	std::vector<PictureIndex> Animation;
	int AnimationIndex;
	//Image change delay speed.
	float AnimationDelay;
	//Current image duration
	float AnimationTime;

public :

	//Constructors
	AnimationComponent(std::vector<const wchar_t*> mAnimation, Vector2D mPosition, float mAngle);
	AnimationComponent(std::vector<const wchar_t*> mAnimation, Vector2D mPosition, float mAngle, float mScale, float mTransparency);
	//Destructor
	~AnimationComponent();

	//Update 
	void Update(GameObject* pOwner) override;
	//Render/Draw function
	void Render(int index);
};

