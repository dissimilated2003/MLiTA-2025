/*
	ВОЛИК АНДРЕЙ ОЛЕГОВИЧ ПС-23

	4.4. Забор (6)

		Фермер Питер огородил пастбище забором, состоящим из N досок. Забор имеет форму замкнутой ломаной. 
	Некоторые из этих досок покрашены в белый цвет, а некоторые – нет. Фермер решил покрасить весь забор 
	в белый цвет. 
		Он обратился в компанию, и ему предложили сделать заказ. Каждый заказ формируется из 
	множества предложений компании. Каждое предложение характеризуется количеством окрашиваемых 
	досок Ai и стоимостью Ci, и заключается в том, что за сумму Ci сотрудники компании покрасят 
	любые Ai идущих подряд досок.
		В процессе выполнения заказа разрешается доску красить сколько угодно раз, при этом уже 
	окрашенные доски заново красить не требуется (хотя разрешается), а еще не окрашенные доски надо 
	обязательно покрасить. Написать программу, с помощью которой можно определить, какую минимальную 
	сумму Питер заплатит компании за то, что весь забор будет покрашен в белый цвет.

	Ввод:
	N M				1 ≤ N ≤ 1000,	1 ≤ M ≤ 40
	<+, 0>N			замкнутая N-последовательность из символов + или 0
	<Ai, Ci \n>M	M строк с предложениями Ai окрашиваемых досок стоимостью Ci
					1 < Ai < N
					1 < Ci < 10^6

	Источник: --
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <climits>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iterator>

struct Offer
{
	int ai{};
	int ci{};
};

struct Zabor
{
	int n{};
	int m{};
	std::string zabor{};
	std::vector<Offer> offers{};
};

int ReadInput(std::ifstream& input, Zabor& zabor)
{
	input >> zabor.n >> zabor.m;
	if (zabor.n > 1000 || zabor.m > 40)
	{
		std::cerr << "Out of borderline" << "\n";
		return -1;
	}

	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(input, zabor.zabor);

	std::set<char> validZabor = { '0', '+' };
	for (const auto& doska : zabor.zabor) 
	{
		if (validZabor.find(doska) == validZabor.end())
		{
			std::cerr << "Invalid zabor element" << "\n";
			return -1;
		}
	}

	if (zabor.m <= 0)
	{
		std::cerr << "Invalid number of offers: " << zabor.m << "\n";
		return -1;
	}

	zabor.offers.resize(zabor.m);
	for (int i = 0; i < zabor.m; ++i)
	{
		input >> zabor.offers[i].ai >> zabor.offers[i].ci;
	}

	return 0;
}

void ViewZabor(const Zabor& zabor)
{
	std::cout << "Input: " << "\n";
	std::cout << zabor.n << " " << zabor.m << "\n";
	std::cout << zabor.zabor << "\n";
	for (int i = 0; i < zabor.m; ++i)
	{
		std::cout << zabor.offers[i].ai << " " << zabor.offers[i].ci << "\n";
	}
	std::cout << "\n";
}

long long PokrasilZabor(const Zabor& zabor)
{
	std::vector<int> zeros;
	for (int i = 0; i < zabor.n; ++i)
	{
		if (zabor.zabor[i] == '0')
		{
			zeros.push_back(i + 1);
		}
	}
	if (zeros.empty())
	{
		return 0;
	}

	long long min_total = LLONG_MAX;
	int k = zeros.size();

	for (int start_idx = 0; start_idx < k; ++start_idx)
	{
		std::vector<int> linear_zero;
		int offset = zeros[start_idx] - 1;
		for (int i = 0; i < k; ++i)
		{
			int pos = zeros[(start_idx + i) % k];
			pos -= offset;
			if (pos <= 0)
			{
				pos += zabor.n;
			}
			linear_zero.push_back(pos);
		}

		std::sort(linear_zero.begin(), linear_zero.end());

		int m = linear_zero.size();
		std::vector<long long> dp(m + 1, LLONG_MAX);
		dp[0] = 0;

		for (int i = 1; i <= m; ++i)
		{
			int x_i = linear_zero[i - 1];
			for (const auto& offer : zabor.offers)
			{
				int ai = offer.ai;
				long long ci = offer.ci;
				if (ai == 0) continue;

				int s = x_i - ai + 1;
				if (s < 1)
				{
					s = 1;
				}
				auto it = std::lower_bound(linear_zero.begin(), linear_zero.end(), s);
				int j = std::distance(linear_zero.begin(), it);
				if (j < i)
				{
					if (dp[j] != LLONG_MAX)
					{
						if (dp[i] > dp[j] + ci)
						{
							dp[i] = dp[j] + ci;
						}
					}
				}
			}
		}

		if (dp[m] < min_total)
		{
			min_total = dp[m];
		}
	}

	return min_total;
}

int main()
{
	Zabor zabor{};
	std::ifstream input{ "input.txt" };
	if (!input)
	{
		std::cerr << "Failed to open input file" << "\n";
		return -1;
	}

	if (ReadInput(input, zabor) != 0)
	{
		return -1;
	}

	ViewZabor(zabor);

	long long minCost = PokrasilZabor(zabor);
	std::cout << minCost << "\n";
	std::ofstream output{ "output.txt" };
	output << minCost << "\n";

	return 0;
}