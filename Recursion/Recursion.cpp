#include "stdafx.h"
#include "Recursion.h"
#include <iostream>
#include <cstdlib>
#define getmax(a,b) a > b ? a : b
typedef const int* intpoint;
typedef const char* charpoint;
typedef unsigned char* uchar;

Recursion::Recursion(void)
{
}


Recursion::~Recursion(void)
{
}

int Recursion::fib(intpoint n)
{
	if(*n <= 1)
		return 1;
	else
		return fib(n-1) + fib(n-2);
}
int Recursion::fib(int n)
{
	if(n <= 1)
		return 1;
	else
		return fib(n-1) + fib(n-2);
}

void Recursion::printFib(intpoint LIMIT)
{
	using std::cout;
	using std::endl;
	long double* fast = new long double[*LIMIT];
	fast[0] = 1;
	fast[1] = 1;
	cout << 0 << "\t" << fast[0] << endl;
	cout << 1 << "\t" << fast[1] << endl;

	for(int i = 2; i < *LIMIT; i++)
	{
		fast[i] = fast[i-1] + fast[i-2];
		cout << i << "\t" << fast[i] << endl;
	}

	delete[] fast;

}

void Recursion::printFib(int LIMIT)
{
	using std::cout;
	using std::endl;
	long double* fast = new long double[LIMIT];
	fast[0] = 1;
	fast[1] = 1;
	cout << 0 << "\t" << fast[0] << endl;
	cout << 1 << "\t" << fast[1] << endl;

	for(int i = 2; i < LIMIT; i++)
	{
		fast[i] = fast[i-1] + fast[i-2];
		cout << i << "\t" << fast[i] << endl;
	}

	delete[] fast;

}

/**
	 * Divides two integers and returns the
	 * int[] = {Quotient, Remainder}
	 * 
	 * @param x
	 *            the x is any number
	 * @param y
	 *            the y is a number >= 1
	 * @return the int[] = {Quotient, Remainder}
	 */
int* Recursion::divide(int x, int y)
{
	int* output = new int[2];
	output[0] = 0;
	output[1] = 0;

	if(x == 0)
		return output;
	output = divide(x/2, y);
	output[0] *= 2;
	output[1] *= 2;

	if(x % 2 == 1)
			output[1]++;
	if(output[1] >= y)
	{
		output[0]++;
		output[1] -= y;
	}
		
	return output;
}

int* Recursion::divide(intpoint x, intpoint y)
{
	int* output = new int[2];
	output[0] = 0;
	output[1] = 0;

	if(*x == 0)
		return output;
	output = divide(*x/2, *y);
	output[0] *= 2;
	output[1] *= 2;

	if(*x % 2 == 1)
			output[1]++;
	if(output[1] >= *y)
	{
		output[0]++;
		output[1] -= *y;
	}
		
	return output;
}

/**
	 * Modular Exponentiation
	 * 
	 * @param x
	 *            the x is the integer base
	 * @param y
	 *            the y is the integer power
	 * @param N
	 *            the N is the integer modulous
	 * @return the int returned is x^y % N with increased running time
	 */
	int Recursion::modExp(int x, int y, int N)
	{
		
		if(y == 0)
			return 1;
		
		int a = modExp(x, y/2, N);
		
		if(y % 2 == 0)
			return a*a % N;
		else
			return x*a*a % N;
	}

	int Recursion::modExp(intpoint x, intpoint y,intpoint N)
	{
		
		if(*y == 0)
			return 1;
		
		int a = modExp(*x, *y/2, *N);
		
		if(*y % 2 == 0)
			return a*a % *N;
		else
			return *x*a*a % *N;
	}

	/**
	 * Greatest Common Factor
	 * 
	 * @param x
	 *            the x is one integer
	 * @param y
	 *            the y is another integer
	 * @return the int is the Greatest Common Factor of x and y
	 */
	int Recursion::gcf(int x, int y)
	{
		if(y == 0)
			return x;
		else
			return gcf(y, x%y);
	}

	int Recursion::gcf(intpoint x, intpoint y)
	{
		if(*y == 0)
			return *x;
		else
			return gcf(*y, *x%*y);
	}

	/**
	 * Primality test.
	 * 
	 * @param N
	 *            the N is a prime number of with which to test whether it is prime or nor
	 * @return true if prime. There is a 2^-100 chance that the answer will be wrong, 
	 * and that is astronomically improbable
	 */
	bool Recursion::isPrime(int N)
	{	
		for(int i = 0; i <= 100; i++)
		{
			if(Recursion::modExp(rand() % (N - 1) + 1, N-1, N) != 1)
				return false;
		}
		
		return true;
	}

	bool Recursion::isPrime(int* N)
	{	
		for(int i = 0; i <= 100; i++)
		{
			if(Recursion::modExp(rand() % (*N - 1) + 1, *N-1, *N) != 1)
				return false;
		}
		
		return true;
	}
	
	/**
	 * One time pad encode.
	 * 
	 * @param message
	 *            the message is an integer to be encoded
	 * @param key
	 *            the key
	 * @return the int
	 */
	int Recursion::oneTimePadEncode(int message, int key)
	{
		return message^key;
	}
	
	void Recursion::oneTimePadEncode(int* message, int* key)
	{
		*message = *message^*key;
	}

	void Recursion::oneTimePadDecode(int* message, int* key)
	{
		*message = *message^*key;
	}
	int Recursion::oneTimePadDecode(int message, int key)
	{
		return message^key;
	}

	uchar Recursion::karatsubaMultiply(charpoint binary1, charpoint binary2)
	{
		int len1 = sizeof(binary1);
		return NULL;
	}