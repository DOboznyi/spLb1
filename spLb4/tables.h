struct recrdKWD	// ��������� ����� ������� �������� ���� � ������������
{char* key;// �������� ��������� �����
 enum tokType func;// �������� ������������� �������
 int  versn;	// ����� ��������� ������ ������������
};
//---!!! ������� ����� ���������!!!---
// ��������� �����
int cmpStr(unsigned char* s1, unsigned char* s2);
// ������ �� �������� �������
struct recrdKWD*selBin(char* kArg, struct recrdKWD*tb, int ln);
//---!!! ������� ����� ������������ � ������������!!!---
// ���������� ��� ��������� ������
struct recrdKWD*srtBin(struct recrdKWD*tb, int ln);
// ��������� �� �������� �������
struct recrdKWD*insBin(struct recrdKWD*pElm, struct recrdKWD*tb, int*pQnElm, int ln, int plc);
// ��������� �� �������� �������
struct recrdKWD*delBin(struct recrdKWD*pElm,
					struct recrdKWD*tb, int*pQnElm);
// �������� �� �������� �������
struct recrdKWD*updBin(struct recrdKWD*pElm,
					struct recrdKWD*tb, int*pQnElm);
//------------------------------------------------------
