/*********************************************************************
** Author: Jaspal Bainiwal	
** Date: 04/30/2018
** Description: This is the implementation for the data structure linked list
*********************************************************************/
#include "linkedHeader.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
* Allocates the list's sentinel and sets the size to 0.
* The sentinels' next and prev should point to eachother or NULL
* as appropriate.
*/
static void init(struct LinkedList* list) {
	list->frontSentinel = malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);

	list->backSentinel = malloc(sizeof(struct Link));
	/*[front] <----------list --------->[back]*/
	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
	list->size = 0;
}

/**
* Adds a new link with the given value before the given link and
* increments the list's size.
*/
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	struct Link *holder = (struct Link *) malloc(sizeof(struct Link));
	assert(holder != 0);
	holder->next = link;
	holder->prev = link->prev;
	holder->value = value;

	link->prev->next = holder;
	link->prev = holder;

	list->size++;

}

/**
* Removes the given link from the list and
* decrements the list's size.
*/
static void removeLink(struct LinkedList* list, struct Link* link)
{
	link->next->prev = link->prev;
	link->prev->next = link->next;

	free(link);
	link = 0;

	list->size--;
}

/**
* Allocates and initializes a list.
*/
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
* Deallocates every link in the list including the sentinels,
* and frees the list itself.
*/
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
* Adds a new link with the given value to the front of the deque.
*/
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	/*Now with sentinel thank you sentinel I save time cuz of you */
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
* Adds a new link with the given value to the back of the deque.
*/
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list->backSentinel, value);
}

/**
* Returns the value of the link at the front of the deque.
*/
TYPE linkedListFront(struct LinkedList* list)
{
	return list->frontSentinel->next->value;
}

/**
* Returns the value of the link at the back of the deque.
*/
TYPE linkedListBack(struct LinkedList* list)
{
	return list->backSentinel->prev->value;
}

/**
* Removes the link at the front of the deque.
*/
void linkedListRemoveFront(struct LinkedList* list)
{
	removeLink(list, list->frontSentinel->next);
}

/**
* Removes the link at the back of the deque.
*/
void linkedListRemoveBack(struct LinkedList* list)
{
	removeLink(list, list->backSentinel->prev);
}

/**
* Returns 1 if the deque is empty and 0 otherwise.
*/
int linkedListIsEmpty(struct LinkedList* list)
{
	if (list->size == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
* Prints the values of the links in the deque from front to back.
*/
void linkedListPrint(struct LinkedList* list)
{
	struct Link *holder;
	holder = list->frontSentinel->next;
	int _size = list->size;

	for (int index = 0; index < _size; index++)
	{
		printf("%d \n", holder->value);
		holder = holder->next;
	}
}

/**
* Adds a link with the given value to the bag.
*/
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list->backSentinel, value);
}

/**
* Returns 1 if a link with the value is in the bag and 0 otherwise.
*/
int linkedListContains(struct LinkedList* list, TYPE value)
{
	struct Link *holder;
	holder = list->frontSentinel->next;
	int contain = 0;

	while ((holder != list->backSentinel) && (contain == 0))
	{
		if (EQ(holder->value, value))
		{
			contain = 1;
		}
		else
		{
			holder = holder->next;
		}
	}
	return contain;
}

/**
* Removes the first occurrence of a link with the given value.
*/
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	struct Link *holder;
	holder = list->frontSentinel->next;
	int contain = 0;

	while ((holder != list->backSentinel) && (contain == 0))
	{
		if (EQ(holder->value, value))
		{
			contain = 1;
		}
		else
		{
			holder = holder->next;
		}
	}
	removeLink(list, holder);

}
