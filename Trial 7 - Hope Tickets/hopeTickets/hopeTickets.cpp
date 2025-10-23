/*
	ВОЛИК АНДРЕЙ ОЛЕГОВИЧ ПС-23
	
	6.1. Счастливые билеты (8). 

		Номера автобусных билетов состоят из 2N цифр, включая незначащие нули (1 <= N <= 500). 
	Минимальный возможный номер состоит из 2N нулей, а максимальный – из 2N девяток. Студент Вася 
	ездит в университет на автобусе и коллекционирует счастливые билеты, в которых сумма 
	первых N цифр совпадает с суммой последних N цифр. Как и всякий настоящий коллекционер, 
	Вася готов пойти на все для пополнения своей коллекции. Вместе с тем ему пока приходится 
	учитывать свои финансовые возможности.
		Каждый раз после приобретения билета Вася определяет, какое минимальное количество 
	билетов нужно купить еще, чтобы среди них обязательно оказался счастливый билет. Если у него 
	оказывается достаточно денег, он тут же покупает необходимое число билетов. Иногда он не 
	успевает закончить расчеты, проезжает свою остановку и опаздывает на занятия. Помогите Васе.

	Примеры:	^ input1.txt:		^ input2.txt:		^ input3.txt:
				  2					  2					  2
				  3817				  0839				  0000
				^ output1.txt:		^ output2.txt:		^ output3.txt:
				  12				  5					  0

	Источник: --
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

void ReadInput(std::istream& input, int& n, std::string& ticket) 
{
    input >> n >> ticket;
}

int CalcDigitSum(const std::string& s, int start, int end) 
{
    int sum = 0;
    for (int i = start; i < end; ++i) sum += s[i] - '0';
    return sum;
}

std::string HandleLGreaterR(const std::string& ticket, int N) // L > R
{
    int sumL = CalcDigitSum(ticket, 0, N);
    int sumR = CalcDigitSum(ticket, N, 2 * N);
    std::string buffer = ticket;
    size_t i = ticket.size() - 1;
    for (; i >= N; --i)
    {
        int diff = '9' - buffer[i];
        buffer[i] = '9';
        sumR += diff;
        if (sumL <= sumR) break;
    }
    
    buffer[i] -= static_cast<char>(sumR - sumL);
    return buffer;
}

std::string HandleLLessR(const std::string& ticket, int N) // L < R
{
    int sumL = CalcDigitSum(ticket, 0, N);
    int sumR = CalcDigitSum(ticket, N, 2 * N);
    std::string buffer = ticket;
    size_t i = ticket.size() - 1;
    while (i >= N)
    {
        int diff = buffer[i] - '0';
        if (diff == 0) continue;
        buffer[i] = '0';
        sumR -= diff;
        --i;

        for (; i >= 1; --i)
        {
            if (buffer[i] != '9') break;
            if (i >= N) sumR -= 9;
            buffer[i] = '0';
        }

        buffer[i] += 1;
        if (i >= N) sumR += 1;
        if (sumL >= sumR) break;
    }

    sumL = CalcDigitSum(buffer, 0, N);
    if (sumL == sumR) return buffer;
    return HandleLGreaterR(buffer, N);
}

std::string Subtract(const std::string& a, const std::string& b) 
{
    std::string res{};
    int borrow = 0;
    size_t n = std::max(a.size(), b.size());
    for (size_t i = 0; i < n; ++i) 
    {
        int digit_a = (i < a.size()) ? a[a.size() - 1 - i] - '0' : 0;
        int digit_b = (i < b.size()) ? b[b.size() - 1 - i] - '0' : 0;
        int diff = digit_a - digit_b - borrow;
        borrow = diff < 0 ? 1 : 0;
        res.push_back((diff + 10) % 10 + '0');
    }

    while (res.size() > 1 && res.back() == '0') res.pop_back();
    std::reverse(res.begin(), res.end());
    return res.empty() ? "0" : res;
}

int main() 
{
    std::ifstream input("input.txt");
    int N{};
    std::string ticket{};
    ReadInput(input, N, ticket);
    int sumL = CalcDigitSum(ticket, 0, N);
    int sumR = CalcDigitSum(ticket, N, 2 * N);

    std::cout << "ticket: \t" << ticket << "\n\n";
    std::string lucky{};
    std::string result{};
    if (sumL > sumR) lucky = HandleLGreaterR(ticket, N);
    if (sumL < sumR) lucky = HandleLLessR(ticket, N);
    if (sumL == sumR)
    {
        lucky = ticket;
        result = "0";
    }
    
    std::ofstream output{ "output.txt" };
    result = Subtract(lucky, ticket);
    std::cout << "near lucky: \t" << lucky << "\n\n";
    std::cout << "answ:     \t" << result << "\n";
    output << result << "\n";
    return 0;
}