#include "stdafx.h"
#include "tables.h"
#include <string.h>
// ������ �������											// empty element
struct recrd emptyElm = { { "",0 },		// ������ ����			// key fields
{ 0 },0 };	// ������������ ����	// functional fields
			//------------------------------------------------------
			// ������� ������ ������� �� ������ �������
			// ������ �� ������ �������
			// retreaving by direct address
struct recrd* selNmb(struct recrd*tb, unsigned int nElm)
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
// ��������� �� ������ �������
// insertion by direct address
struct recrd* insNmb(struct recrd*pElm,
	struct recrd*tb, unsigned int nElm, int *pQnElm)
{
	unsigned int n = *pQnElm;
	if (nElm<n)return 0;
	while (nElm<n)tb[nElm++] = emptyElm;
	tb[nElm++] = *pElm;
	*pQnElm = nElm;
	return &tb[nElm - 1];
}
// ��������� �� ������ �������
// deleting by direct address
struct recrd* delNmb(struct recrd*tb, unsigned int nElm)
{
	tb[nElm]._del = -1;
	return &tb[nElm];
}
// �������� �� ������ �������
// correction by direct address
struct recrd* updNmb(struct recrd*pElm,
	struct recrd*tb, unsigned int nElm, int *pQnElm)
{
	unsigned int n = *pQnElm;
	if (nElm >= n)return 0;
	tb[nElm] = *pElm;
	return &tb[nElm];
}
//------------------------------------------------------
// ��������� �� ���������� ��������
// comparison by nonequlity relation
int neqKey(struct recrd* el, struct keyStr kArg)
{
	return (strcmp(el->key.str, kArg.str) ||
		el->key.nMod != kArg.nMod);
}
// ��������� �����
// row comparison 
int cmpStr(unsigned char*s1, unsigned char*s2)
{
	unsigned n = 0;
#if(ASM==0)
	while (s1[n] == s2[n] && s1[n] != 0)n++;
	return s1[n] - s2[n];
#else
	_asm
	{
		xor	eax, eax; ������� �����������
		; clear accumulator
		xor	ecx, ecx; ������������ n
		; loading n
		mov esi, s1; dword ptr[ebp + 8]; ������������ ��������� 1 - �� �����
		; loading pointer of the 1st string
		mov edi, s2; dword ptr[ebp + 12]; ������������ ��������� 2 - �� �����
		; loading pointer of the 2nd string
		lb : lodsb; ������������ ��������� ����� 1 - �� �����
			 ; loading next byte of the 1st string
			 and al, al; �������� ���� 1 - �� ����� ���� C / C++
			 ; testing end of 1st string C / C++ language
			 jz		lf; �� ����� � ����������
			 ; to returning from this function
			 scasb; ��������� �������� ����� �����
			 ; comparing next byte of strings
			 loopz	lb; ����������� ����� ���������
			 ; continuing of comparison cycle
			 dec	edi; ����������� ������ � ����� ��������
			 ; compensation of 2nd string element number
			 lf : sub	al, [edi]; ���������� �������� ��������� �������
				  ; forming value of order relation
				  cbw; ��������� ����� �� 2 �����
				  ; sign extension to 2 bytes
				  cwd; ��������� ����� �� 4 �����
				  ; sign exten�sion to 4 bytes
	}
#endif
}
// ��������� �� ���������� ������� �����
// comparison by order relation for rows
int cmpKey(struct recrd* el, struct keyStr kArg)
{
	int i = cmpStr((unsigned char*)el->key.str,
		(unsigned char*)kArg.str);
	if (i)return i;
	return el->key.nMod - kArg.nMod;
}
// ��������� �� ���������� ������� ��� ������
// comparison by order relation for keys
int cmpKys(struct keyStr *k0, struct keyStr *kArg)
{
	int i = cmpStr((unsigned char*)k0->str,
		(unsigned char*)kArg->str);
	if (i)return i;
	return k0->nMod - kArg->nMod;
}
//------------------------------------------------------
// ������ �� ������ �������
// retreaving by linear search
struct recrd* selLin(struct keyStr kArg,
	struct recrd* tb, int ln)
{
	while (--ln >= 0 && neqKey(&tb[ln], kArg));
	if (ln<0)return 0;
	return &tb[ln];
}
// �������� ������ �� ������ �������
// next retreaving by linear search
struct recrd* selLinNxt(struct keyStr kArg,
	struct recrd* tb, int ln)
{
	static struct recrd* prPtr = 0;
	struct recrd* prPtrN;
	if (prPtr == 0)
		prPtr = tb;
	prPtrN = selLin(kArg, prPtr, ln);
	if (prPtrN)prPtr = prPtrN + 1; else prPtr = 0;
	return prPtrN;
}
// ��������� �� ������ �������
// insertion by linear search
struct recrd*insLin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm)
{
	int n = 0;
	while (n<*pQnElm&&tb[n].key.str[0] != 0)n++;
	if (n == *pQnElm)(*pQnElm)++;
	tb[n] = *pElm;
	pQnElm++;
	return &tb[n];
}
// ��������� �� ������ �������
// deleting by linear search
struct recrd*delLin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm)
{
	struct recrd*pEl = selLin(pElm->key, tb, *pQnElm);
	if (pEl)pEl->_del = -1;
	return pEl;
}
// �������� �� ������ �������
// correction by linear search
struct recrd*updLin(struct keyStr kArg, struct recrd*pElm,
	struct recrd*tb, int*pQnElm)
{
	struct recrd*pEl = selLin(kArg, tb, *pQnElm);
	if (pEl)*pEl = *pElm;
	return pEl;
}
// ��������� ��� ������� ������ 
// packing for linear search
struct recrd*pckLin(struct recrd*tb, int*pQnElm)
{
	int n = 0, ln = 0;
	while (n<*pQnElm)
	{
		if (tb[n]._del == 0) { tb[ln] = tb[n]; ln++; } n++;
	}
	*pQnElm = ln;
	return tb;
}
//------------------------------------------------------
// ���������� ��� ��������� ������
// sorting for linear search
struct recrd*srtBin(struct recrd*tb, int ln)
{
	int n = 0, n1;
	struct recrd el;
	for (; n<ln; n++)for (n1 = n + 1; n1<ln; n1++)
		if (cmpKey(&tb[n], tb[n1].key)>0)
		{
			el = tb[n]; tb[n] = tb[n1]; tb[n1] = el;
		}
	return tb;
}
// ������ �� �������� �������
// retreaving by binary search
struct recrd*selBin(struct keyStr kArg, struct recrd*tb, int ln)
{
	int i, nD = -1, nU = ln, n = (nD + nU) >> 1;
	while (i = cmpKey(&tb[n], kArg))
	{
		if (i>0)nU = n; else nD = n;
		n = (nD + nU) >> 1;
		if (n == nD)return NULL;
	}
	return &tb[n];
}
// ��������� �� �������� �������
// insertion by binary search
struct recrd*insBin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm, int ln, int plc)
{
	if (plc > *pQnElm) {
		plc = *pQnElm + 1;
	}
	struct recrd*pr = selBin(pElm->key, tb, plc);
	// ��� ��������� �������� �������� ��� ����� ����,
	// ���������� ������ �������� � ������� �� ���� ����� ������
	// If appropriate element is absent free place  for it
	// by moving of last element forward for one record 
	// �������� ����� ������� �� �������� ����
	// To write new element into free place
	if (pr) {
		pr->func = pElm->func;
		return pr;
	}
	int n = ln;
	for (n; n >= plc; n--) {
		tb[n] = tb[n - 1];
	}
	tb[n] = *pElm;
	n = *pQnElm;
	n++;
	*pQnElm = n;
	n = plc - 1;
	return &tb[n];
}
// ��������� �� �������� �������
// deleting by binary search
struct recrd*delBin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm)
{
	struct recrd*pr = selBin(pElm->key, tb, *pQnElm);
	// ��� ���������� �������� ������� ���� ��� ��������� 
	// if appropriate element is found to mark it as deleted
	if (pr) {
		pr->_del = -1;
	}
	return pr;
}
// �������� �� �������� �������
// correction by binary search
struct recrd*updBin(struct keyStr, struct recrd*pElm,
	struct recrd*tb, int*pQnElm)
{
	struct recrd*pr = selBin(pElm->key, tb, *pQnElm);
	// ��� ���������� �������� ��������� ���� ������ ���������� ����
	// if appropriate element is found to replace fields with new values
	if (pr) {
		*pr = *tb;
	}
	return pr;
}

int cmpKey(unsigned char* s1, unsigned char* s2) {
	int count = 0;
	for (int i = 0; (s1[i] != 0) && (s2[i] != 0); i++) {
		if (s1[i] != s2[i]) {
			break;
		}
		count++;
	}
	return count;
}

int countMaxSame(struct keyStr *k0, struct keyStr *kArg)
{
	int i = cmpKey((unsigned char*)k0->str,
		(unsigned char*)kArg->str);
	return i;
}

void selBinSame(struct keyStr kArg, struct recrd*tb, struct recrd*rs, int* pQnElm)
{
	int max = 0;
	int temp = 0;
	int last = 0;
	for (int i = 0; i < *pQnElm; i++) {
		temp = countMaxSame(&kArg, &tb[i].key);
		if (temp > max) {
			max = temp;
		}
	}
	if (max != 0) {
		for (int i = 0; i < *pQnElm; i++) {
			temp = countMaxSame(&kArg, &tb[i].key);
			if (temp == max) {
				updNmb(&tb[i], rs, last, pQnElm);
				last++;
			}
		}
	}
}
