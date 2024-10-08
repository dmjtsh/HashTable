#ifndef LIST_H
#define LIST_H

#include <stdio.h>

#define VALUE_T_SPECIFIER "%.3lf"
typedef char* Value_t;

enum ListErrorBits
{
	LIST_PTR_NULL              = 1 << 0,
	LIST_DATA_PTR_NULL         = 1 << 1,
	LIST_SIZE_GREATER_CAPACITY = 1 << 2,
	LIST_SIZE_LESS_ONE         = 1 << 3,
	LIST_REALLOC_ERROR         = 1 << 4,
	LIST_BAD_CAPACITY          = 1 << 5,
	LIST_BAD_SIZE              = 1 << 6,
	LIST_LOGGER_ERROR          = 1 << 7,
	LIST_GRAPH_ERROR           = 1 << 8,
	LIST_DELETED               = 1 << 9
};

const int    REALLOC_UP_COEFF    = 2;

const size_t LIST_MAX_SIZE       = 10e15;
const size_t LIST_START_CAPACITY = 4;

const Value_t ELEM_VALUE_POISON = nullptr;
const size_t  ELEM_INDEX_POISON = 666;

const int     FICT_ELEM_INDEX       = 0;
const Value_t FICT_ELEM_VALUE       = nullptr;

const int LIST_FREE_START_INDEX = FICT_ELEM_INDEX + 1;

struct Node
{
	size_t  prev;
	Value_t value;
	size_t  next;
};

struct List
{
	size_t capacity;
	size_t size;

	Node*  data;
	size_t head;
	size_t tail;
	size_t free;

	unsigned errors;
	FILE* logger;
};

size_t ListInsertFront(List* list, Value_t new_value);
size_t ListInsertBack(List* list, Value_t new_value);
size_t ListInsertAfter (List* list, size_t elem_index, Value_t new_elem_value);
size_t ListInsertBefore(List* list, size_t elem_index, Value_t new_elem_value);

extern "C" bool ListSearch(List* list, Value_t elem_to_search);

unsigned ListRemoveFirst(List* list);
unsigned ListRemoveLast (List* list);
unsigned ListRemove(List* list, size_t elem_index);

unsigned ListCtor(List* list);
unsigned ListDtor(List* list);

unsigned ListVerifier(List* list);

#endif // LIST_H
