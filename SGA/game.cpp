#include "pch.h"

// 숫자 슬라이드 퍼즐 게임

void NumberSlideGame() {
	system("mode con:lines=25 cols=48"); //lines : 세로 cols : 가로


	HANDLE hOP; // 핸들 값 가져 오기
	hOP = GetStdHandle(STD_OUTPUT_HANDLE);

	// 커서 숨기기
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(hOP, &curInfo);


	bool isPlaying = true;
	int nPuzzle[5][5];
	int nX = 4, nY = 4; // 처음 빈칸 인덱스 번호

	InitPuzzle(nPuzzle);
	Print(hOP, nPuzzle, nX, nY);

	while (isPlaying)
	{
		if (_kbhit()) { // 아무 키를 누르면 true가 반환 된다.			

			system("cls");

			Keyboard(&isPlaying, nPuzzle, &nX, &nY);
			Print(hOP, nPuzzle, nX, nY);
			isPlaying = !Check(nPuzzle);

			if (isPlaying == false) {
				cout << "게임 클리어 : 게임을 종료합니다" << endl;
				system("pause");
			}

			while (_kbhit()) _getch(); // 버퍼 리셋 (버퍼에 데이터가 남아있지 않을때까지 지운다.
		}
	}
}

bool Check(int puzzle[5][5]) {

	bool isComplete = false;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 4 && j == 4)
				isComplete = true;
			if (puzzle[i][j] != j + 1 + i * 5)
				break;
		}
	}

	return isComplete;
}

void Swap(int* prevBlock, int* currBlock) {
	int nTemp = *prevBlock;
	*prevBlock = *currBlock;
	*currBlock = *prevBlock;
}

void Print(HANDLE hOP, int puzzle[5][5], int x, int y) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			//숫자를 문자로 변환
			char* szTemp = new char;
			//itoa : 정수값을 문자로 변환하는 함수;
			if (j == x && i == y) {
				DrawBlock(hOP, 10 + j * 6, 5 + i * 3, (char*)"■", BACKGROUND_RED | FOREGROUND_GREEN);
			}
			else {
				DrawBlock(hOP, 10 + j * 6, 5 + i * 3, itoa(puzzle[i][j], szTemp, 10), BACKGROUND_RED | FOREGROUND_GREEN);
			}

		}
	}
}

void DrawBlock(HANDLE hOP, int x, int y, char *str, WORD color) {
	Draw(hOP, x + 0, y + 0, str, color);
	Draw(hOP, x + 2, y + 0, (char*)"■", color);
	Draw(hOP, x + 0, y + 1, (char*)"■", color);
	Draw(hOP, x + 2, y + 1, (char*)"■", color);
}

void InitPuzzle(int puzzle[5][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			puzzle[i][j] = i * 5 + j + 1;
		}
	}

	for (int i = 0; i < 1000; i++) {
		int nDestX = rand() % 5;
		int nDestY = rand() % 5;

		int nSrcX = rand() % 5;
		int nSrcY = rand() % 5;

		if ((nDestX == 4 && nDestY == 4) || (nSrcX == 4 && nSrcY == 4) ||
			(nDestX == nSrcX && nDestY == nSrcY)) { // 실제로 스왑을 시키지 않는 경우
			i--;
			continue;
		}
		int nTemp = puzzle[nDestX][nDestY];
		puzzle[nDestX][nDestY] = puzzle[nSrcX][nSrcY];
		puzzle[nSrcX][nSrcY] = nTemp;
	}
}

void Keyboard(bool* playing, int puzzle[5][5], int* x, int* y) {
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && *x < 4) {
		Swap(&puzzle[*y][*x], &puzzle[*y][*x + 1]);
		(*x)++;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000 && *x > 0) {
		Swap(&puzzle[*y][*x], &puzzle[*y][*x - 1]);
		(*x)--;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000 && *y > 0) {
		Swap(&puzzle[*y][*x], &puzzle[*y - 1][*x]);
		(*y)--;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && *y < 4) {
		Swap(&puzzle[*y][*x], &puzzle[*y + 1][*x]);
		(*y)++;
	}
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // ESC
		*playing = false;
}

// superman graphic

