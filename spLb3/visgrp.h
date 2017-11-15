#include <stdio.h>
void	prOpBr(struct lxNode*rt);	//відкриті дужки
void	prClBr(struct lxNode*rt);	//закриті дужки
									// виведення піддерва лексем
void	prLxTxt(struct lxNode*rt);	//корінь піддерева 
void	prLxTxt(struct lxNode*rt, FILE*f); //корінь піддерева 
										   // виведення масиву лексем
void	prLaTxt(char* res,struct lxNode*ar, unsigned n); //початок масиву лексем 
void	prLaTbl(struct lxNode*ar, unsigned n); //початок масиву лексем 
void	prNode(struct lxNode*ar);
void	getout(char* outx);
void checkout(char* res, char* out);