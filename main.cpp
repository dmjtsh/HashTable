#include <stdio.h>

#include "HashTable.h"
#include "text_info.h"
#include "hash.h"

int main(int argc, char** argv)
{
    printf("!!!!!!!!!!!!!!!!!Hello!!!!!!!!!!!!!!!!");

    TextInfo text_info = {};

    TextInfoCtor(&text_info, (argc > 1) ? argv[1] : "tests/tests.txt");

    HashTable hash_table = {};
    HashTableCtor(&hash_table, HASH_TABLE_INIT_CAPACITY, StrlenHash);

    HashTableInit(&hash_table, &text_info);

    printf("%d", HashTableSearch(&hash_table, (Value_t)"apple"));

    HashTableDtor(&hash_table);
    TextInfoDtor(&text_info);

    return 0;
}
