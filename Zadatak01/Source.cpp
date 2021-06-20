#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <thread>
using namespace std;

const int Line = 20;
const int Column = 40;

struct Koordinata {

	int x, y;
};

void Ordering_Player(Koordinata& Player, Koordinata& End, char Grid[Line][Column], char Case) {
	
	if (Case == 'x')
	{
		for (size_t i = 0; i < Line; i++)
		{
			for (size_t j = 0; j < Column; j++)
			{
				if (Player.x == j && Player.y == i)
				{
					cout << 'x';
				}
				else
				{
					cout << Grid[i][j];
				}

			}
			cout << endl;
		}
		if (Player.x < End.x)
		{
			Player.x++;
		}
		else if (Player.x > End.x)
		{
			Player.x--;
		}
	}
	
	else
	{
		for (size_t i = 0; i < Line; i++)
		{
			for (size_t j = 0; j < Column; j++)
			{
				if (Player.x == j && Player.y == i)
				{
					cout << 'x';
				}
				else
				{
					cout << Grid[i][j];
				}
			}
			cout << endl;
		}

		if (Player.y < End.y)
		{
			Player.y++;
		}
		else if (Player.y > End.y)
		{
			Player.y--;
		}
	}
}

int main() {

	int A[2], B[2];
	cout << "Insert A Line: ";
	cin >> A[0];
	cout << "Insert A Column: ";
	cin >> A[1];

	cout << "Insert B Line: ";
	cin >> B[0];
	cout << "Insert B Column: ";
	cin >> B[1];

	char Grid[Line][Column];

	for (int i = 0; i < Line; i++)
	{
		for (int j = 0; j < Column; j++)
		{
			if (A[0] - 1 == i && A[1] - 1 == j)
			{
				Grid[i][j] = 'A';
			}
			else if (B[0] - 1 == i && B[1] - 1 == j)
			{
				Grid[i][j] = 'B';
			}
			else
			{
				Grid[i][j] = '-';
			}
		}
	}

	Koordinata Player;
	Player.x = A[1] - 1;
	Player.y = A[0] - 1;

	Koordinata End;
	End.x = B[1] - 1;
	End.y = B[0] - 1;

	for (size_t i = 0; i < Line; i++)
	{
		for (size_t j = 0; j < Column; j++)
		{
			cout << Grid[i][j];
		}
		cout << endl;
	}

	while (Player.x != End.x)
	{
		this_thread::sleep_for(chrono::milliseconds(100));
		system("cls");
		cout << endl << endl;
		Ordering_Player(Player, End, Grid, 'x');
	}

	while (Player.y != End.y)
	{
		this_thread::sleep_for(chrono::milliseconds(100));
		system("cls");
		cout << endl << endl;
		Ordering_Player(Player, End, Grid, 'y');
	}

	return 0;
}