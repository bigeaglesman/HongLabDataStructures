#include <iostream>

#include "../shared/Stack.h"

using namespace std;

constexpr int kNumRows = 10;
constexpr int kNumCols = 9;

char maze[kNumRows][kNumCols] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', 'S', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '0', '1', '0', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1'},
	{'1', '1', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', 'G', '1'}, // <- 'G'를 만나면 종료
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

void PrintMaze()
{
	for (int j = 0; j < kNumRows; j++)
	{
		for (int i = 0; i < kNumCols; i++)
			cout << maze[j][i] << " ";
		cout << endl;
	}
}

struct Pos
{
	int row;
	int col;

	// 디버깅을 위한 편의 기능
	friend ostream& operator<<(ostream& os, const Pos& pos)
	{
		cout << "(" << pos.row << ", " << pos.col << ")" << flush;
		return os;
	}
};

int RecurMaze(Pos p) 
{
	const char mark = maze[p.row][p.col];

	if (mark == 'G')
	{
		cout << "Found!" << endl;
		return 1;
	}

	if (mark != 'X' && mark != '1')
	{
		maze[p.row][p.col] = 'X';

		if (RecurMaze({p.row + 1, p.col})) return 1;		// 1을 반환받으면 재귀적으로 함수 종료시키고 밑의 재귀함수는 실행시키지 않음
		if (RecurMaze({p.row , p.col + 1})) return 1;
		if (RecurMaze({p.row - 1, p.col})) return 1;
		if (RecurMaze({p.row , p.col - 1})) return 1;
	}
	return (0);
}

void StackMaze()
{
	Stack<Pos> s;

	Pos start = { 1, 1 }; // i = 1, j = 1  시작 지점
	// Pos start;
	// start.row = 1;
	// start.col = 1;

	s.Push(start); // s.Push({1, 1});

	// s.Print(); // 디버깅에 사용 가능

	while (!s.IsEmpty())
	{
		Pos p = s.Top();
		s.Pop();

		cout << p << " "; // 디버깅 출력

		const char mark = maze[p.row][p.col];

		if (mark == 'G')
		{
			cout << "Found!" << endl;
			break;
		}
		if (mark != '1' && mark != 'X')
		{
			maze[p.row][p.col] = 'X';

			s.Push({p.row+1, p.col}); //	스택에 정확한 경로를 쌓는게 아니라 일단 4방향 모두 쌓아놓고 스택의 탑부터 검사한다 
			s.Push({p.row, p.col+1}); //	탑을 팝해서 검사했는데 접근이 불가능하면 다음 탑을 팝한다
			s.Push({p.row-1, p.col}); //	접근이 가능하면 다시 4방향 푸쉬한다
			s.Push({p.row, p.col-1});
		}
	}
}

int main()
{
	PrintMaze();

	//RecurMaze({ 1, 1 });

	StackMaze();

	PrintMaze();

	return 0;
}

