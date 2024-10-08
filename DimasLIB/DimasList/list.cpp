#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "../DimasUtilities/error_processing.h"
#include "list_io.h"

unsigned ListVerifier(List* list)
{
	if (!list)
		return LIST_PTR_NULL;

	CHECK_ERROR(list, list->data         == NULL,          LIST_DATA_PTR_NULL);
	CHECK_ERROR(list, list->size         >= LIST_MAX_SIZE, LIST_BAD_SIZE);
	CHECK_ERROR(list, list->capacity + 1 >= LIST_MAX_SIZE, LIST_BAD_CAPACITY);
	CHECK_ERROR(list, list->capacity + 1 < list->size,     LIST_SIZE_GREATER_CAPACITY);

	return list->errors;
}

unsigned ListDataReallocUp(List* list, size_t new_capacity)
{
	assert(list !=  NULL);

	Node* new_data = (Node*)realloc(list->data, new_capacity * sizeof(Node));
	if (!new_data)
	{
		list->errors |= LIST_REALLOC_ERROR;
		return list->errors;
	}

	list->data     = new_data;
	list->capacity = new_capacity - 1;

	list->data[list->free].next = list->size + 1;

	// FILL DATA WITH POISON AND CONNECT FREE
	for (size_t i = list->size + 1; i < list->capacity + 1; i++)
	{
		list->data[i].next = i + 1;

		list->data[i].prev  = ELEM_INDEX_POISON; // POISON
		list->data[i].value = ELEM_VALUE_POISON; // POISON
	}

	list->data[list->capacity].next = ELEM_INDEX_POISON; // FILLING LAST FREE ELEM WITH POISON

	return 0;
}

size_t ListInsertAfter(List* list, size_t elem_index, Value_t new_value)
{
	ERROR_PROCESSING(list, ListVerifier, ListDump, ListDtor);

	if (elem_index == ELEM_INDEX_POISON)
		return WRONG_COMMAND_USAGE;

	Node*  data            = list->data;
	size_t next_index      = list->data[elem_index].next;
	size_t free_next_index = list->data[list->free].next;
	size_t free_index      = list->free;

	data[next_index].prev  = free_index;
	data[elem_index].next  = free_index;

	data[free_index].next  = next_index;
	data[free_index].prev  = elem_index;
	data[free_index].value = new_value;

	list->free = free_next_index;

	list->size++;

	if (list->size + 1 >= list->capacity)
		ListDataReallocUp(list, (list->capacity + 1) * REALLOC_UP_COEFF);

	list->head = list->data[FICT_ELEM_INDEX].next;
	list->tail = list->data[FICT_ELEM_INDEX].prev;

	return free_index;
}

size_t ListInsertBefore(List* list, size_t elem_index, Value_t new_value)
{
	ERROR_PROCESSING(list, ListVerifier, ListDump, ListDtor);

	if(elem_index == ELEM_INDEX_POISON)
		return WRONG_COMMAND_USAGE;

	Node* data = list->data;
	size_t prev_index      = list->data[elem_index].prev;
	size_t free_index      = list->free;
	size_t free_next_index = list->data[list->free].next;

	data[prev_index].next = free_index;
	data[elem_index].prev = free_index;

	data[free_index].next  = elem_index;
	data[free_index].prev  = prev_index;
	data[free_index].value = new_value;

	list->free = free_next_index;

	list->size++;

	if (list->size + 1 >= list->capacity)
		ListDataReallocUp(list, (list->capacity + 1) * REALLOC_UP_COEFF);

	list->head = list->data[FICT_ELEM_INDEX].next;
	list->tail = list->data[FICT_ELEM_INDEX].prev;

	return free_index;
}

size_t ListInsertFront(List* list, Value_t new_value)
{
	return ListInsertBefore(list, list->head, new_value);
}

size_t ListInsertBack(List* list, Value_t new_value)
{
	return ListInsertAfter(list, list->tail, new_value);
}

unsigned ListRemove(List* list, size_t remove_index)
{
	ERROR_PROCESSING(list, ListVerifier, ListDump, ListDtor);

	if(remove_index == FICT_ELEM_INDEX || remove_index == ELEM_INDEX_POISON)
		return WRONG_COMMAND_USAGE;

	Node* data = list->data;
	size_t next_index = data[remove_index].next;
	size_t prev_index = data[remove_index].prev;

	data[prev_index].next = data[remove_index].next;
	data[next_index].prev = data[remove_index].prev;

	data[remove_index].next = list->free;
	list->free = remove_index;

	data[list->free].prev  = ELEM_INDEX_POISON; // POISON
	data[list->free].value = ELEM_VALUE_POISON; // POISON

	list->size--;

	list->head = data[FICT_ELEM_INDEX].next;
	list->tail = data[FICT_ELEM_INDEX].prev;

	return 0;
}

unsigned ListRemoveFirst(List* list)
{
	return ListRemove(list, list->tail);
}

static inline int OptStrCmp(const char* str1, const char* str2)
{
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    int result = 0;

    __asm__ inline (
        ".intel_syntax noprefix\n\t"
        "vlddqu ymm1, [%1]\n\t"
        "vptest ymm1, [%2]\n\t"

        "setc %b0\n\t"                       

        ".att_syntax prefix\n\t"

        : "+r" (result)
        : "r" (str1), "r" (str2)
    );

    return result;
}

// Replaced With ASM Func

//bool ListSearch(List* list, Value_t elem_to_search);
/*{
	//ERROR_PROCESSING(list, ListVerifier, ListDump, ListDtor);

	Node* node_ptr = &list->data[list->head];

	while(node_ptr != nullptr && node_ptr->value != nullptr)
	{
		if(OptStrCmp(elem_to_search, node_ptr->value) == 0)
			return true;

		node_ptr = &list->data[node_ptr->next];
	}

	return false;
}
*/

unsigned ListCtor(List* list)
{
	if (!list)
		return LIST_PTR_NULL;

	list->free = LIST_FREE_START_INDEX;

	list->logger = stderr;

	ListDataReallocUp(list, LIST_START_CAPACITY);

	list->data[FICT_ELEM_INDEX].next  = FICT_ELEM_INDEX;
	list->data[FICT_ELEM_INDEX].prev  = FICT_ELEM_INDEX;
	list->data[FICT_ELEM_INDEX].value = FICT_ELEM_VALUE;

	list->head = FICT_ELEM_INDEX;
	list->tail = FICT_ELEM_INDEX;

	ERROR_PROCESSING(list, ListVerifier, ListDump, ListDtor);

	return 0;
}

unsigned ListDtor(List* list)
{
	if (!list)
		return LIST_PTR_NULL;

	if (!(list->errors & LIST_DELETED))
	{
		if(!list->data)
			return LIST_DATA_PTR_NULL;

		free(list->data);

		list->errors |= LIST_DELETED;
	}
	else
		return LIST_DELETED;

	return 0;
}
