#pragma once
#include <stdbool.h>

typedef void* LIST_DATA_TYPE;

typedef struct Link_t {
	LIST_DATA_TYPE value;
	struct Link_t* next;
} Link;

typedef Link* LinkedList;

typedef enum { SUCCESS, ALLOC_FAIL, NO_SUCH_ELEMENT, INVALID_PARAM, NOT_IMPLEMENTED } List_ErrorCodes;


LinkedList List_Create();

List_ErrorCodes List_Find(Link* anchor, LIST_DATA_TYPE valueToFind, Link** link);

List_ErrorCodes List_FindPrev(Link* anchor, Link* link, Link** prev);

/// <summary>
/// Retrieves a pointer to the last link in the list.
/// </summary>
/// <param name="anchor">List Anchor</param>
/// <param name="lastLink"> Output Parameter: pointer to last link.</param>
/// <returns>If list is empty (has only anchor) - returns NO_SUCH_ELEMENT. 
/// Otherwise returns SUCCESS</returns>
List_ErrorCodes List_LastLink(Link* anchor, Link** lastLink);

List_ErrorCodes List_Remove(Link* anchor, Link* linkToRemove, bool isToFree);

/// <summary>
/// Frees all links in the list, including the Anchor (Hint: with List_Remove).
/// </summary>
void List_Free(Link* anchor);

/// <summary>
/// Returns number of links in the list (that have actual values, not the anchor).
/// </summary>
size_t List_Length(Link* anchor);

/// <summary>
/// Inserts a new link into the list (allocates it inside), with given value,
/// right after the anchor.
/// </summary>
List_ErrorCodes List_Insert(Link* anchor, LIST_DATA_TYPE value);

/// <summary>
/// Sorts the list in Ascending Order. 
/// For example: List: 12, 5, 7, 10, 1, 160 
/// When arranged in ascending order, would be: 1, 5, 7, 10, 12, 160.
/// </summary>
/// <param name="anchor">List Anchor</param>
/// <returns></returns>
List_ErrorCodes List_Sort(Link* anchor);

typedef void (*link_printer)(LIST_DATA_TYPE value);
/// <summary>
/// Debug Utility: Prints list to the console.
/// </summary>
void List_Print(Link* anchor, link_printer printer);

/// <summary>
/// Test Utility: Converts list into an array (allocates array inside)
/// </summary>
/// <param name="anchor"> List anchor </param>
/// <param name="outArray"> OUTPUT (allocated inside) array. should be freed with free(.)</param>
/// <param name="outArraySize"> OUTPUT size of allocated array.</param>
/// <returns>SUCCESS if all went well. otherwise can return ALLOC_FAIL.
/// If length of list is zero, outArray returns NULL and outArraySize = 0</returns>
List_ErrorCodes List_ToArray(Link* anchor, LIST_DATA_TYPE** outArray, size_t* outArraySize);