void SuperGarphic() {
	HANDLE hOP; // 핸들 값 가져 오기
	hOP = GetStdHandle(STD_OUTPUT_HANDLE);
	_ChInfo chinfo = { 0,0 };
	// 커서 숨기기
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(hOP, &curInfo);

	bool isPlaying = true;
	bool posiLR = true;
	__Superman(hOP, &chinfo, posiLR);
	while (isPlaying) {
		if (_kbhit()) {
			__Keyboard(&isPlaying, &chinfo);
			system("cls");
			__Superman(hOP, &chinfo, posiLR);
			while (_kbhit)_getch();
		}
	}

	//for (int i = 0; i < 16; i++) {
	//	
	//	//cout << ((INT16)(16 + (i*3)) | (INT16)(1 + (i*0.3))) << endl;
	//	//| (INT16)(1+(i*0.3))
	//	pr
	//	__Draw(hOP, 0, i, "■", (INT16)(16+(i*3)) );
	//}
	system("pause");
}


void __Keyboard(bool* playing, _ChInfo* chinfo) {
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // 오른쪽 방향키
		(chinfo->x)++;
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 왼쪽 방향키
		(chinfo->x)--;
	else if (GetAsyncKeyState(VK_UP) & 0x8000) // 위쪽 방향키
		(chinfo->y)--;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) // 아래 방향키
		(chinfo->y)++;
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // ESC
		*playing = false;
}
void __Draw(HANDLE hOP, int x, int y, const char* str, WORD color) {
	DWORD dwCharsWritten;
	COORD cdFill = { x,y };
	FillConsoleOutputAttribute(hOP, color, strlen(str), cdFill, &dwCharsWritten);
	//FillConsoleOutputCharacter(hOP, color, strlen(str), cdFill, &dwCharsWritten);
	WriteConsoleOutputCharacter(hOP, str, strlen(str), cdFill, &dwCharsWritten);
}

void __CallDraw(HANDLE hOP, int character[CHARACTER_Y][CHARACTER_X],
	_ChInfo *chinfo, bool posiLR) {
	int i, j, k;
	int temp[CHARACTER_Y][CHARACTER_X];

	if (posiLR) {
		for (i = 0; i < CHARACTER_Y; i++) {
			for (j = 0; j < CHARACTER_X; j++) {
				temp[i][j] = character[i][j];
			}
		}
	}
	else {
		for (i = 0; i < CHARACTER_Y; i++) {
			for (j = 0; j < CHARACTER_X; j++) {
				k = CHARACTER_X - 1 - j;
				temp[i][j] = character[i][j];
			}
		}
	}

	for (i = 0; i < CHARACTER_Y; i++) {
		for (j = 0; j < CHARACTER_X; j++) {
			switch (temp[i][j])
			{
			case 0:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_00 | FG_00);
				break;
			case 1:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_01 | FG_01);
				break;
			case 2:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_02 | FG_02);
				break;
			case 3:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_03 | FG_03);
				break;
			case 4:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_04 | FG_04);
				break;
			case 5:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_05 | FG_05);
				break;
			case 6:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_06 | FG_06);
				break;
			case 7:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_07 | FG_07);
				break;
			case 8:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_08 | FG_08);
				break;
			case 9:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_09 | FG_09);
				break;
			case 10:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_10 | FG_10);
				break;
			case 11:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_11 | FG_11);
				break;
			case 12:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_12 | FG_12);
				break;
			case 13:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_13 | FG_13);
				break;
			case 14:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_14 | FG_14);
				break;
			case 15:
				__Draw(hOP, chinfo->x + j * 2, chinfo->y + i, "■", BG_15 | FG_15);
				break;
			}
		}
	}
}
void __Superman(HANDLE hOP, _ChInfo *chinfo, bool posiLR) {
	int character[CHARACTER_Y][CHARACTER_X] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 5, 5, 1, 1, 5, 5, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 1, 5, 5, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 1, 5, 5, 5, 5, 1, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 5, 5,13,13, 5, 5, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0,13,13,13, 5, 5,13,13,13, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0,13,13,13, 8, 8, 8, 8,13,13,13, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8, 8,13,13,13,13, 8, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8,13,15,15,15,15,13, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8,15,13,13,13,15,15, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8, 8,15,15,13,13,15, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8, 8,13,15,13,13, 8, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8, 8, 8,13,13, 8, 8, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8,15,15,15,15,15,15, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8,13,13,13,13,13,13, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8, 8,13,13,13,13, 8, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 8, 8, 8, 8,13,13, 8, 8, 8, 8,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 5, 5, 8, 8,13,13, 8, 8, 5, 5,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13, 5,13, 8, 8,13,13, 8, 8,13, 5,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13,13,13, 8, 8,13,13, 8, 8,13,13,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13,13,13, 8, 8,13,13, 8, 8,13,13,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13,13,13, 8, 8,13,13, 8, 8,13,13,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13,13,13, 8, 8,13,13, 8, 8,13,13,13, 0, 0, 0, 0 },
		{ 0, 0, 0, 0,13,13,13,13, 8,13,13, 8,13,13,13,13, 0, 0, 0, 0 },
		{ 0, 0, 0,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 0, 0, 0 },
		{ 0, 0,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	__CallDraw(hOP, character, chinfo, posiLR);
}
// dote graphic moving draw
void DoteDraw() {

	HANDLE hOP; // 핸들 값 가져 오기
	hOP = GetStdHandle(STD_OUTPUT_HANDLE);

	// 커서 숨기기
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(hOP, &curInfo);



	bool isPlaying = true;
	int x = 10, y = 10;

	cout << "x 좌표 : " << x << " y 좌표 : " << y << endl;
	Draw(hOP, x * 2, y, (char*)"A", BACKGROUND_RED);

	while (isPlaying)
	{
		if (_kbhit()) { // 아무 키를 누르면 true가 반환 된다.
			Keyboard(&isPlaying, &x, &y);

			system("cls");
			cout << "x 좌표 : " << x << " y 좌표 : " << y << endl;
			Draw(hOP, x * 2, y, (char*)"A", BACKGROUND_RED);
			while (_kbhit()) _getch(); // 버퍼 리셋 (버퍼에 데이터가 남아있지 않을때까지 지운다.
		}
	}
}
void Keyboard(bool* playing, int* x, int* y) {
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // 오른쪽 방향키
		(*x)++;
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 왼쪽 방향키
		(*x)--;
	else if (GetAsyncKeyState(VK_UP) & 0x8000) // 위쪽 방향키
		(*y)--;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) // 아래 방향키
		(*y)++;
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // ESC
		*playing = false;
}

