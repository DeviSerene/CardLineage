#include "Text.h"



Text::Text(SDL_Renderer* _renderer, std::string& _text, SDL_Color _colour, int _textsize, int _x, int _y, int _w)
{
	_TTF_Font* font = TTF_OpenFont("assets/OpenSansRegular.ttf", _textsize); //font and fontsize

	SDL_Surface* surfaceText = TTF_RenderText_Solid(font, _text.c_str(), _colour);

	m_texture = SDL_CreateTextureFromSurface(_renderer, surfaceText); //convert the surface into a texture

	m_position.x = _x;
	m_position.y = _y;
	if (_w == 0)
		m_position.w = surfaceText->w;
	else
		m_position.w = _w;
	m_position.h = surfaceText->h;
	m_renderer = _renderer;

	SDL_FreeSurface(surfaceText); //free the surface
	surfaceText = nullptr;

	TTF_CloseFont(font);
	font = nullptr;

}

Text::~Text()
{
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;

	m_renderer = nullptr;
}

void Text::DrawText()
{
	
	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_position); //send the text to the renderer
}

void Text::DrawText(SDL_Rect _position)
{
	SDL_RenderCopy(m_renderer, m_texture, NULL, &_position); //send the text to the renderer
}

void Text::DrawText(int _x, int _y, int _w)
{
	m_newPosition.x = _x;
	m_newPosition.y = _y;
	m_newPosition.h = m_position.h;
	if (_w > 0)
	{
		m_newPosition.w = _w;
	}
	else
	{
		m_newPosition.w = m_position.w;
	}
	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_newPosition); //send the text to the renderer
}

void Text::CenterAt(SDL_Rect _pos)
{
	m_newPosition = _pos;
	if (_pos.w > m_position.w)
	{
		m_newPosition.x = _pos.x + ((_pos.w - m_position.w)/2);
		m_newPosition.w = m_position.w;
	}
	else
	{
		m_newPosition.w = _pos.w;
	}
	if (_pos.h <= 0)
	{
		m_newPosition.h = m_position.h;
	}
	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_newPosition); //send the text to the renderer
}