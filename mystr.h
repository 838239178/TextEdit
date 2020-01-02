#pragma once
#include <cassert>

char* str_cpy(char* s1, char* s2);
int str_len(char* s);
int str_cmp(char* s1, char* s2);
int str_strKMP(char* s, char* p);
void MakeNext(int next[], char s[]);

char* str_cpy(char* s1, char* s2)                            //若s2长度大于s1则部分复制，并返回多余部分
{
	assert(s1 != NULL && s2 != NULL);
	int maxlen = 79;										 //规定最大复制长度为80,下标最多到79
	int cnt = 0;											 //记录下标
	char* temp = s1;									
	while ( cnt++ < maxlen && (*(s1++) = *(s2++)) != '\0');
	temp[79] = '\0';
	if (*(s2-1) != '\0') return s2;                          //如果s2没有完全复制就返回
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
/*KMP算法查找子串*/
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
		//如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++    
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			//如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]  
			//失配时，模式串向右移动的位数为：已匹配字符数 - 失配字符的上一位字符所对应的最大长度值
			//next[j]即为j所对应的next值      
			j = next[j];
		}
	}
	delete[]next;
	/*找到返回下标，找不到返回-1*/
	if (j == pLen)
		return i - j;
	else
		return -1;
}