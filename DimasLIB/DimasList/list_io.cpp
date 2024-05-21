#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdlib.h>

#include "list_io.h"

void ListDump(List* list, FILE* logger)
{
	assert(list   != NULL);
	assert(logger != NULL);

    //static size_t num_of_call = 1;
    //
    //fprintf(logger,
    //	"=======================================\n"
    //	"List DUMP CALL #%zu\n",
    //	num_of_call);
    //
    //if (list->errors)
    //{
    //	fprintf(logger,
    //	"-------------ERRORS------------\n");
    //	if (list->errors & LIST_PTR_NULL)
    //	{
    //		fprintf(logger, "List POINTER IS NULL\n");
    //		return;
    //	}
    //	if (list->errors & LIST_LOGGER_ERROR)          fprintf(logger, "List LOGGER ERROR\n");
    //	if (list->errors & LIST_DATA_PTR_NULL)         fprintf(logger, "List Data Ptr Null\n");
    //       if (list->errors & LIST_SIZE_GREATER_CAPACITY) fprintf(logger, "List Size GREATER Capacity\n");
    //       if (list->errors & LIST_SIZE_LESS_ONE)         fprintf(logger, "List Size LESS One\n");
    //       if (list->errors & LIST_REALLOC_ERROR)         fprintf(logger, "List REALLOC ERROR\n");
    //       if (list->errors & LIST_BAD_SIZE)              fprintf(logger, "List Size TOO BIG\n");
    //       if (list->errors & LIST_BAD_CAPACITY)          fprintf(logger, "List Capacity TOO BIG\n");
    //	if (list->errors & LIST_GRAPH_ERROR)           fprintf(logger, "List Graph Error\n");
    //
    //	fprintf(logger,
    //	"----------END_OF_ERRORS--------\n");
    //}
    //else
    //{
    //	fprintf(logger,
    //	"------------NO_ERRORS----------\n");
    //
    //}
    //
    //fprintf(logger,
    //"=======================================\n\n");
    //
    //num_of_call++;
}
