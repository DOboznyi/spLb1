struct indStrUS// ��������� ������� � ������ ��������� ������
{
	struct lxNode* pKyStr;//�������� �� �����
	struct indStrUS* pLtPtr;//�������� ����
	struct indStrUS* pRtPtr;//�������� ������
	int dif;
};
//---!!! ������� ����� ���������!!!---
// ��������� �������� �� ���������� �������
int cmpTrm(struct lxNode*k0, struct lxNode*kArg);//cmpKys
												 // ������ ����� ����� �� �������� �������
struct indStrUS*selBTr(struct lxNode*kArg, struct indStrUS*rtTb);
// ������������ ��� ��������� ������
struct indStrUS*balBTr(struct indStrUS*rtTb);
// ��������� ����� ����� �� �������� �������
struct indStrUS*insBTr(struct lxNode*pElm, struct indStrUS*rtTb);
// ��������� ����� ����� �� �������� �������
struct indStrUS*delBTr(struct lxNode*pElm,
	struct recrdKWD*tb, int*pQnElm);
// �������� ����� ����� �� �������� �������
struct indStrUS*updBTr(struct lxNode*pElm, struct indStrUS*rtTb);
// ��� ������ � ������� �� ��������
struct lxNode*selNmb(struct lxNode*tb, unsigned int nElm);
// ��� ������� �� ������� � ��������� �������
struct lxNode*insNmb(struct lxNode*pElm, struct lxNode*tb, int *pQnElm, int ln, int plc);
// ��� �������� ������� � ��������
struct lxNode*updNmb(struct lxNode*pElm, struct lxNode*tb, unsigned int nElm, int *pQnElm);