#include <algorithm>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// Направления для удобного управления стенами
enum Direction { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };

// Класс, представляющий замок и его структуру
class Castle
{
private:
    int rows; //< Количество строк в замке
    int cols; //< Количество столбцов в замке
    vector<vector<int>> walls; // Стены замка в виде битовой маски
    vector<vector<bool>> visited; // Массив для отслеживания посещённых ячеек
    vector<vector<int>> roomIds; // Идентификаторы комнат в замке
    unordered_map<int, int> roomSizes; // Словарь размеров комнат

    // Смещения для перемещения по направлению (NORTH, EAST, SOUTH, WEST)
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};

    int currentRoomId = 0; // Текущий идентификатор комнаты

public:
    // Конструктор класса замка
    Castle(const int m, const int n) : rows(m), cols(n)
    {
        walls.resize(rows, vector<int>(cols, 0));
        visited.resize(rows, vector<bool>(cols, false));
        roomIds.resize(rows, vector<int>(cols, -1));
    }

    // Устанавливает стену в указанной ячейке и направлении
    void setWall(const int x, const int y, const Direction dir)
    {
        walls[x][y] |= (1 << dir);
        const int nx = x + dx[dir];
        const int ny = y + dy[dir];
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols)
        {
            walls[nx][ny] |= (1 << ((dir + 2) % 4)); // Устанавливаем стену с противоположной стороны
        }
    }

    // Проверяет, есть ли стена в заданной ячейке и направлении
    bool hasWall(const int x, const int y, const Direction dir) const
    {
        return walls[x][y] & (1 << dir);
    }

    // Вычисляет площадь комнаты с использованием DFS
    int countArea(const int x, const int y)
    {
        if (x < 0 || x >= rows || y < 0 || y >= cols || visited[x][y])
        {
            return 0;
        }

        visited[x][y] = true;
        roomIds[x][y] = currentRoomId;
        int area = 1;

        // Обходим соседние ячейки
        for (int dir = 0; dir < 4; ++dir)
        {
            const int nx = x + dx[dir];
            const int ny = y + dy[dir];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                !hasWall(x, y, static_cast<Direction>(dir)))
            {
                area += countArea(nx, ny);
            }
        }

        return area;
    }

    // Находит количество комнат и максимальную площадь комнаты
    void findRooms(int& roomCount, int& maxArea)
    {
        visited.assign(rows, vector<bool>(cols, false));
        roomSizes.clear();
        currentRoomId = 0;
        roomCount = 0;
        maxArea = 0;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (roomIds[i][j] == -1)
                {
                    currentRoomId++;
                    int area = countArea(i, j);
                    roomSizes[currentRoomId] = area;
                    roomCount++;
                    maxArea = max(maxArea, area);
                }
            }
        }
    }

    // Находит стену, удаление которой объединяет две комнаты с максимальной площадью
    void findBestWallToRemove(int& maxCombinedArea, pair<int, int>& wallPosition,
                          Direction& bestDir, int& iterationCount)
    {
            maxCombinedArea = 0;
            iterationCount = 0;

            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < cols; ++j)
                {
                    for (int dir = 0; dir < 4; ++dir)
                    {
                        iterationCount++;

                        const int nx = i + dx[dir];
                        const int ny = j + dy[dir];

                        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                            hasWall(i, j, static_cast<Direction>(dir)))
                        {
                            int room1 = roomIds[i][j];
                            int room2 = roomIds[nx][ny];

                            if (room1 != room2)
                            {
                                // Если комнаты разные, вычисляем объединённую площадь
                                const int combinedArea = roomSizes[room1] + roomSizes[room2];
                                if (combinedArea > maxCombinedArea)
                                {
                                    maxCombinedArea = combinedArea;
                                    wallPosition = {i, j};
                                    bestDir = static_cast<Direction>(dir);
                                }
                            }
                        }
                    }
                }
            }
    }

    // Выводит текстовую визуализацию замка
    void printLayout() const
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                cout << "+";
                if (hasWall(i, j, NORTH) || i == 0)
                {
                    cout << "---";
                }
                else
                {
                    cout << "   ";
                }
            }
            cout << "+" << endl;

            for (int j = 0; j < cols; ++j)
            {
                if (hasWall(i, j, WEST) || j == 0)
                {
                    cout << "|";
                }
                else
                {
                    cout << " ";
                }
                cout << "   ";
            }
            cout << "|" << endl;
        }

        for (int j = 0; j < cols; ++j)
        {
            cout << "+---";
        }
        cout << "+" << endl;
    }

    // Выводит информацию о найденных комнатах и лучшей стене для удаления
    static void printRoomInfo(const int roomCount, const int maxArea,
                              const pair<int, int>& wallPosition,
                              const Direction bestDir)
    {
        cout << "Количество комнат: " << roomCount << endl;
        cout << "Площадь наибольшей комнаты: " << maxArea << endl;
        cout << "Стену следует удалить из клетки (" << wallPosition.first
             << ", " << wallPosition.second << ") в направлении " << bestDir
             << endl;
    }
};

// Функция для создания замка
Castle createCastle()
{
    Castle castle(5, 5);

    // Добавление горизонтальных стен
    castle.setWall(0, 0, EAST);
    castle.setWall(0, 1, EAST);
    castle.setWall(1, 0, EAST);
    castle.setWall(1, 1, EAST);
    castle.setWall(1, 2, EAST);
    castle.setWall(2, 1, EAST);
    castle.setWall(2, 2, EAST);
    castle.setWall(2, 3, EAST);
    castle.setWall(3, 3, EAST);

    // Добавление вертикальных стен
    castle.setWall(0, 0, SOUTH);
    castle.setWall(0, 1, SOUTH);
    castle.setWall(1, 1, SOUTH);
    castle.setWall(1, 2, SOUTH);
    castle.setWall(2, 2, SOUTH);
    castle.setWall(2, 3, SOUTH);
    castle.setWall(3, 3, SOUTH);
    castle.setWall(3, 4, SOUTH);

    return castle;
}

int main()
{
    Castle castle = createCastle();

    cout << "\nПланировка замка:\n";
    castle.printLayout();
    cout << endl;

    int roomCount, maxArea;
    castle.findRooms(roomCount, maxArea);

    int maxCombinedArea;
    pair<int, int> wallPosition;
    Direction bestDir;
    int iterationCount; // Переменная для подсчёта переборов

    const auto start = chrono::high_resolution_clock::now();
    castle.findBestWallToRemove(maxCombinedArea, wallPosition, bestDir, iterationCount);
    const auto end = chrono::high_resolution_clock::now();

    cout << "Время выполнения findBestWallToRemove: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << " наносекунд" << endl;

    //cout << "Количество переборов: " << iterationCount << endl;

    Castle::printRoomInfo(roomCount, maxArea, wallPosition, bestDir);

    return 0;
}
