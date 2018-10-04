#include "BattleEffect.h"



BattleEffect::BattleEffect(int* _battleState, int* _target, int* _targetType, std::shared_ptr<AnimationManager> _animan, std::vector<std::shared_ptr<Character>>& _partyPointer, std::vector<std::shared_ptr<Enemy>>& _enemyPointer, std::vector<SDL_Rect> _partyPos, std::vector<SDL_Rect> _enemyPos)
{
	m_battleState = (std::shared_ptr<int>)_battleState;
	m_target = (std::shared_ptr<int>)_target;
	m_targetType = (std::shared_ptr<int>)_targetType;
	m_animan = _animan;
	m_party = _partyPointer;
	m_enemies = _enemyPointer;
	m_partyPos = _partyPos;
	m_enemyPos = _enemyPos;
}


BattleEffect::~BattleEffect()
{
	/*
	m_battleState = nullptr;
	m_target = nullptr;
	m_animan = nullptr;

	m_effects.clear();
	m_aniEffects.clear();
	m_party.clear();
	m_enemies.clear();
	*/
}

void BattleEffect::DeInit()
{
//	m_battleState = nullptr;
//	m_target = nullptr;
//	m_animan = nullptr;

	m_effects.clear();
	m_aniEffects.clear();
	m_party.clear();
	m_enemies.clear();
}

void BattleEffect::AddEffects(std::vector<std::shared_ptr<Effect>> _effects, std::vector<std::shared_ptr<AniEffect>> _aniEffects)
{
	for each (std::shared_ptr<Effect> effect in _effects)
	{
		m_effects.push_back(effect);
	}
	for (int i = 0; i < _aniEffects.size(); i++)
	{
		m_aniEffects.push_back(_aniEffects[i]);
		m_aniEffects[m_aniEffects.size() - 1]->Reset();
	}
}

void BattleEffect::Update(float& _deltaTime)
{
	//in this function, we need to go through each effect and update their animation, apply their effect when the ani says we should, and remove them if it is over
	if (!m_aniEffects.empty())
	{
		for (int i = 0; i < m_aniEffects.size(); i++)
		{
			m_aniEffects[i]->Update(_deltaTime);
			if (!m_aniEffects[i]->StartedAni())
			{
				//if the animation hasn't started, and it is time to, start it
				if (m_aniEffects[i]->StartAnimation())
				{
					GetAniPlacement(m_effects[i]);
					if (!m_aniList.empty())
					{
						//we have a list to draw the sprites to
						for each(SDL_Rect pos in m_aniList)
						{
							m_animan->AddAnimation(m_aniEffects[i]->GetAnimationID(), pos);
						}
					}
				}
			}

			if (!m_aniEffects[i]->StartedEffect())
			{
				//if the effect hasn't happened yet, and it is time to start it, do so
				if (m_aniEffects[i]->StartEffect())
				{
					//apply the effect to all targets
					ApplyEffect(m_effects[i]);
				}
			}

			if (m_aniEffects[i]->StartedAni() && m_aniEffects[i]->StartedEffect())
			{
				//remove this effect as we no longer care about it
				m_aniEffects.erase(m_aniEffects.begin() + i);
				m_effects.erase(m_effects.begin() + i);
				i--;
			}
		}
	}
}

void BattleEffect::ApplyEffect(std::shared_ptr<Effect> _effect)
{
	switch (_effect->GetIDType())
	{
	case 0:
		//Deal x + (r *[stat]) { elemental } {type} damage to[Target].
		DealDamageEffect(_effect);
		break;
	case 1:
		//Restore x + (r *[stat]) hp to[Target].
		HealDamageEffect(_effect);
		break;
	default:
		break;
	}
}

