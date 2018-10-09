#include "BattleDeck.h"
#include <algorithm>


BattleDeck::BattleDeck()
{
	m_highC = -1;
	m_cardsToDraw = 0;
	m_highlightCard = nullptr;
	m_drawDrawDeck = false;
	m_discardAni = false;
	m_aniFin = false;
}


BattleDeck::~BattleDeck()
{
	//delete all cardHolders in piles
	//clear piles
	if (!m_DrawPile.empty())
	{
//		for each (CardHolder* var in m_DrawPile)
//		{
//			delete var;
//		}
		m_DrawPile.clear();
	}

	if (!m_DiscardPile.empty())
	{
//		for each (CardHolder* var in m_DiscardPile)
//		{
//			delete var;
//		}
		m_DiscardPile.clear();
	}

	if (!m_Exiled.empty())
	{
//		for each (CardHolder* var in m_Exiled)
//		{
//			delete var;
//		}
		m_Exiled.clear();
	}

	//clear the chand
	if (!m_ComboHand.empty())
	{
//		for each (CardHolder* var in m_ComboHand)
//		{
//			delete var;
//		}
		m_ComboHand.clear();
	}

	if (m_highlightCard != nullptr)
	{
//		delete m_highlightCard;
		m_highlightCard = nullptr;
	}
}


void BattleDeck::InitCharacter(std::vector <std::shared_ptr<Card>> _card, std::vector <int> _cards, std::shared_ptr<Stats> _stats, int _col)
{
	//add the characters cards to the drawpile with this colour
	for (int i = 0; i < _cards.size(); i++)
	{

		m_DrawPile.push_back(std::shared_ptr<CardHolder>(new CardHolder(_col, _stats, _card[_cards[i]])));
	}
}

void BattleDeck::ShuffleDraw()
{
	//Shuffle the Draw Pile

	std::random_shuffle(m_DrawPile.begin(), m_DrawPile.end());
}

void BattleDeck::ShuffleDiscardToDraw()
{
	m_drawDrawDeck = false;
	//start the animation
	if (!m_discardAni && !m_drawAni && !m_discardHandAni && !m_reshuffleAni) //can't perform this action if alraedy in another card animation type
	{
		if (!m_DiscardPile.empty())
		{
			m_time = 0;
			m_reshuffleAni = true;
			m_xSpeed = (1500.0f - 10.0f) / 2.0f;
			m_ySpeed = 400.0f;
			m_hSpeed = 85.0f;
			m_ShuffleRect = { 1515,779,75,111 };

			//shuffle the cards into the drawpile
			std::random_shuffle(m_DiscardPile.begin(), m_DiscardPile.end());

			for (int i = 0; i < m_DiscardPile.size(); i++)
			{
				m_DrawPile.push_back(m_DiscardPile[i]);
			}
			m_DiscardPile.clear();
		}
	}
}

void BattleDeck::ShuffleDDAni(float _deltaTime)
{
	if (m_reshuffleAni)
	{
		m_time += _deltaTime;
		if (m_time < 1.0f)
		{
			m_ShuffleRect.x -= m_xSpeed * _deltaTime;
			m_ShuffleRect.y -= m_ySpeed * _deltaTime;
			m_wSpeed = m_ShuffleRect.y;
		}
		else if (m_time < 3.0f)
		{
			if (m_time < 1.5f)
			{
				m_wSpeed -= m_hSpeed * _deltaTime;
			}
			else if (m_time < 2.0f)
			{
				m_wSpeed += m_hSpeed * _deltaTime;
			}
			else if (m_time < 2.5f)
			{
				m_wSpeed -= m_hSpeed * _deltaTime;
			}
			else
			{
				m_wSpeed += m_hSpeed * _deltaTime;
			}
		}
		else if (m_time < 4.0f)
		{
			m_ShuffleRect.x -= m_xSpeed * _deltaTime;
			m_ShuffleRect.y += m_ySpeed * _deltaTime;
		}
		else if (m_time > 4.25f)
		{
			m_reshuffleAni = false;
		}
	//	SpriteFactory::Draw("assets/cards/cardBack.png", m_ShuffleRect);
	}
}

