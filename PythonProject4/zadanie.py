import random
import time

NUM_COUNT = 10000

def generate_random_number():
    return str(random.uniform(0, 100))

def main():
    start = time.time()
    with open("numbers.txt", "w") as outFile:
        for _ in range(NUM_COUNT):
            outFile.write(generate_random_number() + "\n")
    end = time.time()
    duration_write = end - start

    start = time.time()
    numbers = []
    with open("numbers.txt", "r") as inFile:
        for line in inFile:
            try:
                numbers.append(float(line.strip()))
            except ValueError as e:
                print(f"Błąd konwersji: {e}")
                return 1
    end = time.time()
    duration_read = end - start

    start = time.time()
    numbers.sort()
    end = time.time()
    duration_sort = end - start

    start = time.time()
    with open("sorted_numbers.txt", "w") as sortedFile:
        for num in numbers:
            sortedFile.write(f"{num}\n")
    end = time.time()
    duration_write_sorted = end - start

    print("Operacja zakonczona pomyslnie!")
    print(f"Czas zapisu do pliku: {duration_write} sekund")
    print(f"Czas wczytywania z pliku: {duration_read} sekund")
    print(f"Czas sortowania: {duration_sort} sekund")
    print(f"Czas zapisu posortowanych danych do pliku: {duration_write_sorted} sekund")

if __name__ == "__main__":
    main()