void Draw(HANDLE hOP, int x, int y, char* str, WORD color) {
	DWORD dwCharsWritten;
	COORD cdFill = { x,y };

	FillConsoleOutputAttribute(hOP, color, strlen(str), cdFill, &dwCharsWritten);
	WriteConsoleOutputCharacter(hOP, str, strlen(str), cdFill, &dwCharsWritten);
	
}

//highlowseven

void HighLowSeven() {
	srand(time(NULL));
	rand();

	tagCard stCards[52];
	bool	isPlaying = true;
	int		nMyMoney = 10000;
	int		nCurrIndex = 5;


	InitCards(stCards);
	Shuffle(stCards);
	Print(stCards);

	while (isPlaying)
	{
		system("cls");

		Print(stCards, nCurrIndex);

		if (nMyMoney < 100) {
			cout << " 거지 입니다 " << endl;
			isPlaying = false;
		}
		else if (nCurrIndex > 42) {
			Shuffle(stCards);
			nCurrIndex = 5;
			cout << " 새 카드로 계속 진행" << endl;

		}
		else {
			Playing(stCards, &nMyMoney, &nCurrIndex, &isPlaying);
			nCurrIndex += 6;
			Sleep(2000);
		}
	}

	cout << " 게임을 종료 합니다" << endl;
}

void Playing(tagCard* cards, int* money, int* index, bool* playing) {
	int nSelect;
	E_SELECT eSelect;
	int nBet;

	cout << "현재 금액 : " << *money << endl;
	cout << "1.하이 2.로우 3.세븐 (0.종료) : ";
	cin >> nSelect;
	eSelect = (E_SELECT)nSelect;
	switch (eSelect) {
	case E_HIGH:
		nBet = Batting(*money);

		if (cards[*index].nNumber > 7) {
			cout << "배팅 성공 : ";
			*money += nBet;
		}
		else {
			cout << "배팅 실패 : ";
			*money -= nBet;
		}

		cout << cards[*index].szShape << cards[*index].nNumber << endl;
		break;
	case E_LOW:
		nBet = Batting(*money);
		if (cards[*index].nNumber < 7) {
			cout << "배팅 성공 : ";
			*money += nBet;
		}
		else {
			cout << "배팅 실패 : ";
			*money -= nBet;
		}

		cout << cards[*index].szShape << cards[*index].nNumber << endl;
		break;
	case E_SEVEN:
		nBet = Batting(*money);
		if (cards[*index].nNumber == 7) {
			cout << "배팅 성공 : ";
			*money += nBet * 2;
		}
		else {
			cout << "배팅 실패 : ";
			*money -= nBet;
		}

		cout << cards[*index].szShape << cards[*index].nNumber << endl;
		break;
	case E_QUIT:
		cout << " 게임 종료 " << endl;
		*playing = false;
		break;
	}


}
int Batting(int money) {
	int nBet = 0;

	while (nBet < 100 || nBet > money) {
		cout << " 금액을 배팅하시오 : ";
		cin >> nBet;
	}

	return nBet;
}