void BattleDeck::DrawShuffleAni()
{
	if (m_reshuffleAni)
	{
		if (m_time < 3.0f)
		{
			if (m_time < 1.5f)
			{
				SpriteFactory::Draw("assets/cards/cardBack.png", { m_ShuffleRect.x, (int)m_wSpeed, m_ShuffleRect.w, m_ShuffleRect.h });
				SpriteFactory::Draw("assets/cards/cardBack.png", m_ShuffleRect);
			}
			else if (m_time < 2.0f)
			{
				SpriteFactory::Draw("assets/cards/cardBack.png", m_ShuffleRect);
				SpriteFactory::Draw("assets/cards/cardBack.png", { m_ShuffleRect.x, (int)m_wSpeed, m_ShuffleRect.w, m_ShuffleRect.h });
			}
			else if (m_time < 2.5f)
			{
				SpriteFactory::Draw("assets/cards/cardBack.png", { m_ShuffleRect.x, (int)m_wSpeed, m_ShuffleRect.w, m_ShuffleRect.h });
				SpriteFactory::Draw("assets/cards/cardBack.png", m_ShuffleRect);
			}
			else
			{
				SpriteFactory::Draw("assets/cards/cardBack.png", m_ShuffleRect);
				SpriteFactory::Draw("assets/cards/cardBack.png", { m_ShuffleRect.x, (int)m_wSpeed, m_ShuffleRect.w, m_ShuffleRect.h });
			}
		}
		else
		{
			SpriteFactory::Draw("assets/cards/cardBack.png", m_ShuffleRect);
		}
	}
}

void BattleDeck::DrawCard()
{//clear the chand
	if (!m_ComboHand.empty())
	{
	//	for each (CardHolder* var in m_ComboHand)
	//	{
	//		delete var;
	//	}
		m_ComboHand.clear();
	}
	m_drawDrawDeck = false;
	if (!m_DrawPile.empty())
	{
		if (!m_drawAni && !m_discardAni && !m_discardHandAni && !m_reshuffleAni)
		{//take the card at the front of the drawpile
			//m_Hand.push_back(m_DrawPile[0]);
			//m_DrawPile.erase(m_DrawPile.begin());
			m_drawAni = true;
			m_aniFin = false;
			m_xSpeed = ((1600.0f / 2.0f) - 75.0f) / 1.0f;
			m_ySpeed = ((779.0f) -300.0f) / 1.0f;
			m_wSpeed = -(75.0f / 0.50f);
			m_hSpeed = 111.0f / 1.0f;
			m_xPos = 10;
			m_yPos = 779;
			m_wPos = 75;
			m_hPos = 111;
			m_time = 0;
		}
	}
}

void BattleDeck::DiscardCard(int _i)
{
	//clear the chand
	if (!m_ComboHand.empty())
	{
	//	for each (CardHolder* var in m_ComboHand)
	//	{
	//		delete var;
	//	}
		m_ComboHand.clear();
	}

	m_drawDrawDeck = false;
	if (!m_Hand.empty() && m_Hand.size() > _i) //might just need to do "m_Hand.size() > _i" -  safety check to ensure we're not getting rid of a card that doesnt exist
	{
		if (!m_drawAni && !m_discardAni && !m_discardHandAni && !m_reshuffleAni)
		{//take the card at the front of the drawpile
		 //m_Hand.push_back(m_DrawPile[0]);
		 //m_DrawPile.erase(m_DrawPile.begin());
			m_discardAni = true;
			m_aniFin = false;
			//the position the card is at
			m_xPos = m_Hand[_i]->GetPos().x;
			m_yPos = m_Hand[_i]->GetPos().y;
			m_wPos = m_Hand[_i]->GetPos().w;
			m_hPos = m_Hand[_i]->GetPos().h;
			//the speed of the animation will play based on the distance to the discard pile
			//the discard pile is at {1515,779,75,111} //
			// speed = distance / time
			m_xSpeed = ((1515.0f) - m_xPos) / 1.0f;
			m_ySpeed = -((779.0f) - m_yPos) / 1.0f;
			m_wSpeed = -(150.0f / 0.50f);
			m_hSpeed = -100.0f / 1.0f;
			m_time = 0;
			//set the card from the hand to the discard pile
			m_DiscardPile.push_back(m_Hand[_i]);
			m_Hand.erase(m_Hand.begin() + _i);
		}
	}
}

