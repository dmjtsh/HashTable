#include <string.h>
#include <stdint.h>
#include <intrin.h>
#include <assert.h>

#include "hash.h"

Hash_t AsciiCodeSumHash(const void* value)
{
    assert(value != nullptr);

	Hash_t hash = 0;
	size_t value_len = strlen((char*)value);
	for (size_t i = 0; i < value_len; ++i)
		hash += ((char*)value)[i];

	return hash;
}

Hash_t StrlenHash(const void* value)
{
    assert(value != nullptr);

	return strlen((char*)value);
}

Hash_t FirstLetterHash(const void* value)
{
    assert(value != nullptr);
	
    return *(char*)value;
}

Hash_t ZeroHash(const void* value)
{
    assert(value != nullptr);
	
    return 0;
}

Hash_t DimasHash(const void* value)
{
    assert(value != nullptr);

	Hash_t hash = 0;
	size_t value_len = strlen((char*)value);
	for (size_t i = 0; i < value_len; ++i) {
		hash += ((char*)value)[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}

constexpr size_t CRC32_POLYNOMIAL = 0xEDB88320;
Hash_t CRC32Hash(const void* value) 
{  
    assert(value != nullptr);

    size_t crc = 0xFFFFFFFF;
    size_t value_len = strlen((char*)value);

    for (size_t i = 0; i < value_len; i++) 
    {
        crc = crc ^ ((size_t)((char*)value)[i]);
        for (size_t j = 0; j < 8; j++) 
        {
            crc = (crc >> 1) ^ (CRC32_POLYNOMIAL & ~((crc & 1) - 1));
        }
    }

    return ~crc;
}

Hash_t OptCRC32Hash(const void* value) 
{    
    assert(value != nullptr);

    uint32_t hash = 0;
    
    // String Is No Longer than 16 symbs
    hash = _mm_crc32_u64(hash, *((uint64_t*)value));
    hash = _mm_crc32_u64(hash, *((uint64_t*)value + 1));
    
    return hash;
}