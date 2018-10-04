#pragma once
#include "Animation.h"
#include <vector>
#include <memory>

//when you want an animation to come up, you just want to say "this animation, this location"
//not deal with all the animation creation and then clean up
//this will manage the animations, you just need to Add them, and call the Draw and Updates
class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();
	void Draw();
	void Update(float& _deltaTime);
	void AddAnimation(int _animationID, SDL_Rect _position);
private:
	std::vector <std::shared_ptr<Animation>> m_animations;
	std::vector <std::shared_ptr<Animation>> m_templates;
};