void BattleDeck::DiscardCC(int _i)
{
	if (m_ComboHand.size() > _i && _i > -1 && !m_ComboHand.empty())
	{
	//	delete m_ComboHand[_i];
		m_ComboHand.erase(m_ComboHand.begin() + _i);

		if (m_combo[_i][0] > m_combo[_i][1])
		{
			m_DiscardPile.push_back(m_Hand[m_combo[_i][0]]);
			m_Hand.erase(m_Hand.begin() + m_combo[_i][0]);
			m_DiscardPile.push_back(m_Hand[m_combo[_i][1]]);
			m_Hand.erase(m_Hand.begin() + m_combo[_i][1]);
		}
		else
		{
			m_DiscardPile.push_back(m_Hand[m_combo[_i][1]]);
			m_Hand.erase(m_Hand.begin() + m_combo[_i][1]);
			m_DiscardPile.push_back(m_Hand[m_combo[_i][0]]);
			m_Hand.erase(m_Hand.begin() + m_combo[_i][0]);
		}

		//DiscardCard(m_combo[_i][0]);
		//DiscardCard((m_combo[_i][1])-1);

		m_combo.erase(m_combo.begin() + _i);
		UpdateHandPosition();
	}
}

void BattleDeck::DiscardHand()
{
	//clear the chand
	if (!m_ComboHand.empty())
	{
	//	for each (CardHolder* var in m_ComboHand)
	//	{
	//		delete var;
	//	}
		m_ComboHand.clear();
	}

	m_drawDrawDeck = false;
	if (!m_drawAni && !m_discardAni && !m_discardHandAni && !m_reshuffleAni)
	{
		m_discardHandAni = true;
		m_aniFin = false;
		m_time = 0;
		if (!m_discardSpeed.empty())
			m_discardSpeed.clear();
		for each (std::shared_ptr<CardHolder> card in m_Hand)
		{
			//1515,779,75,111
			Speed newSpeed((((1515.0f) - (float)card->GetPos().x) / 1.0f), (-((779.0f) - (float)card->GetPos().y) / 1.0f), (-(150.0f / 0.50f)), (-100.0f / 1.0f));
			m_discardSpeed.push_back(newSpeed);
		}
	}
}

void BattleDeck::SetHighlightCard(int _i, bool _comboDeck)
{
	if (_i < 0) //if asked to highlight a card below 0, then take that as a request to stop highlighting anything
	{
		m_highC = -1;
		if (m_highlightCard != nullptr)
		{
		//	delete m_highlightCard;
			m_highlightCard = nullptr;
		}
		m_comboHighlight.clear();
	}
	else if (!_comboDeck)
	{
		if (m_Hand.size() > _i && _i != m_highC) //if it is in the bounds of the handsize and is not requesting to highlight a card that is already highlighted
		{
			m_highC = _i;
			if (m_highlightCard != nullptr)
			{
			//	delete m_highlightCard;
				m_highlightCard = nullptr;
			}
			m_highlightCard = std::shared_ptr<CardHolder>(new CardHolder());
			m_highlightCard->Set({ 675,75,250,400 }, m_Hand[_i]->GetCol(), m_Hand[_i]->GetStats(), m_Hand[_i]->GetCard());
		}
	}
	else if (m_ComboHand.size() > _i && _i != m_highC) //if it is in the bounds of the handsize and is not requesting to highlight a card that is already highlighted
	{
		m_highC = _i;
		if (m_highlightCard != nullptr)
		{
		//	delete m_highlightCard;
			m_highlightCard = nullptr;
		}
		m_highlightCard = std::shared_ptr<CardHolder>(new CardHolder());
		m_highlightCard->Set({ 675,75,250,400 }, m_ComboHand[_i]->GetCol(), m_ComboHand[_i]->GetStats(), m_ComboHand[_i]->GetStats2(), m_ComboHand[_i]->GetCard());
		m_comboHighlight = m_combo[_i];
	}
}

