#include <stdio.h>
void	prOpBr(struct lxNode*rt);	//������ �����
void	prClBr(struct lxNode*rt);	//������ �����
									// ��������� ������� ������
void	prLxTxt(struct lxNode*rt);	//����� �������� 
void	prLxTxt(struct lxNode*rt, FILE*f); //����� �������� 
										   // ��������� ������ ������
void	prLaTxt(char* res,struct lxNode*ar, unsigned n); //������� ������ ������ 
void	prLaTbl(struct lxNode*ar, unsigned n); //������� ������ ������ 
void	prNode(struct lxNode*ar);
void	getout(char* outx);
void checkout(char* res, char* out);