#include "stdafx.h"
#include "..\spLb3\token.h"
#include "syntaxP.h"
#include <stdio.h>
#include <stdlib.h>
extern enum tokPrec opPrFC[256];
extern enum tokPrec opPrGC[256];
extern enum tokPrec opPrFP[256];
extern enum tokPrec opPrGP[256];
enum tokPrec *opPrF,*opPrG;
extern char *oprtrC[], *oprtrP[], *oprtrV[],
			*cprC[], *cprP[], *cprV[];
extern char **oprtr, **cpr,
	modeP, // тип роздільника операторних дужок для Паскаля
	modeC, // тип роздільника операторних дужок для С
	modeL; 
void SxAnInit(char nl)
{char i=0;
 switch (nl)
 {case 'P': opPrF=opPrFP; opPrG=opPrGP; modeC=0; 
		modeL=modeP; modeP=1; oprtr=oprtrP; cpr=cprP;
	 break;
 case 'V':
 default:
 case 'C':opPrF=opPrFC; opPrG=opPrGC; modeP=0; 
		modeL=modeC; modeC=1; oprtr=oprtrC; cpr=cprC;
}
}
int nxtProd(struct lxNode*nd,	// вказівник на початок масиву вузлів 
 		  int nR,	// номер кореневого вузла
 		  int nC)	// номер поточного вузла
{int n=nC-1;		// номер попереднього вузла
 enum tokPrec pC = opPrF[nd[nC].ndOp],// передування поточного вузла
	*opPr=opPrG;//F;// nd[nC].prvNd = nd+n;
 while(n!=-1)	// цикл просування від попереднього вузла до кореню
 {if(opPr[nd[n].ndOp]<pC//)// порівняння функцій передувань
		&&nd[n].ndOp</*_ctbz*/_frkz)
 {if(n!=nC-1&&nd[n].pstNd!=0)		// перевірка необхідності вставки
		{nd[nC].prvNd = nd[n].pstNd;	// підготовка зв’язків 
		 nd[nC].prvNd->prnNd=/*nd+*/nC;}	// для вставки вузла
	 if(opPrF[nd[n].ndOp]==pskw&&nd[n].prvNd==0)
		 nd[n].prvNd = nd+nC;
		 else 
			 nd[n].pstNd = nd+nC;
	 nd[nC].prnNd=/*nd+*/n;	// додавання піддерева
	 return nR;}
  if(opPrG[nd[n].ndOp]==pC&&
	  (nd[n].ndOp==_brkt||nd[n].ndOp==_ixbr||nd[n].ndOp==_opbr||nd[n].ndOp==_tdbr))
  {nd[n].ndOp=(enum tokType)((nd[n].ndOp-_fork)/2+_frkz);//09.04.07	  //замена на 
	nd[nC]=nd[n];
   if(nd[nC].prnNd==-1){nR=nC; nd[nR].prnNd=-1;}
   else if(opPrF[nd[nd[nC].prnNd].ndOp]==pskw&&nd[nC].ndOp<_frkz)
	   nd[nd[nC].prnNd].prvNd = nd+nC;
   else if(opPrF[nd[nd[nC].prnNd].ndOp]==pekw&&nd[nC].ndOp==_opbz)
   {
	   nd[nd[nC].prnNd].prvNd =nd+nC;
	   nd[nd[nC].prnNd].pstNd=0;}
	  return nR;}
/* if(nd[n].ndOp==_brkt||nd[n].ndOp==_ixbr||nd[n].ndOp==_opbr||nd[n].ndOp==_tdbr)
	{nd[nC].prnNd=n; nd[nC].prvNd=nd[n].pstNd; 
	 nd[n].pstNd->prnNd=nC; nd[n].pstNd= nd+nC;
	 return nR;}*/
  n=nd[n].prnNd;
  opPr=opPrG;}	// просування до кореню
//  if(n<=)	else 
  nd[nC].prvNd = nd+nR; 
  nd[nR].prnNd=/*nd+*/nC; nR = nC; nd[nR].prnNd=-1;
return nR;}
int	prCmpr(struct lxNode*nd, int nn, int nr) //компресія для скорочення графа
{int nR, nN=0, nC=0;
do{
	if((nd+nN)->ndOp==_remL||(nd+nN)->ndOp==_rem)
	{if(nd[nN].pstNd>&nd[nN]&&nd[nN].prnNd!=-1)
		{if(nC-nN>1)nd[nN]=nd[nC];
//		 nN++; 
		 nC++; continue;}
	}
//	if(nR<-1){nC++; continue;}
	if(nr==nC)nr=nN;
	if(nd[nC].ndOp==_brkz&&nd[nC].prvNd==0)
	{if(nd[nd[nC].prnNd].prvNd==&nd[nC])
		{nd[nC].pstNd->prnNd=nd[nC].prnNd;
		 nd[nd[nC].prnNd].prvNd=nd[nC].pstNd;}
	 if(nd[nd[nC].prnNd].pstNd==&nd[nC])	// b 02/06/07
		{nd[nC].pstNd->prnNd=nd[nC].prnNd;
		 nd[nd[nC].prnNd].pstNd=nd[nC].pstNd;}// e 02/06/07
		nC++;
	}
	if(nN!=nC)
	{nR=nd[nC].prnNd;
	 nd[nN]=nd[nC];
//зв'язок з батьківським вузлом
	 if(nd[nR].prvNd==&nd[nC])
		 nd[nR].prvNd=&nd[nN];
	 if(nd[nR].pstNd==&nd[nC])
		 nd[nR].pstNd=&nd[nN];
	 if(nd[nN].ndOp>_cnst){
//зв'язок з лівим наступником
	 if(nd[nN].prvNd)
		 nd[nN].prvNd->prnNd=nN;
//зв'язок з правим наступником
	 if(nd[nN].pstNd)
		 nd[nN].pstNd->prnNd=nN;
	 }
//	 if(nR<nN)nd[nN].prnNd=nR;
//	 nd[nR].prvNd
	}
//	 else nC
//}else
	nN++; nC++;
}while(nC<nn);
return nr;
}