void BattleEffect::GetAniPlacement(std::shared_ptr<Effect> _effect)
{
	//return a list of the Rects to play the animation on
	m_aniList.clear();

	switch (_effect->GetTargetInfo())
	{
	case 0:
		// "Self";
		for (int i = 0; i < m_party.size(); i++)
		{
			if (m_party[i] == m_user || m_party[i] == m_comboer)
				m_aniList.push_back(m_partyPos[i]);
		}
		break;
	case 1:
		// "One Enemy";
		m_aniList.push_back(m_enemyPos[*m_target]);
		break;
	case 2:
		// "All Enemies";
		for (int i = 0; i < m_enemies.size(); i++)
		{
			if (!m_enemies[i]->IsDead())
			{
				m_aniList.push_back(m_enemyPos[i]);
			}
		}
		break;
	case 3:
		// "a Random Enemy";
		break;
	case 4:
		// "One Ally";
		m_aniList.push_back(m_partyPos[*m_target]);
		break;
	case 5:
		// "All Allies";
		for (int i = 0; i < m_party.size(); i++)
		{
			if (!m_party[i]->IsDead())
			{
				m_aniList.push_back(m_partyPos[i]);
			}
		}
		break;
	case 6:
		// "a Random Ally";
		break;
	case 7:
		// "all other Enemies";
		for (int i = 0; i < m_enemies.size(); i++)
		{
			if (!m_enemies[i]->IsDead() && i != *m_target)
			{
				m_aniList.push_back(m_enemyPos[i]);
			}
		}
		break;
	case 8:
		// "all other Allies";
		//this works in two ways: if the card targets an enemy, then it effects all allies other than the caster
		//								if it targets an ally, then it effects all other allies than the target
		if (*m_targetType < 4 && *m_targetType > 0) //one enemy, all enemies, random enemies
		{
			for (int i = 0; i < m_party.size(); i++)
			{
				if (!m_party[i]->IsDead() && m_user != m_party[i] && m_comboer != m_party[i])
				{
					m_aniList.push_back(m_partyPos[i]);
				}
			}
		}
		else
		{
			for (int i = 0; i < m_party.size(); i++)
			{
				if (!m_party[i]->IsDead() && *m_target != i)
				{
					m_aniList.push_back(m_partyPos[i]);
				}
			}
		}
		break;
	default:
		break;
	}

}

void BattleEffect::GetTargets(std::shared_ptr<Effect> _effect)
{
	//return a list of the Rects to play the animation on
	m_enemyTargets.clear();
	m_partyTargets.clear();

	switch (_effect->GetTargetInfo())
	{
	case 0:
		// "Self";
		m_partyTargets.push_back(m_user);
		if(m_comboer != NULL)
			m_partyTargets.push_back(m_comboer);
		break;
	case 1:
		// "One Enemy";
		if(m_enemies.size() > *m_target)
			m_enemyTargets.push_back(m_enemies[*m_target]);
		break;
	case 2:
		// "All Enemies";
		for (int i = 0; i < m_enemies.size(); i++)
		{
			if (!m_enemies[i]->IsDead())
			{
				m_enemyTargets.push_back(m_enemies[i]);
			}
		}
		break;
	case 3:
		// "a Random Enemy";
		break;
	case 4:
		// "One Ally";
		if (m_party.size() > *m_target)
			m_partyTargets.push_back(m_party[*m_target]);
		break;
	case 5:
		// "All Allies";
		for (int i = 0; i < m_party.size(); i++)
		{
			if (!m_party[i]->IsDead())
			{
				m_partyTargets.push_back(m_party[i]);
			}
		}
		break;
	case 6:
		// "a Random Ally";
		break;
	case 7:
		// "all other Enemies";
		for (int i = 0; i < m_enemies.size(); i++)
		{
			if(!m_enemies[i]->IsDead() && i != *m_target)
				m_enemyTargets.push_back(m_enemies[i]);
		}
		break;
	case 8:
		// "all other Allies";
		//this works in two ways: if the card targets an enemy, then it effects all allies other than the caster
		//								if it targets an ally, then it effects all other allies than the target
		if (*m_targetType < 4 && *m_targetType > 0) //one enemy, all enemies, random enemies
		{
			for (int i = 0; i < m_party.size(); i++)
			{
				if (!m_party[i]->IsDead() && m_user != m_party[i] && m_comboer != m_party[i])
				{
					m_partyTargets.push_back(m_party[i]);
				}
			}
		}
		else
		{
			for (int i = 0; i < m_party.size(); i++)
			{
				if (!m_party[i]->IsDead() && *m_target != i)
				{
					m_partyTargets.push_back(m_party[i]);
				}
			}
		}
		break;
	default:
		break;
	}

}

