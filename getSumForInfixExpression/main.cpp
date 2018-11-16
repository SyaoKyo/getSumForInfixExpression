/**************************************
 *                                    *
 *  求操作数皆为正数的中缀表达式的值  *
 *                                    *
 **************************************/
#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int getPriority(char op);
int calSub(float opnd1, char op, float opnd2, float &result);
int calStackTopTwo(float s1[], int &top1, char s2[], int &top2);
float calInfix(char exp[]);

const float MIN = 1e-35;
const int maxSize = 1000;

int main()
{
	char exp[maxSize];
	cin >> exp;
	cout << calInfix(exp) << endl;
	//char *str = strrev(exp);
	//cout << atof(str) << endl;
	return 0;
}

int getPriority(char op)
{
	if (op == '+' || op == '-')
		return 0;
	else
		return 1;
}

int calSub(float opnd1, char op, float opnd2, float &result)
{
	switch (op)
	{
	case '+':
		result = opnd1 + opnd2;
		break;
	case '-':
		result = opnd1 - opnd2;
		break;
	case '*':
		result = opnd1 * opnd2;
		break;
	case '/':
		if (fabs(opnd2) < MIN)
			return 0;
		else
			result = opnd1 / opnd2;
		break;
	default:
		break;
	}
	return 1;
}

int calStackTopTwo(float s1[], int &top1, char s2[], int &top2)
{
	float opnd1, opnd2, result;
	char op;
	int flag;
	opnd2 = s1[top1--];
	opnd1 = s1[top1--];
	op = s2[top2--];
	flag = calSub(opnd1, op, opnd2, result);
	if (!flag)
		cout << "error" << endl;
	s1[++top1] = result;
	return flag;
}

float calInfix(char exp[])
{
	float s1[maxSize];int top1 = -1;
	char s2[maxSize];int top2 = -1;
	int i = 0;
	while (exp[i] != '\0')
	{
		if (exp[i] >= '0'&&exp[i] <= '9')
		{
			int j = 0;
			char str[maxSize];
			str[j++] = exp[i];
			while (exp[i + 1] >= '0'&&exp[i + 1] <= '9'||exp[i + 1] == '.')
			{
				str[j++] = exp[++i];
			}
			i++;
			s1[++top1] = atof(str);
			while (j >-1)
			{
				str[j--] = ',';
			}
		}
		else if (exp[i] == '(')
		{
				s2[++top2] = exp[i];
				i++;
		}
		else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
		{
			if (top2 == -1 || s2[top2] == '(' || getPriority(exp[i]) > getPriority(s2[top2]))
			{
				s2[++top2] = exp[i];
				i++;
			}
			else
			{
				if (!calStackTopTwo(s1, top1, s2, top2))
					return 0;
			}
		}
		else if (exp[i] == ')')
		{
			while (s2[top2] != '(')
			{
				if (!calStackTopTwo(s1, top1, s2, top2))
					return 0;
			}
			top2--;
			i++;
		}
	}
	while (top2 != -1)
	{
		if (!calStackTopTwo(s1, top1, s2, top2))
			return 0;
	}
	return s1[top1];
}