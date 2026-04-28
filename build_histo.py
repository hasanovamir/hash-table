import sys
import matplotlib.pyplot as plt
import numpy as np

def read_data (filename):
    hashes = []
    counts = []

    with open (filename, 'r') as f:
        for line in f:
            line = line.strip ()
            if not line:
                continue
            parts = line.split ()
            if len (parts) >= 2:
                try:
                    h = int (parts[0])
                    c = int (parts[1])

                    hashes.append (h)
                    counts.append (c)

                except ValueError:
                    print (f"Пропущена строка с ошибкой: {line}")
    return hashes, counts

def main():
    if len (sys.argv) < 2:
        print ("Использование: python plot_hist.py <файл_с_данными> [выходной_файл.png]")
        print ("Пример: python plot_hist.py data.txt result.png")
        sys.exit (1)

    data_filename   = sys.argv[1]
    output_filename = sys.argv[2] if len (sys.argv) >= 3 else "histogram.png"

    hashes, counts = read_data (data_filename)

    if not hashes:
        print ("Нет данных для отображения.")
        return

    sorted_pairs = sorted (zip (hashes, counts))
    sorted_hashes = [p[0] for p in sorted_pairs]
    sorted_counts = [p[1] for p in sorted_pairs]

    plt.figure (figsize = (14, 7))
    bars = plt.bar (sorted_hashes, sorted_counts, width = 0.8,
                   color = plt.cm.plasma (np.linspace (0.2, 0.9, len (sorted_hashes))),
                   edgecolor = 'black', linewidth = 0.6, alpha = 0.85)

    max_count = max (sorted_counts) if sorted_counts else 1
    for bar, cnt in zip (bars, sorted_counts):
        if cnt > 0:
            plt.text (bar.get_x () + bar.get_width () / 2, bar.get_height () + max_count * 0.01,
                     str (cnt), ha = 'center', va = 'bottom', fontsize = 8, rotation = 45)

    plt.xlabel ('Хеш', fontsize = 12)
    plt.ylabel ('Количество элементов', fontsize = 12)
    plt.title ('Гистограмма количества элементов по значениям хеша', fontsize = 15, fontweight = 'bold')

    step = max (1, len (sorted_hashes) // 20)
    plt.xticks (sorted_hashes[::step], rotation = 45, ha = 'right', fontsize = 9)
    plt.grid (axis = 'y', linestyle = '--', alpha = 0.5)
    plt.tight_layout ()

    plt.savefig (output_filename, dpi = 150, bbox_inches = 'tight')
    print (f"Гистограмма сохранена в файл: {output_filename}")

if __name__ == "__main__":
    main ()