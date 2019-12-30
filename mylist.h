#pragma once
#define ERROR -1
using namespace std;

struct LNode
{
	char str[80];
	LNode* next;
	LNode* tail;  //β���ָ�루ֻ��ͷ�ڵ��ж��壩
	LNode();      //Ĭ�Ϲ��캯��
};
typedef struct LNode LNode;
typedef struct LNode* LNodeP;
typedef struct LNode* Positon;

LNode::LNode() {
	str_cpy(str, (char*)"");
	next = tail = NULL;
}

void CreateList(LNodeP head)                             //��ʼ��ͷ�ڵ�
{
	if (!head) return;
	str_cpy(head->str, (char*)"");
	head->next = NULL;
	head->tail = head;
}
void InsertList(LNodeP head, char* s, Positon p = NULL)  //���뵽P���棬û��ָ��positonĬ�ϲ����һ��
{
	LNodeP newLNode = new LNode;
	if (!p) p = head;
	char* temp = str_cpy(newLNode->str, s);
	newLNode->next = p->next;
	p->next = newLNode;
	if (temp)InsertList(head, temp, newLNode);			 //�������ʣ�µ�û������ٲ���
}
void AppendList(LNodeP head, char* s)                    //β������
{
	LNodeP newLNode = new LNode;
	char* temp = str_cpy(newLNode->str, s);
	head->tail->next = newLNode;
	head->tail = newLNode;
	if (temp)InsertList(head, temp, newLNode);           //�������ʣ�µ�û������ٲ���
}
                                         /*��������ʼλ*/    /*�ڵڼ����ҵ�*/ /*��������±�*/
Positon FindList(LNodeP begin, char* f, /*Positon begin = NULL,*/ int* count = NULL, int* index = NULL)        //���ַ�������
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
Positon FindList(LNodeP head, int n)                                //���кŲ��ҷ���ǰһ����ָ��
{
	int cnt = 0;
	for (Positon i = head; i; i = i->next) {
		if (cnt++ == n-1)
			return i;
	}
	return NULL;
}
int DeleteList(LNodeP head,int begin,int count)                     //����ɾ��
{
	if (!head->next) return ERROR;
	Positon b = FindList(head, begin);                             //�ҵ���ɾ����ǰһ�����
	Positon e = FindList(head, begin+count-1)->next->next;         //�ҵ���ɾ�������һ������һ����㣨��b��ʼ�ң�
	Positon q = b->next;                                           //��ָ��q��λ�ڴ�ɾ���ĵ�һ���ڵ�
	if (!b) return ERROR;	                                       //λ�ò�����
	for (Positon i = q->next; i != e; q = i, i = i->next)          //��ָ��i����q���ͷ�qָ��Ĵ�����
		delete q;
	delete q;                                                      //ѭ��������qָ�����һ��Ҫɾ���Ľ��
	b->next = e;                                                   //�ѶϿ�����������������
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
