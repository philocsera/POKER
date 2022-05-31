#include "Base.h"
#include "CardClass.h"
#include <cstdio>
#include <conio.h>

#define BaseX 11
#define BaseY 9

void Init() {
	CurcorOnOff(FALSE, 1);
	system("title Poker Game!!");
}

void gotoxy(int x, int y) {
	COORD Pos = { short(x - 1), short(y - 1) };
	SetConsoleCursorPosition(StdOutH, Pos);
}

void PrintCard(Trump Trump, int line) {
	for (int i = 0; i < 5; i++) {
		int x = CardX[i], PN = Trump.GetCardPattern(i);
		const char* N = Number[Trump.GetCardNum(i)];
		PN % 3 != 0 ?
		SetConsoleTextAttribute(StdOutH, Color) :
		SetConsoleTextAttribute(StdOutH, Base);
		gotoxy(x, 1);
		printf("┌────┐ "); // 에디터 상에서 - 하나 빠짐
		for (int i = 2; i < 7; i++) {
			gotoxy(x, i);
			printf("│       │ ");
		}
		gotoxy(x, 7);
  	printf("└──────┘ "); // 마찬가지
		gotoxy(x + 2, 2);
		printf("%s", N?N:"");
		gotoxy(x + 4, 4);
		printf("%s", PN?cardShape[PN]:"이걸골라야됨"); // 뒤집힌거
		gotoxy(x+(N=="10"?6:7), 6);
		printf("%s", N?N:"");
	}
}

void PrintChangeScreen(Trump Trump){
	system("mode con cols=66 lines=10");
	PrintCard(Trump, 0);
	SetConsoleTextAttribute(StdOutH, WHITE);
	for (int i = 0; i < 5;i++) {
		gotoxy(ChoiceX[i] - 1, 8);
		printf("[  ]");
	}
	gotoxy(22, 10);
	printf("Pick a replacement card");
	Trump.Change(GetChangeCard());
	system("cls");
}

void PrintWideScreen(bool plag) {
	system("mode con cols=66 lines=40");

}


void CurcorOnOff(bool Visible, int CursorSize) {
	CONSOLE_CURSOR_INFO Cinfo = { 0, };
	Cinfo.dwSize = CursorSize;
	Cinfo.bVisible = Visible;
	SetConsoleCursorInfo(StdOutH, &Cinfo);
}

TradeSwit GetChangeCard() {
	int NowX = 0, LastX = 0;
	TradeSwit RETN;
	gotoxy(ChoiceX[NowX], BaseY);
	printf("%s", InGameArrow);
	while (TRUE) {
		if(_kbhit()) {
			int get = _getch();
			switch (get) {
			case 75: // ←
				NowX = NowX == 0 ? 4 : NowX - 1;
				break;
			case 77: // →
				NowX = NowX == 4 ? 0 : NowX + 1;
				break;
			case 32: // Space
				RETN.PushSwit(NowX);
				gotoxy(ChoiceX[NowX], BaseY-1);
				printf("%s", RETN.getSwit(NowX)?Check:" ");
				break;
			case 13: // Enter
				return RETN;
			}
			if (NowX != LastX) {
				gotoxy(ChoiceX[LastX], BaseY);
				printf(" ");
				gotoxy(ChoiceX[NowX], BaseY);
				printf("%s", InGameArrow);
				LastX = NowX;
			}
		}
	}
}

