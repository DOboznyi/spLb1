struct indStrUS// структура індексу у вигляді двійкового дерева
{
	struct lxNode* pKyStr;//вказівник на вузол
	struct indStrUS* pLtPtr;//вказівник вліво
	struct indStrUS* pRtPtr;//вказівник вправо
	int dif;
};
//---!!! функції етапу виконання!!!---
// порівняння терміналів за відношенням порядку
int cmpTrm(struct lxNode*k0, struct lxNode*kArg);//cmpKys
												 // вибірка через пошук за двійковим деревом
struct indStrUS*selBTr(struct lxNode*kArg, struct indStrUS*rtTb);
// балансування для двійкового дерева
struct indStrUS*balBTr(struct indStrUS*rtTb);
// включення через пошук за двійковим деревом
struct indStrUS*insBTr(struct lxNode*pElm, struct indStrUS*rtTb);
// вилучення через пошук за двійковим деревом
struct indStrUS*delBTr(struct lxNode*pElm,
	struct recrdKWD*tb, int*pQnElm);
// корекція через пошук за двійковим деревом
struct indStrUS*updBTr(struct lxNode*pElm, struct indStrUS*rtTb);
// для вибірки з таблиці за індексом
struct lxNode*selNmb(struct lxNode*tb, unsigned int nElm);
// для вставки до таблиці з корекцією індексу
struct lxNode*insNmb(struct lxNode*pElm, struct lxNode*tb, int *pQnElm, int ln, int plc);
// для корекції таблиці з індексом
struct lxNode*updNmb(struct lxNode*pElm, struct lxNode*tb, unsigned int nElm, int *pQnElm);