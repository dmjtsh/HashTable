#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <math.h>

#include "../include/HashTable.h"
#include "../DimasLIB/DimasTextInfo/text_info.h"
#include "../DimasLIB/DimasList/list.h"

void HashTableWriteData(HashTable* hash_table, const char* filename)
{
    FILE* data_file = fopen(filename, "w");
    assert(data_file != nullptr);

    for (int i = 0; i < hash_table->capacity; i++) 
    {
        int count = 0;
        
        size_t head_elem_ind = hash_table->lists[i].head;
        Node* node = &hash_table->lists[i].data[head_elem_ind];
        
        while (node->value != nullptr) 
        {
            count++;
            node = &hash_table->lists[i].data[node->next];
        }
        fprintf(data_file, "%d\n", count);
    }

    fclose(data_file);
}

void HashTableBuildHistogram(HashTable* hash_table, const char* hash_func_name) 
{
    HashTableWriteData(hash_table, "data/hash_table_data.txt");

    FILE* py_file = fopen("data/graphic_builder.py", "w");

    fprintf(py_file, "import matplotlib.pyplot as plt\n"
                     "def read_histogram(filename):\n"
                     "    with open(filename, 'r') as file:\n"
                     "        counts = [int(line.strip()) for line in file]\n"
                     "    return counts\n\n"
                     
                     "def plot_histogram(counts, output_filename):\n"
                     "    plt.bar(range(len(counts)), counts)\n"
                     "    plt.xlabel('Index of Hash Table')\n"
                     "    plt.ylabel('Number of elements')\n"
                     "    plt.title('Histogram of Dimas Hash Table (%s)')\n\n"
                     
                     "    plt.savefig(output_filename)\n"
                     "    plt.show()\n\n"
                     
                     "output_filename = '%s.jpg'\n"
                     "filename = 'data/hash_table_data.txt'\n\n"
                     
                     "counts = read_histogram(filename)\n\n"
                     
                     "plot_histogram(counts, output_filename)", hash_func_name, hash_func_name);

    fclose(py_file);

    //system("python data/graphic_builder.py");
}

double CountMeanValue(int* counts, int size) 
{
    assert(counts != nullptr);

    int sum = 0;
    for (int i = 0; i < size; i++) 
    {        
        sum += counts[i];
    }

    return sum / size;
}

double HashTableCountDispersion(HashTable* hash_table, const char* data_filename) 
{
    assert(hash_table    != nullptr);
    assert(data_filename != nullptr);

    FILE* data_file = fopen(data_filename, "r");
    assert(data_file != nullptr);

    int* table_counts = (int*)calloc(hash_table->capacity, sizeof(int));
    assert(table_counts != nullptr);
    
    // Filling Table Counts Arr
    for (int i = 0; fscanf(data_file, "%d", &table_counts[i]) != EOF && i < hash_table->capacity; i++) {;}

    double table_mean_value = CountMeanValue(table_counts, hash_table->capacity);
    double sum_squares = 0;

    for (int i = 0; i < hash_table->capacity; i++) {
        sum_squares += (table_counts[i] - table_mean_value) * (table_counts[i] - table_mean_value);
    }

    fclose(data_file);

    return sum_squares / hash_table->capacity;
}

bool HashTableSearch(HashTable* hash_table, const Value_t value)
{
    assert(hash_table != nullptr);

    Hash_t hash_index = hash_table->hash_function(value) % hash_table->capacity;

    if(ListSearch(&hash_table->lists[hash_index], value))
        return true;

    return false;
}

void HashTableAdd(HashTable* hash_table, const Value_t value)
{
    assert(hash_table != nullptr);

    Hash_t hash_index = hash_table->hash_function(value) % hash_table->capacity;

    ListInsertBack(&hash_table->lists[hash_index], value);
}

void HashTableInit(HashTable* hash_table, TextInfo* text_info)
{
    assert(hash_table != nullptr);
    assert(text_info  != nullptr);

    for(size_t i = 0; i < text_info->strings_num ;i++)
    {
        HashTableAdd(hash_table, text_info->text_strings[i].str);
    }
}

void HashTableCtor(HashTable* hash_table, const size_t capacity,
                  Hash_t (*function_ptr)(const void* value))
{
    assert(hash_table   != nullptr);
    assert(function_ptr != nullptr);

    hash_table->hash_function = function_ptr;
    hash_table->capacity      = capacity;

    hash_table->lists = (List*)calloc(capacity, sizeof(List));
    assert(hash_table->lists != nullptr);

    for(size_t i = 0; i < hash_table->capacity; i++)
        ListCtor(&hash_table->lists[i]);
}

void HashTableDtor(HashTable* hash_table)
{
    assert(hash_table != nullptr);

    for(size_t i = 0; i < hash_table->capacity; i++)
        ListDtor(&hash_table->lists[i]);

    free(hash_table->lists);
}
