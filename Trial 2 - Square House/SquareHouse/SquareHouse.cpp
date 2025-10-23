/*
ВОЛИК АНДРЕЙ ОЛЕГОВИЧ ПС-23

2.7. Квадратный дом (5)

	В квадратной комнате размером M × M дециметров расставлена квадратная мебель. 
Стороны каждого предмета мебели параллельны стенам комнаты. Размер 
каждого предмета мебели представляется целым числом дециметров, а сам предмет 
отстоит от стен на целое число дециметров. Так как мебель может быть 
разной по высоте, то одну и ту же площадь пола могут занимать несколько 
предметов (например, табуретки могут быть полностью или частично задвинуты под стол). 
Сверху комната освещена точечным источником света, расположенным очень высоко, 
поэтому лучи падают строго перпендикулярно полу.
	Имеются N предметов мебели, для каждого из которых заданы в дециметрах размер D, 
а также расстояния от левой стены X и от передней стены Y.
	Требуется написать программу, которая определяет площадь максимальной освещенной 
области на полу. Областью считается совокупность квадратных дециметров пола, 
на которые не падает тень от мебели и такой, что любой квадратный дециметр области 
граничит хотя бы одной своей стороной с другим квадратным дециметром этой же 
области (исключение составляет только область из одного квадратного дециметра).

Числа 
	N: 0 < N
	M: M ≤ 100
числа 
	D: 1 ≤ D ≤ M
	X: 0 ≤ X
	Y: Y ≤ M - D

В выходной файл необходимо вывести значение P - площадь максимальной освещенной области.

Источник: --
*/

#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <fstream>

using std::string;

struct Furniture 
{
	int side;
	int x;
	int y;
};

using Room = std::vector<Furniture>;

using Matrix = std::vector<std::vector<char>>;

void readFile(Room& room, int& n, int& m) 
{
	std::ifstream inputFile{ "input.txt" };
	inputFile >> n >> m;
	if (m > 100) 
	{
		std::cerr << "out of data limit! \n";
	}
	
	room.resize(n);
	for (int i = 0; i < n; i++) 
	{
		inputFile >> room[i].side >> room[i].x >> room[i].y;
	}
}

Matrix declareMatrix(Room& room, int& n, int& m) 
{
	Matrix matrix{};
	matrix.resize(m);
	for (auto& row : matrix) 
	{
		row.resize(m);
	}

	for (int i = 0; i < m; i++) 
	{
		for (int j = 0; j < m; j++) 
		{
			matrix[i][j] = '.';
		}
	}

	for (int i = 0; i < n; i++) 
	{
		int startX = room[i].x;
		int endX = room[i].x + room[i].side;
		int startY = room[i].y;
		int endY = room[i].y + room[i].side;

		if (startX < 0 || startY < 0 || endX > m || endY > m) 
		{
			std::cerr << "furniture out of borderline! \n";
			continue;
		}

		for (int j = room[i].x; j < endX; j++) 
		{
			for (int k = room[i].y; k < endY; k++) 
			{
				matrix[k][j] = '#';
			}
		}
	}

	return matrix;
}

int searchMaxRegion(Matrix& matrix, int startX, int startY, int& m) 
{
	const std::vector<std::pair<int, int>> directions = 
	{ 
		{-1, 0}, 
		{1, 0}, 
		{0, -1}, 
		{0, 1} 
	};
	std::stack<std::pair<int, int>> stack{};
	stack.push({ startY, startX });
	int regionSize{ 0 };

	while (!stack.empty()) 
	{
		auto top = stack.top();
		int y = top.first;
		int x = top.second;
		stack.pop();

		bool skip = y < 0 || y >= m || x < 0 || x >= m || matrix[y][x] != '.';
		if (skip) 
		{
			continue;
		}

		matrix[y][x] = '#';
		regionSize++;

		for (const auto& direction : directions) 
		{
			int dy = direction.first;
			int dx = direction.second;
			stack.push({ y + dy, x + dx });
		}
	}

	return regionSize;
}

int regionAnalyzer(Matrix& matrix, int& m) 
{
	int maxRegionArea{ 0 };

	for (int y = 0; y < m; y++) 
	{
		for (int x = 0; x < m; x++) 
		{
			if (matrix[y][x] == '.') 
			{
				int currentRegionArea = searchMaxRegion(matrix, x, y, m);
				maxRegionArea = std::max(maxRegionArea, currentRegionArea);
			}
		}
	}

	return maxRegionArea;
}

void printReadedInput(Room& room, int& n, int& m) 
{
	std::cout << "input data: \n";
	std::cout << n << " " << m << "\n";
	for (int i = 0; i < n; i++) 
	{
		std::cout << room[i].side << " ";
		std::cout << room[i].x << " ";
		std::cout << room[i].y << "\n";
	}
}

void printMatrix(Matrix& matrix, int& m) 
{
	std::cout << "inner matrix content: \n";
	for (int i = 0; i < m; i++) 
	{
		for (int j = 0; j < m; j++) 
		{
			std::cout << matrix[i][j];
		}
		std::cout << "\n";
	}
}

int main() 
{
	Room room{};
	int n{}; // кол-во мебели
	int m{}; // размер комнаты

	readFile(room, n, m);
	printReadedInput(room, n, m);
	std::cout << "\n";

	Matrix matrix = declareMatrix(room, n, m);
	printMatrix(matrix, m);

	int maxArea = regionAnalyzer(matrix, m);
	std::cout << maxArea << "\n";
	std::ofstream outputFile{ "output.txt" };
	outputFile << maxArea;
	outputFile.close();

	return 0;

}
