// SGA.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.



#include "pch.h"
#include "cPlayer.h"
#include "cMonster.h"

void Town(cPlayer* player, bool& playing);
void Store(cPlayer* player);
void Dungeon(cPlayer* player);

int main()
{	
	bool		isPlaying = true;
	bool		nSelect;
	cPlayer*	pPlayer = new cPlayer();
	while (isPlaying) {
		system("cls");
		
		cout << "이름 : " << pPlayer->GetName().c_str()  << endl;
		cout << "레벨 : " << pPlayer->GetLevel() << endl;		
		cout << "체력 : " << pPlayer->GetCurrHp() << " / " << pPlayer->GetMaxHp() << endl;
		cout << "공격력 : " << pPlayer->GetAttDamage() << endl<<endl;

		cout << "현재 장소 : ";
		switch (pPlayer->GetPlace())
		{
		case EP_QUIT:
			cout << "게임을 종료합니다" << endl;
			isPlaying = false;
			break;
		case EP_TOWN:
			cout << "마을" << endl;
			Town(pPlayer, isPlaying);
			break;
		case EP_STORE:
			cout << "상점" << endl;
			Store(pPlayer);
			break;
		case EP_DUNGEON:
			cout << "던전" << endl;
			Dungeon(pPlayer);
			break;
		}	
		Sleep(2000);
	}
	
	delete pPlayer;

	system("pause");
}








// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

void Town(cPlayer * player, bool& playing)
{
	int nSelect;
	
	cout << "1.여관 2.상점 3.던전 (0.게임 종료) : ";
	cin >> nSelect;

	if (nSelect == 1) {
		cout << "휴식을 취합니다 최대 체력으로 회복" << endl;
		cout << "마을로 돌아갑니다." << endl;
		player->SetMaxHp();
		player->SetPlace(EP_TOWN);
	}
	else if (nSelect == 2) {
		cout << "상점으로 이동합니다." << endl;
		player->SetPlace(EP_STORE);
	}
	else if (nSelect == 3) {
		cout << "던전으로 이동합니다." << endl;
		player->SetPlace(EP_DUNGEON);
	}
	else if (nSelect == 0) {
		player->SetPlace(EP_QUIT);
	}
	else {
		cout << "제대로 입력하세요" << endl;
	}

}

void Store(cPlayer * player)
{
	cout << "상점이 비었습니다 마을로 돌아값니다." << endl;
	player->SetPlace(EP_TOWN);
	
}

void Dungeon(cPlayer * player)
{
	cout << "던전으로 이동합니다. 몬스터와 전투를 시작합니다." << endl;
	
	cMonster* pMonster = new cMonster("오우거",200,20,300);
	cout << "몬스터 이름 : " << pMonster->GetName().c_str() << endl;
	cout << "몬스터 체력 : " << pMonster->GetHp() << endl;
	cout << "몬스터 공격력 : " << pMonster->GetAttDamage() << endl;
	cout << "====================================================" << endl << endl;
	while (true) {	


		int nDamage = player->GetAttDamage() + player->GetExDamage();
		cout << "플레이어가 공격합니다. : " << nDamage << endl;
		pMonster->TakeDamage(nDamage);
		Sleep(500);

		if (pMonster->GetHp() <= 0) {
			cout << "몬스터를 처치했습니다" << endl;
			cout << "경험치 " << pMonster->GetExp() << "를 획득했습니다" << endl;
			player->IncreaseExp(pMonster->GetExp());
			break;
		}

		nDamage = pMonster->GetAttDamage() + pMonster->GetExDamage();
		cout << "몬스터가 공격합니다. : " << nDamage << endl;
		player->TakeDamage(nDamage);
		Sleep(500);

		if (player->GetCurrHp() <= 0) {
			cout << "플레이어가 죽었습니다" << endl;
			
			break;
		}
	}
	cout << "마을로 돌아갑니다." << endl;
	Sleep(2000);
	player->SetPlace(EP_TOWN);

	delete pMonster;
}