void BattleDeck::DrawHand(int _selectedCard)
{
	if (!m_DrawPile.empty()) //draw the drawpile
	{
		if((!m_drawAni || m_DrawPile.size() > 1))
		SpriteFactory::Draw("assets/cards/cardBack.png", { 10,779,75,111 });
	}
	//{1515,779,75,111}
	if (!m_DiscardPile.empty()) //draw the discardpile
	{
		if ((!m_discardAni || m_DiscardPile.size() > 1) && !m_reshuffleAni)
			SpriteFactory::Draw("assets/cards/cardBack.png", { 1515,779,75,111 });
	}
	DrawShuffleAni();

	if (!m_discardHandAni)
	{
		if (!m_Hand.empty())
		{
			for (int i = 0; i < m_Hand.size(); i++)
			{
				if (_selectedCard == i)
				{
					m_Hand[i]->SetPosition({ m_Hand[i]->GetPos().x, 490 ,m_Hand[i]->GetPos().w,m_Hand[i]->GetPos().h });
					m_Hand[i]->Draw();
				}
				else
				{
					m_Hand[i]->Draw();
				}

			}
		}
		if (!m_ComboHand.empty())
		{

			if (!m_comboHighlight.empty())
			{
				for (int i = 0; i < m_comboHighlight.size(); i++)
				{
					SpriteFactory::Draw("assets/cards/cardShine.png", m_Hand[m_comboHighlight[i]]->GetPos());
				}
			}

			for (int i = 0; i < m_ComboHand.size(); i++)
			{
				if (_selectedCard-100 == i)
				{
					m_ComboHand[i]->DrawAt({ m_ComboHand[i]->GetPos().x, 715 ,m_ComboHand[i]->GetPos().w,m_ComboHand[i]->GetPos().h });
				}
				else
				{
					m_ComboHand[i]->Draw();
				}
			}

		}
	}
	else
	{
		for (int i = 0; i < m_Hand.size(); i++) //if discarding the hand, decide whether to draw the card or the back
		{
			if (m_discardSpeed[i].w < 0)
				m_Hand[i]->Draw();
			else
				SpriteFactory::Draw("assets/cards/cardBack.png", { m_Hand[i]->GetPos() });
		}
	}

	

	if (m_drawAni || m_discardAni) //draw the animated cards
	{
		if (m_drawAni) //when drawing a particular card
		{
			m_DrawPile[0]->UpdatePosition({ (int)m_xPos, (int)m_yPos, (int)m_wPos, (int)m_hPos });
			if (m_wSpeed > 0)
				m_DrawPile[0]->Draw();
			else
				SpriteFactory::Draw("assets/cards/cardBack.png", { (int)m_xPos, (int)m_yPos, (int)m_wPos, (int)m_hPos });
		}
		else if (m_discardAni) //when discarding a particular card
		{
			m_DiscardPile[m_DiscardPile.size()-1]->UpdatePosition({ (int)m_xPos, (int)m_yPos, (int)m_wPos, (int)m_hPos });
			if (m_wSpeed < 0)
				m_DiscardPile[m_DiscardPile.size() - 1]->Draw();
			else
				SpriteFactory::Draw("assets/cards/cardBack.png", { (int)m_xPos, (int)m_yPos, (int)m_wPos, (int)m_hPos });
		}
	}
	else
	{
		if (m_drawDrawDeck && !m_DrawPileSorted.empty())  //if inspecting a deck, draw a shade over the screen
		{
			SpriteFactory::Draw("assets/shade.png", { 0,0,1600,900 });
			DrawDeck(m_DrawPileSorted, 40, 50, 1);
		}
		else if (m_highlightCard) //draw the highlighted card
		{
			m_highlightCard->Draw();

		}
	}
	
}