void BattleEffect::DealDamageEffect(std::shared_ptr<Effect> _effect)
{
	GetTargets(_effect);
	GetAniPlacement(_effect);

	if (!m_enemyTargets.empty())
	{
		for (int i = 0; i < m_enemyTargets.size(); i++)
		{
			if (m_comboer == NULL)
			{
				m_enemyTargets[i]->TakeDamage(_effect->GetDamage(m_user->GetStats()), _effect->GetDType(), _effect->GetElement());
			}
			else
			{
				m_enemyTargets[i]->TakeDamage(_effect->GetDamage(m_user->GetStats(), m_comboer->GetStats()), _effect->GetDType(), _effect->GetElement());
			}
		}
	}
	if (!m_partyTargets.empty())
	{
		for (int i = 0; i < m_partyTargets.size(); i++)
		{
			if (m_comboer == NULL)
			{
				m_partyTargets[i]->TakeDamage(_effect->GetDamage(m_user->GetStats()), _effect->GetDType(), _effect->GetElement());
			}
			else
			{
				m_partyTargets[i]->TakeDamage(_effect->GetDamage(m_user->GetStats(), m_comboer->GetStats()), _effect->GetDType(), _effect->GetElement());
			}
		}
	}

	if (!m_aniList.empty())
	{
		for (int i = 0; i < m_aniList.size(); i++)
		{
			if (m_comboer == NULL)
			{
				m_texts->AddNewText(std::to_string(_effect->GetDamage(m_user->GetStats())), m_aniList[i].x + 100, m_aniList[i].y + 100, 255, 0, 0);
			}
			else
			{
				m_texts->AddNewText(std::to_string(_effect->GetDamage(m_user->GetStats(), m_comboer->GetStats())), m_aniList[i].x + 100, m_aniList[i].y + 100, 255, 0, 0);
			}
		}
	}
}

void BattleEffect::HealDamageEffect(std::shared_ptr<Effect> _effect)
{
	GetTargets(_effect);
	GetAniPlacement(_effect);

	if (!m_enemyTargets.empty())
	{
		for (int i = 0; i < m_enemyTargets.size(); i++)
		{
			if (m_comboer == NULL)
			{
				m_enemyTargets[i]->GetStats()->Heal(_effect->GetDamage(m_user->GetStats()));
			}
			else
			{
				m_enemyTargets[i]->GetStats()->Heal(_effect->GetDamage(m_user->GetStats(), m_comboer->GetStats()));
			}
		}
	}
	if (!m_partyTargets.empty())
	{
		for (int i = 0; i < m_partyTargets.size(); i++)
		{
			if (m_comboer == NULL)
			{
				m_partyTargets[i]->GetStats()->Heal(_effect->GetDamage(m_user->GetStats()));
			}
			else
			{
				m_partyTargets[i]->GetStats()->Heal(_effect->GetDamage(m_user->GetStats(), m_comboer->GetStats()));
			}
		}
	}

	if (!m_aniList.empty())
	{
		for (int i = 0; i < m_aniList.size(); i++)
		{
			if (m_comboer == NULL)
			{
				m_texts->AddNewText(std::to_string(_effect->GetDamage(m_user->GetStats())), m_aniList[i].x + 100, m_aniList[i].y + 100, 0, 255, 0);
			}
			else
			{
				m_texts->AddNewText(std::to_string(_effect->GetDamage(m_user->GetStats(), m_comboer->GetStats())), m_aniList[i].x + 100, m_aniList[i].y + 100, 0, 255, 0);
			}
		}
	}
}