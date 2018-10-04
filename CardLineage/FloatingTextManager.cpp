#include "FloatingTextManager.h"



FloatingTextManager::FloatingTextManager(SDL_Renderer* _renderer)
{
	m_renderer = _renderer;
}


FloatingTextManager::~FloatingTextManager()
{
}


void FloatingTextManager::AddNewText(std::string _text, int _x, int _y, int _r, int _g, int _b)
{
	m_texts.push_back((std::shared_ptr<FloatingText>)new FloatingText(m_renderer, _text, _x, _y, _r, _g, _b));
}

void FloatingTextManager::Update(float& _deltaTime)
{
	for (int i = 0; i < m_texts.size(); i++)
	{
		if (m_texts[i]->Update(_deltaTime))
		{
			//if true, we should delete it
			m_texts.erase(m_texts.begin() + i);
			i--;
		}
	}
}

void FloatingTextManager::Draw()
{
	for each (std::shared_ptr<FloatingText> text in m_texts)
	{
		text->Draw();
	}
}