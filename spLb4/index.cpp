#include "stdafx.h"
#include "..\spLb3\token.h"
#include "tables.h"
#include "index.h"
#include <stdlib.h>
struct lxNode emptyElm = { _nil,0,0,0,0,0,0,0,0 };
// ��������� �����
// ��������� �������� �� ���������� �������
int cmpTrm(struct lxNode*k0, struct lxNode*kArg)//cmpKys
{
	int i = cmpStr((unsigned char*)k0->prvNd,
		(unsigned char*)kArg->prvNd);
	if (i)return i;
	return k0->stkLength - kArg->stkLength; // ��������� ������ ������
}
unsigned nNdxNds = 0;
struct indStrUS ndxNds[50] = { { NULL,NULL,NULL,0 } },
	*pRtNdx = ndxNds, nilNds = { NULL,NULL,NULL,0 };
// ������ ����� ����� �� �������� �������
struct indStrUS*selBTr(struct lxNode*kArg, struct indStrUS*rtTb)
{
	int df;
	while (df = cmpTrm(kArg, rtTb->pKyStr))
		if (df>0) {
			if (rtTb->pRtPtr)rtTb = rtTb->pRtPtr;
			else break;
		}
		else {
			if (rtTb->pLtPtr)rtTb = rtTb->pLtPtr;
			else break;
		}
		rtTb->dif = df;
		return rtTb;
}
// ��������� ����� ����� �� �������� �������
struct indStrUS*insBTr(struct lxNode*pElm, struct indStrUS*rtTb)
{
	struct indStrUS*pInsNod;//,*pNod;
	if (rtTb->pKyStr == NULL)
	{
		rtTb->pKyStr = pElm;
		return rtTb;
	}
	// if(rtTb->pKyStr->ndOp==_nil)rtTb->pKyStr=pElm;
	else {
		pInsNod = selBTr(pElm, rtTb);
		if (pInsNod->dif)
		{
			ndxNds[++nNdxNds] = nilNds;
			if (pInsNod->dif<0)pInsNod = pInsNod->pLtPtr = ndxNds + nNdxNds;
			else pInsNod = pInsNod->pRtPtr = ndxNds + nNdxNds;
			ndxNds[nNdxNds].pKyStr = pElm;
		}
	}
	return pInsNod;
}

// ��� ������ � ������� �� ��������
struct lxNode*selNmb(struct lxNode*tb, unsigned int nElm)
{
#if ASM
	int sr = 4;
	_asm {
		sub eax, eax
		mov al, nElm
		mov ecx, sr;//sr=log2(SizeRc);
		shl eax, cl
			add eax, tb
	}
#else
	return &tb[nElm];
#endif
}

// ��� �������� ������� � ��������
struct lxNode*updNmb(struct lxNode*pElm, struct lxNode*tb, unsigned int nElm, int *pQnElm)
{
	unsigned int n = *pQnElm;
	if (nElm >= n)return 0;
	tb[nElm] = *pElm;
	return &tb[nElm];
}

// ��� ������� �� ������� � ��������� �������
struct lxNode*insNmb(struct lxNode*pElm, struct lxNode*tb, int *pQnElm, int ln, int plc)
{
	if (plc > *pQnElm) {
		plc = *pQnElm + 1;
	}
	int n = ln;
	for (n; n > plc; n--) {
		tb[n] = tb[n - 1];
	}
	tb[n] = *pElm;
	n = *pQnElm;
	n++;
	*pQnElm = n;
	n = plc - 1;
	return &tb[n];
}