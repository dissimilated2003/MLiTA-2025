/*
    ВОЛИК АНДРЕЙ ОЛЕГОВИЧ ПС-23

    19.3. Длинная разность (4)

        Заданы два целых положительных числа. Требуется найти их разность. Запрещается 
    использование библиотек длинной арифметики.
        Ввод: В первых двух строках содержатся два целых числа M и N (1 <= [N < M] <= 10^200).
        Вывод: В единственной строке необходимо вывести разность M – N.

        Примеры:
    
        Ввод 1                   Ввод 2
        123456787654321          1000000000000000
        35                       1
        Вывод 1                  Вывод 2
        123456787654286          999999999999999

    Источник: Задача "6.1. Счастливые билеты (8)"
*/

#include <iostream>
#include <fstream>
#include <string>

std::string Subtract(const std::string& a, const std::string& b)
{
    std::string result{};
    int borrow = 0;
    size_t length = std::max(a.size(), b.size());
    for (size_t i = 0; i < length; ++i)
    {
        int digit_A = (i < a.size()) ? a[a.size() - 1 - i] - '0' : 0;
        int digit_B = (i < b.size()) ? b[b.size() - 1 - i] - '0' : 0;
        int difference = digit_A - digit_B - borrow;
        borrow = difference < 0 ? 1 : 0;
        result.push_back((difference + 10) % 10 + '0');
    }

    while (result.size() > 1 && result.back() == '0') result.pop_back();
    std::reverse(result.begin(), result.end());
    return result.empty() ? "0" : result;
}


int main()
{
    std::ifstream input{ "input.txt" };
    std::ofstream output{ "output.txt" };
    std::string str1{};
    std::string str2{};
    
    input >> str1 >> str2;

    std::string result = Subtract(str1, str2);
    std::cout << "input:\n" << str1 << "\n" << str2 << "\n\n";
    std::cout << "result:\n" << result << "\n";

    output << result << "\n";
}