/*
    ВОЛИК АНДРЕЙ ОЛЕГОВИЧ ПС-23

    3.6. Бальные танцы (5)
        В школу бальных танцев записались N учеников — мальчиков и девочек. 
    Профессор построил их в один ряд, и хочет отобрать из них для первого 
    занятия группу стоящих подряд учеников, в которой количество мальчиков          <пример>
    и девочек одинаково. Сколько вариантов выбора есть у профессора?
    Решить задачу с помощью рекуррентных соотношений.                             ^ input.txt:
        Ввод. В первой строке входного файла задано число N (1 ≤ N ≤ 10^6).         8
    Во второй строке задается описание построенного ряда из мальчиков               abbababa
    и девочек — строка из N символов a и b (символ "a" соответствует девочке,     ^ output.txt:
    а символ "b" — мальчику).                                                       13
        Вывод. В единственной строке выходного файла должно содержаться 
    количество вариантов выбора требуемой группы.

    Источник: https://www.cyberforum.ru/python-beginners/thread2653363.html
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

int ReadAndCheckInput(uint64_t& n, std::string& expression) 
{
    std::ifstream input{ "input.txt" };

    if (!input.is_open())
    {
        std::cerr << "Failed to open file\n";
        return -1;
    }

    input >> n >> expression;
    std::cout << n << "\n" << expression << "\n\n";
    if (n != expression.length()) 
    {
        std::cerr << "Not compatible N & length of expression <ab..>\n";
        return -1;
    }

    return 0;
}

bool IsValidExpression(uint64_t n, std::string expression)
{
    for (char iter : expression) 
    {
        if (iter != 'a' && iter != 'b')
        {
            std::cerr << "Only 'a' or 'b' allowed\n";
            return false;
        }
    }
    return true;
}

uint64_t JustDance(uint64_t n, const std::string& expression) 
{
    std::vector<uint64_t> arr(2 * n + 1, 0);
    arr[n] = 1;
    
    uint64_t prefixSum{ n };
    for (char iter : expression) 
    {
        prefixSum += (iter == 'a' ? 1 : -1);
        arr[prefixSum]++;
    }

    uint64_t result{ 0 };
    for (uint64_t iter : arr) 
    {
        result += iter * (iter - 1) / 2;
    }
    
    std::cout << result << "\n";
    return result;
}

int main() 
{
    uint64_t n{};
    std::string expression{};

    ReadAndCheckInput(n, expression);
    if (!IsValidExpression(n, expression)) 
    {
        return -1;
    } 

    uint64_t combos = JustDance(n, expression);
    std::ofstream outputFile{ "output.txt" };
    outputFile << combos << "\n";
    outputFile.close();

    return 0;

}
