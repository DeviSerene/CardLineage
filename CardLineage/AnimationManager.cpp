#include "AnimationManager.h"



AnimationManager::AnimationManager()
{
	//here is where we would load a file, which will give us all the animations in the game to choose from?
}


AnimationManager::~AnimationManager()
{
	//for each (Animation* ani in m_animations)
	//{
	//	delete ani;
	//}
	m_animations.clear();
}

void AnimationManager::Draw()
{
	for each (std::shared_ptr<Animation> ani in m_animations)
	{
		ani->Draw();
	}
}

void AnimationManager::Update(float& _deltaTime)
{

	if (!m_animations.empty())
	{
		for (int i = 0; i < m_animations.size(); i++)
		{
			if (m_animations[i]->Update(_deltaTime))
			{
				//delete m_animations[i];
				m_animations.erase(m_animations.begin() + i);
				--i;
			}
		}
	}
}

void AnimationManager::AddAnimation(int _animationID, SDL_Rect _position)
{
	switch (_animationID)
	{
	case 0:
		m_animations.push_back(std::shared_ptr<Animation>(new Animation("assets/animation.png", "", 100, 100, 4, 5, 0.2f, _position)));
		break;
	case 1:
		m_animations.push_back(std::shared_ptr<Animation>(new Animation("assets/battle/fire.png", "", 100, 100, 4, 1, 0.2f, _position)));
		break;
	case 2:
		m_animations.push_back(std::shared_ptr<Animation>(new Animation("assets/battle/cure.png", "", 100, 100, 4, 1, 0.2f, _position)));
		break;
	}
}