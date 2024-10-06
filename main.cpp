#include <x86intrin.h>
#include <stdint.h>
#include <stdio.h>

#include "include/HashTable.h"
#include "DimasLIB/DimasTextInfo/text_info.h"
#include "DimasLIB/DimasHash/hash.h"

constexpr size_t TESTS_COUNT = 2000;

uint64_t rdtsc() {
    return __rdtsc();
}

int main(int argc, char** argv)
{
    TextInfo text_info = {};

    TextInfoCtor(&text_info, (argc > 1) ? argv[1] : "tests/test1.txt");

    HashTable hash_table = {};
    HashTableCtor(&hash_table, HASH_TABLE_INIT_CAPACITY, OptCRC32Hash);
    HashTableInit(&hash_table, &text_info);

    //HashTableBuildHistogram(&hash_table, "CRC32Hash");
    printf("%lf\n", HashTableCountDispersion(&hash_table, "data/hash_table_data.txt"));
    
    uint64_t timer_start = 0;
    uint64_t timer_end   = 0;

    timer_start = rdtsc();
    for(size_t i = 0; i < TESTS_COUNT; i++)
    {
        for(size_t j = 0; j < text_info.strings_num; j++)
        {
            HashTableSearch(&hash_table, text_info.text_strings[j].str);
        }
    }
    timer_end = rdtsc();
    printf("%zu\n", timer_end - timer_start);

    HashTableDtor(&hash_table);
    TextInfoDtor(&text_info);
    
    return 0;
}
