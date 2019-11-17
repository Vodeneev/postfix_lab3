#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string expression;
	TPostfix postfix;
	double res;
	setlocale(LC_ALL, "Russian");
	postfix.SetInfix("a+a + b + c +a");
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	postfix.ToPostfix();
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	res = postfix.Calculate();
	cout << res << endl;
	system("pause");
	return 0;
}