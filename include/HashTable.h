#include <stdio.h>
#include <stdlib.h>

#include "../DimasLIB/DimasList/list.h"
#include "../DimasLIB/DimasHash/hash.h"
#include "../DimasLIB/DimasTextInfo/text_info.h"

const size_t HASH_TABLE_INIT_CAPACITY = 301;

struct HashTable
{
    size_t capacity;
    List* lists;

    Hash_t (*hash_function)(const void* value);
};

double HashTableCountDispersion(HashTable* hash_table, const char* data_filename);

void HashTableBuildHistogram(HashTable* hash_table, const char* hash_func_name);

bool HashTableSearch(HashTable* hash_table, const Value_t value);

void HashTableAdd(HashTable* const  hash_table, const Value_t value);

void HashTableCtor(HashTable* const hash_table, const size_t capacity,
                  Hash_t (*function_ptr)(const void* value));

void HashTableInit(HashTable* hash_table, TextInfo* text_info);

void HashTableDtor(HashTable* const hash_table);
