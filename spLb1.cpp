// spLb1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tables.h"
#include "vistab.h"
#include <stdlib.h>

int nTbStud = 2, lnTbStud = 100;
struct recrd tbStud[100] = // static table defintion
{ { { "Diatlov",88 },4,0 },	// 1st record ititialization
{ { "Kutsar",89 },3.5,0 } };// 2nd record ititializaton
struct recrd tstArg = { { "Diatlov",89 },40,0 },	// appending element intialization
	insArg = { { "Dazizov",89 },32,0 },	// appending element intialization
	insArg0 = { { "Dazizov",55 },3,0 },	// appending element intialization
	insArg1 = { { "Dilyk",8 },41,0 },		// appending element intialization
	insArg2 = { { "Rax",80 },(float)4.2,0 },// appending element intialization
	insArg3 = { { "iazt",8 },41,0 };		// appending element intialization
struct recrd res[100] = { { 0,0 },0,0 };

int main(int argc, char* argv[])
{
	struct recrd*pTb;
	pTb = (struct recrd*)malloc(100 * sizeof(struct recrd));
	pTb = new struct recrd[100];
	prRow(&tstArg);
	prRow(selNmb(tbStud, 1));
	prRow(selLin(tstArg.key, tbStud, 2));
	prRow(insNmb(&insArg, tbStud, 3, &nTbStud));
	prTab(tbStud, 0, nTbStud - 1);
	prRow(updNmb(&insArg1, tbStud, 2, &nTbStud));
	prRow(delNmb(tbStud, 1));
	prTab(tbStud, 0, nTbStud - 1);
	prRow(insLin(&insArg2, tbStud, &nTbStud));
	prTab(tbStud, 0, nTbStud - 1);
	prRow(delLin(&insArg1, tbStud, &nTbStud));
	prTab(tbStud, 0, nTbStud - 1);
	prRow(updLin(insArg.key, &insArg0, tbStud, &nTbStud));
	prTab(tbStud, 0, nTbStud - 1);
	prRow(pckLin(tbStud, &nTbStud));
	prTab(tbStud, 0, nTbStud - 1);
	prRow(srtBin(tbStud, nTbStud));
	prTab(tbStud, 0, nTbStud - 1);
	prRow(selBin(insArg2.key, tbStud, nTbStud));
	prTab(tbStud, 0, nTbStud - 1);
	prRow(insBin(&insArg1, tbStud, &nTbStud, lnTbStud, 3));
	prTab(tbStud, 0, nTbStud - 1);
	prClr(blue);
	selBinSame(insArg3.key, tbStud, res, &nTbStud);
	prTab(res, 0, lnTbStud - 1);
	system("pause");
	return 0;
}