void InitCards(tagCard* cards) {
	for (E_SHAPE i = E_SPADE; i < E_MAX; i = (E_SHAPE)(i + 1)) {
		for (int j = 0; j < 13; j++) {
			switch (i)
			{
			case E_SPADE:
				cards[j + 13 * i].szShape = (char*)"♠";
				break;
			case E_DIA:
				cards[j + 13 * i].szShape = (char*)"◆";
				break;
			case E_HEART:
				cards[j + 13 * i].szShape = (char*)"♥";
				break;
			case E_CLOVER:
				cards[j + 13 * i].szShape = (char*)"♣";
				break;
			}

			cards[j + 13 * i].nNumber = j + 1;
		}
	}
}
void Shuffle(tagCard* cards) {
	int select;
	tagCard temp;
	for (int i = 0; i < 52; i++) {
		select = rand() % (52 - i) + i;
		temp = cards[i];
		cards[i] = cards[select];
		cards[select] = temp;
	}
}

void Print(tagCard* cards, int index) {
	for (int i = index - 5; i < index; i++) {
		cout << cards[i].szShape << cards[i].nNumber << "\t";

	}
	cout << "\t( ? )" << endl;
}

void Print(tagCard* cards) {
	for (int i = 0; i < 52; i++) {
		switch (cards[i].nNumber)
		{
		case 1:
			cout << cards[i].szShape << "A" << "\t";
			break;
		case 11:
			cout << cards[i].szShape << "J" << "\t";
			break;
		case 12:
			cout << cards[i].szShape << "Q" << "\t";
			break;
		case 13:
			cout << cards[i].szShape << "K" << "\t";
			break;
		default:
			cout << cards[i].szShape << cards[i].nNumber << "\t";
			break;
		}

		if (i % 13 == 12) cout << endl;
	}
}

//bingo

void BingoGame() {
	srand(time(NULL));
	rand();

	int nUserTable[25];
	int nUserBingo = 0;

	int nComTable[25];
	int nComWeight[25];
	int nComBingo = 0;

	bool isPlaying = true;
	bool isMyTurn = true;
	while (isPlaying) {

		// play
		InitTable(nUserTable);
		InitTable(nComTable);
		InitWeight(nComWeight);

		while (true) {
			system("cls");

			// 빙고 확인
			nUserBingo = CheckingBingo(nUserTable);
			nComBingo = CheckingBingo(nComTable);

			// 테이블 확인
			ShowTable(nUserTable);
			cout << "유저 : " << nUserBingo << endl;
			HideTable(nComTable);
			cout << "컴퓨터 : " << nComBingo << endl;
			/*ShowTable(nComWeight);*/


			if (nUserBingo >= 3 && nComBingo >= 3) {
				cout << "무승부" << endl;
				break;
			}
			else if (nUserBingo >= 3) {
				cout << "유저 승리" << endl;
				break;
			}
			else if (nComBingo >= 3) {
				cout << "컴퓨터 승리" << endl;
				break;
			}

			// 턴 확인
			if (isMyTurn) {
				UserSelect(nUserTable, nComTable, nComWeight);
				isMyTurn = false;
			}
			else {
				ComSelect(nUserTable, nComTable, nComWeight);
				isMyTurn = true;
			}
		}
		// stop
		cout << "0:게임 종료 1:새 게임 : ";
		cin >> isPlaying;
	}
}


