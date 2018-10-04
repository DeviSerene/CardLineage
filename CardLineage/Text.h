#pragma once
#include <SDL.h>
#include <iostream>
#include <string.h>
#include <SDL_ttf.h>

class Text
{
public:
	Text(SDL_Renderer* _renderer, std::string& _text, SDL_Color _colour, int _textsize, int _x, int _y, int _w = 0);
	~Text();
	void DrawText();
	void DrawText(SDL_Rect _position);
	void DrawText(int _x, int _y, int _w = 0);
	void CenterAt(SDL_Rect _pos);
	SDL_Rect GetPos() { return m_position; }

	void SetAlpha(int _alpha) { SDL_SetTextureAlphaMod(m_texture, _alpha); }
	void SetXY(int _x, int _y) { m_position.x = _x; m_position.y = _y; }
private:
	SDL_Texture* m_texture;
	SDL_Rect m_position;
	SDL_Renderer* m_renderer;
	SDL_Rect m_newPosition;
};

