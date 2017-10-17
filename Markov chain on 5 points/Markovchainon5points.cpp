// Markovchainon5points.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <random>
#include <unordered_map>
#include <iomanip>
using namespace std;

size_t* markov(int len, size_t tests)
{
	random_device rd;
	mt19937 mtRand(rd());
	bernoulli_distribution dist(0.5);
	unordered_map<size_t, int> pow2;
	for (int i = 0; i < len; i++)
		pow2[1 << i] = i;
	long long arr = 1 << (len - 1);
	size_t* stats = new size_t[len]();
	for (size_t i = 0; i < tests; i++)
	{
		int pos = pow2[(arr & -arr)];
		stats[pos]++;
		if (pos == 0)
			arr <<= 1;
		else if (pos == len - 1)
			arr >>= 1;
		else
		{
			if (dist(mtRand))
				arr <<= 1;
			else
				arr >>= 1;
		}
	}
	return stats;
}

int main()
{
	ios::sync_with_stdio(false);
	while (1)
	{
		cout << "Input number of points: ";
		int len;
		cin >> len;
		if (len > 64)
		{
			cout << "Too long to simulate.";
			continue;
		}
		cout << "Input number of tests: ";
		size_t test;
		cin >> test;
		size_t* stats = markov(len, test);
		cout << "Occurances are:\n";
		for (int i = 0; i < len; i++)
		{
			if (i)
				cout << ' ';
			cout << stats[i];
		}
		cout << "\nProbabilities are:\n" << fixed << setprecision(3);
		for (int i = 0; i < len; i++)
		{
			if (i)
				cout << ' ';
			cout << (double)stats[i] / test;
		}
		cout << '\n' << endl;
	}
	return 0;
}

