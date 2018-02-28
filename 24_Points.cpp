//在计算后缀表达式的过程直接以中缀表达式的形式记录路径，最后输出。

#include <iostream>
#include <algorithm>
#include <cmath>
#include <stack>
#include <cstring>
using namespace std;

const double eps = 0.000001;
int num[4];
char permutation[7];	//用来做全排列的数组，包括4个运算数和3个运算符
int op_count[4];		//下标表示4种运算符，值表示这种运算符有几个
string expression;		//在计算过程中记录路径，格式为中缀表达式

char num_to_op(int op)
{
	switch (op)
	{
	case 0:
		return '+';
	case 1:
		return '-';
	case 2:
		return '*';
	case 3:
		return '/';
	}
	return 0;
}

double op_calc(char op, double a, double b)
{
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	}
	return 0;
}

double calc()
{
	int i;
	double a, b, sum;
	expression = "";
	stack<double> my_stack;
	for (i = 0; i < 7; ++i)
	{
		if (permutation[i] >= 0 && permutation[i] <= 3)		//表示当前是操作数
			my_stack.push(num[permutation[i]]);		//将操作数压栈
		else
		{
			if (my_stack.empty())
				return 0;		//表示当前排列不是合法的后缀表达式，返回0
			b = my_stack.top();
			my_stack.pop();
			if (my_stack.empty())
				return 0;
			a = my_stack.top();
			my_stack.pop();
			sum = op_calc(permutation[i], a, b);
			my_stack.push(sum);

			if (expression == "")
				expression = to_string(int(a)) + permutation[i] + to_string(int(b));
			else
				expression = to_string(int(a)) + permutation[i] + "(" + expression + ")";
		}
	}
	return sum;
}

void permutate()
{
	int i, j;
	for (i = 0; i < 4; ++i)
		permutation[i] = i;		//permutation数组中的0～3表示4个运算数
	for (j = 0; j < 4; ++j)
	{
		int count = op_count[j];
		while (count--)
			permutation[i++] = num_to_op(j);	//'+','-','*','/'总共有3个
	}
	while (next_permutation(permutation, permutation + 7))
		if (abs(calc() - 24) < eps)
			cout << expression << endl;
}

void dfs(int count, int left)	//一共有3个运算符的位置，left表示还剩几个
{
	if (count == 4)
	{
		if (left == 0)
			permutate();
		return;
	}
	int i;
	for (i = 0; i <= 3; ++i)	//当前的运算符取0～3个
	{
		op_count[count] = i;
		dfs(count + 1, left - i);
	}
}

int main()
{
	int i;
	for (i = 0; i < 4; ++i)
		cin >> num[i];
	dfs(0, 3);
	return 0;
}
