
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <map>
#include <vector>
// #include <random>
// #include <utility>
// #include <algorithm>

#include "SkipList.h"

template <class T>
void shuffle_vec(std::vector<T> &vec)
{
	srand(time(NULL));
	int size = vec.size();
	for (int i = 0; i < size - 1; i++)
	{
		int pos = rand() % (size - i) + i;
		T tmp = vec[i];	
		vec[i] = vec[pos];
		vec[pos] = tmp;
	}
}

typedef std::map<int, int>::iterator mapiter;
typedef std::vector<std::pair<int, int> >::iterator veciter;

int main(int argc, char **argv)
{
	printf("hello %s\n", argv[0]);

	std::map<int, int> tmpMap;
	std::vector<std::pair<int, int> > tmpVec;
	
	enum { MAX_NUM = 100000 };
	int MAX_LEVEL = 1;
	int num = 1;
	while (num < MAX_NUM)
	{
		num = num << 1;
		MAX_LEVEL++;
	}
	printf("MAX_NUM=%d MAX_LEVEL=%d\n", MAX_NUM, MAX_LEVEL);

	for (int i = 1; i <= MAX_NUM; i++)
	{
		int key = i;
		int value = i;
		tmpMap[key] = value;
	}

	for (mapiter iter = tmpMap.begin(); iter != tmpMap.end(); iter++)
	{
		tmpVec.push_back(std::make_pair(iter->first, iter->second));
	}

	SkipList sl(MAX_LEVEL);
	bool bSuccess = true;

	struct timeval startTime;
	struct timeval endTime;
	double diff;

	{
	// insert
	bSuccess = true;
	// std::shuffle(tmpVec.begin(), tmpVec.end(), std::default_random_engine(time(NULL)));
	shuffle_vec(tmpVec);
	gettimeofday(&startTime,NULL);
	for (veciter iter = tmpVec.begin(); iter != tmpVec.end(); iter++)
	{
		// printf("k=[%d] v=[%d]\n", iter->first, iter->second);
		bSuccess = sl.Insert(iter->first, iter->second);
		if (!bSuccess)
		{
			printf("insert error key=%d value=%d\n", iter->first, iter->second);
			break;
		}
		// sl.Print();
		// printf("\n");
	}
	if (!bSuccess)
	{
		return 0;
	}
	gettimeofday(&endTime,NULL);
	diff = ((double)endTime.tv_sec-startTime.tv_sec) * 1000 + ((double)endTime.tv_usec-startTime.tv_usec) / 1000;
	printf("insert success, cost %lfms\n",diff);
	// sl.Print();
	}

	/*
	{
	// insert again
	int counter = 0;
	bSuccess = true;
	// std::shuffle(tmpVec.begin(), tmpVec.end(), std::default_random_engine(time(NULL)));
	shuffle_vec(tmpVec);
	gettimeofday(&startTime,NULL);
	for (veciter iter = tmpVec.begin(); iter != tmpVec.end(); iter++)
	{
		// printf("k=[%d] v=[%d]\n", iter->first, iter->second);
		bSuccess = sl.Insert(iter->first, iter->second);
		if (bSuccess)
		{
			printf("insert again error key=%d value=%d\n", iter->first, iter->second);
			break;
		}
		counter++;
		// sl.Print();
		// printf("\n");
	}
	if (bSuccess)
	{
		return 0;
	}
	gettimeofday(&endTime,NULL);
	diff = ((double)endTime.tv_sec-startTime.tv_sec) * 1000 + ((double)endTime.tv_usec-startTime.tv_usec) / 1000;
	printf("insert again %d success, cost %lfms\n", counter, diff);
	// sl.Print();
	}
	*/

	{
	// search
	bSuccess = true;
	gettimeofday(&startTime,NULL);
	for (int i = 1; i <= MAX_NUM; i++)
	{
		int value = sl.Search(i);
		if (value == 0)
		{
			printf("search error key=%d\n", i);
			bSuccess = false;
			break;
		}
	}
	if (!bSuccess)
	{
		return 0;
	}
	gettimeofday(&endTime,NULL);
	diff = ((double)endTime.tv_sec-startTime.tv_sec) * 1000 + ((double)endTime.tv_usec-startTime.tv_usec) / 1000;
	printf("search success, cost %lfms\n",diff);
	}

	{
	// delete
	bSuccess = true;
	// std::shuffle(tmpVec.begin(), tmpVec.end(), std::default_random_engine(time(NULL)));
	shuffle_vec(tmpVec);
	gettimeofday(&startTime,NULL);
	for (veciter iter = tmpVec.begin(); iter != tmpVec.end(); iter++)
	{
		// printf("k=[%d]\n", iter->first);
		bSuccess = sl.Delete(iter->first);
		if (!bSuccess)
		{
			printf("delete error key=%d\n", iter->first);
			break;
		}
	}
	if (!bSuccess)
	{
		return 0;
	}
	gettimeofday(&endTime,NULL);
	diff = ((double)endTime.tv_sec-startTime.tv_sec) * 1000 + ((double)endTime.tv_usec-startTime.tv_usec) / 1000;
	printf("delete success, cost %lfms\n",diff);
	// sl.Print();
	}

	/*
	{
	// delete again
	bSuccess = true;
	// std::shuffle(tmpVec.begin(), tmpVec.end(), std::default_random_engine(time(NULL)));
	shuffle_vec(tmpVec);
	gettimeofday(&startTime,NULL);
	for (veciter iter = tmpVec.begin(); iter != tmpVec.end(); iter++)
	{
		// printf("k=[%d]\n", iter->first);
		bSuccess = sl.Delete(iter->first);
		if (bSuccess)
		{
			printf("delete again error key=%d\n", iter->first);
			break;
		}
	}
	if (bSuccess)
	{
		return 0;
	}
	gettimeofday(&endTime,NULL);
	diff = ((double)endTime.tv_sec-startTime.tv_sec) * 1000 + ((double)endTime.tv_usec-startTime.tv_usec) / 1000;
	printf("delete again success, cost %lfms\n",diff);
	// sl.Print();
	}
	*/

	return 0;
}
