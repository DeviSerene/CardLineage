#pragma once
#include"FloatingText.h"
#include<vector>
#include <memory>

class FloatingTextManager
{
public:
	FloatingTextManager(SDL_Renderer* _renderer);
	~FloatingTextManager();

	void AddNewText(std::string _text, int _x, int _y, int _r, int _g, int _b);
	void Update(float& _deltaTime);
	void Draw();


private:
	std::vector<std::shared_ptr<FloatingText>> m_texts;
	SDL_Renderer* m_renderer;

};