int CheckingBingo(int* table) {

	/*
	0	1	2	3	4
	5	6	7	8	9
	10	11	12	13	14
	15	16	17	18	19
	20	21	22	23	24
	*/
	int nBingo = 0;
	//가로
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (table[j + i * 5] == 0) {
				if (j == 4) {
					cout << "가로" << endl;
					nBingo++;
				}
			}
			else {
				break;
			}
		}
	}

	//세로
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (table[i + j * 5] == 0) {
				if (j == 4) {
					cout << "세로" << endl;
					nBingo++;
				}
			}
			else {
				break;
			}
		}
	}

	//왼쪽 대각선
	for (int i = 0; i < 5; i++) {
		if (table[i + i * 5] == 0) {
			if (i == 4) {
				cout << "왼쪽 대각선" << endl;
				nBingo++;
			}
		}
		else {
			break;
		}
	}

	//오른쪽 대각선
	for (int i = 0; i < 5; i++) {
		if (table[(i + 1) * 4] == 0) {
			if (i == 4) {
				cout << "오른쪽 대각선" << endl;
				nBingo++;
			}
		}
		else {
			break;
		}
	}

	return nBingo;

}

void ComSelect(int* userTable, int* comTable, int* weightTable) {
	int nSelect = 0;
	int sleeptime = 0;
	cout << "컴퓨터 선택 중";
	Sleep(sleeptime);
	cout << ".";
	Sleep(sleeptime);
	cout << ".";
	Sleep(sleeptime);
	cout << ".";

	for (int i = 0; i < 25; i++) {
		if (weightTable[nSelect] < weightTable[i]) {
			nSelect = i;
		}
	}

	// searching table
	for (int i = 0; i < 25; i++) {
		if (nSelect == userTable[i]) {
			userTable[i] = 0;
			break;
		}
	}
	comTable[nSelect] = 0;
	weightTable[nSelect] = 0;
	for (int j = 0; j < 5; j++) {
		if (nSelect % 5 == nSelect / 5) {
			if (j * 5 + j != nSelect && comTable[j * 5 + j] != 0) {
				weightTable[j * 5 + j] += 1;
			}
		}
		if (4 - (nSelect / 5) == nSelect % 5) {
			if ((j + 1) * 4 != nSelect && comTable[(j + 1) * 4] != 0) {
				weightTable[(j + 1) * 4] += 1;
			}
		}
		if (nSelect % 5 + j * 5 != nSelect && comTable[nSelect % 5 + j * 5] != 0) {
			weightTable[nSelect % 5 + j * 5] += 1;
		}
		if ((nSelect / 5) * 5 + j != nSelect && comTable[(nSelect / 5) * 5 + j] != 0) {
			weightTable[(nSelect / 5) * 5 + j] += 1;
		}
		cout << nSelect % 5 + j * 5 << " | " << (nSelect / 5) * 5 + j << endl;
	}

	system("pause");
}

void UserSelect(int* userTable, int* comTable, int* weightTable) {
	int nSelect;
	bool isUserFind = false;
	bool isComFind = false;
	cout << "선택 ( 1 ~ 25 ) : ";
	cin >> nSelect;

	/*
	3	0	0	0	3
	0	3	0	3	0
	0	0	4	0	0
	0	3	0	3	0
	3	0	0	0	3
	*/
	// select table
	for (int i = 0; i < 25; i++) {
		if (nSelect == userTable[i]) {
			userTable[i] = 0;
			isUserFind = true;
		}
		if (nSelect == comTable[i]) {
			comTable[i] = 0;
			weightTable[i] = 0;
			isComFind = true;
			for (int j = 0; j < 5; j++) {
				if (i % 5 == i / 5) {
					if (j * 5 + j != i && comTable[j * 5 + j] != 0) {
						weightTable[j * 5 + j] += 1;
					}
				}
				if (4 - (i / 5) == i % 5) {
					if ((j + 1) * 4 != i && comTable[(j + 1) * 4] != 0) {
						weightTable[(j + 1) * 4] += 1;
					}
				}
				if (i % 5 + j * 5 != i && comTable[i % 5 + j * 5] != 0) {
					weightTable[i % 5 + j * 5] += 1;
				}
				if ((i / 5) * 5 + j != i && comTable[(i / 5) * 5 + j] != 0) {
					weightTable[(i / 5) * 5 + j] += 1;
				}
				cout << i % 5 + j * 5 << " | " << (i / 5) * 5 + j << endl;
			}
		}
		if (isUserFind && isComFind) break;
	}

	system("pause");

}

void ShowTable(int* table) {
	cout << "================================================================================" << endl;
	for (int i = 0; i < 25; i++) {
		cout << "|	" << table[i] << "\t|";
		if (i % 5 == 4) {
			cout << endl;
			cout << "================================================================================" << endl;
		}
	}
}

