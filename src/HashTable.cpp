#include <assert.h>

#include "HashTable.h"
#include "text_info.h"
#include "list.h"

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
