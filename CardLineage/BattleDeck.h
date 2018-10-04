#pragma once
#include "CardHolder.h"
#include <vector>
#include "BinaryTreeCardSorter.h"
#include <memory>

struct Speed
{
	Speed(float _x, float _y, float _w, float _h)
	{
		x = _x;
		y = _y;
		h = _h;
		w = _w;
	}
	float x;
	float y;
	float h;
	float w;
};

class BattleDeck
{
public:
	BattleDeck();
	~BattleDeck();

	void InitCharacter(std::vector <std::shared_ptr<Card>> _card, std::vector <int> _cards, std::shared_ptr<Stats> _stats,  int _col); //initiates a character into the deck

	void ShuffleDraw(); //shuffle the cards in the draw deck
	void DrawCards(int _i) { m_cardsToDraw += (_i-1); DrawCard(); } //draw x ammount of cards from the draw deck
	void DrawCard();  //animation for drawing the cards
	void SetHighlightCard(int _i, bool _comboDeck); //set the card that is being highlighted/magnified for inspection
	void DiscardCard(int _i); //discard a particular card from the hand
	void DiscardHand(); //discard all cards from hand
	void DiscardCC(int _i);
	void ShuffleDiscardToDraw();

	void DrawHand(int _selectedCard = -1); //draw the deck(to appear on screen)
	void DrawDeck(std::vector <std::shared_ptr<CardHolder>> _cards, int _x, int _y, float _scale); //draw the specific deck pile in the middle of the screen, +x, +y with scale

	void Update(float _deltaTime);				//update animations etc
	void UpdateHandPosition();

	//Inspecting the DrawPile/DiscardPile
	void ToggleDDD(int _pile) { ToggleDDD(!m_drawDrawDeck, _pile); }
	void ToggleDDD(bool _set, int _pile);
	void ChangeRow(int _i);

	//Getters
	std::vector <std::shared_ptr<CardHolder>> GetHand() { return m_Hand; } //
	std::vector <std::shared_ptr<CardHolder>> GetComboHand() { return m_ComboHand; } //
	std::vector<std::vector<int>> GetComboHighlights() { return m_combo; }
	bool InspectingDeck() { return m_drawDrawDeck; }
	bool CanChangeRow(int _i);

	void SetCCDeck(std::vector <std::shared_ptr<Card>> _cc) { combocards = _cc; }

private:

	//the decks
	std::vector <std::shared_ptr<CardHolder>> m_DrawPile;
	std::vector <std::shared_ptr<CardHolder>> m_DiscardPile;
	std::vector <std::shared_ptr<CardHolder>> m_Hand;
	std::vector <std::shared_ptr<CardHolder>> m_ComboHand;
	std::vector <std::shared_ptr<CardHolder>> m_Exiled;
	std::vector <std::shared_ptr<CardHolder>> m_DrawPileSorted;

	//reference to the list of combocards
	std::vector <std::shared_ptr<Card>> combocards;

	//the highlighted card on screen
	std::shared_ptr<CardHolder> m_highlightCard;
	int m_highC;
	std::vector<int> m_comboHighlight;
	std::vector<std::vector<int>> m_combo;

	//display a pile on screen
	bool m_drawDrawDeck;
	int m_deckDisplay;
	int m_row;

	int m_cardsToDraw;
	//animation variables
	bool m_drawAni;
	bool m_discardAni;
	bool m_discardHandAni;
	bool m_reshuffleAni;
	bool m_aniFin;
	float m_xPos, m_yPos, m_wPos, m_hPos;
	float m_xSpeed, m_ySpeed, m_wSpeed, m_hSpeed;
	std::vector <Speed> m_discardSpeed;
	float m_time;

	//member functions
	
	void HandleDrawDiscardAni(float& _deltaTime);
	void ShuffleDDAni(float _deltaTime);
	void DrawShuffleAni();
	SDL_Rect m_ShuffleRect;
	std::vector <std::shared_ptr<CardHolder>> GetPile(int _i) { if (_i == 0) return m_DrawPile; else if (_i == 1) return m_DiscardPile; if (_i == 2) return m_DrawPile; }

	void RefreshCHand();
	void UpdateCCPosition();
};

