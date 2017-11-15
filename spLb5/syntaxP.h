#define MAX_NODES 1024	// �������� ������� ����� �����
#define MAX_CCNST 1024	// ��������� ����� ���������� ��������
#define MAX_UCNST 1024	// ��������� ����� �������� ��������
#define MAX_SCNST 1024	// ��������� ����� ���������� ������
#define BRK_LIM	  1024	// ��������� ����� ����� �����
#define LENGTHKW  230	// ������� ������� ���������� ��� ��� Verilog HDL
#define NTYPE 35
enum tokPrec // ����������� �������� ���� ������
{nil,	// ����� �����
 pend,//�������� ������� ��������-������ - '.' ��� 'endmodule' 
 pclf,// ������� ���������� ����� - '}' ��� 'end' �� 'join'
 pclb,// ������� ����� - ')'
 peos,// ���� ��������� - ';'
 pekw,// ����������� ��������� ����� ����������� - 'enum', 'struct'
 pmkw,// ��������� ��������� ����� ����������� - 'else', ...
 pskw,// ����������� ��������� ����� ����������� - 'if', 'for'
 prep,// ����������� ��������� ����� ����������� - 'do', 'repeat'
 popf,// ������� ���������� ����� - '{' ��� 'begin' �� 'fork'
 pcld,// ������� ����� ����� - '}'
 pbkw,// ����������� ��������� ����� ����������� - 'int', 'float'
 pdol,// ���������� ������ - ',' ��� ��������� ^ ���� �������
 pcls,// ������� ����� - ']'
 pass,// ����������� - '=', '+=', ... 
 psmc,// ��������� - ':'
 pcnd,// ������ �������� - '?'
 pacf,// ������� �� ���� - '.' �� '->'
 porl,// ������ ���'������ - '||'
 panl,// ������ ���'������ - '&&'
 porw,// ������� ���'������ - '|' �� '~|'
 pxrw,// ��������� �� ������� 2 - '^', '^~' �� '~^'
 panw,// ������� ���'������ - '&' �� '~&'
 pequ,//�������� ������-�������� - '==', '!=', '===','!==' 
 prel,// �������� �����-�����  - '<', '<=', '>=' �� '>'
 pshf,// ����� - '<<', '>>', '<<<' �� '>>>'
 padd,// ���������-��������� - '+' �� '-'
 pmul,// ��������-������ - '*', '/' �� '%'
 ppwr,// ��������� �� �������  
 popd,// ������� ����� ����� - '{'
 pops,// ������� ����� - '['
 popb,// ������� ����� - '('
 puno,// ������ ��������
 ptrm,// �����: ��������� �� ����� �����, �������, ����
 pprg//�������� ������� ��������-������- 'progam' ��� 'module' 
};
void SxAnInit(char nl);
int nxtProd(struct lxNode * nd,	// �������� �� ������� ������ ����� 
 		  int nR,	// ����� ���������� �����
 		  int nC);	// ����� ��������� �����
int	prCmpr(struct lxNode*nd, int nn, int nr); //�������� ��� ���������� �����

int SxAnlz(struct lxNode * nd,	// �������� �� ������� ������ ����� 
	int nn);	// ����� ��������� �����
