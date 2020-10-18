#pragma once
#include "pch.h"

// 대기,전투,이동
enum E_PSTATE{ P_IDLE, P_FIGHT, P_WALK,};
enum E_ARMOR { A_EMPTY, A_LIGHT, A_MEDIUM, A_HEAVY};

class cPlayer
{
private:
	string		m_strName;	//캐릭터 이름
	E_PSTATE	m_eState;	//캐릭터 상택
	int			m_nLevel;	//레벨
	int			m_nExp;		//경험치
	int			m_nMaxHp;	//최대 체력
	int			m_nCurrHp;	//현재 체력
	int			m_nAtt;		//공격력

	E_ARMOR m_eArmor;

	E_PLACE m_eCurrPlace; // 현재 캐릭터 장소;

public:
	cPlayer();
	~cPlayer();

	string GetName() { return m_strName; }
	E_PSTATE GetState() { return m_eState; }
	int GetLevel() { return m_nLevel; }
	int GetExp() { return m_nExp; }
	int GetMaxHp() { return m_nMaxHp; }
	int GetCurrHp() { return m_nCurrHp; }
	void SetMaxHp() { m_nCurrHp = m_nMaxHp; }
	int GetAttDamage() { return m_nAtt; }
	int GetExDamage() { return rand() % 6; }
	void TakeDamage(int damage) { m_nCurrHp -= damage; }

	E_PLACE GetPlace() { return m_eCurrPlace; }
	void SetPlace(E_PLACE place) { m_eCurrPlace = place; }


	void IncreaseExp(int exp);
	void CalcMaxHp();
	void CalcAttDamage();
};

