#include "stdafx.h"
#include "tables.h"
#include <string.h>
// ��������� �����
int cmpStr(unsigned char* s1, unsigned char* s2)
{
	unsigned n = 0;
	while (s1[n] == s2[n] && s1[n] != 0)n++;
	return s1[n] - s2[n];
}
// ��������� �� ���������� �������
int cmpKys(char *k0, char *kArg)
{
	int i = cmpStr((unsigned char*)k0,
		(unsigned char*)kArg);
	//if(i)
	return i;
}
//------------------------------------------------------
// ������ �� �������� �������
struct recrdKWD*selBin(char* kArg, struct recrdKWD*tb, int ln)
{
	/*int count = -1;
	for (int i = 0; i < ln; i++) {
		if (cmpKys(tb[i].key, kArg) == 0) {
			return &tb[i];
		}
	}
	return NULL;
	*/
	
	int i, nD = -1, nU = ln, n = (nD + nU) >> 1;
	while (i = cmpKys(tb[n].key, kArg))
	{
		if (i>0)nU = n; else nD = n;
		n = (nD + nU) >> 1;
		if (n == nD)return NULL;
	}
	return &tb[n];
	
}
// ���������� ��� ��������� ������
struct recrdKWD*srtBin(struct recrdKWD*tb, int ln)
{
	int n = 0, n1;
	struct recrdKWD el;
	for (; n<ln; n++)for (n1 = n + 1; n1<ln; n1++)
		if (cmpKys(tb[n].key, tb[n1].key)>0)
		{
			el = tb[n]; tb[n] = tb[n1]; tb[n1] = el;
		}
	return tb;
}

struct recrdKWD*insBin(struct recrdKWD*pElm, struct recrdKWD*tb, int*pQnElm, int ln, int plc)
{
	if (plc > *pQnElm) {
		plc = *pQnElm + 1;
	}
	struct recrdKWD*pr = selBin(pElm->key, tb, plc);
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
	n = plc;
	return &tb[n];
}

struct recrdKWD*delBin(struct recrdKWD*pElm, struct recrdKWD*tb, int*pQnElm)
{
	struct recrdKWD*pr = selBin(pElm->key, tb, *pQnElm);
	if (pr) {
		pr->versn = -1;
	}
	return pr;
}

struct recrdKWD*updBin(struct recrdKWD*pElm, struct recrdKWD*tb, int*pQnElm)
{
	struct recrdKWD*pr = selBin(pElm->key, tb, *pQnElm);
	// ��� ���������� �������� ��������� ���� ������ ���������� ����
	// if appropriate element is found to replace fields with new values
	if (pr) {
		*pr = *tb;
	}
	return pr;
}