void HideTable(int* table) {
	cout << "================================================================================" << endl;
	for (int i = 0; i < 25; i++) {
		if (table[i] == 0) {
			cout << "|	" << table[i] << "\t|";
		}
		else {
			cout << "|\t?\t|";
		}

		if (i % 5 == 4) {
			cout << endl;
			cout << "================================================================================" << endl;
		}
	}
}

void InitTable(int* table) {
	for (int i = 0; i < 25; i++) {
		table[i] = i + 1;
	}
	int select;
	int temp;
	for (int i = 0; i < 25; i++) {
		select = rand() % (25 - i) + i;
		temp = table[i];
		table[i] = table[select];
		table[select] = temp;
	}
}

void InitWeight(int* table) {
	for (int i = 0; i < 25; i++) {
		if (i / 5 == 2 && i % 5 == 2) {
			table[i] = 4;
		}
		else if (i / 5 == i % 5 || 4 - (i / 5) == i % 5) {
			table[i] = 3;
		}
		else {
			table[i] = 0;
		}
	}
}

void TextRPG() {
	srand(time(NULL));
	int nSleep = 200;

	E_STATE eState = E_IDLE;
	int nHp = 100;
	int nCoordX = 0, nCoordY = 0;
	int nSelect;

	int nMonHp[E_MONMAX];
	int nMonX[E_MONMAX];
	int nMonY[E_MONMAX];

	char MonName[100];
	int nFightMon;

	for (int i = 0; i < E_MONMAX; i++) {
		nMonHp[i] = 100;
		nMonX[i] = 5 + i * 5;
		nMonY[i] = 0;
	}

	while (true)
	{
		system("cls");
		cout << "현재위치 x : " << nCoordX << " y : " << nCoordY << endl;
		cout << "player hp : " << nHp << endl;
		if (eState == E_IDLE) {
			cout << " 입력하시오 . (0:대기 1:왼쪽 2:오른쪽 3:위쪽 4:아래쪽) : ";
		}
		else if (eState == E_FIGHT) {

			cout << "monster hp : " << nMonHp[nFightMon] << endl;
			cout << " 입력하시오 . (0:도망 1:공격 2:방어 3:마법) : ";
		}
		cin >> nSelect;

		cout << ".";
		Sleep(nSleep);
		cout << ".";
		Sleep(nSleep);
		cout << ".";
		Sleep(nSleep);
		if (eState == E_IDLE) {
			switch (nSelect)
			{
			case E_IDLE:
				cout << "대기" << endl;
				break;
			case E_MOVE_LEFT:
				cout << "왼쪽으로 한칸 이동" << endl;
				nCoordX--;
				break;
			case E_MOVE_RIGHT:
				cout << "오른쪽으로 한칸 이동" << endl;
				nCoordX++;
				break;
			case E_MOVE_UP:
				cout << "왼쪽으로 한칸 이동" << endl;
				nCoordY++;
				break;
			case E_MOVE_DOWN:
				cout << "왼쪽으로 한칸 이동" << endl;
				nCoordY--;
				break;
			default:
				cout << "잘못된 입력 강제로 한턴 휴식" << endl;
				break;
			}

			for (int i = 0; i < E_MONMAX; i++) {
				if (nCoordX == nMonX[i] && nCoordY == nMonY[i] && nMonHp[i] > 0) {
					switch (i)
					{
					case E_ORC:
						cout << "오크를 만났다" << endl;
						break;
					case E_ELF:
						cout << "엘프를 만났다" << endl;
						break;
					case E_TROLL:
						cout << "트롤을 만났다" << endl;
						break;
					}
					nFightMon = i;
					eState = E_FIGHT;
					break;
				}
			}
		}
		else if (eState == E_FIGHT) {
			switch (nSelect) {
			case E_AWAY:
			{
				int nRand = rand() % 3;
				if (nRand == 0) {
					cout << " 탈출 성공" << endl;
					nCoordX++;
					eState = E_IDLE;
				}
				else
				{
					cout << " 탈출 실패" << endl;
				}
				break;
			}
			case E_ATTACK:
			{

				int nRand = rand() % 5 + 20;
				cout << " 공격 : " << nRand << endl;
				nMonHp[nFightMon] -= nRand;
				break;
			}

			case E_DEFFENCE:
				break;
			case E_MAGIC:
				break;
			default:
				cout << "잘못된 입력 강제로 한턴 휴식" << endl;
				break;
			}

			if (nMonHp[nFightMon] <= 0) {
				cout << "몬스터가 죽었습니다." << endl;
				eState = E_IDLE;
			}
		}




		system("pause");
	}
}

