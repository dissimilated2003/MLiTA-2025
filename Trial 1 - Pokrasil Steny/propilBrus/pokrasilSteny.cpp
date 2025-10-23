/*
ВОЛИК АНДРЕЙ ОЛЕГОВИЧ ПС-23

1.1. Покраска лабиринта (5)

Лабиринт представляет собой квадрат, состоящий из NxN сегментов.             ПРИМЕР:
Каждый из сегментов может быть либо пустым, либо заполненным
монолитной каменной стеной. Гарантируется, что левый верхний и               ..*****
правый нижний сегменты пусты. Лабиринт обнесён сверху, снизу,                ......*
слева и справа стенами, оставляющими свободными только левый верхний и       *...##*
правый нижний углы. Директор лабиринта решил покрасить стены лабиринта,      *..#..*
видимые изнутри (см. пример). Помогите ему рассчитать количество краски,     *..###*
необходимой для этого. 3 < N < 33 размер сегмента 3 x 3 м,                   *......
высота стен 3 м, время 1 с.                                                  *****..
                                                                          
Источник: --
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <stack>

using std::string;
using Row = std::vector<char>;
using Matrix = std::vector<Row>;

void readFile(Matrix& Matrix, int& n) {
    std::ifstream inFile{ "input.txt" };
    if (!inFile) {
        std::cerr << "Out of file\n";
        return;
    }

    inFile >> n;
    if (n < 3 || n > 33) {
        std::cerr << "Out of borderline\n";
        return;
    }

    Matrix.resize(n, Row(n));
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            inFile >> Matrix[y][x];
        }
    }
}

void redeclareMatrix(Matrix& Labyrinth, Matrix& Matrix, int& n) {
    std::ifstream inFile{ "input.txt" };
    inFile >> n;
    int dn = n + 2;
    Labyrinth.resize(dn, Row(dn));
    
    int breadth = Labyrinth.size() - 3;
    for (int y = 0; y < dn; y++) {
        for (int x = 0; x < dn; x++) {
            if ((y < 2 && x < 2) || (y > breadth && x > breadth)) {
                Labyrinth[y][x] = '.';
            } else {
                Labyrinth[y][x] = '#';
            }
        }
    }

    for (int y = 1; y <= n; y++) {
        for (int x = 1; x <= n; x++) {
            Labyrinth[y][x] = Matrix[y - 1][x - 1];
        }
    }

    Labyrinth[1][1] = '.';
    Labyrinth[n][n] = '.';
}

int innerWallSearch(Matrix& Matrix) {
    int n = Matrix.size();
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
    int totalPaintedWalls{ 0 };
    const std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    
    auto paintWallsFrom = [&](int startX, int startY) -> int {
        int paintedWalls{ 0 };
        std::stack<std::pair<int, int>> stack{};
        stack.push({ startX, startY });
        visited[startX][startY] = true;

        while (!stack.empty()) {
            auto top = stack.top();
            int x = top.first;
            int y = top.second;
            stack.pop();

            for (const auto& direction : directions) {
                int dx = direction.first;
                int dy = direction.second;
                int newX = x + dx;
                int newY = y + dy;

                if (newX < 0 || newY < 0 || newX >= n || newY >= n) {
                    continue;
                }

                if (Matrix[newX][newY] == '#') {
                    paintedWalls++;
                } else if (Matrix[newX][newY] == '.' && !visited[newX][newY]) {
                    visited[newX][newY] = true;
                    stack.push({ newX, newY });
                }
            }
        }

        return paintedWalls;
    };

    auto isAvailable = [&]() -> bool {
        std::stack<std::pair<int, int>> stack{};
        stack.push({ 0, 0 });
        visited.assign(n, std::vector<bool>(n, false));
        visited[0][0] = true;

        while (!stack.empty()) {
            auto top = stack.top();
            int x = top.first;
            int y = top.second;
            stack.pop();

            if (x == n - 1 && y == n - 1) {
                return true;
            }

            for (const auto& direction : directions) {
                int dx = direction.first;
                int dy = direction.second;
                int newX = x + dx;
                int newY = y + dy;

                if (newX < 0 || newY < 0 || newX >= n || newY >= n) {
                    continue;
                }

                if (Matrix[newX][newY] == '#') {

                }
                else if (Matrix[newX][newY] == '.' && !visited[newX][newY]) {
                    visited[newX][newY] = true;
                    stack.push({ newX, newY });
                }
            }
        }

        return false;
    };

    if (isAvailable()) {
        visited.assign(n, std::vector<bool>(n, false));
        totalPaintedWalls = paintWallsFrom(0, 0);
    } else {
        visited.assign(n, std::vector<bool>(n, false));
        totalPaintedWalls += paintWallsFrom(0, 0);
        visited.assign(n, std::vector<bool>(n, false));
        totalPaintedWalls += paintWallsFrom(n - 1, n - 1);
    }

    return totalPaintedWalls;
}

void printVV(Matrix& Matrix, int& n) {
    n = Matrix.size();
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            std::cout << Matrix[y][x];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    int n{};

    Matrix squareMatrix{};
    readFile(squareMatrix, n);
    printVV(squareMatrix, n);

    Matrix labyrinth{};
    redeclareMatrix(labyrinth, squareMatrix, n);
    printVV(labyrinth, n);

    int segmentCost{ 9 };
    int totalCost{};
    int findedWalls{};
    int extraWalls{ 4 };
    findedWalls = innerWallSearch(labyrinth) - extraWalls;
    totalCost = segmentCost * findedWalls;

    std::cout << findedWalls << "\n";
    std::cout << totalCost << "\n";

    std::ofstream outputFile{ "output.txt" };
    outputFile << totalCost;
    outputFile.close();
    
    return 0;
}