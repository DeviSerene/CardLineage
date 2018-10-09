#include "CardHolder.h"



CardHolder::CardHolder()
{
	m_desc = "Description goes here";
	m_position = { 10,10,10,10 };
}

CardHolder::CardHolder(int _col, std::shared_ptr<Stats> _stats, std::shared_ptr<Card> _card)
{
	m_desc = "Description goes here";
	m_position = { 10,10,10,10 };
	m_col = _col;
	m_stats = _stats;
	m_card = _card;
}

CardHolder::CardHolder(int _col, int _col2, std::shared_ptr<Stats> _stats, std::shared_ptr<Stats> _stats2, std::shared_ptr<Card> _card)
{
	m_desc = "Description goes here";
	m_position = { 10,10,10,10 };
	if (_col < _col2)
	{
		m_col = (_col * 10) + _col2;
	}
	else
	{
		m_col = (_col2 * 10) + _col;
	}
	m_stats = _stats;
	m_stats2 = _stats2;
	m_card = _card;
}


CardHolder::~CardHolder()
{
	//CardHolder shouldn't delete the Card or Stats, but it should delete its textboxes
//	delete m_card;
//	delete m_stats;

	m_card = nullptr;
	m_stats = nullptr;

	if (m_nameText != nullptr)
	{
//		delete m_nameText;
		m_nameText = nullptr;
	}
	if (m_description != nullptr)
	{
//		delete m_description;
		m_description = nullptr;
	}
}


void  CardHolder::Set(SDL_Rect _position, int _col, std::shared_ptr<Stats> _stats, std::shared_ptr<Card> _card)
{
	m_desc = "Description goes here";
	m_position = _position;
	m_col = _col;
	m_stats = _stats;
	m_card = _card;

	SetText();
}

void  CardHolder::Set(SDL_Rect _position, int _col, std::shared_ptr<Stats> _stats, std::shared_ptr<Stats> _stats2, std::shared_ptr<Card> _card)
{
	m_desc = "Description goes here";
	m_position = _position;
	m_col = _col;
	m_stats = _stats;
	m_stats2 = _stats2;
	m_card = _card;

	SetText();
}

void CardHolder::Draw()
{
	SpriteFactory::Draw("assets/cards/Bkg_" + std::to_string(m_col) + ".png", m_position); //draw the bkg 
	SpriteFactory::Draw("assets/cards/card.png", m_position); //draw the border
	SpriteFactory::Draw("assets/cards/ability_" + std::to_string(m_card->GetImage()) + ".png", m_position); //draw the card image
	SpriteFactory::Draw("assets/cards/mana_" + std::to_string(m_card->GetMana()) + ".png", m_position); //draw the card image
	SpriteFactory::Draw("assets/cards/target_" + std::to_string(m_card->GetTarget()) + ".png", m_position); //draw the card image


	//pos.w = 150; pos.h = 212;
	if (m_nameText != nullptr)
	{
		m_nameText->CenterAt({ m_position.x + (int)(0.1f * (float)m_position.w), m_position.y + (int)(0.07f * (float)m_position.h), m_position.w - (int)(0.2f * (float)m_position.w), 0 });
		m_description->Draw({ m_position.x + (int)(0.1f * (float)m_position.w), m_position.y + (int)(0.47f * (float)m_position.h), m_position.w - (int)(0.2f * (float)m_position.w), m_position.h });
	}
}

void CardHolder::DrawAt(SDL_Rect _pos)
{
	//this draw function is a bit more expensive, as it remakes the text, useful for when you want to draw the cards in a specific and possibly changing location
	UpdatePosition(_pos);
	SpriteFactory::Draw("assets/cards/Bkg_" + std::to_string(m_col) + ".png", _pos); //draw the bkg 
	SpriteFactory::Draw("assets/cards/card.png", _pos); //draw the border
	SpriteFactory::Draw("assets/cards/ability_" + std::to_string(m_card->GetImage()) + ".png", _pos); //draw the card image
	SpriteFactory::Draw("assets/cards/mana_" + std::to_string(m_card->GetMana()) + ".png", _pos); //draw the card image
	SpriteFactory::Draw("assets/cards/target_" + std::to_string(m_card->GetTarget()) + ".png", _pos); //draw the card image


																											//pos.w = 150; pos.h = 212;
	if (m_nameText != nullptr)
	{
		m_nameText->CenterAt({ _pos.x + (int)(0.1f * (float)_pos.w), _pos.y + (int)(0.07f * (float)_pos.h), _pos.w - (int)(0.2f * (float)_pos.w), 0 });
		m_description->Draw({ _pos.x + (int)(0.1f * (float)_pos.w), _pos.y + (int)(0.47f * (float)_pos.h), _pos.w - (int)(0.2f * (float)_pos.w), _pos.h });
	}
}

void CardHolder::UpdatePosition(SDL_Rect _pos)
{ 
	m_position = _pos; 
	SetText();
	
}

void CardHolder::SetText()
{
	SDL_Color col = { 0,0,0,255 };
	if (m_nameText != nullptr)
	{
	//	delete m_nameText;
		//std::cout << "Deleted Text \n";

		m_nameText = nullptr;
	}
	m_nameText = std::shared_ptr<Text>(new Text(SpriteFactory::GetRenderer(), m_card->GetName(), col, abs((int)(0.1f * (float)m_position.w)), 15, 25));
	//std::cout << "Created Text \n";

	if (m_description != nullptr)
	{
	//	delete m_description;
		m_description = nullptr;
	}

	m_desc = "";
	for (int i = 0; i < m_card->GetEffects().size(); i++)
	{
		if(!m_card->IsCC())
			m_desc += m_card->GetEffects()[i]->GetDescription(m_stats);
		else
			m_desc += m_card->GetEffects()[i]->GetDescription(m_stats, m_stats2);
	}
	int w = m_position.w - (int)(0.3f * (float)m_position.w);
	if (w <= 0)
		w = 1;
	m_description = std::shared_ptr<TextBox>(new TextBox(m_desc, SpriteFactory::GetRenderer(), col, { m_position.x + 15, m_position.y + 100, w, m_position.h }, abs((int)(0.075f * (float)m_position.w))));
}