void error() {
	printf("\n\nFix an error and try again later\n\n");
	system("pause");
	exit(1);
}

void brackets_analyse(struct lxNode*nd,int size) {
	int c1 = 0; // Operations count
	int c2 = 0; // Parametrs count
	for (int i = 1; i < size-1; i++) {
		if (((nd[i].ndOp == _nam) && (nd[i + 1].ndOp == _ixbr)) || (nd[i].ndOp == _ixbr)) {
			struct lxNode nw[20] = { { _nil,NULL,NULL,0,0,0,0,0,NULL,0 }, };
			if (nd[i].ndOp == _nam) {
				nd[i].prnNd = i + 1;
				nd[i + 1].prvNd = &nd[i];
				int x = i + 1;
				i++;
			}
			int j = 0;
			int size = 0;
			do
			{
				nw[size] = nd[i];
				if (nd[i].ndOp == _ixbr) {
					j++;
				}
				if (nd[i].ndOp == _scbr) {
					j--;
				}
				i++;
				size++;
			} while (j != 0);
			nw[size].ndOp = _EOF;
			//nd[i - 1].prnNd = nw[0];
			brackets_analyse(nw, size);
			//nd[x].ndOp = _ixbz;
			//nd[i - 1] = nd[x];
		}
		if (nd[i].ndOp == _brkt) {
			struct lxNode nw[200] = { { _nil,NULL,NULL,0,0,0,0,0,NULL,0 }, };
			int j = 0;
			int size1 = 0;
			do
			{
				nw[size1] = nd[i];
				if (nd[i].ndOp == _brkt) {
					j++;
				}
				if (nd[i].ndOp == _bckt) {
					j--;
				}
				i++;
				size1++;
			} while (j != 0);
			nw[size1].ndOp = _EOF;
			brackets_analyse(nw, size1);
			c2++;
		}
		//Если после цифры или буквы стоит не арифметическая операция
		//if ((nd[i].ndOp == _nam) || (nd[i].ndOp == _srcn) && !((nd[i + 1].ndOp >= 233) && (nd[i + 1].ndOp <= 236) && (nd[i + 1].ndOp >= 219) && (nd[i+1].ndOp <= 220))) {
			//Если там всего 1 буква то можно
		//	if (size != 3) {
		//		error();
		//	}
		//}

		if ((nd[i].ndOp == 219)|| (nd[i].ndOp == 220) || (nd[i+1].ndOp == 219) || (nd[i+1].ndOp == 220)) {
			if ((nd[i].ndOp == _nam) && ((nd[i + 1].ndOp == 219) || (nd[i + 1].ndOp == 220))) {
				c1++;
				i++;
			}
			else if ((nd[i + 1].ndOp == _nam) && ((nd[i].ndOp == 219) || (nd[i].ndOp == 220))) {
				c1++;
				i++;
			}
			else {
				error();
			}
		}

		if (((nd[i].ndOp >= 233) && (nd[i].ndOp <= 236)) || ((nd[i].ndOp >= 244) && (nd[i].ndOp <= 247))) {
			c1++;
		}
		if ((nd[i].ndOp == _nam) || (nd[i].ndOp == _srcn)) {
			c2++;
		}
	}
	c2 -= c1;
	if (c2 != 1) {
		error();
	}
	if (nd[0].ndOp == _brkt) {
		nd[0].ndOp = _brkz;
		nd[size] = nd[0];
	}
	if (nd[0].ndOp == _ixbr) {
		nd[0].ndOp = _ixbz;
		nd[size] = nd[0];
	}
}

