/*
    ВОЛИК АНДРЕЙ ОЛЕГОВИЧ ПС-23

    10.5. Последовательность 3 (5)

        Задана неубывающая последовательность целых чисел. Найти количество пар
    чисел с заданной разностью D.
        Ввод из файла INPUT.TXT. В первой строке задаются через пробел
    два целых числа: количество членов последовательности N и разность D
    (2 ≤ N ≤ 10^6, 1 ≤ D ≤ 10^9). Во второй строке вводятся через пробел N натуральных
    чисел последовательности A1 ≤ A2 ≤ ... ≤ AN  (Ai ≤ 10^9).
        Вывод в файл OUTPUT.TXT. Вывести число пар (Ai, Aj) таких, что Ai – Aj = D.
    Ограничения: Объем используемой памяти до 1 Мб.

    Пример 1:                           Пример 2:                       Пример 3:
    input.txt:                          input.txt:                      input.txt:
        10 7                                10 4                            5 4
        3 5 12 18 25 40 47 47 48 49         4 5 7 8 8 8 12 12 17 21         8 8 8 12 12
    output.txt:                         output.txt:                     output.txt:
        4                                   10                              6

    Источник: --
*/

#include <cstddef>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <new>
#include <atomic>
#include <cstdint>

std::atomic<uint64_t> kBytesAllocated{ 0 };

void* operator new(std::size_t count) noexcept
{
    kBytesAllocated.fetch_add(count);
    return std::malloc(count);
}

void operator delete(void* ptr)
{
    std::free(ptr);
}

int CalculatePairsWithDifference(std::ifstream& input, std::ifstream& input2, int n, long long d) 
{
    int pairCount = 0;
    long long a, b;

    if (!(input >> a)) return 0;
    if (!(input2 >> b)) return 0;

    while (true) 
    {
        long long diff = a - b;

        if (diff < d) 
        {
            if (!(input >> a)) break;
        }
        else if (diff > d) 
        {
            if (!(input2 >> b)) break;
        }
        else 
        {
            const long long current_a = a;
            const long long current_b = b;
            int count_a = 0;
            int count_b = 0;

            do 
            {
                count_a++;
                if (!(input >> a)) break;
            } 
            while (a == current_a);

            do 
            {
                count_b++;
                if (!(input2 >> b)) break;
            } 
            while (b == current_b);

            pairCount += count_a * count_b;
            if (!input || !input2) break;
        }
    }

    return pairCount;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    const auto fileName = "INPUT10.TXT";
    std::ifstream input{ fileName };
    int n{}, diff{};
    input >> n >> diff;
    std::cout << "N = " << n << ", D = " << diff << "\n";

    std::ifstream input2{ fileName };
    int buff{};
    input2 >> buff >> buff;
    int result = CalculatePairsWithDifference(input, input2, n, diff);

    std::ofstream output("output.txt");
    output << result << "\n";
    std::cout << "\n" << result << "\n\n";

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    double elapsed_seconds = elapsed.count() / 1000.0;
    std::cout << std::fixed << std::setprecision(3) << elapsed_seconds << " sec." << "\n";

    float bytesAllocated = static_cast<float>(kBytesAllocated);
    float kbAllocated = bytesAllocated / 1024.0f;
    float mBytesAllocated = kbAllocated / 1024.0f;
    std::cout << "Bytes allocated on heap: " << bytesAllocated << "\n";
    std::cout << "Kilobytes: " << kbAllocated << "\n";
    std::cout << "Megabytes: " << mBytesAllocated << "\n";
    return 0;

}

