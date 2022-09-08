#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include<time.h>
#pragma warning(disable:4996)

struct Item
{
	int val;
	int key;
	struct Item* prev;
	struct Item* next;
};
//Variables
struct Item* head = NULL;
struct Item* tail = NULL;
//Function - Specifications
struct Item* add(int key, int val);
struct Item* search(int key);
void Pop(int key);
void releaseAll();

int main()
{
	int key;
	int keySearch;
	int keyRemove;
	int val;
	int userResponse = 0;
	printf("1.Create Item List\n2.Enter A Key To Find Its Value\n3.Remove an item from the list\n4.Free all allocated memory\n9.exit\n");
	while (userResponse != 9)
	{
		printf("Choose the next action: \n");
		scanf("%d", &userResponse);
		switch (userResponse)
		{
		case 1:
			printf("Enter A Key And Enter A Value \n");
			scanf("%d %d", &key, &val);
			add(key,val);
			break;
		case 2:
			printf("Enter A Key To Find Its Value \n");
			scanf("%d", &keySearch);
			search(keySearch);
			break;
		case 3:
			printf("Remove an item from the list\nEnter a key\n");
			scanf("%d", &keyRemove);
			Pop(keyRemove);
			break;
		case 4:
			printf("Free all allocated memory \n");
			releaseAll();
			break;
		case 9:
			printf("Exit");
			exit(1);
			break;
		default:
			printf("Wrong User Input... Plz Try Again");
			break;
		}
	}
	return 0;
}

struct Item* add(int key, int val)
{
	struct Item* curr = head;
	curr = (struct Item*)malloc(sizeof(struct Item));
	if (!curr)
	{
		printf("Allocating Memory Error");
		return;
	}
	else // Creating LinkedList
	{
		curr->val = val;
		curr->key = key;
		if (!head)
		{
			head = curr;
			tail = curr;
			head->next = NULL;
			head->prev = NULL;
		}
		else
		{
			curr->prev = tail;
			curr->next = NULL;
			tail->next = curr;
			tail = curr;
		}
	}
	
}
struct Item* search(int key)
{
	struct Item* curr = head;
	if (key == curr->key)
	{
		printf("found Item with the same key:\nThe val is: %d\n", curr->val);
		return curr; // found Item with the same key
	}
	else
	{
		while (curr != NULL) // searching item with the same key
		{

			if (key == curr->key)
			{
				printf("found Item with the same key:\nThe val is: %d\n",curr->val);
				return curr; // found Item with the same key
			}

			curr = curr->next;
		}

		printf("The key is not found\n");
		return curr;
	}
	
}
void Pop(int key)
{
	struct Item* removeItem = search(key);
	if (removeItem == NULL)
	{
		printf("The item was not found\n");
		return;
	}
	else
	{
		if (removeItem->prev == NULL && removeItem->next == NULL)
		{
			printf("The item is removed!\n");
			head = NULL;
			tail = NULL;
			free(removeItem);
		}
		else if (removeItem->next != NULL && removeItem->prev != NULL)
		{
			printf("The item is removed!\n");
			removeItem->prev->next = removeItem->next;
			removeItem->next->prev = removeItem->prev;
			free(removeItem);
		}
		else if (removeItem->prev == NULL && removeItem->next != NULL)
		{
			removeItem->next->prev = NULL;
			head = removeItem->next;
			free(removeItem);
		}
		else
		{
			printf("The item is removed!\n");
			removeItem->prev->next = NULL;
			tail = removeItem->prev;
			free(removeItem);
		}
		
	}
}
void releaseAll()
{
	struct Item* curr = head;
	struct Item* release = NULL;
	while (curr != NULL)
	{
		release = curr;
		curr = curr->next;
		free(release);
	}
}
