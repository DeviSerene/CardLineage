#include "MenuState.h"

MenuState::MenuState(std::shared_ptr<GameData> _gamedata)
	: GameState(_gamedata)
{
	m_background = std::shared_ptr<ParallaxBg>(new ParallaxBg("grass", 5));
	m_battleState = 0;
	m_chosenCard = -1;
	//initialise the party position data
	m_partyPos.push_back({ 350, 250, 200,200 });
	m_partyPos.push_back({ 150, 275, 200,200 });

	m_enemyPos.push_back({ 950, 250, 200,200 });
	m_enemyPos.push_back({ 1150, 275, 200,200 });

	//AudioManager::MusicPlay("assets/music.wav");
	//Here we are initiating the cards, however this will be loading into the GameData in the real game
	m_cards.push_back(std::shared_ptr<Card>(new Card()));
	m_cards.push_back(std::shared_ptr<Card>(new Card("Test")));
	m_cards.push_back(std::shared_ptr<Card>(new Card("Hello")));
	m_cards.push_back(std::shared_ptr<Card>(new Card("Healing Fire")));
	m_cards.push_back(std::shared_ptr<Card>(new Card("Curing")));
	m_combocards.push_back(std::shared_ptr<Card>(new Card(m_cards[0])));

	std::vector< std::shared_ptr<Effect>> kamiEffects;
	std::vector< std::shared_ptr<AniEffect>> kamiAniEffects;
	kamiEffects.push_back(std::shared_ptr<Effect>(new Effect(0, 3, 75, 2, 0, 1, 1)));
	kamiAniEffects.push_back(std::shared_ptr<AniEffect>(new AniEffect(2, 0.5f, 0.55f)));
	kamiEffects.push_back(std::shared_ptr<Effect>(new Effect(0, 1, 25, 2, 0, 0, 0)));
	kamiAniEffects.push_back(std::shared_ptr<AniEffect>(new AniEffect(2, 0.70f, 0.75f)));
	m_cards.push_back(std::shared_ptr<Card>(new Card("Kami", 0, 1, 1, 1, kamiEffects, kamiAniEffects)));

	//Load up the characters, in the real game, we will have them loaded up from data
	m_party.push_back(std::shared_ptr<Character>(new Character()));
	m_party.push_back(std::shared_ptr<Character>(new Character()));
	m_party[0]->SetColour(1);
	m_party[1]->SetColour(2);
	m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy()));
	m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy()));
	ResetAlliesPos();
	ResetEnemyPos();

	//Create the deck, and fill it with the party members, shuffle, and set the comboCard data
	deck = new BattleDeck();
	deck->InitCharacter(m_cards, m_party[0]->GetCards(), m_party[0]->GetStats(), 1);
	deck->InitCharacter(m_cards, m_party[1]->GetCards(), m_party[1]->GetStats(), 2);
	deck->ShuffleDraw();
	deck->SetCCDeck(m_combocards);

	//m_button.SetFunction([](BattleDeck* deck) {deck->ChangeRow(1);});
	m_buttons.push_back(new Button("assets/ui/up.png", { 795,20,25,25 }, false));
	//212 * 3 = 636
	m_buttons.push_back(new Button("assets/ui/down.png", { 795,700,25,25 }, false));

	m_animations = std::shared_ptr<AnimationManager>(new AnimationManager());
	m_animations->AddAnimation(0, m_partyPos[0]);
	m_animations->AddAnimation(0, m_partyPos[1]);
	m_effectManager = std::shared_ptr<BattleEffect>(new BattleEffect(&m_battleState, &m_target, &m_targetType, m_animations, m_party, m_enemies, m_partyPos, m_enemyPos));
	m_battleText = std::shared_ptr<FloatingTextManager>(new FloatingTextManager(m_gameData->GetRenderer()));
	m_effectManager->InitText(m_battleText);
	m_enemyController = std::shared_ptr<EnemyController>(new EnemyController(&m_battleState, &m_target, &m_targetType, m_effectManager, m_party, m_enemies, m_partyPos, m_enemyPos));
}

MenuState::~MenuState()
{
	//delete m_animations;
	m_effectManager->DeInit();
	m_effectManager = nullptr;

	
	delete deck;

	for each (Button* var in m_buttons)
	{
		delete var;
	}
	m_buttons.clear();

}

