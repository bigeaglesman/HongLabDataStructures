#include <iostream>

#include "../shared/Stack.h"
#include "../shared/Queue.h"

using namespace std;

int Prec(char c); // 연산자 우선순위를 반환
void InfixToPostfix(Queue<char>& q, Queue<char>& output);
int EvalPostfix(Queue<char>& q);

/*
   infix: A/B-C+D*E-A*C
 postfix: AB/C-DE*+AC*-

   infix: 8 / 2 - 3 + 4 * 5 - 1 * 2 = 19
 postfix: 8 2 / 3 - 4 5 * + 1 2 * - // 연산자를 만날때까지 진행
		  = 4 3 - 4 5 * + 1 2 * -
		  = 1 4 5 * + 1 2 * -
		  = 1 20 + 1 2 * -
		  = 21 1 2 * -
		  = 21 2 -
		  = 19
*/

int main()
{
	// 예제에서는 빈칸 없이 한 자리 숫자만 가능

	const char infix[] = "8/2+(3+4)*5-1*2";
	// const char infix[] = "1+(1*2+3)*4";
	//const char infix[] = "1+2*3+3";
	//const char infix[] = "1+2*(3+1)";
	const int size = sizeof(infix) / sizeof(char) - 1;

	// 큐에 모두 넣기
	Queue<char> q;
	for (int i = 0; i < size; i++)
		q.Enqueue(infix[i]);

	Queue<char> postfix;

	cout << "Infix: ";
	q.Print();
	cout << endl;

	InfixToPostfix(q, postfix);

	cout << "Postfix: ";
	postfix.Print();

	cout << "Evaluated = " << EvalPostfix(postfix) << endl;

	return 0;
}

// Function to return precedence of operators
int Prec(char c)
{
	if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1; // '('는 우선순위가 아주 낮은 것으로 처리, ')' 닫는 괄호를 만날때까지 남겨두기 위함
}

void InfixToPostfix(Queue<char>& q, Queue<char>& output)
{
	Stack<char> s; // 우선순위가 낮은 연산을 보류하기 위한 스택

	output.SetDebugFlag(false);

	while (!q.IsEmpty())
	{
		char c = q.Front();
		q.Dequeue();

		cout << c << endl;

		if (c >= '1' && c <= '9')
			output.Enqueue(c);
		else if (Prec(c) == -1)
		{
			if (c == '(')
				s.Push(c);
			else // )이 들어왔을 때
			{
				while (s.Top() != '(')
				{
					output.Enqueue(s.Top());
					s.Pop();
				}
				s.Pop();
			}
		}
		else
		{
			if (s.IsEmpty())
				s.Push(c);
			else if (Prec(c) > Prec(s.Top()))
				s.Push(c);
			else
			{
				while (Prec(c) <= Prec(s.Top()))
				{
					output.Enqueue(s.Top());
					s.Pop();
					if (s.IsEmpty())
						break;
				}
				s.Push(c);
			}
		}
		cout << "Stack: ";
		s.Print();
		cout << "Output:";
		output.Print();
		cout << endl;
	}

	// 스택에 남아있는 것들을 모두 추가
	while (!s.IsEmpty())
	{
		output.Enqueue(s.Top());
		s.Pop();
	}
}

int EvalPostfix(Queue<char>& q)
{
	Stack<int> s;
	int a;
	int b;

	while (!q.IsEmpty())
	{
		char c = q.Front();
		q.Dequeue();

		cout << c << endl;

		if (c >= '0' && c <= '9')
			s.Push(c - '0');
		else
		{
			b = s.Top();
			s.Pop();
			a = s.Top();
			s.Pop();
			if (c == '*')
				s.Push(a * b);
			else if (c == '/')
				s.Push(a/b);
			else if (c == '+')
				s.Push(a+b);
			else if (c == '-')
				s.Push(a-b);
		}

		cout << "Stack: ";
		s.Print();
	}

	return s.Top();
}