void BattleDeck::UpdateHandPosition()
{
	//Update the positions of all the cards in the Hand
	//((1/2 * w) + 20) * nOfCards + (1/2 * w * i)
	//m_handPositions.clear();
	SDL_Rect pos;
	pos.x = 0;
	pos.y = 550;
	pos.w = 150;
	pos.h = 212;
	float sep = 20.0f;
	//(width / 2) + ((float(_deck.size()) / -2 + i)
	if (m_Hand.size() > 9)
	{
		pos.w -= 10 * (m_Hand.size() - 9);
		sep -= 1 * (m_Hand.size() - 8);
	}

	for (int i = 0; i < m_Hand.size(); i++)
	{
		//pos.x = ((pos.w / 2))*m_Hand.size() + ((pos.w+20) * i);
		pos.x = (1600 / 2) + ((float(m_Hand.size()) / -2 + i))* (pos.w + sep);
		m_Hand[i]->SetPosition(pos);
		//m_handPositions.push_back(&m_Hand[i]->GetPos());
	}
	RefreshCHand();
}

void BattleDeck::Update(float _deltaTime)
{
	HandleDrawDiscardAni(_deltaTime);
	ShuffleDDAni(_deltaTime);
}

void BattleDeck::DrawDeck(std::vector <std::shared_ptr<CardHolder>> _cards, int _x, int _y, float _scale)
{
	//when a player wants to check what is in the draw/discard pile, we need to show the cards on screen
	//this would be a big list
	//if we are drawing the draw pile, we typically need to organise the list
	//otherwise we should show the order it is in ->next card to draw for draw, or last card to be put in for discard

	SDL_Rect drawRect;

	for (int i = 0+(m_row*5); i <= (14 + (m_row * 5)) && i < _cards.size(); i++)
	{
		drawRect.x = 800 - ((150 * _scale)*2.5);
		drawRect.y = _y;
		drawRect.h = 212 * _scale;
		drawRect.w = 150 * _scale;
		drawRect.x += ((i % 5) * drawRect.w) + 5;
		drawRect.y += (((i - (m_row * 5)) / 5) * (drawRect.h+5));
		_cards[i]->DrawAt(drawRect);
	}

}

void BattleDeck::ChangeRow(int _i)
{
	//changing the view row when examining the decks
	if (_i > 0)
	{
		if (m_DrawPileSorted.size() > ((m_row + 3) * 5))
			m_row += _i;
	}
	else 
	{
		m_row += _i;
		if (m_row < 0)
		{
			m_row = 0;
		}
	}
}

bool BattleDeck::CanChangeRow(int _i)
{
	//changing the view row when examining the decks
	if (_i > 0)
	{
		if (m_DrawPileSorted.size() > ((m_row + 3) * 5))
			return true;
	}
	else
	{
		if (m_row > 0)
			return true;
	}
	return false;
}