bool MenuState::HandleSDLEvents()
{
	//create an SDL event
	SDL_Event ev;
	int x, y;
	SDL_GetMouseState(&x, &y); //locate where the mouse is

	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_QUIT: //player has pressed the X button
			m_gameData->m_stateManager->RemoveLastState();
			return false;
			break;
		case SDL_KEYDOWN:
			DebugKeys(ev.key.keysym.sym);
			switch (ev.key.keysym.sym) //what key has been pressed?
			{
			case SDLK_ESCAPE:
				m_gameData->m_stateManager->RemoveLastState();
				return false;
				break;
			
			}
			break;

		case SDL_MOUSEBUTTONDOWN: //mouse button pressed
			switch (ev.button.button) //what key has been pressed?
			{
			case SDL_BUTTON_LEFT:
				PlayerTurnLeftClick(x, y);

				break;
			case SDL_BUTTON_RIGHT:
				if (m_chosenCard != -1)
				{
					//m_targetType = -1;
					m_chosenCard = -1;
					deck->UpdateHandPosition();
					ResetAlliesPos();
				}
				break;
			}
			
		}
	}

	if (m_chosenCard < 0) //mousing over a card to inspect it
	{
		deck->SetHighlightCard(-1, false);
		m_characterHighlights.clear();
		m_manaHighlight = 0;
		for (int i = 0; i < deck->GetHand().size(); i++)
		{
			if (MouseRect(x, y, deck->GetHand()[i]->GetPos()))
			{
				deck->SetHighlightCard(i, false);

				m_characterHighlights.push_back(deck->GetHand()[i]->GetCol() - 1);
				m_manaHighlight = deck->GetHand()[i]->GetCard()->GetMana();
			}
		}
		for (int i = 0; i < deck->GetComboHand().size(); i++)
		{
			if (MouseRect(x, y, deck->GetComboHand()[i]->GetPos()))
			{
				deck->SetHighlightCard(i, true);

				m_characterHighlights.push_back(deck->GetHand()[deck->GetComboHighlights()[i][0]]->GetCol() - 1);
				m_characterHighlights.push_back(deck->GetHand()[deck->GetComboHighlights()[i][1]]->GetCol() - 1);
				m_manaHighlight = deck->GetComboHand()[i]->GetCard()->GetMana();
			}
		}
	}

	MouseOverTarget(x, y);

	return true;
}

void MenuState::InitTargets()
{
	m_targets.clear();
	m_highlightTargets.clear();
	//add all targets accoring to the card type to the m_targetPos list
	if (m_targetType == 0) //self
	{
		for (int i = 0; i < m_party.size(); i++)
		{
			if (i == deck->GetHand()[deck->GetComboHighlights()[m_chosenCard - 100][0]]->GetCol() - 1)
			{
				m_targets.push_back({ m_partyPos[i], i });
			}
		}
	}
	else if (m_targetType < 4) //one enemy, all enemies, random enemies
	{
		for (int i = 0; i < m_enemies.size(); i++)
		{
			if (!m_enemies[i]->IsDead())
			{
				m_targets.push_back({ m_enemyPos[i], i });
			}
		}
	}
	else
	{
		for (int i = 0; i < m_party.size(); i++)
		{
			if (!m_party[i]->IsDead())
			{
				m_targets.push_back({ m_partyPos[i], i });
			}
		}
	}

}

void MenuState::MouseOverTarget(int& x, int& y)
{
	m_highlightTargets.clear();

	if (!m_targets.empty() && m_chosenCard > -1) //this only runs if a card has been chose (thus we are chosing a target), and the targetlist has been populated
	{
		for (int i = 0; i < m_targets.size(); i++)
		{
			if (MouseRect(x, y, m_targets[i].m_pos))
			{
				//the player is mousing over a suitable target
				if (m_targetType == 2 || m_targetType == 3 || m_targetType == 5 || m_targetType == 6)
				{
					for (int u = 0; u < m_targets.size(); u++)
					{
						m_highlightTargets.push_back(m_targets[u].m_pos);
					}
					return;
				}
				else
				{
					m_highlightTargets.push_back(m_targets[i].m_pos);
					return;
				}
			}
		}
	}
}