void RockSiccorPaper() {
	int nP, nC;
	int nPlayerScore = 0, nComputerScore = 0;
	bool isContinue = true;

	while (isContinue)
	{
		std::cout << "가위 1, 바위 2, 보 3 : ";
		std::cin >> nP;

		nC = rand() % 3 + 1;

		std::cout << "플레이어 : " << nP << "컴퓨터 : " << nC << std::endl;
		if (nP == nC) {
			std::cout << "무승부" << std::endl;
		}
		// 0 < 1 , 1 < 2 < , 2 < 0 : (n+1) % 3
		// 1 < 2 , 2 < 3 < , 3 < 1 : n%3  + 1

		else if (nP != nC) {
			if ((nP % 3) + 1 == nC) {
				std::cout << "컴퓨터 승" << std::endl;
				nComputerScore++;
			}
			else {
				std::cout << "플레이어 승" << std::endl;
				nPlayerScore++;
			}
		}

		if (nComputerScore == 3 || nPlayerScore == 3) {
			cout << nPlayerScore << " : " << nComputerScore << endl;
			isContinue = false;
		}
	}
}

void gugudan() {
	for (int i = 1; i < 9; i += 3) {
		for (int j = 1; j < 10; j++) {
			for (int k = 0; k < 3; k++) {
				cout << k + i << " x " << j << " = " << j * (k + i) << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
}

void baseball() {
	int n1, n2, n3;
	for (int i = 0; i < 3; i++) {
		srand(time(NULL));
		if (i == 0) n1 = rand() % 10;
		if (i == 1) {
			n2 = rand() % 10;
			if (n2 == n1) i = 0;
		}
		if (i == 2) {
			n3 = rand() % 10;
			if (n3 == n2 || n3 == n1) i = 1;
		}
	}
	cout << n1 << n2 << n3 << endl;
	int p1, p2, p3;
	int strike, ball, out;
	while (true) {
		strike = 0; ball = 0; out = 0;
		cout << " 숫자 세개를 순차적으로 입력하시오 : ";
		cin >> p1 >> p2 >> p3;
		
		if (p1 == n1) {
			strike += 1;
		}
		else if (p1 == n2 || p1 == n3) {
			ball += 1;
		}
		else {
			out += 1;
		}

		if (p2 == n2) {
			strike += 1;
		}
		else if (p2 == n1 || p2 == n3) {
			ball += 1;
		}
		else {
			out += 1;
		}

		if (p3 == n3) {
			strike += 1;
		}
		else if (p3 == n1 || p3 == n2) {
			ball += 1;
		}
		else {
			out += 1;
		}

		cout << "strike : " << strike << " ball : " << ball << " out : " << out << endl;
		
	}
}

void WallNamPPong() {
	srand(time(NULL));

	int Cards[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int cardSize = sizeof(Cards) / sizeof(int);
	bool isContinue = true;
	int select, temp;

	int PlayerChoice;

	int nMoney = 200;
	int nBatting;
	int nAddBattiongRatio;

	int Max, Min, Answer;

	while (isContinue) {
		// initialization to Game
		for (int i = 0; i < cardSize; i++) {
			select = rand() % (cardSize - i) + i;
			temp = Cards[i];
			Cards[i] = Cards[select];
			Cards[select] = temp;
			cout << Cards[i] << endl;
		}

		// initialization Min and Max
		if (Cards[1] < Cards[2]) {
			Max = Cards[2];
			Min = Cards[1];
		}
		else {
			Max = Cards[1];
			Min = Cards[2];
		}
		Answer = Cards[0];

		// initialization batting
		int NextCard = 3;
		nBatting = 100;
		nAddBattiongRatio = 2;

		// playing game limit to max 4rounds
		for (NextCard; NextCard < 7; NextCard++) {
			system("cls");
			// showing present event;
			cout << " 현재 보유 금액 : " << nMoney << " 현재 배팅 금액 : " << nBatting * nAddBattiongRatio << endl;
			cout << "현재 확인 가능한 카드 : ";
			for (int i = 1; i < NextCard; i++) {
				cout << Cards[i] << " ";
			}
			// selecting player choice
			cout << "\n스탑 : 1, 승부 : 2, 베팅: 3\n선택 : ";
			std::cin >> PlayerChoice;

			// checking choiced job
			switch (PlayerChoice) {
			case 1:
				cout << "스탑" << endl;
				nMoney -= nBatting * nAddBattiongRatio / 2;
				break;
			case 2:
				break;
			case 3:
				// checking valid to batting
				if (nAddBattiongRatio * nBatting * 2 > nMoney) {
					NextCard--;
					break;
				}
				nAddBattiongRatio *= 2;

				if (Min > Cards[NextCard]) Min = Cards[NextCard];
				if (Max < Cards[NextCard]) Max = Cards[NextCard];


				break;
			}
			// checking result if choice
			if (PlayerChoice == 2 || NextCard == 6) {
				cout << Min << " " << Answer << " " << Max;
				if (Min < Answer&&Answer < Max) {
					cout << "승리" << endl;
					nMoney += nBatting * nAddBattiongRatio;
				}
				else {
					cout << "패배" << endl;
					nMoney -= nBatting * nAddBattiongRatio;
				}
				break;
			}
			else if (PlayerChoice == 1) {
				break;
			}

		}

		cout << " 계임을 계속 하실건가요? 계속 : 1, 중단 : 0\n선택 : ";
		std::cin >> isContinue;

		// check valid to play game minimum money
		if (nMoney < 200)break;
	}
}

void DottingStar1() {
	char chArray[5][5];
	//case1
	for (int i = 0; i < 5 * 5; i++) {
		chArray[i / 5][i % 5] = '*';
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << chArray[i][j];
		}
		cout << endl;
	}
	//case2
	for (int i = 0; i < 5 * 5; i++) {
		if (i / 5 == 0) chArray[i / 5][i % 5] = '_';
		else chArray[i / 5][i % 5] = '*';
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << chArray[i][j];
		}
		cout << endl;
	}
	//case3
	for (int i = 0; i < 5 * 5; i++) {
		if (i % 5 == 0) chArray[i / 5][i % 5] = '_';
		else chArray[i / 5][i % 5] = '*';
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << chArray[i][j];
		}
		cout << endl;
	}
	//case4
	for (int i = 0; i < 5 * 5; i++) {
		if (i / 5 == 4) chArray[i / 5][i % 5] = '_';
		else chArray[i / 5][i % 5] = '*';
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << chArray[i][j];
		}
		cout << endl;
	}
	//case5
	for (int i = 0; i < 5 * 5; i++) {
		if (i % 5 == 5) chArray[i / 5][i % 5] = '_';
		else chArray[i / 5][i % 5] = '*';
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << chArray[i][j];
		}
		cout << endl;
	}
	//case6
	for (int i = 0; i < 5 * 5; i++) {
		if (i % 5 == 0 || i % 5 == 4 || i / 5 == 0 || i / 5 == 4) chArray[i / 5][i % 5] = '_';
		else chArray[i / 5][i % 5] = '*';
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << chArray[i][j];
		}
		cout << endl;
	}
	//case7
	for (int i = 0; i < 5 * 5; i++) {
		if (i % 5 == 0 || i % 5 == 4 || i / 5 == 0 || i / 5 == 4) chArray[i / 5][i % 5] = '*';
		else chArray[i / 5][i % 5] = '_';
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << chArray[i][j];
		}
		cout << endl;
	}
}

void DottingStar2() {
	char chArray[5][5];

	for (int i = 0; i < 5 * 5; i++) {
		if (i % 5 <= i / 5) chArray[i / 5][i % 5] = '*';
		else chArray[i / 5][i % 5] = '_';
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << chArray[i][j];
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 5 * 5; i++) {
		if (i % 5 < 4 - i / 5) chArray[i / 5][i % 5] = '_';
		else chArray[i / 5][i % 5] = '*';
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << chArray[i][j];
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 5 * 5; i++) {
		if (i % 5 < i / 5) chArray[i / 5][i % 5] = '_';
		else chArray[i / 5][i % 5] = '*';
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << chArray[i][j];
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 5 * 5; i++) {
		if (i % 5 <= 4 - i / 5) chArray[i / 5][i % 5] = '*';
		else chArray[i / 5][i % 5] = '_';
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << chArray[i][j];
		}
		cout << endl;
	}
}