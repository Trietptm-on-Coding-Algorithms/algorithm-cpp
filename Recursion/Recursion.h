#pragma once
typedef const int* intpoint;
typedef const char* charpoint;
typedef unsigned char* uchar;
class Recursion
{
public:
	Recursion(void);
	static int fib(intpoint);
	static int fib(int);
	static void printFib(int);
	static void printFib(intpoint);
	static int* divide(int, int);
	static int* divide(intpoint, intpoint);
	static int modExp(int, int, int);
	static int modExp(intpoint, intpoint, intpoint);
	static int gcf(int, int);
	static int gcf(intpoint, intpoint);
	static bool isPrime(int);
	static bool isPrime(int*);
	static int oneTimePadEncode(int, int);
	static int oneTimePadDecode(int, int);
	static void oneTimePadEncode(int*, int*);
	static void oneTimePadDecode(int*, int*);
	static uchar karatsubaMultiply(uchar, uchar);
	~Recursion(void);
};