void MenuState::DrawTargets()
{
	if (!m_targets.empty() && m_chosenCard > -1) //this only runs if a card has been chose (thus we are chosing a target), and the targetlist has been populated
	{
		for (int i = 0; i < m_targets.size(); i++)
		{
			std::string targetName;
			if (m_targetType > 0 && m_targetType < 4)
				targetName = "assets/ui/target_0.png"; //enemy targeter
			else
				targetName = "assets/ui/target_1.png";

			SpriteFactory::Draw(targetName, { m_targets[i].m_pos.x,m_targets[i].m_pos.y, 125, 30 }, 170,170,170);
		}
		if (!m_highlightTargets.empty()) //ones that are being moused over are in the highlighted target list
		{
			for (int i = 0; i < m_highlightTargets.size(); i++)
			{
				std::string targetName;
				if (m_targetType > 0 && m_targetType < 4)
					targetName = "assets/ui/target_0.png";
				else
					targetName = "assets/ui/target_1.png";

				SpriteFactory::Draw(targetName, { m_highlightTargets[i].x,m_highlightTargets[i].y, 125, 30 }, 255, 255, 255);
			}
		}
	}
}

void MenuState::Update(float _deltaTime)
{
	m_background->Update(_deltaTime);
	DrawPhase();
	//update part and enemies animations
	for (int i = 0; i < m_party.size(); i++)
	{
		m_party[i]->Update(_deltaTime);
	}
	if (!m_enemies.empty())
	{
		for (int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->Update(_deltaTime);
		}
	}
	deck->Update( _deltaTime);
	m_animations->Update(_deltaTime);
	m_effectManager->Update(_deltaTime);
	m_battleText->Update(_deltaTime);

	if (m_battleState == 10)
	{
		m_enemyController->Update(_deltaTime);
	}

}

void MenuState::Draw()
{
	m_background->Draw();
	//SpriteFactory::Draw("assets/greece2.png", { 0,0,1600,900 });
	//draw party 
	if (!m_party.empty())
	{
		for (int i = 0; i < m_party.size(); i++)
		{
			m_party[i]->SetManaHighlight(0);
			m_party[i]->DrawBattle( 230, 230, 230);
		}
	}
	if (!m_enemies.empty())
	{
		for (int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->DrawBattle( 230, 230, 230);
		}
	}

	//if a party member/s are highlighted,
	if (!m_characterHighlights.empty())
	{
		for (int i = 0; i < m_characterHighlights.size(); i++)
		{
			m_party[m_characterHighlights[i]]->SetManaHighlight(m_manaHighlight);
			m_party[m_characterHighlights[i]]->DrawBattle(255, 255, 255);
			
		}
		
	}
	DrawTargets();

	deck->DrawHand(m_chosenCard);
	m_animations->Draw();

	for each (Button* butt in m_buttons)
	{
		butt->Draw();
	}


	m_battleText->Draw();
}

void MenuState::ResetAlliesPos()
{
	if (!m_party.empty())
	{
		for (int i = 0; i < m_party.size(); i++)
		{
			m_party[i]->DrawBattle(m_partyPos[i], 200, 200, 200);
		}
	}
}

void MenuState::ResetEnemyPos()
{
	if (!m_enemies.empty())
	{
		for (int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->DrawBattle(m_enemyPos[i], 200, 200, 200);
		}
	}
}

