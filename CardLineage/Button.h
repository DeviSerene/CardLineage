#pragma once
#include <SDL.h>
#include "SpriteFactory.h"
#include <functional>

// template <class T>
class Button
{
public:
	Button();
	Button(std::string _image, SDL_Rect _pos, bool _visible);
	~Button();
	void SetRect(SDL_Rect _new) { m_position = _new; }
	void SetVisibility(bool _visible) { m_visible = _visible; }
//	void SetFunction(std::function<void(class T)> _function) { m_function = _function; }

	void Draw();
	bool MouseRect(int _x, int _y);
private:
	std::string m_image;
	SDL_Rect m_position;
	bool m_visible;
//	std::function<void(T)> m_function;
};

