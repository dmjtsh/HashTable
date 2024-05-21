#ifndef HASH_H
#define HASH_H

typedef long long Hash_t;

Hash_t OptCRC32Hash(const void* value);
Hash_t CRC32Hash(const void* value);
Hash_t AsciiCodeSumHash(const void* value);
Hash_t StrlenHash(const void* value);
Hash_t FirstLetterHash(const void* value);
Hash_t ZeroHash(const void* value);
Hash_t DimasHash(const void* value);

#endif // HASH_H
