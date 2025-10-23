/*
    ВОЛИК АНДРЕЙ ОЛЕГОВИЧ ПС-23

    18.2. Магические квадраты (11)

        Вася учится в первом классе школы магов. Однажды Главный Магистр рассказал о магических квадратах. 
    Такой квадрат порядка N состоит из N строк по N целых чисел в строке и должен иметь одинаковую сумму чисел 
    в строках, столбцах и на длинных диагоналях. Вася попросил показать, как строятся такие квадраты.
        Главный Магистр сказал, что это будет проходиться в следующей четверти, а пока стоит научиться строить 
    полумагические квадраты. В них одинаковая сумма чисел S должна быть в строках и столбцах, но на диагоналях 
    сумму S получать не обязательно. Вася много раз заполнял квадрат начальными числами, но дальше часто что-то 
    не клеилось. Нужно срочно ему помочь.

        Ввод. В первой строке содержатся числа N и S, разделенные пробелом (1 <= N <= 1000, 1 <= S <= 10^6). В следующих
    N строках задаются значения матрицы a[i, j] по N целых чисел в строке через пробел (0 <= a[i, j] <= 1000), причем 0 
    обозначает пустую клетку. Требуется заполнить пустые клетки целыми числами так, чтобы сумма чисел в каждой 
    строке и в каждом столбце оказалась равной S.

        Вывод. В N строках по N чисел в строке через пробел выводятся элементы построенного квадрата b[i, j] 
    (-10^9 <= b[i, j] <= 10^9). В клетках могут содержаться как положительные значения, так и отрицательные, либо 
    нулевые. Если ответов больше одного, вывести любой из них. Если решения нет, вывести No.
       
        Примеры:

        Ввод 1     Ввод 2     Ввод 3     Ввод 4
        3 50       3 85       2 21       2 5
        34 9 7     0 0 43     0 9        0 0
        0 0 20     25 0 0     6 0        0 0
        0 0 23     0 5 18

        Вывод 1    Вывод 2    Вывод 3    Вывод 4
        34 9 7     -2 44 43   No         5 0
        15 15 20   25 36 24              0 5
        1 26 23    62 5 18

    Подсказка. Заполнять на каждом шаге строку либо столбец с максимальным количеством пустых клеток. Информацию 
    о количестве пустых клеток в строках и столбцах хранить в бинарной куче.

    Источник: --
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>

int main() 
{
    std::ifstream input{ "input36.txt" };
    std::ofstream output{ "output.txt" };
    int n{}, s{};
    input >> n >> s;

    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    std::vector<int> sumNumbersRow(n, 0);
    std::vector<int> sumNumbersColumn(n, 0);
    std::vector<int> countZerosRow(n, 0);
    std::vector<int> countZerosColumn(n, 0);

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            input >> a[i][j];
            sumNumbersRow[i] += a[i][j];
            if (a[i][j] == 0) countZerosRow[i]++;
        }
    }

    for (int j = 0; j < n; ++j) 
    {
        for (int i = 0; i < n; ++i) 
        {
            sumNumbersColumn[j] += a[i][j];
            if (a[i][j] == 0) countZerosColumn[j]++;
        }
    }

    std::priority_queue<std::tuple<int, char, int>> maxHeap{};
    for (int i = 0; i < n; ++i) maxHeap.push(std::make_tuple(-countZerosRow[i], 'R', i));
    for (int j = 0; j < n; ++j) maxHeap.push(std::make_tuple(-countZerosColumn[j], 'C', j));

    bool possibleToBuild = true;
    while (!maxHeap.empty()) 
    {
        auto current = maxHeap.top();
        maxHeap.pop();

        int zerosCount = -std::get<0>(current);
        char type = std::get<1>(current);
        int idx = std::get<2>(current);
        int currentZerosCount{};

        if (type == 'R') 
        {
            currentZerosCount = countZerosRow[idx];
        }
        else 
        {
            currentZerosCount = countZerosColumn[idx];
        }

        if (currentZerosCount != zerosCount) continue;
        if (currentZerosCount == 0) 
        {
            int currentSumNums = (type == 'R') ? sumNumbersRow[idx] : sumNumbersColumn[idx];
            if (currentSumNums != s) 
            {
                possibleToBuild = false;
                break;
            }
        }
        else 
        {
            if (type == 'R') 
            {
                int remainingZeros = countZerosRow[idx];
                for (int j = 0; j < n && remainingZeros > 0; ++j) 
                {
                    if (a[idx][j] == 0) 
                    {
                        if (remainingZeros > 1) 
                        {
                            a[idx][j] = 1;
                            sumNumbersRow[idx] += 1;
                            sumNumbersColumn[j] += 1;
                            countZerosRow[idx]--;
                            countZerosColumn[j]--;
                            remainingZeros--;

                            maxHeap.push(std::make_tuple(-countZerosRow[idx], 'R', idx));
                            maxHeap.push(std::make_tuple(-countZerosColumn[j], 'C', j));
                        }
                        else 
                        {
                            int val = s - sumNumbersRow[idx];
                            a[idx][j] = val;
                            sumNumbersRow[idx] += val;
                            sumNumbersColumn[j] += val;
                            countZerosRow[idx]--;
                            countZerosColumn[j]--;
                            remainingZeros--;

                            maxHeap.push(std::make_tuple(-countZerosRow[idx], 'R', idx));
                            maxHeap.push(std::make_tuple(-countZerosColumn[j], 'C', j));
                        }
                    }
                }
            }
            else 
            {
                int remainingZeros = countZerosColumn[idx];
                for (int i = 0; i < n && remainingZeros > 0; ++i) 
                {
                    if (a[i][idx] == 0) 
                    {
                        if (remainingZeros > 1) 
                        {
                            a[i][idx] = 1;
                            sumNumbersColumn[idx] += 1;
                            sumNumbersRow[i] += 1;
                            countZerosColumn[idx]--;
                            countZerosRow[i]--;
                            remainingZeros--;

                            maxHeap.push(std::make_tuple(-countZerosColumn[idx], 'C', idx));
                            maxHeap.push(std::make_tuple(-countZerosRow[i], 'R', i));
                        }
                        else 
                        {
                            int val = s - sumNumbersColumn[idx];
                            a[i][idx] = val;
                            sumNumbersColumn[idx] += val;
                            sumNumbersRow[i] += val;
                            countZerosColumn[idx]--;
                            countZerosRow[i]--;
                            remainingZeros--;

                            maxHeap.push(std::make_tuple(-countZerosColumn[idx], 'C', idx));
                            maxHeap.push(std::make_tuple(-countZerosRow[i], 'R', i));
                        }
                    }
                }
            }
        }
    }

    if (possibleToBuild) 
    {
        for (int i = 0; i < n; ++i) 
        {
            if (sumNumbersRow[i] != s) 
            {
                possibleToBuild = false;
                break;
            }
        }

        for (int j = 0; j < n; ++j) 
        {
            if (sumNumbersColumn[j] != s) 
            {
                possibleToBuild = false;
                break;
            }
        }
    }

    if (!possibleToBuild) 
    {
        output << "No" << "\n";
        std::cout << "No" << "\n";
    }
    else 
    {
        for (int i = 0; i < n; ++i) 
        {
            for (int j = 0; j < n; ++j) 
            {
                output << a[i][j];
                //std::cout << a[i][j];
                if (j != n - 1) 
                {
                    output << " ";
                    //std::cout << " ";
                }
            }

            output << "\n";
            //std::cout << "\n";
        }
    }

    return 0;
}