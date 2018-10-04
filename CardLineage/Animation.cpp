#include "Animation.h"



Animation::Animation(std::string _filename, std::string _sound, int _width, int _height, int _maxHor, int _maxVert, float _speed, SDL_Rect _position)
{
	m_filename = _filename;
	m_sound = _sound;
	m_maxHor = _maxHor;
	m_maxVert =_maxVert;
	m_frameTime =_speed;
	m_position = _position;

	m_cell.x = 0;
	m_cell.y = 0;
	m_cell.w = _width;
	m_cell.h = _height;

	m_frame = 0;
	m_row = 0;
	m_currentTime = 0;

}


Animation::~Animation()
{
}

void Animation::Draw()
{
	SpriteFactory::Draw(m_filename, m_position, m_cell);
}

bool Animation::Update(float _time)
{
	m_currentTime += _time;
	while (m_currentTime >= m_frameTime)
	{
		m_frame += 1;
		if (m_frame >= m_maxHor)
		{
			m_frame = 0;
			m_row++;
			if (m_row >= m_maxVert)
			{
				m_row = 0;
				return true;
			}
		}
		m_cell.x = m_frame * m_cell.w;
		m_cell.y = m_row * m_cell.h;
		m_currentTime -= m_frameTime;
	}
	return false;
}