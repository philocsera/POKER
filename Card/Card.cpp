#include "Base.h"
#include "CardClass.h"

Card::Card(int N, int P) {
	this->Num = N;
	this->Pattern = P;
}

Card::Card(){}

int Card::GetPattern() { return this->Pattern; }
char Card::GetNum() { return this->Num; }


