#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_set_and_get_string)
{
	TPostfix pf;
	string a = "a+a";
	pf.SetInfix(a);
	EXPECT_EQ("a+a", pf.GetInfix());
}

// тесты на нахождение ошибок в выражении

TEST(TPostfix, right_infix1) {
	TPostfix pf;
	string a = "a+a";
	pf.SetInfix(a);
	EXPECT_EQ(pf.Check(), 1);
}

TEST(TPostfix, right_infix2) {
	TPostfix pf;
	string a = "1+2";
	pf.SetInfix(a);
	EXPECT_EQ(pf.Check(), 1);
}

TEST(TPostfix, right_infix3) {
	TPostfix pf;
	string a = "(12+2)*3";
	pf.SetInfix(a);
	EXPECT_EQ(pf.Check(), 1);
}

TEST(TPostfix, right_infix4) {
	TPostfix pf;
	string a = "1.5+1.5";
	pf.SetInfix(a);
	EXPECT_EQ(pf.Check(), 1);
}

TEST(TPostfix, wrong_infix1) {
	TPostfix pf;
	string a = "sdlfslf";
	pf.SetInfix(a);
	EXPECT_EQ(pf.Check(), 0);
}

TEST(TPostfix, wrong_infix2) {
	TPostfix pf;
	string a = "+2+3";
	pf.SetInfix(a);
	EXPECT_EQ(pf.Check(), 0);
}

TEST(TPostfix, wrong_infix3) {
	TPostfix pf;
	string a = "(1+2";
	pf.SetInfix(a);
	EXPECT_EQ(pf.Check(), 0);
}

TEST(TPostfix, wrong_infix4) {
	TPostfix pf;
	string a = "1.23.4";
	pf.SetInfix(a);
	EXPECT_EQ(pf.Check(), 0);
}


// тесты на перевод в польскую запись

TEST(TPostfix, wrong_infix_to_postfix)
{
	TPostfix pf;
	string a = "(1+2";
	ASSERT_ANY_THROW(pf.ToPostfix());
}

TEST(TPostfix, topostfix1) {
	TPostfix pf;
	string a = "1+2";
	pf.SetInfix(a);
	pf.ToPostfix();
	vector<string> b = { "1","2","+" };
	EXPECT_EQ(pf.GetPostfix(), b);
}

TEST(TPostfix, topostfix2) {
	TPostfix pf;
	string a = "(1+2)*3";
	pf.SetInfix(a);
	pf.ToPostfix();
	vector<string> b = { "1","2","+","3","*" };
	EXPECT_EQ(pf.GetPostfix(), b);
}

TEST(TPostfix, topostfix3) {
	TPostfix pf;
	string a = "1.5+1.5";
	pf.SetInfix(a);
	pf.ToPostfix();
	vector<string> b = { "1.5","1.5","+" };
	EXPECT_EQ(pf.GetPostfix(), b);
}

// тесты на подсчёт

TEST(TPostfix, calculate1)
{
	TPostfix pf;
	string a = "1+2";
	pf.SetInfix(a);
	pf.ToPostfix();
	EXPECT_EQ(3, pf.Calculate());
}
TEST(TPostfix, calculate2)
{
	TPostfix pf;
	string a = "1*2+(1+2)";
	pf.SetInfix(a);
	pf.ToPostfix();
	EXPECT_EQ(5, pf.Calculate());
}
TEST(TPostfix, calculate3)
{
	TPostfix pf;
	string a = "1.5+1.5";
	pf.SetInfix(a);
	pf.ToPostfix();
	EXPECT_EQ(3, pf.Calculate());
}

TEST(TPostfix, calculate4)
{
	TPostfix pf;
	string a = "a+b"; // ввдоим так, чтобы сумма была равна 3
	pf.SetInfix(a);
	pf.ToPostfix();
	EXPECT_EQ(3, pf.Calculate());
}