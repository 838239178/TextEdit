#pragma once
#include <cassert>

char* str_cpy(char* s1, char* s2);
int str_len(char* s);
int str_cmp(char* s1, char* s2);
int str_strKMP(char* s, char* p);
void MakeNext(int next[], char s[]);

char* str_cpy(char* s1, char* s2)                            //��s2���ȴ���s1�򲿷ָ��ƣ������ض��ಿ��
{
	assert(s1 != NULL && s2 != NULL);
	int maxlen = 79;										 //�涨����Ƴ���Ϊ80,�±���ൽ79
	int cnt = 0;											 //��¼�±�
	char* temp = s1;									
	while ( cnt++ < maxlen && (*(s1++) = *(s2++)) != '\0');
	temp[79] = '\0';
	if (*(s2-1) != '\0') return s2;                          //���s2û����ȫ���ƾͷ���
	else return NULL;
}
int str_len(char* s)
{
	int cnt = 0;
	while (*s != '\0') {
		cnt++;
		s++;
	}
	return cnt;
}
int str_cmp(char* s1, char* s2)
{
	assert(s1 != NULL && s2 != NULL);
	int ret = 0;
	while (!(ret = *(s1++) - *(s2++)) && *s1 || *s2);
	if (ret < 0) return -1;
	if (ret == 0) return 0;
	if (ret > 0) return 1;
}
/*KMP�㷨�����Ӵ�*/
void MakeNext(int next[],char s[])
{
	int slen = str_len(s);
	int j = 0, k = -1;
	next[0] = -1;
	while (j < slen)
		if (k == -1 || s[j] == s[k])
			next[++j] = ++k;
		else
			k = next[k];
}
int str_strKMP(char* s, char* p)
{
	int i = 0;
	int j = 0;
	int sLen = str_len(s);
	int pLen = str_len(p);
	int* next = new int[pLen+1];
	MakeNext(next, p);
	while (i < sLen && j < pLen)
	{
		//���j = -1�����ߵ�ǰ�ַ�ƥ��ɹ�����S[i] == P[j]��������i++��j++    
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			//���j != -1���ҵ�ǰ�ַ�ƥ��ʧ�ܣ���S[i] != P[j]�������� i ���䣬j = next[j]  
			//ʧ��ʱ��ģʽ�������ƶ���λ��Ϊ����ƥ���ַ��� - ʧ���ַ�����һλ�ַ�����Ӧ����󳤶�ֵ
			//next[j]��Ϊj����Ӧ��nextֵ      
			j = next[j];
		}
	}
	delete[]next;
	/*�ҵ������±꣬�Ҳ�������-1*/
	if (j == pLen)
		return i - j;
	else
		return -1;
}