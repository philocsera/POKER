#include "Base.h"
#include "CardClass.h"

HANDLE StdOutH = GetStdHandle(STD_OUTPUT_HANDLE);

const char * Check = "��";
const char * InGameArrow = "��";
const char * MainArrow = "��";
const char * cardShape[4] = { "��","��","��","��" };
const char * Number[] =
{ "2" ,"3" ,"4" ,"5" ,"6" ,"7" ,"8" ,"9" ,"10" ,"J" ,"Q" ,"K" ,"A" };

int CardX[5] = { 1, 15, 29, 43, 57 };
int ChoiceX[5] = { 5, 19, 33, 47, 61 };
int MainY[3] = { 2 ,4 ,6 };

Deck Dealer;