void BattleDeck::ToggleDDD(bool _set, int _pile)
{
	if (!m_drawAni && !m_discardAni && !m_discardHandAni && !m_reshuffleAni)
	{
		m_drawDrawDeck = _set;// !m_drawDrawDeck;  //toogles whether to show the deck or not
		m_DrawPileSorted.clear(); //clear the sorted cards
		m_row = 0;
		if (m_drawDrawDeck == true)
		{
			if (GetPile(_pile).size() > 1)
			{
				if (_pile == 0)
				{
					//sort the cards via binary tree method
					BinaryTreeCardSorter sorter;
					BSTNode* root = NULL;
					root = sorter.CreateNewNode(m_DrawPile[0]);
					for (int i = 1; i < m_DrawPile.size(); i++)
					{
						sorter.Insert(root, m_DrawPile[i], root);
					}
					sorter.Sort(root);
					m_DrawPileSorted = sorter.GetData();
				}
				else
				{
					m_DrawPileSorted = GetPile(_pile);
				}
			}
			else if (GetPile(_pile).size() == 1)
			{
				m_DrawPileSorted = GetPile(_pile);
			}
			else
			{
				m_drawDrawDeck = false;
			}
		}
	}
}

void BattleDeck::RefreshCHand()
{
	//clear the chand
	if (!m_ComboHand.empty())
	{
		//for each (CardHolder* var in m_ComboHand)
		//{
		//	delete var;
		//}
		m_ComboHand.clear();
	}
	m_combo.clear();
	//check every card in the hand with every other card
	//if there is a valid combo combination, add that combocard to the combohand
	if (!m_Hand.empty())
	{
		for (int i = 0; i < m_Hand.size(); i++)
		{
			for (int j = i; j < m_Hand.size(); j++)
			{
				if (m_Hand[i]->GetCol() != m_Hand[j]->GetCol()) //cannot combo with itself
				{
					for (int c = 0; c < combocards.size(); c++) //check the combodeck
					{
						if ((combocards[c]->GetCCNeeded()[0] == m_Hand[i]->GetCard() && combocards[c]->GetCCNeeded()[1] == m_Hand[j]->GetCard()) 
							|| (combocards[c]->GetCCNeeded()[1] == m_Hand[i]->GetCard() && combocards[c]->GetCCNeeded()[0] == m_Hand[j]->GetCard()))
						{
							m_ComboHand.push_back(std::shared_ptr<CardHolder>(new CardHolder(m_Hand[i]->GetCol(), m_Hand[j]->GetCol(), m_Hand[i]->GetStats(), m_Hand[j]->GetStats(), combocards[c])));
							m_combo.push_back({ i,j });
						}
					}
				}
			}
		}
	}
	UpdateCCPosition();
}

void BattleDeck::UpdateCCPosition()
{
	if (!m_ComboHand.empty())
	{//Update the positions of all the cards in the Hand
	//((1/2 * w) + 20) * nOfCards + (1/2 * w * i)
	//m_handPositions.clear();
		SDL_Rect pos;
		pos.x = 0;
		pos.y = 780;
		pos.w = 75;
		pos.h = 106;
		float sep = 10.0f;
		//(width / 2) + ((float(_deck.size()) / -2 + i)
		if (m_ComboHand.size() > 9)
		{
			pos.w -= 10 * (m_Hand.size() - 9);
			sep -= 1 * (m_Hand.size() - 8);
		}

		for (int i = 0; i < m_ComboHand.size(); i++)
		{
			//pos.x = ((pos.w / 2))*m_Hand.size() + ((pos.w+20) * i);
			pos.x = (1600 / 2) + ((float(m_ComboHand.size()) / -2 + i))* (pos.w + sep);
			m_ComboHand[i]->SetPosition(pos);
			m_ComboHand[i]->SetText();
			//m_handPositions.push_back(&m_Hand[i]->GetPos());
		}
	}
}

