#include "pch.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	m_strName = "노란귤이좋아";
	m_eState = P_IDLE;
	
	m_nLevel = 1;	
	m_nExp = 0;

	m_eArmor = A_LIGHT;

	CalcMaxHp();
	m_nCurrHp = m_nMaxHp;	

	m_nAtt = 10;	

	m_eCurrPlace = EP_TOWN;
}


cPlayer::~cPlayer()
{
}

void cPlayer::IncreaseExp(int exp)
{
	// 0 ~ 99 : 1  // 100 ~ 200 : 2
	m_nExp += exp;
	if (m_nLevel * 100 < m_nExp)
		m_nLevel = m_nExp / 100 + 1;

}

void cPlayer::CalcMaxHp() // 장비 착용시 능력치 변경을 위해 호출
{
	switch (m_eArmor)
	{
	case A_LIGHT:
		m_nMaxHp = 150;
		break;
	case A_MEDIUM:
		m_nMaxHp = 200;
		break;
	case A_HEAVY:
		m_nMaxHp = 300;
		break;
	case A_EMPTY:
		m_nMaxHp = 100;
		break;
	}
}

void cPlayer::CalcAttDamage()
{
}

	

