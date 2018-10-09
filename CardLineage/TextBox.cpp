#include "TextBox.h"



TextBox::TextBox(std::string& _text, SDL_Renderer* _renderer, SDL_Color _colour, SDL_Rect _position, int _textsize)
{
	_TTF_Font* font = TTF_OpenFont("assets/OpenSansRegular.ttf", _textsize); //font and fontsize
	int w, h;

	std::string text;

	TTF_SizeText(font, _text.c_str(), &w, &h); //get the size of the entire text string in the font
	int textLength;
	float division = ((float)w / (float)_position.w);
	if (division != 0)
		textLength = _text.size() / division; //the max length of the sentences
	else
		textLength = _text.size();
	
	std::vector <std::string> words;
	std::string word; //divide the text into words
	for (int i = 0; i < _text.length(); i++)
	{
		if (_text.at(i) == ' ' || i == _text.length())
		{
			words.push_back(word);
			word.clear();
		}
		else
		{
			word += _text.at(i);
		}
	}
	if(word != "")
		words.push_back(word);

	int heightMultiply = 0;
	for (int i = 0; i < words.size(); i++)
	{
		text = words[i];
		if (i < words.size() -1)
		{
			while ((text.length() + words[i + 1].length() + 1) <= textLength)
			{
				text += " ";
				text += words[i + 1];
				i++;
				if (i >= words.size() -1)
				{
					break;
				}
			}
		}
		m_text.push_back(std::shared_ptr<Text>(new Text(_renderer, text, _colour, _textsize, _position.x, _position.y + (h*heightMultiply))));
		heightMultiply++;
	}

	/*
	for (float i = 0; i < (float)w / (float)_position.w; i++)
	{
		text.assign(_text, i * textLength, textLength);
		m_text.push_back(new Text(_renderer, text, _colour, _position.x, _position.y + (h*i), _textsize));
	}
	*/

	TTF_CloseFont(font);
	font = nullptr;
}


TextBox::~TextBox()
{
	for each (std::shared_ptr<Text> text in m_text)
	{
		//delete text; 
		text = nullptr;
	}
}

void TextBox::Draw()
{
	for each (std::shared_ptr<Text> text in m_text)
	{
		text->DrawText();
	}
}


void TextBox::Draw(SDL_Rect _pos)
{
	//find out the difference in x and y
	int xDif = _pos.x - m_text[0]->GetPos().x;
	int yDif = _pos.y - m_text[0]->GetPos().y;
	SDL_Rect newPos;

	for (int i = 0; i < m_text.size(); i++)
	{
		newPos = m_text[i]->GetPos();
		newPos.x += (xDif);
		newPos.y += (yDif);
		if(newPos.w > _pos.w)
			newPos.w = _pos.w;

		m_text[i]->DrawText(newPos);
	}
}