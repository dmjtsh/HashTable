#include <string.h>

#include "hash.h"

Hash_t AsciiCodeSumHash(const void* value)
{
	Hash_t hash = 0;
	size_t value_len = strlen((char*)value);
	for (size_t i = 0; i < value_len; ++i)
		hash += ((char*)value)[i];

	return hash;
}

Hash_t StrlenHash(const void* value)
{
	return strlen((char*)value);
}

Hash_t FirstLetterHash(const void* value)
{
	return *(char*)value;
}

Hash_t ZeroHash(const void* value)
{
	return 0;
}

Hash_t DimasHash(const void* value)
{
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