int SxAnlz(struct lxNode*nd,int nn)	// вказівник на початок масиву вузлів 
{
	int nR;
	int nC;
	int c1 = 0;
	int c2 = 0;
	if (nd[nn - 1].ndOp != _EOS) {
		error();
	}
	nd[nn - 1].pstNd = &nd[nn];
	nR = nn - 1;
	nC = nR;
	bool flag = false;
	for (int i = nn - 1; i >= 0; i--) {
		if ((nd[i].ndOp == _err) || (c1>0) || (c2>0)) {
			error();
		}
		if ((nd[i].ndOp == 219) || (nd[i].ndOp == 220)) {
			if (i == 0) {
				if (nd[i + 1].ndOp != _nam) {
					error();
				}
			}
			else if ((nd[i + 1].ndOp != _nam) && (nd[i - 1].ndOp != _nam) && (nd[i - 1].ndOp != _scbr)) {
				error();
			}
		}
		if (nd[i].ndOp == _ixbr) {
			c1++;
		}
		if (nd[i].ndOp == _scbr) {
			c1--;
		}
		if (nd[i].ndOp == _brkt) {
			c2++;
		}
		if (nd[i].ndOp == _bckt) {
			c2--;
		}
		if (nd[i].ndOp == _EOS) {
			nd[nC].prvNd = &nd[i];
			nd[i].prnNd = nC;
			if (flag) {
				nd[i].pstNd = &nd[nR];
				nd[nR].prnNd = i;
			}
			flag = false;
			nC = i;
		}
		if ((nd[i].ndOp == 218) || ((nd[i].ndOp >= 212) && (nd[i].ndOp <= 215)))
		{
			if (!flag) {
				flag = true;
				nR = i;
			}
			else {
				error();
			}
		}
		if ((nd[i].ndOp == 0) && (nd[i].ndOp != 1) && (nd[i].ndOp != 2) && (nd[i].ndOp < 233) && (nd[i].ndOp>236) && (nd[i].ndOp < 208) && (nd[i].ndOp > 215) && (nd[i].ndOp != 218) && (nd[i].ndOp < 196) && (nd[i].ndOp > 199) && (nd[i].ndOp != 219) && (nd[i].ndOp != 220)) {
			error();
		}
	}
	if (flag) {
		nd[nC].prvNd = &nd[nR];
		nd[nR].prnNd = nC;
	}
	if (c1 != 0 || c2 != 0 || (!flag && (nC != 0))) {
		error();
	}
	for (int i = 0; i < nn; i++) {
		if (((nd[i].ndOp == _nam) && (nd[i + 1].ndOp == _ixbr)) || (nd[i].ndOp == _ixbr)) {
			struct lxNode nw[20] = { { _nil,NULL,NULL,0,0,0,0,0,NULL,0 }, };
			if (nd[i].ndOp == _nam) {
				nd[i].prnNd = i + 1;
				nd[i + 1].prvNd = &nd[i];
				int x = i + 1;
				i++;
			}
			int j = 0;
			int size = 0;
			do
			{
				nw[size] = nd[i];
				if (nd[i].ndOp == _ixbr) {
					j++;
				}
				if (nd[i].ndOp == _scbr) {
					j--;
				}
				i++;
				size++;
			} while (j != 0);
			nw[size].ndOp = _EOF;
			brackets_analyse(nw, size);
		}
		if (nd[i].ndOp == _brkt) {
			struct lxNode nw[200] = { { _nil,NULL,NULL,0,0,0,0,0,NULL,0 }, };
			int j = 0;
			int size = 0;
			do
			{
				nw[j] = nd[i];
				if (nd[i].ndOp == _brkt) {
					j++;
				}
				if (nd[i].ndOp == _bckt) {
					j--;
				}
				i++;
				size++;
			} while (j != 0);
			nw[size].ndOp = _EOF;
			brackets_analyse(nw, size);
		}
	}
	for (int i = 0; i < nn; i++) {
		bool flag = false;
		c1 = 0;
		c2 = 0;
		while (nd[i].ndOp != _EOS) {
			if (!flag) {
				/*if ((nd[i].ndOp == 219) || (nd[i].ndOp == 220) || (nd[i + 1].ndOp == 219) || (nd[i + 1].ndOp == 220)) {
				if ((nd[i].ndOp == _nam) && ((nd[i + 1].ndOp == 219) || (nd[i + 1].ndOp == 220))) {
				i++;
				if (nd[i + 2].ndOp == _EOS) {
				i++;
				}
				else {
				flag = true;
				}
				}
				else if ((nd[i + 1].ndOp == _nam) && ((nd[i].ndOp == 219) || (nd[i].ndOp == 220)) && (nd[i + 2].ndOp == _EOS)) {
				i++;
				if (nd[i + 2].ndOp == _EOS) {
				i++;
				}
				else {
				flag = true;
				}
				}
				else if ((nd[i + 1].ndOp == _nam) && ((nd[i].ndOp == 219) || (nd[i].ndOp == 220)) && (nd[i + 2].ndOp == _ixbr)) {
				i++;
				}
				else {
				error();
				}
				}
				*/
				if (((nd[i].ndOp == _nam) && (nd[i + 1].ndOp == _ixbr)) || ((nd[i].ndOp == _nam) && (((nd[i + 1].ndOp >= 208) && (nd[i + 1].ndOp <= 215)) || (nd[i + 1].ndOp == 218)))) {
					if ((nd[i].ndOp == _nam) && (((nd[i + 1].ndOp >= 208) && (nd[i + 1].ndOp <= 215)) || (nd[i + 1].ndOp == 218))) {
						flag = true;
						i++;
					}
					else {
						while (!(((nd[i].ndOp == _scbr) && ((nd[i + 1].ndOp == _ass) || (nd[i + 1].ndOp >= 208) || (nd[i + 1].ndOp <= 215) || (nd[i + 1].ndOp == _EOS) || (nd[i + 1].ndOp == 219) || (nd[i + 1].ndOp == 220))) || flag)) {
							if ((nd[i].ndOp == _scbr) && (nd[i + 1].ndOp != _ass) && (nd[i + 1].ndOp < 208) && (nd[i + 1].ndOp > 215) && (nd[i + 1].ndOp != 219) && (nd[i + 1].ndOp != 220)) {
								error();
							}
							i++;
						}
						i++;
						if ((nd[i].ndOp == 219) || (nd[i].ndOp == 220)) {
							if ((nd[i + 1].ndOp == _ass) || (nd[i + 1].ndOp >= 208) || (nd[i + 1].ndOp <= 215) || (nd[i + 1].ndOp == _EOS)) {
								i++;
							}
							else {
								error();
							}
						}
						flag = true;
					}
				}
				if (nd[i + 1].ndOp == _EOS) {
					flag = true;
				}
			}
			if (!flag) {
				error();
			}
			if ((nd[i].ndOp == _nam) && (nd[i + 1].ndOp == _ixbr)) {
				i++;
				int j = 1;
				do {
					do
					{
						i++;
						if (nd[i].ndOp == _ixbr) {
							j++;
						}
						if (nd[i].ndOp == _scbr) {
							j--;
						}
					} while (j != 0);
				} while ((nd[i].ndOp == _scbr) && (nd[i + 1].ndOp == _ixbr));
				c2++;
			}

			if (nd[i].ndOp == _brkt) {
				i++;
				int j = 1;
				do
				{
					i++;
					if (nd[i].ndOp == _brkt) {
						j++;
					}
					if (nd[i].ndOp == _bckt) {
						j--;
					}
				} while (j != 0);
				c2++;
			}

			if ((nd[i].ndOp == _scbr) && (nd[i + 1].ndOp != _EOS) && (nd[i + 1].ndOp < 233) && (nd[i + 1].ndOp > 236)) {
				error();
			}

			if (((nd[i].ndOp == _nam) || (nd[i].ndOp == _srcn)) && (nd[i + 1].ndOp != _EOS) && (nd[i + 1].ndOp < 233) && (nd[i + 1].ndOp > 236)) {
				error();
			}

			if (((nd[i].ndOp >= 233) && (nd[i].ndOp <= 236)) || ((nd[i].ndOp >= 244) && (nd[i].ndOp <= 247))) {
				c1++;
			}

			if ((nd[i].ndOp == _nam) || (nd[i].ndOp == _srcn)) {
				c2++;
			}
			i++;
		}
		c2 -= c1;
		if ((c2 != 1) || ((c1 == 0) && (c2 == 0))) {
			error();
		}
	}
	/*for (int i = 0; i < nn; i++) {
		if ((nd[i].ndOp == _nam) && ((nd[i + 1].ndOp == 218) || ((nd[i + 1].ndOp > 212) && (nd[i + 1].ndOp < 215)) || (nd[i + 1].ndOp == _ixbz))) {
			if (nd[i + 1].ndOp == _ixbz) {
				nd[i + 1].prvNd = &nd[i];
				nd[i + 3].prvNd = &nd[i+1];
				nd[i + 1].pstNd = &nd[i + 2];
				nd[i].prnNd = i+1;
				nd[i+2].prnNd = i+1;
				i += 2;
			}
			else {
				nd[i + 1].prvNd = &nd[i];
				nd[i].prnNd = i+1;
				i += 1;
			}
		}
		if ((nd[i + 1].ndOp == _srcn)&&(nd[i + 1].ndOp == _ixbz)) {
				nd[i + 1].prvNd = &nd[i];
				nd[i + 3].prvNd = &nd[i + 1];
				nd[i + 1].pstNd = &nd[i + 2];
				nd[i].prnNd = i + 1;
				nd[i + 2].prnNd = i + 1;
				i += 2;
		}
	}
	for (int i = 1; i < nn; i++) {
		if (((nd[i].ndOp == _nam) || (nd[i].ndOp == _srcn) || (nd[i].ndOp == _ixbz)) &&
			((nd[i + 1].ndOp == _add) || (nd[i + 1].ndOp == _sub) || (nd[i + 1].ndOp == _mul) || (nd[i + 1].ndOp == _div) ||
			(nd[i - 1].ndOp == _add) || (nd[i - 1].ndOp == _sub) || (nd[i - 1].ndOp == _mul) || (nd[i - 1].ndOp == _div))) {
			if (((nd[i - 1].ndOp == _mul) || (nd[i - 1].ndOp == _div)) && ((nd[i + 1].ndOp == _add) || (nd[i + 1].ndOp == _sub))) { //слева приоритетнее элемент
				nd[i + 1].prvNd = &nd[i - 1];
				nd[i - 1].pstNd = &nd[i];
				nd[i - 1].prnNd = i + 1;
				nd[i].prnNd = i - 1;
			}
			else if ((((nd[i + 1].ndOp == _mul) || (nd[i + 1].ndOp == _div)) && ((nd[i - 1].ndOp == _add) || (nd[i - 1].ndOp == _sub)))) {
				nd[i - 1].prvNd = &nd[i + 1];
				nd[i + 1].pstNd = &nd[i];
				nd[i + 1].prnNd = i - 1;
				nd[i].prnNd = i + 1;
			}
			else if ((nd[i + 1].ndOp == _add) || (nd[i + 1].ndOp == _sub) || (nd[i + 1].ndOp == _mul) || (nd[i + 1].ndOp == _div)) {
				nd[i].prnNd = i + 1;
				nd[i + 1].prvNd = &nd[i];
			}
			else if ((nd[i+1].ndOp == _ixbz)&&((nd[i - 1].ndOp == _add) || (nd[i - 1].ndOp == _sub) || (nd[i - 1].ndOp == _mul) || (nd[i - 1].ndOp == _div))) {
				nd[i+1].prnNd = i - 1;
				nd[i - 1].pstNd = &nd[i+1];
				nd[i + 3].prnNd = i - 1;
			}
		}
	}
	for (int i = 1; i < nn; i++) {
		if (((nd[i].ndOp == _nam) || (nd[i].ndOp == _srcn) || (nd[i].ndOp == _ixbz)) && (((nd[i - 1].ndOp >= 212) && (nd[i - 1].ndOp <= 215)) || (nd[i - 1].ndOp == 218))) {
			lxNode buf = nd[i];
			int num = i;
			while (buf.prnNd != 0) {
				num = nd[i].prnNd;
				buf = nd[nd[i].prnNd];
			}
			nd[i - 1].pstNd = &nd[num];
			nd[num].prnNd = i - 1;
		}
	}
	for (int i = 1; i < nn; i++) {
		if ((nd[i].ndOp == _ixbz)&&(nd[i+2].ndOp == _ixbz)) {
			nd[i + 2] = nd[i];
		}
	}
	*/
	return nn-1;
}

