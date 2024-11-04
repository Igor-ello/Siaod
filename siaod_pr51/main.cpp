#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include <memory>

using namespace std;

/* ЗАДАНИЕ 1 */

void fiveBitToZero() {
	int n;
	cout << "Введите число: ";
	cin >> n;
	unsigned char x = n;
	constexpr unsigned char mask = 1; // 00000001
	// установка 5-го бита произвольного целого числа в 0
	x = x & (~(mask << 4)); // (00000001 -> 00010000) -> 11101111
	n = x;
	cout << "результат: " << n << endl;
}

void sevenBitToOne() {
	int n;
	cout << "Введите число: ";
	cin >> n;
	unsigned char x = n;
	constexpr unsigned char mask = 1; // 00000001
	// установка 7-го бита произвольного целого числа в 1
	x = x | (mask << 6); // (00000001 -> 01000000)
	n = x;
	cout << "Результат: " << n << endl;
}

void listing() {
	unsigned int x = 25; // 00011001
	constexpr int n = sizeof(int) * 8; // 32
	unsigned mask = (1 << (n - 1));

	cout << "Начальный вид маски: " << bitset<n>(mask) << endl;
	cout << "Результат: ";
	for (int i = 1; i <= n; i++) {
		// приводим изолированный бит к позиции 0
		cout << ((x & mask) >> (n - i));
		// для проверки следующего бита
		mask = mask >> 1;
	}
	cout << endl;
}

/* ЗАДАНИЕ 2 */

void sort_8() {
	int a[8] = {1, 7, 2, 5, 4, 3, 0, 6};
	unsigned char bits = 0; //00000000
	constexpr unsigned mask = 1; //00000001

	// установка битов в переменной b на основе массива a
	for (const int & i : a)
		bits |= (mask << i);

	cout << "Вывод переменной bits в 2-ом виде: " << bitset<8>(bits) << endl;

	// вывод индексов установленных битов
	cout << "Отсортированные числа: ";
	for (int i = 0; i < 8; i++)
		if (((bits >> i) & 1) == 1)
			cout << i << " ";
}

void sort_64() {
	int a[10] = {1, 30, 57, 63, 5};
	unsigned long long bits = 0;
	constexpr unsigned long long mask = 1;
	constexpr int n = sizeof(long long) * 8; // 8 * 8 = 64

	for (const int &i: a)
		bits |= (mask << i);

	cout << "Вывод переменной bits в 2-ом виде: " << endl;
	cout << bitset<64>(bits) << endl;

	cout << "Отсортированные числа: ";
	for (int i = 0; i < n; i++)
		if (((bits >> i) & mask) == 1)
			cout << i << " ";
}

void sort_64_char() {
	int a[5] = {1, 7, 27, 5, 14};
	unsigned long arr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	constexpr unsigned long mask = 1;
	constexpr int n = sizeof(long) * 8;

	// установка битов в массиве arr на основе массива a
	for (const int &i: a)
		// i / 8 указывает на байт, в котором находится бит i
		arr[i / 8] |= (mask << (i % 8));

	cout << "Вывод в 2-ом виде: " << endl;
	for (int i = n - 1; i >= 0; --i)
		cout << ((arr[i / 8] >> (i % 8)) & mask);
	cout << endl;

	cout << "Отсортированные числа: ";
	for (int i = 0; i < n; i++)
		if (((arr[i / 8] >> i % 8) & mask) == 1)
			cout << i << " ";
}

/* ЗАДАНИЕ 3 */

constexpr unsigned long long MAX_MEMORY = 1024 * 1024 * 8; // 1 MB в битах
void bitArraySort(const string &inputFile, const string &outputFile) {
	// Динамически выделяем битовый массив размером в 1 МБ
	unique_ptr<bool[]> bitArray(new bool[MAX_MEMORY]());

	// Открываем файл для чтения
	ifstream inFile(inputFile);
	if (!inFile.is_open()) {
		cerr << "Ошибка открытия входного файла!" << endl;
		return;
	}

	// Читаем числа из файла и устанавливаем соответствующие биты
	int number;
	while (inFile >> number) {
		if (number >= 0 && number < MAX_MEMORY) {
			bitArray[number] = true; // Устанавливаем бит в true для прочитанного числа
		}
	}
	inFile.close();

	// Открываем файл для записи отсортированных чисел
	ofstream outFile(outputFile);
	if (!outFile.is_open()) {
		cerr << "Ошибка открытия выходного файла!" << endl;
		return;
	}

	// Проходим по битовому массиву и записываем отсортированные числа
	for (size_t i = 0; i < MAX_MEMORY; ++i) {
		if (bitArray[i]) {
			// Если бит установлен, записываем число
			outFile << i << " ";
		}
	}
	outFile.close();

	// Выводим объем занимаемой битовым массивом памяти
	size_t usedBytes = sizeof(bool) * MAX_MEMORY;
	cout << "Объем используемой памяти: " << usedBytes << " байт; " << usedBytes / (1024.0 * 1024.0) << " Мб" << endl;
}

void generate_file(const string& filename, const int n) {
	// Диапазон чисел: [1000000, 10000000]
	constexpr unsigned long long MIN_VALUE = 1000000; // Минимальное число (10^6)
	constexpr unsigned long long MAX_VALUE = 10000000; // Максимальное число (10^7)
	constexpr unsigned long long RANGE_SIZE = MAX_VALUE - MIN_VALUE + 1; // Максимальное количество чисел

	// Проверка диапазона
	if (n > RANGE_SIZE) {
		cerr << "Количество чисел выходит за диапазон!" << endl;
		return;
	}

	// Создание вектора с уникальными числами
	vector<int> numbers(n);
	for (int i = 0; i < numbers.size(); ++i)
		if (MIN_VALUE + i < MAX_VALUE)
			numbers[i] = MIN_VALUE + i;

	// Перемешиваем вектор случайным образом
	random_device rd;
	mt19937 g(rd());
	shuffle(numbers.begin(), numbers.end(), g);

	// Открываем файл для записи
	ofstream outfile(filename);
	if (!outfile) {
		cerr << "Ошибка открытия файла!" << endl;
		return;
	}

	// Записываем первые n уникальных чисел в файл
	for (int i = 0; i < n; ++i) {
		outfile << numbers[i] << "\n";
	}

	outfile.close();
	cout << "Файл с " << n << " уникальными числами создан" << endl;
}

int filesort(const int n) {
	// Файлы
	string inputFile = "start.txt";
	string outputFile = "output.txt";

	// Генерируем входной файл
	generate_file(inputFile, n);

	// Измеряем время выполнения сортировки
	auto start = chrono::high_resolution_clock::now();

	// Запускаем сортировку
	bitArraySort(inputFile, outputFile);

	// Останавливаем таймер и выводим время выполнения
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	cout << "Время сортировки: " << duration.count() << " секунд" << endl;

	return 0;
}

int main() {
	setlocale(LC_ALL, "Russian");
	//fiveBitToZero();
	//sevenBitToOne();
	//listing();
	//sort_8();
	//sort_64();
	//sort_64_char();
	filesort(100000);
}
