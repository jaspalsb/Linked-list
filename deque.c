/*********************************************************************
** Author: Jaspal Bainiwal	
** Date: 04/30/2018
** Description: This is the implementation file for the double ended linked lists. 
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dequeHeader.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
* Allocates the list's sentinel and sets the size to 0.
* The sentinel's next and prev should point to the sentinel itself.
*/
static void init(struct CircularList* list)
{
	list->sentinel = (struct Link *)malloc(sizeof(struct Link));
	assert(list->sentinel != 0);

	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	list->size = 0;
}

/**
* Creates a link with the given value and NULL next and prev pointers.
*/
static struct Link* createLink(TYPE value)
{
	struct Link *holder = malloc(sizeof(struct Link));
	//created link with given value
	holder->value = value;
	//setting next and prev now to null
	holder->next = 0;
	holder->prev = 0;
	return holder;
}

/**
* Adds a new link with the given value after the given link and
* increments the list's size.
*/
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	//first step create link
	struct Link *holder = createLink(value);
	//I also want the new link to point next to the given links previous next
	holder->next = link->next;
	//since I want it after the give link I make the new link point to that link
	holder->prev = link;
	//Now I have to make the given link point to the new link [link] ---next> [new link]
	link->next = holder;
	/*now the problem is that the given link that it was point to was also pointing back
	to the give link [given link] <---prev-- [old link] so I need to make the [old link]
	prev point now to the new new link [given link] <---prev [new link] <---- [old link] */
	(link->next)->prev = holder;

	//last thing left is to increase size
	list->size++;

}

/**
* Removes the given link from the list and
* decrements the list's size.
*/
static void removeLink(struct CircularList* list, struct Link* link)
{
	//removing is easy because of links since you just have to make the
	//prev and next point to different links
	/*first I want to get rid of what link was pointing to next and have that next
	point now to what link has had as previous [prev link ] <---[remove link] -> [next link]
													^-----------------------------^*/
	link->next->prev = link->prev;
	//now just do the opposite way its the same but just change the prev for next and vice versa
	link->prev->next = link->next;
	//free that link up
	free(link);
	//last thing decrease size
	list->size--;
}

/**
* Allocates and initializes a list.
*/
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
* Deallocates every link in the list and frees the list pointer.
*/
void circularListDestroy(struct CircularList* list)
{
	//this makes it easy because the removelink function is already written and it deals with the size
	//so I can use the size as base case for while loop

	while (list->size > 0)
	{
		removeLink(list, list->sentinel->next);
	}
	free(list->sentinel);
	free(list);
}

/**
* Adds a new link with the given value to the front of the deque.
*/
void circularListAddFront(struct CircularList* list, TYPE value)
{
	//here the use of the sentinel since it points to next as front saves time so I just call addafter function
	//and pass the parameters. Note not to pass what sentinel points to as next because then calling 
	//the link after function would add it after sentinel->next->new link which was wrong >.<
	addLinkAfter(list, list->sentinel, value);
}

/**
* Adds a new link with the given value to the back of the deque.
*/
void circularListAddBack(struct CircularList* list, TYPE value)
{
	//the sentinel also points to the last item so I can just call the addafter function again
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
* Returns the value of the link at the front of the deque.
*/
TYPE circularListFront(struct CircularList* list)
{
	//returning front just means I need to return the sentinels next
	return list->sentinel->next->value;
}

/**
* Returns the value of the link at the back of the deque.
*/
TYPE circularListBack(struct CircularList* list)
{
	//good thing about pointing sentinel to back I just need to return what sentinel points to last
	return list->sentinel->prev->value;
}

/**
* Removes the link at the front of the deque.
*/
void circularListRemoveFront(struct CircularList* list)
{
	//this easy just call remove function with what the sentinel was pointing to in front
	removeLink(list, list->sentinel->next);

}

/**
* Removes the link at the back of the deque.
*/
void circularListRemoveBack(struct CircularList* list)
{
	//just do opposite of the removefront function since sentinel also pointing to last
	removeLink(list, list->sentinel->prev);
}

/**
* Returns 1 if the deque is empty and 0 otherwise.
*/
int circularListIsEmpty(struct CircularList* list)
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
void circularListPrint(struct CircularList* list)
{
	//re using my code from the linkList.c file
	struct Link *holder;
	holder = list->sentinel->next;
	int _size = list->size;

	for (int index = 0; index < _size; index++)
	{
		printf("%g\n", holder->value);
		holder = holder->next;
	}

}

/**
* Reverses the deque. ran out of time to finish this function.
*/

void circularListReverse(struct CircularList* list)
{
	/*Spent way too much finding the error that I did not have
	time to complete this function. -6 for sure*/
	/*struct Link *sentTemp = list->sentinel;
	struct Link *temp = sentTemp->prev;
	int size = list->size;

	for (int index = 0; index < size; index++)
	{

	}*/

}
