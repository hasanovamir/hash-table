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

    variance = np.var (sorted_counts)
    print (f"Дисперсия распределения по хешам: {variance:.4f}")

    plt.figure (figsize = (14, 7))
    bars = plt.bar (sorted_hashes, sorted_counts, width = 0.4,
                   color = plt.cm.plasma (np.linspace (0.2, 0.9, len (sorted_hashes))),
                   edgecolor = 'black', linewidth = 0.6, alpha = 0.85)

    plt.xlabel ('Хеш', fontsize = 12)
    plt.ylabel ('Количество элементов', fontsize = 12)
    plt.title (data_filename, fontsize = 15, fontweight = 'bold')

    plt.text (0.95, 0.95, f'Дисперсия = {variance:.4f}',
             transform = plt.gca().transAxes, fontsize = 10,
             verticalalignment = 'top', horizontalalignment = 'right',
             bbox = dict (boxstyle = 'round', facecolor = 'white', alpha = 0.8))

    step = max (1, len (sorted_hashes) // 20)
    plt.xticks (sorted_hashes[::step], rotation = 45, ha = 'right', fontsize = 9)
    plt.grid (axis = 'y', linestyle = '--', alpha = 0.5)
    plt.tight_layout ()

    plt.savefig (output_filename, dpi = 150, bbox_inches = 'tight')
    print (f"Гистограмма сохранена в файл: {output_filename}")

if __name__ == "__main__":
    main ()