struct keyStr// ключова частина запису // key part of table element
{
	char* str;
	unsigned int nMod;
};
// функціональна частина запису
struct fStr	// functional part of record
{
	float _f;
};
struct recrd// структура рядка таблиці
{			// примірник структури ключа
	struct keyStr key;	// instantiation of key structure
						// примірник функціональної частини
	struct fStr func;	// instantiation of functional part
						// ознака вилучення 
	char _del;	// mark of deleted record
};
#define ASM 0	// без вставок на Асемблері, коли 0
// when 0 - without Assembler insertions
//------------------------------------------------------
// обробка записів таблиць за прямою адресою
// вибірка за прямою адресою
// retreaving by direct address
struct recrd* selNmb(struct recrd*, unsigned int nElm);
// включення за прямою адресою
// insertion by direct address
struct recrd* insNmb(struct recrd*pElm,
	struct recrd*tb, unsigned int nElm, int*pQnElm);
// вилучення за прямою адресою
// deleting by direct address
struct recrd* delNmb(struct recrd*, unsigned int nElm);
// корекція за прямою адресою
// correction by direct address
struct recrd* updNmb(struct recrd*pElm,
	struct recrd*tb, unsigned int nElm, int*pQnElm);
//------------------------------------------------------
// порівняння за відношенням нерівності
// comparison by nonequlity relation
int neqKey(struct recrd*, struct keyStr);
// порівняння рядків
// row comparison 
int cmpStr(unsigned char* s1, unsigned char* s2);
// порівняння за відношенням порядку рядків
// comparison by order relation for rows
int cmpKey(struct recrd*, struct keyStr);
// порівняння за відношенням порядку для ключів
// comparison by order relation for keys
int cmpKys(struct keyStr*, struct keyStr*);
// порівняння за відношенням схожості
// comparison by similarity relation 
int simKey(struct recrd*, struct keyStr);
//------------------------------------------------------
// вибірка за лінійним пошуком
// retreaving by linear search
struct recrd*selLin(struct keyStr, struct recrd*tb, int ln);
// повторна вибірка за лінійним пошуком
// next retreaving by linear search
struct recrd* selLinNxt(struct keyStr kArg,
	struct recrd* tb, int ln);
// включення за лінійним пошуком
// insertion by linear search
struct recrd*insLin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm);
// вилучення за лінійним пошуком
// deleting by linear search
struct recrd*delLin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm);
// корекція за лінійним пошуком
// correction by linear search
struct recrd*updLin(struct keyStr, struct recrd*pElm,
	struct recrd*tb, int*pQnElm);
// пакування для лінійного пошуку
// packing for linear search
struct recrd*pckLin(struct recrd*tb, int*pQnElm);
//------------------------------------------------------
// сортування за двійковим пошуком
// sorting for linear search
struct recrd*srtBin(struct recrd*, int ln);
// вибірка за двійковим пошуком
// retreaving by binary search
struct recrd*selBin(struct keyStr, struct recrd*, int ln);
//---!!! реалізації дописуються за варіантом!!!---
// включення за двійковим пошуком
// insertion by binary search
struct recrd*insBin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm, int ln, int plc);
// вилучення за двійковим пошуком
// deleting by binary search
struct recrd*delBin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm);
// корекція за двійковим пошуком
// correction by binary search
struct recrd*updBin(struct keyStr, struct recrd*pElm,
	struct recrd*tb, int*pQnElm);
void selBinSame(struct keyStr kArg, struct recrd*tb, struct recrd*rs, int*pQnElm);