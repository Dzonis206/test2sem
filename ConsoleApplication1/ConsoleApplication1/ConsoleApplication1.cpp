#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <chrono>

const int NUM_COUNT = 10000;

std::string generateRandomNumber() {
    float num = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100.0f;
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    auto start = std::chrono::high_resolution_clock::now();
    std::ofstream outFile("numbers.txt");
    if (!outFile) {
        std::cerr << "Nie można otworzyć pliku do zapisu!" << std::endl;
        return 1;
    }

    for (int i = 0; i < NUM_COUNT; ++i) {
        outFile << generateRandomNumber() << std::endl;
    }
    outFile.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationWrite = end - start;

    start = std::chrono::high_resolution_clock::now();
    std::ifstream inFile("numbers.txt");
    if (!inFile) {
        std::cerr << "Nie można otworzyć pliku do odczytu!" << std::endl;
        return 1;
    }

    float numbers[NUM_COUNT];
    std::string line;
    int index = 0;
    while (std::getline(inFile, line) && index < NUM_COUNT) {
        try {
            numbers[index++] = std::stof(line);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Błąd konwersji: " << e.what() << std::endl;
            return 1;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Liczba poza zakresem: " << e.what() << std::endl;
            return 1;
        }
    }
    inFile.close();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationRead = end - start;

    start = std::chrono::high_resolution_clock::now();
    std::sort(numbers, numbers + NUM_COUNT);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationSort = end - start;

    start = std::chrono::high_resolution_clock::now();
    std::ofstream sortedFile("sorted_numbers.txt");
    if (!sortedFile) {
        std::cerr << "Nie można otworzyć pliku do zapisu!" << std::endl;
        return 1;
    }

    for (int i = 0; i < NUM_COUNT; ++i) {
        sortedFile << numbers[i] << std::endl;
    }
    sortedFile.close();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationWriteSorted = end - start;

    std::cout << "Operacja zakonczona pomyslnie!" << std::endl;
    std::cout << "Czas zapisu do pliku: " << durationWrite.count() << " sekund" << std::endl;
    std::cout << "Czas wczytywania z pliku: " << durationRead.count() << " sekund" << std::endl;
    std::cout << "Czas sortowania: " << durationSort.count() << " sekund" << std::endl;
    std::cout << "Czas zapisu posortowanych danych do pliku: " << durationWriteSorted.count() << " sekund" << std::endl;

    return 0;
}
