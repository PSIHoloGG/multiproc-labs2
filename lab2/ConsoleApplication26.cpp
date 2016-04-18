//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;

long *arr;

struct LoopSettings
{
	long start;
	long limit;
	long sum;
};

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	LoopSettings *settings = (LoopSettings*)lpParameter;
	
	settings->sum = 0;
	for(long i = settings->start; i < settings->limit; i++)
	{
		settings->sum += arr[i];
	}

	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{

	long size = 10;
	arr = new long[size];

	for(long i=0; i<size; i++)
	{
		arr[i] = i;		
	}

	LoopSettings loop1;
	loop1.start = 0;
	loop1.limit = size/2;
	
	LoopSettings loop2;
	loop2.start = size/2;
	loop2.limit = size;

	HANDLE hThreads[2];
	hThreads[0] = CreateThread(NULL, NULL, ThreadProc, &loop1, 0, 0);
	hThreads[1] = CreateThread(NULL, NULL, ThreadProc, &loop2, 0, 0);

	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

	cout << "sum is " << loop1.sum + loop2.sum;

	delete[] arr;
	printf("\nPress any key");
	getchar();

	return 0;
}