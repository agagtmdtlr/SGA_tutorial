// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

#ifndef PCH_H
#define PCH_H




// TODO: 여기에 미리 컴파일하려는 헤더 추가
#include <random>
#include <time.h>
#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <conio.h>
#include <string>


// 텍스트형 rpg
enum E_PLACE { EP_QUIT = 0, EP_TOWN, EP_STORE, EP_DUNGEON };

// 숫자 슬라이드 퍼즐 게임

void NumberSlideGame();

void Keyboard(bool* playing, int puzzle[5][5], int* x, int* y);
void InitPuzzle(int puzzle[5][5]);
void Print(HANDLE hOP, int puzzle[5][5], int x, int y); // 화면에 퍼즐
void DrawBlock(HANDLE hOP, int x, int y, char *str, WORD color);

void Swap(int* prevBlock, int* currBlock); // 두블럭을 교체해주는 함수
bool Check(int puzzle[5][5]);

//0 1 2 3 4 5 6 7 8 9 A B C D E F
//10~40
#define BG_00 0x0010
#define BG_01 0x0013
#define BG_02 0x0016
#define BG_03 0x0019
#define BG_04 0x001C
#define BG_05 0x001F
#define BG_06 0x0022
#define BG_07 0x0025
#define BG_08 0x0028
#define BG_09 0x002B
#define BG_10 0x002E
#define BG_11 0x0031
#define BG_12 0x0034
#define BG_13 0x0037
#define BG_14 0x003A
#define BG_15 0x0040

// 1 ~ 4
#define FG_00 0x00000
#define FG_01 0x00010
#define FG_02 0x0001A
#define FG_03 0x00012
#define FG_04 0x0001
#define FG_05 0x0005
#define FG_06 0x0006
#define FG_07 0x0007
#define FG_08 0x0008
#define FG_09 0x0009
#define FG_10 0x000A
#define FG_11 0x000B
#define FG_12 0x000C
#define FG_13 0x000D
#define FG_14 0x000E
#define FG_15 0x0004

#define CHARACTER_Y 36
#define CHARACTER_X 20

struct _ChInfo
{
	int x;
	int y;
};



enum E_STATE { E_IDLE = 0, E_MOVE_LEFT, E_MOVE_RIGHT, E_MOVE_UP, E_MOVE_DOWN, E_FIGHT, E_STATE_NMAX };
enum E_FIGHT { E_AWAY, E_ATTACK, E_DEFFENCE, E_MAGIC, E_FMAX };
enum E_MONTYPE { E_ORC, E_ELF, E_TROLL, E_MONMAX };
void RockSiccorPaper();
void gugudan();
void WallNamPPong();
void DottingStar1();
void DottingStar2();
void TextRPG();
using namespace std;


// 빙고

void BingoGame();
void InitTable(int* table);
void InitWeight(int* table);
void ShowTable(int* table);
void HideTable(int* table);
void UserSelect(int* userTable, int* comTable, int* weightTable);
void ComSelect(int* userTable, int* comTable, int* weightTable);
int CheckingBingo(int* table);

// superman graphic
void SuperGarphic();

void __Keyboard(bool* playing, _ChInfo* chinfo);
void __Draw(HANDLE hOP, int x, int y, const char* str, WORD color);
void __CallDraw(HANDLE hOP, int character[CHARACTER_Y][CHARACTER_X],
	_ChInfo *chinfo, bool posiLR);
void __Superman(HANDLE hOP, _ChInfo *chinfo, bool posiLR);


// 하이로우세븐
// 5장 오픈
// 다음 카드가 7보다 같다,작다,크다 맞추기
enum E_SHAPE { E_SPADE, E_DIA, E_HEART, E_CLOVER, E_MAX };
enum E_SELECT { E_QUIT, E_HIGH, E_LOW, E_SEVEN };

struct tagCard {
	char*	szShape;
	int		nNumber;

};

void HighLowSeven();
void InitCards(tagCard* cards);
void Shuffle(tagCard* cards);
void Print(tagCard* cards);
void Print(tagCard* cards, int index);
void Playing(tagCard* cards, int* money, int* index, bool* playing);
int Batting(int money);

// 도트 그래픽 움직임 구현
void Keyboard(bool* playing, int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);
void DoteDraw();
#endif //PCH_H
