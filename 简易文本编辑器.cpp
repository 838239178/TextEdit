#include<bits/stdc++.h>
#include "mystr.h"
#include "mylist.h"
using namespace std;

void PrintMenu();        //打印菜单
void Loadfile(LNodeP);   //读盘
void Writefile(LNodeP);  //存盘
void Printall(LNodeP);   //显示全部内容
void Delline(LNodeP);    //删除一行
void Insline(LNodeP);    //插入一行
void Changeline(LNodeP); //修改一行
void Copyline(LNodeP);   //拷贝一行
void SearchStr(LNodeP);  //关键字查找
void ReplaceStr(LNodeP); //关键字替换

char address[20];

int main()
{
	LNodeP head = NULL;
	while (1) {
		PrintMenu();
		int ch;
		std::cin >> ch;
		int i;
		switch (ch)
		{
		case 1: head = new LNode;Loadfile(head); break;
		case 2: Printall(head);   break;
		case 3: Insline(head);    break;
		case 4: Delline(head);    break;
		case 5: Copyline(head);   break;
		case 6: Changeline(head); break;
		case 7: SearchStr(head);  break;
		case 8: ReplaceStr(head); break;
		case 9: Writefile(head);  break;
		case 0: exit(0);
		default:std::cout << "输入有误" << endl;
		}
	}
}
void PrintMenu()
{
	std::cout << "请选择：";
	std::cout << "1.打开文件<new/old>"
		<< "\t2.显示文件内容" << endl
		<< "\t3.插入行 4.删除行"
		<< "\t5.拷贝行 6.修改行" << endl
		<< "\t7.查找字符串"
		<< "\t\t8.替换字符串" << endl
		<< "\t9.存盘退出"
		<< "\t\t0.放弃编辑" << endl;
}
void Printall(LNodeP head)
{
	int i;
	i = PrintList(head); 
	if (i == -1)std::cout << "错误：没有打开文件"<< endl;     //返回-1表示head=NULL
	else if(!i) std::cout << "当前没有文字" << endl;	         //成功则返回打印了多少行
}
void Loadfile(LNodeP head)
{
	if (str_cmp(address,(char*)"") != 0) {
		std::cout << "错误：请勿重复打开文件！" << endl;
		return;
	}
	CreateList(head);
	std::cout << "请输入文件名<可包含路径，不超过19个字符>：";
	std::cin >> address;
	FILE* p;												
	p = fopen(address, "a+");							//只读打开文件，没有则创建
	if (!p) {
		std::cout << "文件打开失败" << endl;
	}
	char s[100] = "";
	while (fgets(s,sizeof(s),p)) {
		s[str_len(s) - 1] = '\0';
		AppendList(head, s);
	}
	std::cout << "读取成功" << endl;
	fclose(p);
}
void Writefile(LNodeP head)
{
	FILE* p;
	p = fopen(address, "w");
	if (!p) {
		std::cout << "错误:你还没有读取文件" << endl;
		return;
	}
	for (Positon i = head->next; i; i = i->next) {
		fputs(i->str, p);
		fputc('\n', p);
	}
	std::cout << "保存成功!" << endl;
	fclose(p);
	exit(0);
}
void Insline(LNodeP head)
{
	if(!head) {
		std::cout << "错误:你还没有读取文件" << endl;
		return;
	}
	int n, m;
	std::cout << "在第n行前插入m行，请输入n m：";
	std::cin >> n >> m;
	Positon p = FindList(head, n);
	if (!p) {
		std::cout << "没有找到这一行，默认插入第一行" << endl;
		p = head;
	}
	std::cout << "请输入待插入的文本：" << endl;
	char s[10][200];
	getchar();
	for (int i = 0; i < m; i++)  gets_s(s[i]);
	for (int i = m-1; i >= 0; i--) InsertList(head, s[i], p);
	std::cout << "插入成功" << endl;
}
void Delline(LNodeP head)
{
	if (!head) {
		std::cout << "错误:你还没有读取文件" << endl;
		return;
	}
	int n,m;
	std::cout << "从第n行开始删除m行，请输入 n m：";
	std::cin >> n >> m;
	int flag = DeleteList(head, n, m);
	if (flag == -1)
		std::cout << "错误：文件为空或行号有误" << endl;
	else 
		std::cout << "删除成功" << endl;
}
void Changeline(LNodeP head)
{
	if (!head) {
		std::cout << "错误:你还没有读取文件" << endl;
		return;
	}
	Positon pos;
	char s[500];
	int n;
	std::cout << "请输入要修改的行号：";
	std::cin >> n;
	pos = FindList(head, n);                                 //返回n-1的指针
	if (!pos) {
		std::cout << "没有这一行" << endl;
	}
	else {
		pos = pos->next;
		std::cout << pos->str << endl;
		std::cout << "请输入新内容：";
		getchar();
		gets_s(s);
		if (Modifylist(pos, s))
			std::cout << "修改成功" << endl;
	}
}
void Copyline(LNodeP head)
{
	if (!head) {
		std::cout << "错误:你还没有读取文件" << endl;
		return;
	}
	if (!head->next) {
		std::cout << "错误：没有可以拷贝的内容" << endl;
		return;
	}
	std::cout << "把从n行开始的m行拷贝到k行前，请输入 n m k：";
	int n, m, k;
	std::cin >> n >> m >> k;
	Positon begin, end, pos;
	pos = FindList(head, k);	                          //找到要插入的位置
	begin = FindList(head, n);							  //找到要复制起点的前一个结点
	end = FindList(head, n + m - 1);					  //找到复制结尾的前一个结点
	if (!pos || !begin || !end) {                         //如果起点或者插入的位置找不到就是输入错误
		std::cout << "输入的行号有误" << endl;
		return;
	}
	else {
		begin = begin->next;							  //复制起点
		end = end->next->next;                            //复制结尾的后一个结点
	}
	LNodeP temph = new LNode;
	CreateList(temph);                                    //创建一个临时链表
	for (; begin != end && begin; begin = begin->next)
		AppendList(temph, begin->str);                    //把要复制的内容复制到新链表
	temph->tail->next = pos->next;                        //把临时链表的尾连在插入位置
	pos->next = temph->next;                              //把头换成插入位置的前一个节点
	delete temph;                                         //删掉临时链表的头节点
	std::cout << "拷贝成功！" << endl;
}
void SearchStr(LNodeP head)
{
	if (!head) {
		std::cout << "错误:你还没有读取文件" << endl;
		return;
	}
	if (!head->next) {
		std::cout << "错误:文件为空" << endl;
		return;
	}
	char dst[100];	
	char yn;	
	int cnt = 0;
	int count = 0;
	Positon pos = head;		
	std::cout << "请输入待查找的字符串：";
	std::cin >> dst;
	while (1) {
		pos = FindList(pos->next, dst,&count);
		if (!pos) {
			std::cout << "没找到" << endl;
			break;
		}
		else cnt++;
		std::cout << count << ":" << pos->str;
		std::cout << "第"<<cnt<<"个字符找到"<< endl;
		std::cout << "继续查找吗?<y/n>：";
		std::cin >> yn;
		if (yn == 'n') break;
	}
}
void ReplaceStr(LNodeP head)
{
	if (!head) {
		std::cout << "错误:你还没有读取文件" << endl;
		return;
	}
	char dst[100];                                       //被替换的字符串
	char rep[100];										 //新字符串
	char yn;											 //yes or no
	int count = 0;                                       //被替换字符串所在行号
	int cnt = 0;                                         //被替换字符串的个数
	int index = 0;                                       //被替换字符串在数组的首地址（下标）
	Positon pos = head;		
	std::cout << "请输入要替换的字符：";
	getchar();
	gets_s(dst);
	std::cout << "替换为：";
	getchar();
	gets_s(rep);
	while (1) {
		pos = FindList(pos, dst, &count,&index);
		if (!pos) {
			std::cout << "没找到" << endl;
			break;
		}
		else cnt++;
		std::cout << count << ":" << pos->str;
		std::cout << "第" << cnt << "个字符找到" << endl;
		std::cout << "是否替换?<y/n>：";
		std::cin >> yn;
		if (yn == 'n')break;
		else {
			int j = 0;
			/*生产一个替换后的字符串*/
			char newStr[100] = "";                                  //新字符串
			for (int i = 0; i < str_len(pos->str); i++) {                                   
				if (i == index) {                                   //从被替换字符串的首字符开始变成新字符
					for (int z = 0; z < str_len(rep); z++)
						newStr[j++] = rep[z];
				}
				else if (i > index + strlen(dst)-1 || i < index)    //若被替换的长度大于替换的长度，则应删除多的部分
					newStr[j++] = pos->str[i];                      //其他位置照搬
			}
			/*调用modifylist改写pos的内容*/
			Modifylist(pos, newStr); 
			std::cout << "替换成功，继续替换吗？<y/n>：";
			std::cin >> yn;
			if (yn == 'n')break;
		}
	}
}