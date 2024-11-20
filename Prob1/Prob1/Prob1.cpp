#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Функция для раскрашивания графа
void greedyGraphColoring(const vector<vector<int>>& adjacencyMatrix, vector<int>& colors)
{
    int numVertices = adjacencyMatrix.size();
    colors[0] = 0; // Присваиваем первый цвет первой вершине

    for (int u = 1; u < numVertices; u++)
    {
        vector<bool> available(numVertices, true);
        for (int v = 0; v < numVertices; v++)
        {
            if (adjacencyMatrix[u][v] == 1 && colors[v] != -1)
            {
                available[colors[v]] = false; // Цвет соседней вершины нельзя использовать
            }
        }

        for (int c = 0; c < numVertices; c++)
        {
            if (available[c])
            {
                colors[u] = c;
                break;
            }
        }
    }
}

// Функция для вывода цветов вершин
void printColors(const vector<int>& colors)
{
    cout << "Раскраска:\n";
    for (size_t i = 0; i < colors.size(); i++)
    {
        cout << "Вершина " << i + 1 << " имеет цвет " << colors[i] + 1 << endl;
    }
}

// Функция для вывода матрицы смежности
void printAdjacencyMatrix(const vector<vector<int>>& adjacencyMatrix)
{
    cout << "Матрица смежности:" << endl;
    for (const auto& row : adjacencyMatrix)
    {
        for (int value : row)
        {
            cout << value << " ";
        }
        cout << endl;
    }
}

// Функция для вывода списка смежности
void printAdjacencyList(const vector<vector<int>>& adjacencyMatrix)
{
    cout << "Список смежности:" << endl;
    for (size_t i = 0; i < adjacencyMatrix.size(); i++)
    {
        cout << "Вершина " << i + 1 << ": ";
        for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
        {
            if (adjacencyMatrix[i][j] == 1)
            {
                cout << j + 1 << " ";
            }
        }
        cout << endl;
    }
}

// Функция для записи данных в файл
void writeGraphDataToFile(int numVertices, const vector<vector<int>>& adjacencyMatrix, const vector<int>& colors) 
{
    ofstream outFile("graph_data.txt");
    if (!outFile) {
        cerr << "Ошибка при открытии файла для записи!" << endl;
        return;
    }
    outFile << numVertices << endl;

    for (const auto& row : adjacencyMatrix) 
    {
        for (int value : row) 
        {
            outFile << value << " ";
        }
        outFile << endl;
    }

    for (const auto& color : colors) 
    {
        outFile << color << " ";
    }

    outFile.close();
}

int main()
{
    int rabota = 1;

    while(rabota == 1)
    {
    setlocale(LC_ALL, "ru");
    srand(static_cast<unsigned int>(time(0)));

    metka_0:
    int numVertices;
    cout << "Введите количество вершин графа: ";
    cin >> numVertices;
    if (numVertices < 0)
    {
        cout << "\nОшибка: Вы ввели некорректные данные!\n\n";
        goto metka_0;
    }
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\nОшибка: Вы ввели некорректные данные!\n\n";
        goto metka_0;
    }
    if (std::cin.peek() != '\n')
    {
        cout << "\nОшибка: Вы ввели некорректные данные!\n\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        goto metka_0;
    }
    if (numVertices == 0)
    {
        cout << "\nОшибка: Вы ввели некорректные данные!\n\n";
        goto metka_0;
    }


    // Создаем матрицу смежности
    vector<vector<int>> adjacencyMatrix(numVertices, vector<int>(numVertices, 0));

    // Создание связного графа
    for (int i = 0; i < numVertices - 1; i++)
    {
        adjacencyMatrix[i][i + 1] = adjacencyMatrix[i + 1][i] = 1; // Соединяем i с i+1
    }

    // Добавляем случайные рёбра
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = i + 1; j < numVertices; j++)
        {
            if (rand() % 2 == 0)
            { // С вероятностью 50%
                adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = 1;
            }
        }
    }

    vector<int> colors(numVertices, -1);
    greedyGraphColoring(adjacencyMatrix, colors);

    metka_1:
    cout << "Вывести данные?\n1 - да\n2 - нет\nВыбор: ";
    int vibor;
    cin >> vibor;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\nОшибка: Вы ввели некорректные данные!\n\n";;
        goto metka_1;
    }
    if (std::cin.peek() != '\n')
    {
        cout << "\nОшибка: Вы ввели некорректные данные!\n\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        goto metka_1;
    }
    if (vibor != 1 && vibor != 2)
    {
        cout << "\nОшибка: Вы ввели некорректные данные!\n\n";
        goto metka_1;
    }
    if (vibor == 1)
    {
        cout << "\n";
        printColors(colors);
        cout << "\n";
        printAdjacencyMatrix(adjacencyMatrix);
        cout << "\n";
        printAdjacencyList(adjacencyMatrix);
        cout << "\n";
    }

    writeGraphDataToFile(numVertices, adjacencyMatrix, colors);

    // Запускаем Python скрипт
    system("python \"C:\\Users\\User\\Desktop\\Курсовая работа ЛОАИЗ\\main.py\"");

    metka_2:
    cout << "\nЕщё раз?\n1 - да\n2 - нет\nВыбор: ";
    cin >> rabota;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\nОшибка: Вы ввели некорректные данные!\n\n";
        goto metka_2;
    }
    if (std::cin.peek() != '\n')
    {
        cout << "\nОшибка: Вы ввели некорректные данные!\n\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        goto metka_2;
    }
    if (rabota != 1 && rabota != 2)
    {
        cout << "\nОшибка: Вы ввели некорректные данные!\n\n";
        goto metka_2;
    }
    cout << "\n";
}

    return 0;
}
