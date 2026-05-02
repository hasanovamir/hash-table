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
                    pass
    return hashes, counts

def main ():
    if len (sys.argv) < 2:
        sys.exit (1)

    data_filename   = sys.argv[1]
    output_filename = sys.argv[2] if len (sys.argv) >= 3 else "histogram.png"

    hashes, counts = read_data (data_filename)

    if not hashes:
        return

    sorted_pairs = sorted (zip (hashes, counts))
    sorted_hashes = [p[0] for p in sorted_pairs]
    sorted_counts = [p[1] for p in sorted_pairs]

    variance = np.var (sorted_counts)
    total_elements = sum (sorted_counts)
    num_nonempty = sum (1 for c in sorted_counts if c > 0)
    load_factor = total_elements / num_nonempty if num_nonempty > 0 else 0

    nonzero_hashes = [h for h, c in zip (sorted_hashes, sorted_counts) if c > 0]
    if nonzero_hashes:
        min_x = min (nonzero_hashes) - 0.5
        max_x = max (nonzero_hashes) + 0.5
    else:
        min_x = -0.5
        max_x = max (sorted_hashes) + 0.5

    max_count = max (sorted_counts)

    if len (nonzero_hashes) == 1:
        bar_width = 0.3
    else:
        bar_width = 0.8

    plt.figure (figsize = (14, 7))
    plt.bar    (sorted_hashes, sorted_counts, width = bar_width,
                color = 'black', edgecolor = 'black', linewidth = 0.6, alpha = 0.85)

    plt.xlim (min_x, max_x)
    plt.ylim (0, max_count * 1.05)

    if nonzero_hashes:
        step = max (1, (max (nonzero_hashes) - min (nonzero_hashes) + 1) // 20)
        xticks_positions = list (range (min (nonzero_hashes), max (nonzero_hashes) + 1, step))
        plt.xticks (xticks_positions, rotation = 45, ha = 'right', fontsize = 9)
    else:
        step = max (1, (max (sorted_hashes) + 1) // 20)
        xticks_positions = list (range (0, max (sorted_hashes) + 1, step))
        plt.xticks (xticks_positions, rotation = 45, ha = 'right', fontsize = 9)

    plt.xlabel ('Хеш', fontsize = 12)
    plt.ylabel ('Количество элементов', fontsize = 12)
    plt.title  (data_filename, fontsize = 15, fontweight = 'bold')

    info_text = f'Load Factor = {load_factor:.6f}\nVariance = {variance:.4f}'
    plt.text (0.95, 0.95, info_text,
              transform = plt.gca().transAxes, fontsize = 10,
              verticalalignment = 'top', horizontalalignment = 'right',
              bbox = dict (boxstyle = 'round', facecolor = 'white', alpha = 0.8))

    plt.grid (axis = 'y', linestyle = '--', alpha = 0.5)
    plt.tight_layout ()

    plt.savefig (output_filename, dpi = 150, bbox_inches = 'tight')

if __name__ == "__main__":
    main ()