#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include "vector"
#include "string.h"

using namespace std;

class TPostfix
{
	string infix;
	vector<string> postfix;
public:
	TPostfix()
	{
		infix = '\0';
		postfix;
	}
	void SetInfix(string a) {
		infix = a;
	}
	string GetInfix() {
		return infix;
	}
	vector<string> GetPostfix() { return postfix; }
	void ToPostfix();
	double Calculate(); // Ввод переменных, вычисление по постфиксной форме
	bool Check();
	friend istream& operator >>(istream& in, TPostfix& a) {
		in >> a.infix;
		return in;
	}
	/*friend ostream& operator <<(ostream& out, TPostfix& a) {
		out << a.infix;
		return out;
	}*/
};

class Operation
{
private:

	void set_priorty()
	{
		if (operation == "*" || operation == "/")
			priority = 3;

		else if (operation == "+" || operation == "-")
			priority = 2;

		else if (operation == "(" || operation == ")")
			priority = 1;

	}

public:
	string operation;
	int priority;
	Operation()
	{
		operation = "";
		priority = 0;
	}
	Operation(string _sym)
	{
		operation = _sym;
		set_priorty();
	}
	Operation& operator=(Operation a)
	{
		operation = a.operation;
		set_priorty();
		return *this;
	}
};
bool IsOperand(const char& opd)
{
	const string alphabet = "abcdefghijklmnopqrstuvwxyz";
	const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (alphabet.find(opd) != string::npos)
		return true;

	if (ALPHABET.find(opd) != string::npos)
		return true;

	return false;
}
bool IsNumber(const char& opd)
{
	const string numbers = "0123456789";

	if (numbers.find(opd) != string::npos)
		return true;

	return false;
}

int IsOperator(const char& op)
{
	const string operPr1 = "+-";
	const string operPr2 = "*/";

	if (operPr1.find(op) != string::npos)
		return 1;

	if (operPr2.find(op) != string::npos)
		return 2;

	return 0;
}

bool TPostfix::Check()
{
	int k = 0;
	int status = 0;
	for (int i = 0; i < infix.size(); i++) {
		if (status == 0) {
			if (IsOperand(infix[i]))
				status = 1;
			else if (IsNumber(infix[i]))
				status = 1;
			else if (infix[i] == '(') {
				status = 0;
				k += 1;
			}
			else if (infix[i] == '\0')
				status = 2;
			else status = 3;
		}
		else if (status == 1) {
			if (infix[i] == '\0')
				status = 2;
			else if (infix[i] == ')') {
				k--;
				if (k >= 0)
					status = 1;
				else
					status = 3;
			}
			else if (IsOperator(infix[i]))
				status = 0;
			else if (IsNumber(infix[i]) & IsNumber(infix[i - 1]))
				status = 1;
			else status = 3;
		}
		else if (status == 2) {
			if (k == 0)
				status = 4;
			else
				status = 3;
		}
	}

	if (status == 4)
		return true;

	else if (status == 1) {
		if (k == 0)
			return true;
		else
			return false;
	}
	else return false;
}

void TPostfix::ToPostfix() {
	Stack<Operation> operators;
	string elem;
	if (Check() != 1)
		throw 777;
	for (int i = 0; i < infix.size(); i++) {
		if (IsOperand(infix[i]))
		{
			string s = "";
			s = infix[i];
			postfix.push_back(s);
			continue;
		}
		else if (IsNumber(infix[i]))
		{
			string s = "";
			while (IsNumber(infix[i])) {
				s += infix[i];
				i++;
			}
			postfix.push_back(s);
			i--;
			continue;
		}
		else
		{
			elem = infix[i];
			Operation operation(elem);

			if (operation.operation == "(")
				operators.Push(operation);
			else if (operation.operation == ")")
			{
				while (operators.top().operation != "(")
				{
					elem = "";
					elem += operators.pop().operation;
					postfix.push_back(elem);
				}
				operators.pop();
			}
			else if (operators.empty() || operators.top().priority < operation.priority)
				operators.Push(operation);
			else
			{
				while (!operators.empty() && operators.top().priority >= operation.priority)
				{
					elem = "";
					elem += operators.pop().operation;
					postfix.push_back(elem);
				}
				if (operators.empty() || operators.top().priority < operation.priority || operation.operation == "(")
					operators.Push(operation);
			}
		}
	}

	while (!operators.empty())
	{
		elem = operators.pop().operation;
		postfix.push_back(elem);
	}
}

int string_to_int(string s)
{
	int res = 0, a;
	for (int i = s.size() - 1; i >= 0; i--)
	{
		a = s[i] - 48;
		for (int j = 0; j < s.size() - i - 1; j++)
		{
			a *= 10;
		}
		res += a;
	}
	return res;
}
double TPostfix::Calculate()
{
	Stack<double> operands;
	double res = 0;
	double Resault = 0;
	for (int i = 0; i < postfix.size(); i++) {
		if (postfix[i] == "+") {
			int op = operands.pop();
			Resault = operands.pop() + op;
			operands.Push(Resault);
		}
		else if (postfix[i] == "-") {
			int op = operands.pop();
			Resault = operands.pop() - op;
			operands.Push(Resault);
		}
		else if (postfix[i] == "*") {
			int op = operands.pop();
			Resault = operands.pop() * op;
			operands.Push(Resault);
		}
		else if (postfix[i] == "/") {
			int op = operands.pop();
			Resault = operands.pop() / op;
			operands.Push(Resault);
		}
		else {
			operands.Push(string_to_int(postfix[i]));
		}
	}
	return operands.top();
};
#endif