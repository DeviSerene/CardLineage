#pragma once
#include <SDL.h>
#include "Sprite.h"
#include <vector>
#include <string>

class SpriteFactory //an organisational class that allows me to draw multiples of the same sprite, saving memory
{
public:
	static void SetRenderer(SDL_Renderer* _renderer) {m_renderer = _renderer;} //the sprite factory now has a reference to the renderer, so it can create sprites
	
	static void Draw(std::string _name, SDL_Rect _position) {GetSprite(_name, _position)->Draw(); }
	static void Draw(std::string _name, SDL_Rect _position, Uint8 _r, Uint8 _g, Uint8 _b) { GetSprite(_name, _position)->DrawTint(_r,_g,_b); }
	static void Draw(std::string _name, SDL_Rect _position, SDL_Rect& _cellRect) { GetSprite(_name, _position)->AniDraw(_cellRect); } //two Draws, for static/animation
	static void Draw(std::string _name, SDL_Rect _position, SDL_Rect& _cellRect, Uint8 _r, Uint8 _g, Uint8 _b) { GetSprite(_name, _position)->TintAniDraw(_cellRect, _r, _g, _b); } //two Draws, for static/animation

	static SDL_Renderer* GetRenderer() { return m_renderer; }

private:
	SpriteFactory();
	~SpriteFactory();

	static std::shared_ptr<Sprite> GetSprite(std::string& _name, SDL_Rect& _position); //return a sprite from the spritelist, or call Create Sprite
	static void CreateSprite(std::string& _name, SDL_Rect& _position); //adds a sprite to spritelist

	static SDL_Renderer* m_renderer; //a reference to the renderer, for the creation of sprites
	static std::vector<std::shared_ptr<Sprite>> m_spriteList; //a list of all sprites in memory.
};