void MenuState::PlayerTurnLeftClick(int& x, int& y)
{
	if (m_battleState == 1 && !deck->DrawingCards())
	{
		if (deck->InspectingDeck())
		{
			if (m_buttons[0]->MouseRect(x, y))
			{
				deck->ChangeRow(-1);
				m_buttons[0]->SetVisibility(deck->CanChangeRow(-1));
				m_buttons[1]->SetVisibility(deck->CanChangeRow(1));
			}
			else if (m_buttons[1]->MouseRect(x, y))
			{
				deck->ChangeRow(1);
				m_buttons[0]->SetVisibility(deck->CanChangeRow(-1));
				m_buttons[1]->SetVisibility(deck->CanChangeRow(1));
			}
		}
		else
		{
			if (m_chosenCard == -1 && m_effectManager->IsEffectEmpty())
			{
				for (int i = 0; i < deck->GetHand().size(); i++)
				{
					if (MouseRect(x, y, deck->GetHand()[i]->GetPos()))
					{
						//player has selected a card from the hand
						//does the user have enough mana to cast this?
						if (deck->GetHand()[i]->GetStats()->GetMana() >= deck->GetHand()[i]->GetCard()->GetMana())
						{
							m_chosenCard = i;
							m_targetType = deck->GetHand()[i]->GetCard()->GetTarget();
							InitTargets();

							SDL_Rect moveTo = m_partyPos[deck->GetHand()[i]->GetCol() - 1];
							moveTo.x = moveTo.x + 25;
							m_party[deck->GetHand()[i]->GetCol() - 1]->MoveTo(moveTo);
						}
						else
						{
							//insufficient mana
							m_battleText->AddNewText("Insufficient Mana", x, y, 0, 0, 255);
						}
					}
				}
				for (int i = 0; i < deck->GetComboHand().size(); i++)
				{
					if (MouseRect(x, y, deck->GetComboHand()[i]->GetPos()))
					{
						//player has selected a combocard
						//do the users have enough mana to cast this?
						if (deck->GetComboHand()[i]->GetStats()->GetMana() >= deck->GetComboHand()[i]->GetCard()->GetMana()
							&& deck->GetComboHand()[i]->GetStats2()->GetMana() >= deck->GetComboHand()[i]->GetCard()->GetMana())
						{
							m_chosenCard = i + 100;
							m_targetType = deck->GetComboHand()[i]->GetCard()->GetTarget();
							InitTargets();


							SDL_Rect moveTo = m_partyPos[deck->GetHand()[deck->GetComboHighlights()[i][0]]->GetCol() - 1];
							moveTo.x += 25;
							m_party[deck->GetHand()[deck->GetComboHighlights()[i][0]]->GetCol() - 1]->MoveTo(moveTo);

							moveTo = m_partyPos[deck->GetHand()[deck->GetComboHighlights()[i][1]]->GetCol() - 1];
							moveTo.x += 25;
							m_party[deck->GetHand()[deck->GetComboHighlights()[i][1]]->GetCol() - 1]->MoveTo(moveTo);
						}
						else
						{
							//insufficient mana
							m_battleText->AddNewText("Insufficient Mana", x, y, 0, 0, 255);
						}
					}
				}
			}
			else if (m_chosenCard > -1)
			{
				for (int i = 0; i < m_targets.size(); i++)
				{
					if (MouseRect(x, y, m_targets[i].m_pos)) //cant target a dead enemy
					{
						m_target = m_targets[i].m_id; //set the target
						if (m_chosenCard >= 100) //is this a combo card?
						{
							//decrease mana
							m_party[deck->GetHand()[deck->GetComboHighlights()[m_chosenCard - 100][0]]->GetCol() - 1]->GetStats()->ModifyMana(-deck->GetComboHand()[m_chosenCard - 100]->GetCard()->GetMana());
							m_party[deck->GetHand()[deck->GetComboHighlights()[m_chosenCard - 100][1]]->GetCol() - 1]->GetStats()->ModifyMana(-deck->GetComboHand()[m_chosenCard - 100]->GetCard()->GetMana());
							//add the effects
							m_effectManager->SetUser(deck->GetHand()[deck->GetComboHighlights()[m_chosenCard - 100][0]]->GetCol() - 1, m_party[deck->GetHand()[deck->GetComboHighlights()[m_chosenCard - 100][0]]->GetCol() - 1]->GetStats()); //set the user in the effects manager to get stats from
							m_effectManager->SetComboer(deck->GetHand()[deck->GetComboHighlights()[m_chosenCard - 100][1]]->GetCol() - 1, m_party[deck->GetHand()[deck->GetComboHighlights()[m_chosenCard - 100][1]]->GetCol() - 1]->GetStats()); //set the combo user, to get stats from
							m_effectManager->AddEffects(deck->GetComboHand()[m_chosenCard - 100]->GetCard()->GetEffects(), deck->GetComboHand()[m_chosenCard - 100]->GetCard()->GetAniEffects()); //add all the card's effects
						
							//animate
							m_party[deck->GetHand()[deck->GetComboHighlights()[m_chosenCard - 100][0]]->GetCol() - 1]->SetAnimation(deck->GetComboHand()[m_chosenCard - 100]->GetCard()->GetUAni());
							m_party[deck->GetHand()[deck->GetComboHighlights()[m_chosenCard - 100][1]]->GetCol() - 1]->SetAnimation(deck->GetComboHand()[m_chosenCard - 100]->GetCard()->GetUAni());


							deck->DiscardCC(m_chosenCard - 100); //discard the card
						}
						else
						{
							m_party[deck->GetHand()[m_chosenCard]->GetCol() - 1]->GetStats()->ModifyMana(-deck->GetHand()[m_chosenCard]->GetCard()->GetMana());
							//effects
							m_effectManager->SetUser(deck->GetHand()[m_chosenCard]->GetCol() - 1, m_party[deck->GetHand()[m_chosenCard]->GetCol() - 1]->GetStats());
							m_effectManager->AddEffects(deck->GetHand()[m_chosenCard]->GetCard()->GetEffects(), deck->GetHand()[m_chosenCard]->GetCard()->GetAniEffects());

							//animate
							m_party[deck->GetHand()[m_chosenCard]->GetCol() - 1]->SetAnimation(deck->GetHand()[m_chosenCard]->GetCard()->GetUAni());

							//Discard goes LAST
							deck->DiscardCard(m_chosenCard);
						}

						//m_targetType = -1; //reset variables
						m_chosenCard = -1;
						deck->UpdateHandPosition(); //update removed cards
						ResetAlliesPos(); //reset allies
					}
				}
			}
		}
	}
}


