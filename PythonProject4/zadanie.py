import random
import time

NUM_COUNT = 10000

def generate_random_number():
    return str(random.uniform(0, 100))

def main():
    # Tworzenie pliku z 10000 liczbami typu string
    with open("numbers.txt", "w") as outFile:
        for _ in range(NUM_COUNT):
            outFile.write(generate_random_number() + "\n")

    # Wczytywanie liczb z pliku
    numbers = []
    with open("numbers.txt", "r") as inFile:
        for line in inFile:
            try:
                numbers.append(float(line.strip()))
            except ValueError as e:
                print(f"Błąd konwersji: {e}")
                return 1

    # Pomiar czasu sortowania
    start = time.time()
    numbers.sort()
    end = time.time()
    duration = end - start

    # Zapisywanie posortowanych liczb do nowego pliku
    with open("sorted_numbers.txt", "w") as sortedFile:
        for num in numbers:
            sortedFile.write(f"{num}\n")

    print("Operacja zakonczona pomyslnie!")
    print(f"Czas sortowania: {duration} sekund")

if __name__ == "__main__":
    main()
