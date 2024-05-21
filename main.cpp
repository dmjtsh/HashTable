#include <stdio.h>

#include "include\HashTable.h"
#include "DimasLIB\DimasTextInfo\text_info.h"
#include "DimasLIB\DimasHash\hash.h"

int main(int argc, char** argv)
{
    TextInfo text_info = {};

    TextInfoCtor(&text_info, (argc > 1) ? argv[1] : "tests/test1.txt");

    HashTable hash_table = {};
    HashTableCtor(&hash_table, HASH_TABLE_INIT_CAPACITY, ZeroHash);

    HashTableInit(&hash_table, &text_info);

    HashTableBuildHistogram(&hash_table, "ZeroHash");

    printf("%lf", HashTableCountDispersion(&hash_table, "data/hash_table_data.txt"));

    //printf("%d", HashTableSearch(&hash_table, (Value_t)"banana"));

    HashTableDtor(&hash_table);
    TextInfoDtor(&text_info);
    
    return 0;
}