void MenuState::DebugKeys(SDL_Keycode _key)
{
	switch (_key)
	{
	case SDLK_1:
		m_battleText->AddNewText("1", m_partyPos[0].x + 100, m_partyPos[0].y + 100, 255, 0, 0);
		m_party[0]->GetStats()->ModifyEffect(0, -1);
		//m_party[0]->MoveTo({ 200,300,100,100 });
		break;
	case SDLK_2:
		m_battleText->AddNewText("1", m_partyPos[0].x + 100, m_partyPos[0].y + 100, 0, 255, 0);
		m_party[0]->GetStats()->ModifyEffect(0, 1);
		break;
	case SDLK_3:
		m_enemies[0]->MoveTo({ m_enemyPos[0].x - 20 , m_enemyPos[0].y,m_enemyPos[0].w,m_enemyPos[0].h });
		break;
	case SDLK_4:
		if (m_effectManager->IsEffectEmpty())
		{
			//m_target = 0;
			//m_targetType = 4;
			//m_effectManager->SetUser(0, m_enemies[0]->GetStats(), true);
			//m_effectManager->AddEffects(m_enemies[0]->GetEffects(), m_enemies[0]->GetAniEffects());
			m_battleState = 10;
		}
		break;
	case SDLK_q:
		deck->DrawCard(); m_chosenCard = -1;
		break;
	case SDLK_w:
		deck->DiscardCard(0); m_chosenCard = -1;
		break;
	case SDLK_e:
		deck->DiscardHand(); m_chosenCard = -1;
		break;
	case SDLK_r:
		deck->ShuffleDiscardToDraw(); m_chosenCard = -1;
		break;
	case SDLK_t:
		deck->DiscardCC(0); m_chosenCard = -1;
		break;
	case SDLK_a:
		deck->ToggleDDD(0);
		m_buttons[0]->SetVisibility(deck->CanChangeRow(-1));
		m_buttons[1]->SetVisibility(deck->CanChangeRow(1));
		break;
	case SDLK_z:
		deck->ToggleDDD(1);
		m_buttons[0]->SetVisibility(deck->CanChangeRow(-1));
		m_buttons[1]->SetVisibility(deck->CanChangeRow(1));
		break;
	case SDLK_x:
		deck->ToggleDDD(2);
		m_buttons[0]->SetVisibility(deck->CanChangeRow(-1));
		m_buttons[1]->SetVisibility(deck->CanChangeRow(1));
		break;
	case SDLK_s:
		deck->ChangeRow(1);
		m_buttons[0]->SetVisibility(deck->CanChangeRow(-1));
		m_buttons[1]->SetVisibility(deck->CanChangeRow(1));
		break;
	case SDLK_d:
		deck->ChangeRow(-1);
		m_buttons[0]->SetVisibility(deck->CanChangeRow(-1));
		m_buttons[1]->SetVisibility(deck->CanChangeRow(1));
		break;
	default:
		break;
	}
}

void MenuState::DrawPhase()
{
	if (m_battleState == 0)
	{
		//restire mana
		for each (std::shared_ptr<Character> chara in m_party)
		{
			chara->GetStats()->ModifyMana(1);
		}
		//int cardsToDraw = 0;
		int cardsToDraw = 5 - deck->GetHand().size();
		if (cardsToDraw > 0)
			deck->DrawCards(cardsToDraw);
		m_battleState = 1;
	}
}