void BattleDeck::HandleDrawDiscardAni(float& _deltaTime)
{
	if (m_drawAni || m_discardAni)
	{
		m_time += _deltaTime; //m_time is how long the animation has been playing in total
		if (!m_aniFin)
		{
			if (m_time <= 1.0f) //animation will be finished in 1 second
			{

				m_xPos += _deltaTime * m_xSpeed; //move the card position by the velocity * time
				m_yPos += -_deltaTime * m_ySpeed;
				m_wPos += _deltaTime * m_wSpeed;
				if (m_wPos <= 0) //the width expands or collapses based on the animation to simulate a turnign card
				{
					if (m_drawAni)
						m_wSpeed = (150.0f / 0.50f); //when the width of the card is 0, start expanding it
					else if (m_discardAni)
						m_wSpeed = (75.0f / 0.50f);
				}
				m_hPos += _deltaTime * m_hSpeed;
			}
			else
			{
				m_xPos += (1.0f - (m_time - _deltaTime)) * m_xSpeed; //move the card position by the velocity * time
				m_yPos += -(1.0f - (m_time - _deltaTime)) * m_ySpeed;
				m_wPos += (1.0f - (m_time - _deltaTime)) * m_wSpeed;
				m_hPos += (1.0f - (m_time - _deltaTime)) * m_hSpeed;
				m_aniFin = true;
			}
		}
		if (m_time >= 1.50f) //0.5 seconds of waiting to inspect the card
		{
			if (m_drawAni) //if we are drawing a card
			{
				--m_cardsToDraw;
				m_drawAni = false;
				if (m_cardsToDraw >= 0) //if there are more cards to draw, draw them
				{
					DrawCard();
				}
				m_Hand.push_back(m_DrawPile[0]); //add the card to the hand
				m_DrawPile.erase(m_DrawPile.begin());
				UpdateHandPosition();
				m_Hand[m_Hand.size() - 1]->SetText();
			}
			else if (m_discardAni) //discarding the card
			{
				m_discardAni = false;
				UpdateHandPosition();
				RefreshCHand();
			}
		}
	}
	else if (m_discardHandAni) //Discarding the Hand
	{
		m_time += _deltaTime; //m_time is how long the animation has been playing in total
		if (!m_aniFin)
		{
			if (m_time <= 1.0f) //animation will be finished in 1 second
			{
				int n = 0;
				for each (std::shared_ptr<CardHolder> card in m_Hand)
				{
					/*
					m_xSpeed = ((1515.0f) - m_xPos) / 1.0f;
					m_ySpeed = -((779.0f) - m_yPos) / 1.0f;
					m_wSpeed = -(150.0f / 0.50f);
					m_hSpeed = -100.0f / 1.0f;
					*/

					SDL_Rect pos = card->GetPos();
					pos.x += _deltaTime * m_discardSpeed[n].x; //move the card position by the velocity * time
					pos.y += -_deltaTime * m_discardSpeed[n].y;
					pos.w += _deltaTime * m_discardSpeed[n].w;
					if (pos.w <= 0) //the width expands or collapses based on the animation to simulate a turnign card
					{
						pos.w = 0;
						m_discardSpeed[n].w = (75.0f / 0.50f);
					}
					pos.h += _deltaTime * m_discardSpeed[n].h;

					card->UpdatePosition(pos);
					n++;
				}
			}
			else
			{
				int n = 0;
				for each (std::shared_ptr<CardHolder> card in m_Hand)
				{
					SDL_Rect pos = card->GetPos();
					pos.x += (1.0f - (m_time - _deltaTime)) * m_discardSpeed[n].x; //move the card position by the velocity * time
					pos.y += -(1.0f - (m_time - _deltaTime)) * m_discardSpeed[n].y;
					pos.w += (1.0f - (m_time - _deltaTime)) * m_discardSpeed[n].w;
					pos.h += (1.0f - (m_time - _deltaTime)) * m_discardSpeed[n].h;

					card->UpdatePosition(pos);
					n++;
				}

				m_aniFin = true;
			}
		}
		else if (m_time >= 1.50f) //0.5 seconds of waiting to inspect the card
		{
			m_discardHandAni = false;
			UpdateHandPosition();
			for each (std::shared_ptr<CardHolder> card in m_Hand)
			{
				m_DiscardPile.push_back(card);
			}
			m_Hand.clear();
			RefreshCHand();
		}
	}
}
