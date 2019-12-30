#pragma once
#define ERROR -1
using namespace std;

struct LNode
{
	char str[80];
	LNode* next;
	LNode* tail;  //尾结点指针（只在头节点中定义）
	LNode();      //默认构造函数
};
typedef struct LNode LNode;
typedef struct LNode* LNodeP;
typedef struct LNode* Positon;

LNode::LNode() {
	str_cpy(str, (char*)"");
	next = tail = NULL;
}

void CreateList(LNodeP head)                             //初始化头节点
{
	if (!head) return;
	str_cpy(head->str, (char*)"");
	head->next = NULL;
	head->tail = head;
}
void InsertList(LNodeP head, char* s, Positon p = NULL)  //插入到P后面，没有指定positon默认插入第一个
{
	LNodeP newLNode = new LNode;
	if (!p) p = head;
	char* temp = str_cpy(newLNode->str, s);
	newLNode->next = p->next;
	p->next = newLNode;
	if (temp)InsertList(head, temp, newLNode);			 //如果还有剩下的没插入就再插入
}
void AppendList(LNodeP head, char* s)                    //尾部插入
{
	LNodeP newLNode = new LNode;
	char* temp = str_cpy(newLNode->str, s);
	head->tail->next = newLNode;
	head->tail = newLNode;
	if (temp)InsertList(head, temp, newLNode);           //如果还有剩下的没插入就再插入
}
                                         /*搜索的起始位*/    /*在第几行找到*/ /*在数组的下标*/
Positon FindList(LNodeP begin, char* f, /*Positon begin = NULL,*/ int* count = NULL, int* index = NULL)        //按字符串查找
{
	if (!begin) return NULL;
	int a = 0, b = 0;
	if (!count) count = &b;
	if (!index) index = &a;
	int cnt = *count+1;
	for (Positon i = begin; i; i = i->next,cnt++) {
		if ((*index = str_strKMP(i->str, f)) != -1) {
			*count = cnt;
			return i;
		}
	}
	return NULL;
}
Positon FindList(LNodeP head, int n)                                //按行号查找返回前一个的指针
{
	int cnt = 0;
	for (Positon i = head; i; i = i->next) {
		if (cnt++ == n-1)
			return i;
	}
	return NULL;
}
int DeleteList(LNodeP head,int begin,int count)                     //批量删除
{
	if (!head->next) return ERROR;
	Positon b = FindList(head, begin);                             //找到待删除的前一个结点
	Positon e = FindList(head, begin+count-1)->next->next;         //找到待删除的最后一个的下一个结点（从b开始找）
	Positon q = b->next;                                           //把指针q定位在待删除的第一个节点
	if (!b) return ERROR;	                                       //位置不存在
	for (Positon i = q->next; i != e; q = i, i = i->next)          //用指针i引导q，释放q指向的储存区
		delete q;
	delete q;                                                      //循环结束后q指向最后一个要删除的结点
	b->next = e;                                                   //把断开的链表重新连起来
	return 0;
}

int PrintList(LNodeP head)
{
	int cnt = 1;
	if (!head)       return -1;
	if (!head->next) return 0;
	for (Positon i = head->next;i; i = i->next) {
		cout << cnt++ << ":" << i->str<<endl;
	}
	return cnt-1;
}

bool Modifylist(Positon pos, char* s)
{
	if (!pos) return 0;
	char* temp = str_cpy(pos->str, s);
	if (temp) InsertList(pos, temp);
	return 1;
}