ScoreBoard Marking(Trump UserT) {
	ScoreBoard RETN;
	int Score=0, Overlap[13] = { 0, },
	Best[13] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	CheckBoard[8] = { 0, 0, 0, 0, 0, 0, 1, 0};
	// 0: Pair 1: Triple 2: FourCard 3: Back
	// 4: Royal 5: Straight 6: Flush 7: Full House
	for (int i = 0; i < 5; i++) {
		int Idx = UserT.GetCardNum(i), ShapeN = UserT.GetCardPattern(i);
		Overlap[Idx]++;
		Best[Idx] = ShapeN < Best[Idx] ? ShapeN : Best[Idx];
	}
	for (int i = 0; i < 13; i++) {
		//* 원 페어 투 페어 *//
		if (Overlap[i] == 2) {
			CheckBoard[0]++;
			if (CheckBoard[1]) CheckBoard[7] = 1; // Full House
			Score = Calc(CheckBoard[1]?8:CheckBoard[0], Best[i], i, Score);
		}
		//* 트리플 *//
		else if (Overlap[i] == 3) {
			CheckBoard[1] = 1;
			if (CheckBoard[0]) CheckBoard[7] = 1; // Full House
			Score = Calc(CheckBoard[0]?8:3, Best[i], i, Score);
			break;
		}
		//* 포커 *//
		else if (Overlap[i] == 4) {
			CheckBoard[2] = 1;
			Score = Calc(9, Best[i], i, Score);
			break;
		}
	}
	if (!CheckBoard[1] && !CheckBoard[2] && CheckBoard[0] != 2) {
	  //* 플러쉬 *//
		for (int i = 0; i < 4; i++) {
			for (int j = i + 1; j < 5 && CheckBoard[6]; j++) {
				if (UserT.GetCardPattern(i) != UserT.GetCardPattern(j)) {
					CheckBoard[6] = 0;
					break;
				}
			}
		}
		for (int i = 0; i < 13; i++)
			if (StraightCheck(i, i < 9, Overlap))
				CheckBoard[5] = 1; // 스트레이트가 있는지
		if (CheckBoard[5] && StraightCheck(8, FALSE, Overlap))
			CheckBoard[4] = 1; // 10 J Q K A
		else if (CheckBoard[5] && StraightCheck(12, FALSE, Overlap))
			CheckBoard[3] = 1; // A 1 2 3 4
		for (int i = 12; i >= 0; i--) {
			if (Overlap[i]) {
				Score = Calc(
					CheckBoard[6] * 7 + CheckBoard[5] * 4 +
					CheckBoard[4] * 2 + CheckBoard[3],
					Best[i],i,Score);
				break;
			}
		}
	}
	int TopS=4, TopN=0;
	for (int i = 0; i < 13; i++) {
		if (Overlap[i] && Best[i] < TopS) {
				TopS = Best[i];
				TopN = i;
		}
		else if (Best[i] == TopS && i > TopN) {
			TopN = i;
		}
	}
	Score = Calc(0, TopS, TopN, Score);
	RETN.Init(Score, CheckBoard);
	return RETN;
}

int Calc(int Genealogy, int Shape, int CardNum, int OldBest) {
	int NowBest = Genealogy * 1000 + (5 - Shape) * 100 + CardNum;
	return NowBest>OldBest?NowBest:OldBest;
}

bool StraightCheck(int start, bool Case, int OL[13]) {
	return Case? !( !OL[start] + !OL[start + 1] + !OL[start + 2]
		+ !OL[start + 3] + !OL[start + 4]):
		!(!OL[start] + !OL[(start + 1)%13] + !OL[(start + 2) % 13]
		+ !OL[(start + 3) % 13] + !OL[(start + 4) % 13]);
}

void MainMenu() {
	int NowY=0, LastY=0, Pick=-1;
	bool Power = TRUE;
	PrintMainMenu();
	while (Power) {
		if (_kbhit()) {
			int get = _getch();
			switch (get) {
			case 72:
				NowY = NowY == 0 ? 2 : NowY - 1;
				break;
			case 80:
				NowY = NowY == 2 ? 0 : NowY + 1;
				break;
			case 13:
				Pick = NowY;
			}
			gotoxy(BaseX, MainY[LastY]);
			printf(" ");
			gotoxy(BaseX, MainY[NowY]);
			printf("��");
			LastY = NowY;
		}
		switch (Pick) { // 나중에 음악 추가하면 옵션 추가해야됨
		case 0:
			PokerGame();
			Power = FALSE;
		case 1:
			break; // Q. 크레딧에서 cls를 안 하고 그대로 메인화면 출력하면 어떻게 되는거임
		case 2:
			Power = FALSE;
		default:
			break;
		}
	}
}

void PrintMainMenu() {
	int x = 0;
	system("mode con cols=40 lines=7");
	for (int i = 0; i < 2; i++) {
		x = i ? 1 : 31;
		gotoxy(x, 1);
		printf("┌──────┐ ");
				for (int j = 2; j < 7; j++) {
					gotoxy(x, j);
					printf("│       │ ");
				}
				gotoxy(x, 7);
				printf("└──────┘ ");
		gotoxy(x + 2, 2);
		printf("A");
		gotoxy(x + 4, 4);
		printf("%s", cardShape[0]);
		gotoxy(x + 7, 6);
		printf("A");
	}
	gotoxy(15, 2);
	printf("1. START GAME");
	gotoxy(15, 4);
	printf("2. CREDIT");
	gotoxy(15, 6);
	printf("3. EXIT");
	gotoxy(11, 2);
	printf("��");
}

void Credit() {
	system("mode con cols=20 lines=20");
}
