#pragma once
#include <vector>
#include <string>
#include "Stats.h"
#include <memory>

class Effect
{
public:
	Effect(int _ID, int v1 = 0, int v2 = 0, int v3 = 0, int v4 = 0, int v5 = 0, int v6 = 0, int v7 = 0, int v8 = 0);
	~Effect();

	int GetIDType() { return m_variables[0]; }
	std::vector<int> GetVar() { return m_variables; }
	int GetTargetInfo();
	std::string GetDescription(std::shared_ptr<Stats> _user, std::shared_ptr<Stats> _combo = NULL);

	int GetDamage(std::shared_ptr<Stats> _user, std::shared_ptr<Stats> _combo = NULL);
	int GetDType() { return m_variables[5]; }
	int GetElement() {return m_variables[4];}

private:
	std::vector<int> m_variables;

	std::string GetElement(int _i);
	std::string GetDamageType(int _i);
	std::string GetTargetType(int _i);
};

