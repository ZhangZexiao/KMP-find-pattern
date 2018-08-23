// KMP.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

int *get_kmp_pattern_max_prefix_length_array(char *pattern)
{
	// m is number of char(s)
	int m = strlen(pattern);
	if (0 == m)
	{
		return nullptr;
	}
	// index of pi is from "0" to "m - 1"
	int *pi = new int[m];
	// pi[0] is the length of the max prefix, which should be 0 as pi[0...0] doesn't have prefix.
	pi[0] = 0;
	// calculate from the second char which index is 1
	int q = 1;
	// k is the length of the max prefix
	int k = 0;
	while (q < m)
	{
		while (k > 0 && pattern[k] != pattern[q])
		{
			k = pi[k - 1];
		}
		if (pattern[k] == pattern[q])
		{
			k++;			
		}
		pi[q] = k;
		q++;
	}
	return pi;
}

void findPattern(char *text, char *pattern)
{	
	std::cout << "find pattern \"" << pattern << "\" in text \"" << text << "\"" << std::endl;
	int m = strlen(pattern);
	if (0 == m)
	{
		return;
	}
	int *pi = get_kmp_pattern_max_prefix_length_array(pattern);
	int q = 0;
	for (std::size_t i = 0; i < strlen(text); i++)
	{
		// step 2, if next char after prefix in pattern different from next char in text
		while (q > 0 && pattern[q] != text[i])
		{
			q = pi[q - 1];
		}
		// step 1, find prefix of pattern in text
		if (pattern[q] == text[i])
		{
			q++;
		}
		// step 3, got the result
		if (q == m)
		{
			std::cout << "Pattern occurs with shift " << i - m + 1 << std::endl;
			q = pi[m - 1];
		}		
	}
}

void test1()
{
	char pattern[] = "abc";
	char text[] = "abcabc...abc";
	findPattern(text, pattern);
}
void test2()
{
	char pattern[] = "abca";
	char text[] = "abcabca...abc";
	findPattern(text, pattern);
}
void test3()
{
	char pattern[] = "abcabc";
	char text[] = "abcabca...abc";
	findPattern(text, pattern);
}
int main()
{
	test1();
	test2();
	test3();
	getchar();
    return 0;
}

