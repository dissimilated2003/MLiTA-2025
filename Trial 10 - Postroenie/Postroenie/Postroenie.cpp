/*
    ВОЛИК АНДРЕЙ ОЛЕГОВИЧ ПС-23

    17.3. Построение (7)

        В одной военной части построили солдат в одну колонну по убыванию роста. Часть была далеко 
    не образцовая. Солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из строя 
    за плохо начищенные берцы. Однако солдаты в процессе прихода и ухода всегда должны быть выстроены 
    по росту. 
        Требуется для каждого приходящего солдата указывать, перед каким солдатом в строю он 
    должен становиться. Если пришедший солдат одинакового роста с некоторыми солдатами в строю, 
    то он становится сразу после них.
        Ввод из файла INPUT.TXT. Первая строка содержит количество команд N (1 <=  N <= 200000). 
    В каждой следующей строке содержится описание команды: числа 1 и X, если солдат приходит в строй 
    (X – рост солдата от 1 до 100000) и числа 2 и Y, если солдата, стоящего в строю на месте Y 
    надо удалить из строя. Солдаты в строю нумеруются с 1.
        Вывод в файл OUTPUT.TXT. На каждую команду 1 (добавление в строй) нужно выводить в отдельной 
    строке число K – номер позиции, на которую должен встать этот солдат (все стоящие за ним двигаются назад).

    Пример:

    Ввод:
        5
        1 100
        1 200
        1 50
        2 1
        1 150
    Вывод:
        1
        1
        3
        1

    Источник: --
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

const int MAX_HEIGHT = 100000;
int fenwick[MAX_HEIGHT + 2];

void Update(int idx, int delta, int size) 
{
    while (idx <= size) 
    {
        fenwick[idx] += delta;
        idx += idx & -idx;
    }
}

int Query(int idx) 
{
    int res = 0;
    while (idx > 0) 
    {
        res += fenwick[idx];
        idx -= idx & -idx;
    }

    return res;
}

int main()
{
    std::ifstream input{ "input.txt" };
    std::ofstream output{ "output.txt" };
    int N{};

    input >> N;
    std::vector<std::pair<int, int>> commands(N);
    std::vector<int> heights{};
    for (int i = 0; i < N; ++i) 
    {
        int type{}, val{};
        input >> type >> val;
        commands[i] = { type, val };
        if (type == 1) heights.push_back(val);
    }
    
    std::sort(heights.begin(), heights.end(), std::greater<int>());
    heights.erase(std::unique(heights.begin(), heights.end()), heights.end());
    std::vector<int> compressed(MAX_HEIGHT + 1, 0);
    for (int i = 0; i < heights.size(); ++i) compressed[heights[i]] = i + 1;

    for (const auto& cmd : commands) 
    {
        int commandType = cmd.first;
        int val = cmd.second;
        if (commandType == 1) 
        {
            int pos = compressed[val];
            int k = Query(pos);
            output << (k + 1) << "\n";
            Update(pos, 1, heights.size());
        }
        else if (commandType == 2) 
        {
            int left = 1, right = heights.size();
            int target_pos = 0;
            while (left <= right) 
            {
                int mid = (left + right) / 2;
                int sum = Query(mid);
                if (sum >= val) 
                {
                    target_pos = mid;
                    right = mid - 1;
                }
                else left = mid + 1;
            }

            if (target_pos > 0) Update(target_pos, -1, heights.size());
        }
    }

    std::cout << "answer taken into output.txt" << "\n";
    return 0;
}