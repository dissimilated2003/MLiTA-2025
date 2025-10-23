/*
	ВОЛИК АНДРЕЙ ОЛЕГОВИЧ ПС-23

	12.1. Полеты со скидкой (7)

		Самолеты авиакомпании "Себе в убыток" летают в N городов (2 <= N <= 100) и обслуживают M рейсов.
	Города пронумерованы от 1 до N. Каждый рейс связывает два разных города. Между парой городов может быть не 
	более чем по одному рейсу в каждом направлении. Билет на каждый рейс имеет определенную стоимость. Компания 
	продает единый билет на некоторый маршрут, предусматривающий пересадки с одного рейса на другой. В этом случае 
	если маршрут имеет не менее K пересадок (1 <= K < N), то после K-й пересадки стоимость на каждый рейс маршрута 
	снижается вдвое. Маршрут может иметь повторяющиеся города и рейсы.

		Требуется рассчитать минимальную стоимость перелета из столицы, имеющей номер 1, в другие города. 

		* Ввод из файла INPUT.TXT. Первая строка содержит целые положительные числа N, M и K через пробел. 
	Далее следуют M строк описания рейсов по три целых положительных числа A, B и C в строке 
	(1 <= A, B <= N, 2 <= C <= 10000). Первые два числа задают номера городов, а третье – стоимость перелета.
	Известно, что стоимость каждого рейса выражается четным числом.

		* Вывод в файл OUTPUT.TXT. В i-й строке выводятся минимальная стоимость перелета от 
	столицы до i+1-го города. Если нет ни одного пути, в соответствующей строке выводится 0. Таким образом, 
	файл OUTPUT.TXT состоит из N-1 строки. 
	
	Пример
	Ввод:
		3 3 2		N - количество городов	(от 2 до 100)
		1 2 4		M - количество рейсов	(?)
		2 1 4		K - пересадки			(от 1 до N - 1)
		2 3 20
	Вывод:
		4
		20

		* Пояснение. Для полета в город 3 выгоднее всего слетать в город 2 и вернуться в столицу. Следующий повторный 
	перелет в город 2 происходит после двух пересадок и обходится вдвое дешевле, как и последний перелет в город 3.

	Источник: --
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

struct Edge 
{
    int from{};
    int to{};
    int cost{};
};

int main()
{
    std::ifstream input{ "input.txt" };
    std::ofstream output{ "output.txt" };
    int N{}, M{}, K{};

    input >> N >> M >> K;
    std::vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) 
    {
        input >> edges[i].from >> edges[i].to >> edges[i].cost;
    }

    std::vector<std::vector<int>> BellmanFord(N + 1, std::vector<int>(2 * N, INT_MAX / 2));
    BellmanFord[1][0] = 0;
    for (int j = 0; j < 2 * N - 1; ++j) 
    {
        for (const Edge& edge : edges) 
        {
            if (BellmanFord[edge.from][j] != INT_MAX / 2) 
            {
                int newCost;
                if (j < K) 
                {
                    newCost = BellmanFord[edge.from][j] + edge.cost;
                }
                else 
                {
                    newCost = BellmanFord[edge.from][j] + edge.cost / 2;
                }

                if (newCost < BellmanFord[edge.to][j + 1]) 
                {
                    BellmanFord[edge.to][j + 1] = newCost;
                }
            }
        }
    }

    for (int vertex = 2; vertex <= N; ++vertex) 
    {
        int minDist = *std::min_element(BellmanFord[vertex].begin(), BellmanFord[vertex].end());
        output << (minDist == INT_MAX / 2 ? 0 : minDist) << "\n";
        std::cout << (minDist == INT_MAX / 2 ? 0 : minDist) << "\n";
    }

    return 0;
}