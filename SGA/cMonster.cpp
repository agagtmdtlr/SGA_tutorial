#include "pch.h"
#include "cMonster.h"


cMonster::cMonster()
{
	m_strName = "ΩΩ∂Û¿”";
	m_nHp = 50;
	m_nAtt = 5 + rand() % 11;
	m_nExp = 100;
}

cMonster::cMonster(string Name, int hp, int att, int exp) {
	m_strName = Name;
	m_nHp = hp;
	m_nAtt = att;
	m_nExp = exp;
}


cMonster::~cMonster()
{
}
