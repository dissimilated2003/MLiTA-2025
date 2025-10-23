/*
ВОЛИК АНДРЕЙ ОЛЕГОВИЧ ПС-23

14.15. Удалённый контроль (5)

Пульт дистанционного управления имеет 13 клавиш:
 1  2  3  ↑
 4  5  6  ↓
 7  8  9
--  0
Имеется 100 каналов с номерами от 0 до 99. Можно переключаться, либо           <ПРИМЕР>
уменьшая номер канала кнопкой ↓ (после 0 следует 99), либо увеличивая		 ^ input.txt:
номер кнопкой ↑ (после 99 следует 0), либо набирая нужный номер. Для набора    0 0 1 1
двузначного номера нажимается кнопка '--', а затем цифры номера.			   1 1 1 1
Некоторые кнопки неисправны. Требуется от некоторого начального канала		   1 1 1
переключиться на заданный канал минимальным количеством нажатий.               1 1
																			   23 52
Исправный - 1, неисправный - 0												 ^ output.txt:
																			   4
Источник: --
*/

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <array>
#include <vector>
#include <queue>
#include <climits>

using Navigate = std::array<int, 3>;
struct Pult {
	Navigate firstRow;
	int upwardArrow;
	Navigate secondRow;
	int downwardArrow;
	Navigate thirdRow;
	int twoSignButton;
	int zeroButton;
};

void ReadInput(Pult& pult, int& current, int& destination) {
	std::ifstream inputFile{ "input.txt" };

	if (!inputFile.is_open()) {
		std::cerr << "Failed to open input file\n";
	}

	inputFile >> pult.firstRow[0] >> pult.firstRow[1] >> pult.firstRow[2];    // 1 2 3
	inputFile >> pult.upwardArrow;
	inputFile >> pult.secondRow[0] >> pult.secondRow[1] >> pult.secondRow[2]; // 4 5 6
	inputFile >> pult.downwardArrow;
	inputFile >> pult.thirdRow[0] >> pult.thirdRow[1] >> pult.thirdRow[2];	  // 7 8 9
	inputFile >> pult.twoSignButton;
	inputFile >> pult.zeroButton;											  //   0
	inputFile >> current >> destination;
}

void PrintPult(Pult& pult, int& current, int& destination) {
	std::cout << "Pult & channel change data:\n";
	std::cout << pult.firstRow[0] << " " << pult.firstRow[1] << " " << pult.firstRow[2] << " ";
	std::cout << pult.upwardArrow << "\n";
	std::cout << pult.secondRow[0] << " " << pult.secondRow[1] << " " << pult.secondRow[2] << " ";
	std::cout << pult.downwardArrow << "\n";
	std::cout << pult.thirdRow[0] << " " << pult.thirdRow[1] << " " << pult.thirdRow[2] << "\n";
	std::cout << pult.twoSignButton << " " << pult.zeroButton << "\n";
	std::cout << current << " " << destination << "\n\n";
}

bool IsDigitAvailable(const Pult& pult, int digit) {
	if (digit == 0) {
		return pult.zeroButton;
	} else if (digit >= 1 && digit <= 3) {
		return pult.firstRow[digit - 1];
	} else if (digit >= 4 && digit <= 6) {
		return pult.secondRow[digit - 4];
	} else if (digit >= 7 && digit <= 9) {
		return pult.thirdRow[digit - 7];
	}
	return false;
}

int ChannelTravel(Pult& pult, int& current, int& destination) {
	if (current == destination) {
		return 0;
	}

	if (current < 0 || current > 99 || destination < 0 || destination > 99) {
		return -1;
	}
	
	bool canUseArrows = pult.downwardArrow || pult.upwardArrow;
	bool canUseTwoSignButton = pult.twoSignButton;
	bool canUseDigits = pult.zeroButton ||
		std::any_of(pult.firstRow.begin(), pult.firstRow.end(), [](int x) { return x == 1; }) ||
		std::any_of(pult.secondRow.begin(), pult.secondRow.end(), [](int x) { return x == 1; }) ||
		std::any_of(pult.thirdRow.begin(), pult.thirdRow.end(), [](int x) { return x == 1; });

	if (!canUseArrows && !canUseTwoSignButton && !canUseDigits) {
		return -1;
	}

	std::vector<int> minTaps(100, INT_MAX);
	minTaps[current] = 0;
	std::queue<int> tapQueue{};
	tapQueue.push(current);

	while (!tapQueue.empty()) {
		int currentChannel = tapQueue.front();
		tapQueue.pop();
		int currentTaps = minTaps[currentChannel];

		if (pult.upwardArrow) {
			int nextChannel = (currentChannel + 1) % 100;
			if (currentTaps + 1 < minTaps[nextChannel]) {
				minTaps[nextChannel] = currentTaps + 1;
				if (nextChannel == destination) {
					return minTaps[nextChannel];
				}
				tapQueue.push(nextChannel);
			}
		}

		if (pult.downwardArrow) {
			int nextChannel = (currentChannel - 1 + 100) % 100;
			if (currentTaps + 1 < minTaps[nextChannel]) {
				minTaps[nextChannel] = currentTaps + 1;
				if (nextChannel == destination) {
					return minTaps[nextChannel];
				}
				tapQueue.push(nextChannel);
			}
		}

		if (pult.twoSignButton) {
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					if (IsDigitAvailable(pult, i) && IsDigitAvailable(pult, j)) {
						int nextChannel = i * 10 + j;
						int tapsForTwoDigits = currentTaps + 3;

						if (tapsForTwoDigits < minTaps[nextChannel]) {
							minTaps[nextChannel] = tapsForTwoDigits;
							tapQueue.push(nextChannel);
						}
					}
				}
			}
		}

		for (int i = 0; i < 10; ++i) {
			if (IsDigitAvailable(pult, i)) {
				int nextChannel = i;
				int tapsForOneDigit = currentTaps + 1;

				if (tapsForOneDigit < minTaps[nextChannel]) {
					minTaps[nextChannel] = tapsForOneDigit;
					tapQueue.push(nextChannel);
				}

				if (pult.upwardArrow) {
					int finalChannel = (nextChannel + 1) % 100;
					if (tapsForOneDigit + 1 < minTaps[finalChannel]) {
						minTaps[finalChannel] = tapsForOneDigit + 1;
						if (finalChannel == destination) {
							return minTaps[finalChannel];
						}
						tapQueue.push(finalChannel);
					}
				}

				if (pult.downwardArrow) {
					int finalChannel = (nextChannel - 1 + 100) % 100;
					if (tapsForOneDigit + 1 < minTaps[finalChannel]) {
						minTaps[finalChannel] = tapsForOneDigit + 1;
						if (finalChannel == destination) {
							return minTaps[finalChannel];
						}
						tapQueue.push(finalChannel);
					}
				}
			}
		}
	}

	return minTaps[destination] == INT_MAX ? -1 : minTaps[destination];
}

int main() {
	setlocale(LC_ALL, "Rus");

	Pult pult{};
	int currentChannel{};
	int destinationChannel{};

	ReadInput(pult, currentChannel, destinationChannel);
	PrintPult(pult, currentChannel, destinationChannel);

	int totalMinTaps = ChannelTravel(pult, currentChannel, destinationChannel);
	std::ofstream outputFile{ "output.txt" };
	if (!outputFile.is_open()) {
		std::cerr << "Failed to open output file\n";
		return 1;
	}

	std::cout << totalMinTaps << "\n";
	outputFile << totalMinTaps;
	outputFile.close();

	return 0;
}