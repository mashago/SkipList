
#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SkipList.h"

SkipList::SkipList(int ml) : curLevel(0), maxLevel(ml<=1?1:ml), header(NULL)
{
	srand(time(NULL));
	header = createNode(maxLevel - 1, 0, 0);
	for (int i = 0; i < maxLevel; i++)
	{
		header->forward[i] = NULL;
	}
}

SkipList::~SkipList()
{
	ListNode *p = header;
	while (p)
	{
		ListNode *next = p->forward[0];
		free(p);
		p = next;
	}
}

bool SkipList::Insert(int key, int value)
{
	// 1. from curLevel to 0 level, get <key position, and save the position to array
	// 2. check if key already in list, if exists, return false
	// 3. random a new level x. if x > curLevel, update [curLevel, x] position array
	// 4. create new node
	// 5. insert node into level [0, x] position array forward position
	
	ListNode *update[maxLevel];
	ListNode *p = header, *q = NULL;

	// 1.
	for (int i = curLevel; i >= 0; i--)
	{
		while ((q = p->forward[i]) && (q->key < key))
		{
			p = q;
		}
		update[i] = p;
	}

	// 2.
	if (q && q->key == key)
	{
		return false;
	}

	// 3.
	int x = randomLevel();
	// printf("x=%d\n", x);
	if (x > curLevel)
	{
		for (int i = curLevel+1; i <= x; i++)
		{
			update[i] = header;
		}
		curLevel = x;
	}

	// 4.
	q = createNode(x, key, value);

	// 5.
	for (int i = 0; i <= x; i++)
	{
		q->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = q;
	}
	return true;
}

bool SkipList::Delete(int key)
{
	// 1. from high level to 0 level, get <key position, and save the position to array
	// 2. if node null or node key not match, return false. node should be in header->forward[0] list
	// 3. check every level position array if forward node is target node, and skip that node
	// 4. free target node
	// 5. reset curLevel
	
	ListNode *update[maxLevel];
	ListNode *p = header, *q = NULL;

	// 1.
	for (int i = curLevel; i >= 0; i--)
	{
		while ((q = p->forward[i]) && (q->key < key))
		{
			p = q;
		}
		update[i] = p;
	}

	// 2.
	if (q == NULL || q->key != key)
	{
		return false;
	}
	// printf("q->key=%d\n", q->key);

	// 3.
	for (int i = 0; i <= curLevel; i++)
	{
		if (update[i]->forward[i] == q)
		{
			update[i]->forward[i] = q->forward[i];
		}
	}

	// 4.
	free(q);

	// 5.
	for (int i = curLevel; i >= 1; i--)
	{
		if (header->forward[i] == NULL)
		{
			curLevel--;
		}
	}

	return true;
}

int SkipList::Search(int key)
{
	// 1. search from curLevel to 0 level, find if has <=key, if not exists, goto lower level
	// 2. if key match, return value
	// 3. else, list forward
	
	ListNode *p = header, *q = NULL;
	for (int i = curLevel; i >= 0; i--)
	{
		while ((q = p->forward[i]) && (q->key <= key))
		{
			if (q->key == key)
			{
				return q->value;
			}
			p = q;
		}
	}

	return 0;
}

void SkipList::Print()
{
	printf("maxLevel=%d curLevel=%d\n", maxLevel, curLevel);
	for (int i = curLevel; i >= 0; i--)
	{
		ListNode *p = header, *q = NULL;
		printf("[%d][%d] -> ", p->key, p->value);
		while ((q = p->forward[i]) != NULL)
		{
			printf("[%d][%d] -> ", q->key, q->value);
			p = q;
		}
		printf("\n");
	}
	printf("\n");
}

int SkipList::randomLevel()
{
	// [0, maxLevel)
	int k = 0;
	while (rand() % 2)
	{
		k++;
	}
	k = (k < maxLevel ? k : maxLevel-1);
	return k;
}

SkipList::ListNode *SkipList::createNode(int level, int key, int value)
{
	int size = sizeof(ListNode) + level * sizeof(ListNode *);
	ListNode *node = (ListNode *)malloc(size);
	node->key = key;
	node->value = value;
	return node;
}

