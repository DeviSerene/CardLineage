#include "EnemyController.h"



EnemyController::EnemyController(int* _battleState, int* _target, int* _targetType, std::shared_ptr<BattleEffect>& _effman, std::vector<std::shared_ptr<Character>>& _partyPointer, std::vector<std::shared_ptr<Enemy>>& _enemyPointer, std::vector<SDL_Rect> _partyPos, std::vector<SDL_Rect> _enemyPos)
{
	m_battleState = _battleState;
	m_target = _target;
	m_targetType = _targetType;
	m_effman = _effman;
	m_party = _partyPointer;
	m_enemies = _enemyPointer;
	m_partyPos = _partyPos;
	m_enemyPos = _enemyPos;

	m_phase = 0;
	m_current = 0;
}


EnemyController::~EnemyController()
{
	m_battleState = nullptr;
	m_target = nullptr;
	m_targetType = nullptr;
}

void EnemyController::Update(float& _deltaTime)
{

	if (m_enemies.size() > m_current)
	{
		if (!m_enemies[m_current]->IsDead())
		{
			switch (m_phase)
			{
			case 0:
				if (MoveUp())
				{
					m_phase++;
				}
				break;
			case 1:
				if (m_effman->IsEffectEmpty())
				{
					PerformAbility();
					m_phase++;
				}
				break;
			case 2:
				if (m_effman->IsEffectEmpty())
				{
					if (MoveBack())
					{
						m_current++;
						m_phase = 0;
					}
				}
				break;
			default:
				break;
			}
		}
		else
		{
			m_current++;
			m_phase = 0;
		}
	}
	else
	{
		m_phase = 0;
		m_current = 0;
		*m_battleState = 0;
		//reached the end
	}
}

bool EnemyController::MoveUp()
{
	m_enemies[m_current]->MoveTo({ m_enemyPos[m_current].x - 20 , m_enemyPos[m_current].y,m_enemyPos[m_current].w,m_enemyPos[m_current].h });
	return m_enemies[m_current]->FinishMoving();
}

bool EnemyController::MoveBack()
{
	m_enemies[m_current]->MoveTo(m_enemyPos[m_current]);
	return m_enemies[m_current]->FinishMoving();
}

bool EnemyController::PerformAbility()
{
	//AI will be performed, tis is just temporary
	*m_targetType = m_enemies[m_current]->GetAbilities()[0]->m_target;
	*m_target = rand() % m_party.size();
	m_effman->SetUser(m_current, m_enemies[m_current]->GetStats(), true);
	m_effman->AddEffects(m_enemies[m_current]->GetAbilities()[0]->m_effects, m_enemies[m_current]->GetAbilities()[0]->m_aniEffects);
	m_enemies[m_current]->SetAnimation(m_enemies[m_current]->GetAbilities()[0]->m_userAni);
	return true;
}

