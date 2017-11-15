struct keyStr// ������� ������� ������ // key part of table element
{
	char* str;
	unsigned int nMod;
};
// ������������� ������� ������
struct fStr	// functional part of record
{
	float _f;
};
struct recrd// ��������� ����� �������
{			// �������� ��������� �����
	struct keyStr key;	// instantiation of key structure
						// �������� ������������� �������
	struct fStr func;	// instantiation of functional part
						// ������ ��������� 
	char _del;	// mark of deleted record
};
#define ASM 0	// ��� ������� �� ��������, ���� 0
// when 0 - without Assembler insertions
//------------------------------------------------------
// ������� ������ ������� �� ������ �������
// ������ �� ������ �������
// retreaving by direct address
struct recrd* selNmb(struct recrd*, unsigned int nElm);
// ��������� �� ������ �������
// insertion by direct address
struct recrd* insNmb(struct recrd*pElm,
	struct recrd*tb, unsigned int nElm, int*pQnElm);
// ��������� �� ������ �������
// deleting by direct address
struct recrd* delNmb(struct recrd*, unsigned int nElm);
// �������� �� ������ �������
// correction by direct address
struct recrd* updNmb(struct recrd*pElm,
	struct recrd*tb, unsigned int nElm, int*pQnElm);
//------------------------------------------------------
// ��������� �� ���������� ��������
// comparison by nonequlity relation
int neqKey(struct recrd*, struct keyStr);
// ��������� �����
// row comparison 
int cmpStr(unsigned char* s1, unsigned char* s2);
// ��������� �� ���������� ������� �����
// comparison by order relation for rows
int cmpKey(struct recrd*, struct keyStr);
// ��������� �� ���������� ������� ��� ������
// comparison by order relation for keys
int cmpKys(struct keyStr*, struct keyStr*);
// ��������� �� ���������� �������
// comparison by similarity relation 
int simKey(struct recrd*, struct keyStr);
//------------------------------------------------------
// ������ �� ������ �������
// retreaving by linear search
struct recrd*selLin(struct keyStr, struct recrd*tb, int ln);
// �������� ������ �� ������ �������
// next retreaving by linear search
struct recrd* selLinNxt(struct keyStr kArg,
	struct recrd* tb, int ln);
// ��������� �� ������ �������
// insertion by linear search
struct recrd*insLin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm);
// ��������� �� ������ �������
// deleting by linear search
struct recrd*delLin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm);
// �������� �� ������ �������
// correction by linear search
struct recrd*updLin(struct keyStr, struct recrd*pElm,
	struct recrd*tb, int*pQnElm);
// ��������� ��� ������� ������
// packing for linear search
struct recrd*pckLin(struct recrd*tb, int*pQnElm);
//------------------------------------------------------
// ���������� �� �������� �������
// sorting for linear search
struct recrd*srtBin(struct recrd*, int ln);
// ������ �� �������� �������
// retreaving by binary search
struct recrd*selBin(struct keyStr, struct recrd*, int ln);
//---!!! ��������� ����������� �� ��������!!!---
// ��������� �� �������� �������
// insertion by binary search
struct recrd*insBin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm, int ln, int plc);
// ��������� �� �������� �������
// deleting by binary search
struct recrd*delBin(struct recrd*pElm,
	struct recrd*tb, int*pQnElm);
// �������� �� �������� �������
// correction by binary search
struct recrd*updBin(struct keyStr, struct recrd*pElm,
	struct recrd*tb, int*pQnElm);
void selBinSame(struct keyStr kArg, struct recrd*tb, struct recrd*rs, int*pQnElm);