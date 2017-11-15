// spLb9c.cpp: Визначає вхідну точку для консольної прикладної програми.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{double b,a[4]={2,3,4,5};
unsigned n=2,d=5;
_asm{
	mov	eax,d
	cmp	eax,0
	setne	al
	movsx	eax,al
	push	eax
	fstp	b
	add	esp,4
	fild	n
	mov	esi,n
	fld	a[esi*8]
	fmul	
	fstp b}
return 0;
}