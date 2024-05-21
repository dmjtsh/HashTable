#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "hash.h"
#include "text_info.h"

const size_t HASH_TABLE_INIT_CAPACITY = 200;

struct HashTable
{
    size_t capacity;
    List* lists;

    Hash_t (*hash_function)(const void* value);
};

bool HashTableSearch(HashTable* hash_table, const Value_t value);

void HashTableAdd(HashTable* const  hash_table, const Value_t value);

void HashTableCtor(HashTable* const hash_table, const size_t capacity,
                  Hash_t (*function_ptr)(const void* value));

void HashTableInit(HashTable* hash_table, TextInfo* text_info);

void HashTableDtor(HashTable* const hash_table);
