import matplotlib.pyplot as plt
def read_histogram(filename):
    with open(filename, 'r') as file:
        counts = [int(line.strip()) for line in file]
    return counts

def plot_histogram(counts, output_filename):
    plt.bar(range(len(counts)), counts)
    plt.xlabel('Index of Hash Table')
    plt.ylabel('Number of elements')
    plt.title('Histogram of Dimas Hash Table (ZeroHash)')

    plt.savefig(output_filename)
    plt.show()

output_filename = 'ZeroHash.jpg'
filename = 'data/hash_table_data.txt'

counts = read_histogram(filename)

plot_histogram(counts, output_filename)