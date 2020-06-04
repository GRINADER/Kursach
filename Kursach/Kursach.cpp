#include <iostream>
#include "Sergey.h"

using namespace std;

int main()
{
	Network test;
	test.read();
	test.print();
	int maxWeight;
	cout << "S = 5, T = 3:" << endl;
	maxWeight = test.Algorhytm("5", "3");
	cout << "Max weight: " << maxWeight << endl;
	cout << "S = 8, T = 9:" << endl;
	maxWeight = test.Algorhytm("8", "9");
	cout << "Max weight: " << maxWeight << endl;
	cout << "S = 8, T = 4:" << endl;
	maxWeight = test.Algorhytm("8", "4");
	cout << "Max weight: " << maxWeight << endl;
	cout << "S = 5, T = 1:" << endl;
	maxWeight = test.Algorhytm("5", "1");
	cout << "Max weight: " << maxWeight << endl;
	cout << "S = 3, T = 1:" << endl;
	maxWeight = test.Algorhytm("3", "1");
	cout << "Max weight: " << maxWeight << endl;
	cout << "S = 7, T = 4:" << endl;
	maxWeight = test.Algorhytm("7", "4");
	cout << "Max weight: " << maxWeight << endl;
	cout << "S = 2, T = 8:" << endl;
	maxWeight = test.Algorhytm("2", "8");
	cout << "Max weight: " << maxWeight << endl;
}