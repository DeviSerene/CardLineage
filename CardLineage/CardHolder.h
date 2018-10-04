#pragma once
#include "Card.h"
#include "Stats.h"
#include "SpriteFactory.h"
#include "TextBox.h"
#include <memory>

class CardHolder
{
public:
	CardHolder();
	CardHolder(int _col, std::shared_ptr<Stats> _stats, std::shared_ptr<Card> _card);
	CardHolder(int _col, int _col2, std::shared_ptr<Stats> _stats, std::shared_ptr<Stats> _stats2, std::shared_ptr<Card> _card);
	~CardHolder();
	void Set(SDL_Rect _position, int _col, std::shared_ptr<Stats> _stats, std::shared_ptr<Card> _card);
	void Set(SDL_Rect _position, int _col, std::shared_ptr<Stats> _stats, std::shared_ptr<Stats> _stats2, std::shared_ptr<Card> _card);
	void Draw();
	void DrawAt(SDL_Rect _pos);
	void SetPosition(SDL_Rect _pos) { m_position = _pos; }
	void UpdatePosition(SDL_Rect _pos);
	SDL_Rect GetPos() { return m_position; }
	int GetCol() { return  m_col; }
	std::string GetName() { return m_card->GetName(); }
	std::shared_ptr<Card> GetCard() { return m_card; }
	std::shared_ptr<Stats> GetStats() { return m_stats; }
	std::shared_ptr<Stats> GetStats2() { return m_stats2; }
	void SetText();
private:
	SDL_Rect m_position;
	int m_col;
	std::shared_ptr<Stats> m_stats;
	std::shared_ptr<Stats> m_stats2; //for combocards
	std::shared_ptr<Card> m_card;

	std::shared_ptr<Text> m_nameText;
	std::shared_ptr<TextBox> m_description;
	std::string m_desc;

};

