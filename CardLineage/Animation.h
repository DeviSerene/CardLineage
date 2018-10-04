#pragma once
#include <SDL.h>
#include <string>
#include "SpriteFactory.h"
#include "AudioManager.h"

//this class plays an animation
//once the animation has finished, it will return true on Update, ready for deletion
class Animation
{
public:
	Animation(std::string _filename, std::string _sound, int _width, int _height, int _maxHor, int _maxVert, float _speed, SDL_Rect _position);
	~Animation();
	void Draw();
	bool Update(float _time);
private:
	std::string m_filename;
	std::string m_sound;
	
	int m_maxHor, m_maxVert; //the number of frames in the animation

	int m_frame; //the current frame the animation is on |0|1|2|3
	int m_row; //the current animation row we are on	
	SDL_Rect m_position; //where to draw the animation
	SDL_Rect m_cell; //the rect of the animation sheet to be drawn

	float m_currentTime; //the total time this animation has been playing
	float m_frameTime; //time it takes to go to the next frame
};

