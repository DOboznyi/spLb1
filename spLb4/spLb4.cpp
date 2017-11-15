// spLb4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\spLb3\token.h"
#include "..\spLb3\visgrp.h"
#include "tables.h"
#include "lexan.h"
#include "langio.h"
#include "index.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)
extern struct recrdKWD *tablKWD;
extern
struct lxNode nodes[200] = // масив приймач вузлів дерева
{ { _nil,NULL,NULL,0,0,0,0,0,NULL,0 },{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },
{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },
{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },
{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },
{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },
{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },
{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },
{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },
{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },
{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },{ _nil,NULL,NULL,0,0,0,0,0,NULL,0 },
};
struct lxNode node = { _sub,NULL,NULL,0,0,0,0,0,NULL,0 },
	node1 = { _mul,NULL,NULL,0,0,0,0,0,NULL,0 };
char file_name[20];
extern enum ltrType ltClsC[256];
extern enum ltrType ltClsP[256];
extern enum tokType dlCdsC[256];
extern enum tokType dlCdsP[256];
extern enum ltrType ltClsC[256];
extern enum ltrType ltClsP[256];
enum ltrType *ltCls = ltClsC;
enum tokType *dlCds = dlCdsC;
struct recrdKWD exmpl = { "!=",_ne,1 };
int n = 67;
int main(int argc, char* argv[])
{
	int nn = -1;//np,
	if (argc>1)
	{
		strcpy(file_name, argv[1]);
		printf("Processing file -- %s\n", file_name);
	}
	else
	{
		printf("Please enter file name: ");
		scanf("%s", file_name);
		strcat(file_name, ".h");
	}
	opFls(file_name);
	LxAnInit('C');
	srtBin(tablKWD, 67);
	delBin(&exmpl, tablKWD, &n);
	insBin(&exmpl, tablKWD, &n, 65, 3);
	do {//np=nn;
		nn = LxAnlzr();
	} while (nodes[nn].ndOp != _EOF);
	prLaTxt(nodes, nn);
	printf("\n\nTotal number of elements in table: %i\n", nn);
	printf("\nTable of lexems:\n");
	prLaTbl(nodes, nn);
	printf("\n");

	prNode(selNmb(nodes, 1));
	prNode(updNmb(&node, nodes, 5, &nn));
	prNode(insNmb(&node1, nodes, &nn, 200, 1));

	printf("\n\nTotal number of elements in table: %i\n", nn);
	printf("\nTable of lexems:\n");
	prLaTbl(nodes, nn);
	printf("\n");

	system("pause");
	return 0;
}