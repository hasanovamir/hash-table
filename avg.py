import sys
import re

def average_from_file(filename):
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            content = f.read()
    except FileNotFoundError:
        print(f"Ошибка: файл '{filename}' не найден.")
        return None
    except Exception as e:
        print(f"Ошибка при чтении файла: {e}")
        return None

    numbers = re.findall(r'-?\d+(?:\.\d+)?', content)

    if not numbers:
        print("В файле не найдено чисел.")
        return None

    numbers = [float(num) for num in numbers]

    average = sum(numbers) / len(numbers)
    return average

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(1)

    filename = sys.argv[1]
    avg = average_from_file(filename)
    if avg is not None:
        print(f"Среднее арифметическое чисел в файле: {avg}")