#define magic 0x5f3759df
#define ndiffc .00001f
#include <vector>
#include <algorithm>
#include <deque>
#include <exception>
#include <assert.h>
#include <string>
#include "ops.h"

//const for the invroot function
const float threehalfs = 1.5F;

//column values for shellsort
const int cols[] = {1391376, 463792, 198768, 86961, 33936, 13776, 4592,
                    1968, 861, 336, 112, 48, 21, 7, 3, 1};

//size of the above computed before runtime
const int size = sizeof(cols)/sizeof(int);

/* 
	From The Quake Game Engine
	@param: A number of which you want to take the inverse root of
	@return: returns 1/(num^2) at a much faster speed than normal.
	This function is also considered one because a more accurate
	version is available in this file as invroot2 but it is slightly
	slower. Primarily used for physics and optics.
*/
float invroot1(const float& num)
{
	long point;
	float x2, y;

	x2 = num*.5F;
	y = num;
	point = *(reinterpret_cast<long*>(&y));
	point = magic - (point>>1);
	y = *(reinterpret_cast<float*>(&point));
	y = y * (threehalfs - (x2 *y *y));
	return y;
}

/* 
	From The Quake Game Engine
	@param: A number of which you want to take the inverse root of
	@return: returns 1/(num^2) at a much faster speed than normal.
	This function is also considered two because it is more accurate
	than invroot1 but is slower. Primarily used for physics and optics.
*/
float invroot2(const float& num)
{
	long point;
	float x2, y;

	x2 = num*.5F;
	y = num;
	point = *(reinterpret_cast<long*>(&y)); //Bit operations
	point = magic - (point>>1);
	y = *(reinterpret_cast<float*>(&point));
	y = y * (threehalfs - (x2 *y *y));
	y = y * (threehalfs - (x2 *y *y));
	return y;
}

template<typename T>
int find(std::vector<T> in, T key)
{
	const int n = in.size();
	for(int i = 0; i < n; ++i)
	{
		if(in[0] == key)
			return i;
	}
	return -1;
}

template<typename T>
int binarysearch(std::vector<T> in, T key, const int lo, const int high)
{
	int mid = (lo+high)/2;
	int val = in[mid];

	if(val == key)
		return mid;
	else if(key > val)
		return binarysearch(in, key, mid, high);
	else if(key < val)
		return binarysearch(in, key, lo, mid);
}


/*
	The insertion sort you have come to know
	@param: input will be sorted in ascending order,
	this will not return a new std::vector<T>
	@return: a std::vector<T> sorted in ascending order.
	Note: This method does not swap all values, it simply
	moves up the values that are greater than the index
	for more efficency
*/
template<typename T>
void insertionsort(std::vector<T>& input)
{
	const int n = input.size();
	int key,j;
	for(int i = 1 ; i < n ; ++i)
	{
		key= input[i];
        j = i-1;
        while((j >= 0) && (input[j] > key))
        {
            input[j+1] = input[j];
            j -= 1;
        }
        input[j+1]=key;
	}
}

/*
	The quicksort you have come to know and love
	@param: input needing to be sorted
	@param: lo is the index, inclusive that the sorter
	will start sorting
	@param: hi is the index, INCLUSIVE that the sorter
	will end the sorting
	@return: input will be sorted [lo, hi] inclusive
	in ascending order
*/
template<typename T>
void quicksort(std::vector<T>& input, const int lo, const int hi)
{
	if(lo>=hi)
		return; //Base case
	int mid = input[(lo+hi)/2], i = lo, j = hi, temp;
	while(i<=j)
	{
		while(input[i]<mid) ++i; //close in on values that need to be switched
		while(input[j]>mid) --j;

		if(i<=j) //swap
		{
			temp = input[i];
			input[i] = input[j];
			input[j] = temp;
			++i;
			--j;
		}
	}
		//Next recursive calls
		quicksort(input, lo, j);
		quicksort(input, i, hi);
}


/*
	The heapsort that you have come to know and love
	@param: input an array to be sorted
	@return: input is sorted inclusive
*/
template<typename T>
void heapsort(std::vector<T>& input)
{
	int n = input.size(), temp = 0;
	for(int v = n/2-1; v>=0; v--)
		downheap(input, v, n, temp);
	while(n > 1)
	{
		n--;
		temp = input[0];
		input[0] = input[n];
		input[n] = temp;
		downheap(input, 0, n, temp);
	}

}

/*
	Downheap helper method for heapsort
	@param: input one to be heaped
	@param: v the starting "node" to check
	if heaped or not
	@param: n the original level being decreased
	@param: temp to increase efficency as there is only
	one temp method per call
	@return: input will have the heap property
*/
template<typename T>
void downheap(std::vector<T>& input, int v, const int& n, int& temp)
{
	int w = v*2+1;
	while(w< n)
	{
		if(w+1<n)
			if(input[w+1]>input[w])
				w++;

		if(input[v] >= input[w])
			return;

		temp = input[v];
		input[v] = input[w];
		input[w] = temp;
		v=w;
		w = 2*v+1;
	}
}

/*
	The shellsort that you have come to know and love
	@param: input to be sorted
	@return: input is sorted in ascending order
*/
template<typename T>
void shellsort(std::vector<T>& input)
{
	int i, j, h, v, n = input.size();

	for(int k = 0; k<size; ++k)
	{
		h = cols[k];
		for(i=h; i<n; ++i)
		{
			v=input[i];
			j=i;
			while(j>=h && input[j-h]>v)
			{
				input[j] = input[j-h];
				j-=h;
			}
			input[j] = v;
		}
	}
}


/*
	Splits a string input on a deliminter
	@param: string to be split, will not be destroyed
	@param: delim is the deliminator that the string will
	split on
	@return: vector<string> containing the tokenized strings
*/
std::vector<std::string> split(std::string& in, const char delim)
{
	std::vector<std::string> output;
	std::string temp = "";
	int n = in.size();
	char tmp;
	for(int i = 0; i < n; ++i)
	{
		tmp = in[i];
		if(tmp == delim)
		{
			output.push_back(temp);
			temp.clear();
		}
		else
			temp += tmp;
	}
	output.push_back(temp);
	return output;
}

template<typename T>
void printarr(std::deque<T>&);

/*
	Helper method for evaluate. Catches any exceptions
	and parses tokens.
	@param: token the token to be stringified
	@return: a float that is the number. An assumption is made
	that the user will not put 0 in their evaluation. That is
	why this method should not be a standalone method because of
	that inconsistency.
*/
inline float isNumber(std::string& token)
{
	try{
		return static_cast<float>(::atof(token.c_str()));
	}
	catch(std::exception& e)
	{
		(void)e;
		return 0;
	}
}


/*
	A concrete method to help modularize eval
	@param: output is a stack of LIFO nums
	@param: oper is a stack of LIFO operators
	@param: spot1 a spot to help increase efficency
	@param: spot2 ""		""		""			""
	@return: output will pop the top two elements and apply
	the popped oper operation using spot1 and spot2.
*/
void popandapply(std::deque<float>& output, std::deque<OPS>& oper, float& spot1, float& spot2)
{
	try
	{
		if(isUnary(oper[0]))
		{
			spot1 = output[0];
			output.pop_front();
			output.push_front(applyOppU(spot1, oper[0]));
			oper.pop_front();
		}
		else
		{
			spot1 = output[0];
			output.pop_front();
			spot2 = output[0];
			output.pop_front();	
			output.push_front(applyOpp(spot1, spot2, oper[0]));
			oper.pop_front();
		}
	}
	catch(std::exception& e)
	{
		std::cout<<"Bad Expression!";
		throw e;
	}
}



/*
	Evaluates an expression exp given that each of the char
	acters have spaces in between them, there is only one
	variable, only includes the operations + - * / ^ for the
	time being, and is an accurate mathematical expression.
	Such as ( ( 4 + a ^ 5 ) * ( 3 / 2 ) - 1 ) when a = 3.
	@param: exp is an expression that fits the above criteria
	@param: var is the ONLY variable in the entire expression
	@param: val is the value of the expression when that var=val
	@return: the value of exp, not destroyed, at val
*/
auto eval(std::string& exp, const char var, const float val) -> float
{
	
	std::deque<float> output;
	std::deque<OPS> oper;
	float temp = 0, spot1 = 0, spot2 = 0;
	OPS tmp = ERROR;
	std::vector<std::string> tokens = split(exp, ' ');
	int size = tokens.size();
	std::string hold = "", out = "";
	
	for(int i = 0; i < size; i++)
	{
		hold = tokens[i];
		if((temp = isNumber(hold)) != 0)
		{
			output.push_front(temp);
			continue;
		}
		else if(hold[0] == var)
		{
			output.push_front(val);
			continue;
		}
		else if(hold[0] == 'e')
		{
			output.push_front(2.71828182);
			continue;
		}
		else if(!hold.compare("PI"))
		{
			output.push_front(3.14159265);
			continue;
		}
		else if((tmp = isOperator(hold)) == ERROR)
		{
			std::cout<<"Invalid Operator";
			throw std::runtime_error("Invalid Operator");
		}


		switch(tmp)
		{
		case LEFTP:
			oper.push_front(LEFTP);
			break;
		case RIGHTP:
			while(!oper.empty() && oper[0] != LEFTP)
			{
				popandapply(output, oper, spot1, spot2);
			}
			if(oper.empty())
			{
				std::cout<<"Mismatched Parenths";
				throw std::runtime_error("Mismatched Parenths");
			}
			if(oper[0] == LEFTP)
			{
				oper.pop_front();
			}
			break;
		case HEAVI:
		case SAW:
		case SIGN:
		case SQUARE:
		case TRI:
		case ABS:
		case FLOOR:
		case CEIL:
		case ROUND:
		case LOG10:
		case LN:
		case LB:
		case SIN:
		case COS:
		case TAN:
		case CSC:
		case SEC:
		case COT:
		case SQRT:
		case POWER:
			oper.push_front(tmp);
			break;
		case MODULO:
		case DIVIDE:
		case PLUS:
		case MINUS:
		case MULTIPLY:
			while(!oper.empty() && getPrec(oper[0]) >= getPrec(tmp))
			{
				popandapply(output, oper, spot1, spot2);
			}
			oper.push_front(tmp);
			break;
		default:
			throw std::runtime_error("ERROR, SYMBOL NOT GOOD");
		}
	}

	if(!oper.empty() && oper[0] == LEFTP)
	{
		std::cout<<"Mismatched Parenths";
		throw std::runtime_error("Mismatched Parenths");
	}

	while(!oper.empty())
	{
		popandapply(output, oper, spot1, spot2);
	}
	return output[0];
}

/*
	Evaluates an expression exp given that each of the char
	acters have spaces in between them, there is only one
	variable, only includes the operations + - * / ^ for the
	time being, and is an accurate mathematical expression.
	Such as ( ( 4 + a ^ 5 ) * ( 3 / 2 ) - 1 ) when a = 3.
	@param: exp is an expression that fits the above criteria
	@param: var is the name of EACH variable in the expression
	@param: val is the value of EACH variable in the expression.
	it is assumed that var[i] = val[i] and that they are the same size.
	@return: the value of exp, not destroyed, at val
*/
auto eval2(std::string& exp, std::vector<char>& var, std::vector<float>& val) -> float
{
	const int n = var.size();
	int j;
	if(n == 0 || n != val.size())
		throw new std::runtime_error("Not the same size");
	std::deque<float> output;
	std::deque<OPS> oper;
	float temp = 0, spot1 = 0, spot2 = 0;
	OPS tmp = ERROR;
	std::vector<std::string> tokens = split(exp, ' ');
	int size = tokens.size();
	std::string hold = "", out = "";
	
	for(int i = 0; i < size; i++)
	{
		hold = tokens[i];
		if((temp = isNumber(hold)) != 0)
		{
			output.push_front(temp);
			continue;
		}
		else
		{
			for(j = 0; j < n; ++j)
			{
				if(hold[0] = var[j])
				{
					output.push_front(val[j]);
					break;
				}
			}
			if(j == n)
				continue;
		}
		
		if(hold[0] == 'e')
		{
			output.push_front(2.71828182);
			continue;
		}
		else if(!hold.compare("PI"))
		{
			output.push_front(3.14159265);
			continue;
		}
		else if((tmp = isOperator(hold)) == ERROR)
		{
			std::cout<<"Invalid Operator";
			throw std::runtime_error("Invalid Operator");
		}


		switch(tmp)
		{
		case LEFTP:
			oper.push_front(LEFTP);
			break;
		case RIGHTP:
			while(!oper.empty() && oper[0] != LEFTP)
			{
				popandapply(output, oper, spot1, spot2);
			}
			if(oper.empty())
			{
				std::cout<<"Mismatched Parenths";
				throw std::runtime_error("Mismatched Parenths");
			}
			if(oper[0] == LEFTP)
			{
				oper.pop_front();
			}
			break;
		case HEAVI:
		case SAW:
		case SIGN:
		case SQUARE:
		case TRI:
		case ABS:
		case FLOOR:
		case CEIL:
		case ROUND:
		case LOG10:
		case LN:
		case LB:
		case SIN:
		case COS:
		case TAN:
		case CSC:
		case SEC:
		case COT:
		case SQRT:
		case POWER:
			oper.push_front(tmp);
			break;
		case MODULO:
		case DIVIDE:
		case PLUS:
		case MINUS:
		case MULTIPLY:
			while(!oper.empty() && getPrec(oper[0]) >= getPrec(tmp))
			{
				popandapply(output, oper, spot1, spot2);
			}
			oper.push_front(tmp);
			break;
		default:
			throw std::runtime_error("ERROR, SYMBOL NOT GOOD");
		}
	}

	if(!oper.empty() && oper[0] == LEFTP)
	{
		std::cout<<"Mismatched Parenths";
		throw std::runtime_error("Mismatched Parenths");
	}

	while(!oper.empty())
	{
		popandapply(output, oper, spot1, spot2);
	}
	return output[0];
}


/*
	Computes the standard derivative using the
	(f(x+h)+f(x))/h expression. Highly innaccurate and
	not recommended. The nderivE method is much more
	reliable with the same runtime efficency
	@param: Expression given that each of the char
	acters have spaces in between them, there is only one
	variable, only includes the operations + - * / ^ for the
	time being, and is an accurate mathematical expression.
	Such as ( ( 4 + a ^ 5 ) * ( 3 / 2 ) - 1 ) when a = 3.
	@param: var is the ONLY variable in the entire expression
	@param: val is the value of the expression when that var=val
	@return: the derivative of exp, not destroyed, at val
	Note: The calculus does not have to hold here. The values in the
	immediate area around val have to exist.
*/
float nderivS(std::string& exp,const char var,const float val)
{
	return (eval(exp, var, val+ndiffc) - eval(exp, var, val))/ndiffc;
}

/*
	Computes the derivative using the
	(f(x+h)+f(x-h))/(2*h) expression. Highly accurate and
	recommended. The nderivE method is much more
	reliable with the same runtime efficency
	@param: Expression given that each of the char
	acters have spaces in between them, there is only one
	variable, only includes the operations + - * / ^ for the
	time being, and is an accurate mathematical expression.
	Such as ( ( 4 + a ^ 5 ) * ( 3 / 2 ) - 1 ) when a = 3.
	@param: var is the ONLY variable in the entire expression
	@param: val is the value of the expression when that var=val
	@return: the derivative of exp, not destroyed, at val.
	Note: The calculus does not have to hold here. The values in the
	immediate area around val have to exist.
*/
float nderivE(std::string& exp,const char var,const float val)
{
	return (eval(exp, var, val+ndiffc) - eval(exp, var, val-ndiffc))/(ndiffc*2);
}

/*
	Computes the derivative using the a higher order expression. 
	Most accurate and only recommended when absolute percision, 
	without regards to runtime, is required. The nderivE method 
	is much more reliable with the same runtime efficency
	@param: Expression given that each of the char
	acters have spaces in between them, there is only one
	variable, only includes the operations + - * / ^ for the
	time being, and is an accurate mathematical expression.
	Such as ( ( 4 + a ^ 5 ) * ( 3 / 2 ) - 1 ) when a = 3.
	@param: var is the ONLY variable in the entire expression
	@param: val is the value of the expression when that var=val
	@return: the derivative of exp, not destroyed, at val
	Note: The calculus does not have to hold here. The values in the
	immediate area around val have to exist.
*/
float nderivH(std::string& exp,const char var,const float val)
{
	return (-1*eval(exp, var, val+2*ndiffc) 
		+ 8*eval(exp, var, val+ndiffc)
		- 8*eval(exp, var, val-ndiffc)
		+ eval(exp, var, val-2*ndiffc))/
		(ndiffc*12);
}

/*
	Calculate the numerical integral with percision. The algorithm
	uses simpson's rule, not the 3/8 version, for a continuous function.
	@param: Expression given that each of the char
	acters have spaces in between them, there is only one
	variable, only includes the operations + - * / ^ for the
	time being, and is an accurate mathematical expression.
	Such as ( ( 4 + a ^ 5 ) * ( 3 / 2 ) - 1 ) when a = 3.
	@param: var is the ONLY variable in the entire expression
	@param: a the lower limit of the function
	@param: b is the upper limit of the function
	@return: The integral from a to b of exp dvar.
	Note: The calculus has to hold for this to be true, the function
	must be continuous on [a,b] and differentiable on (a,b)
*/
float fnintSS(std::string& exp,const char var,const float a,const float b)
{
	return ((b-a)/6)
		*(eval(exp, var, a) 
		+ 4*eval(exp, var, (a+b)/2)
		+ eval(exp, var, b));
}

/*
	Calculate the numerical integral with percision. The algorithm
	uses simpson's rule, the 3/8 version, for a continuous function.
	@param: Expression given that each of the char
	acters have spaces in between them, there is only one
	variable, only includes the operations + - * / ^ for the
	time being, and is an accurate mathematical expression.
	Such as ( ( 4 + a ^ 5 ) * ( 3 / 2 ) - 1 ) when a = 3.
	@param: var is the ONLY variable in the entire expression
	@param: a the lower limit of the function
	@param: b is the upper limit of the function
	@return: The integral from a to b of exp dvar.
	Note: The calculus has to hold for this to be true, the function
	must be continuous on [a,b] and differentiable on (a,b)
*/
float fnintSH(std::string& exp,const char var,const float a,const float b)
{
	return ((b-a)/8)
		*(eval(exp, var, a)
		+ 3 * eval(exp, var, (2*a + b)/3) 
		+ 3 * eval(exp, var, (a + 2*b)/3)
		+ eval(exp, var, b));
}

//TBDefined
float eulerMethod(std::string& slope,const char x, const char y, const float x0, const float y0, const float xf, const float stepSize = .1)
{
	if(x0 == xf)
		return y0;
	return 0;
}

float gamma(const float x)
{
	return fnintSH("( ( x ^ ( " + std::to_string(x-1) + " ) ) * e ^ ( -1 * x ) )",
		'x', 0, 99999999);
}

/*
	Helper method for various functions
	and main methods. Prints all the values
	of input with a space
*/
template<typename T>
void printarr(const std::vector<T>& input)
{
	const int n = input.size();
	for(int i = 0; i < n; i++)
	{
		std::cout<<input[i]<<" ";
	}
	std::cout<<"\n";
}

/*
	Helper method for various functions
	and main methods. Prints all the values
	of input with a space
*/
template<typename T>
void printarr(const std::deque<T>& input)
{
	const int n = input.size();
	for(int i = 0; i < n; i++)
	{
		std::cout<<input[i]<<" ";
	}
	std::cout<<"\n";
}


/*
	Helper method for various functions
	and main methods. Prints all the values
	of input with a space. Specialized for strings
	due to compiler errors
*/
void printarr(const std::vector<std::string>& input)
{
	const int n = input.size();
	for(int i = 0; i < n; i++)
	{
		std::cout<<input[i].c_str()<<"\n";
	}
	std::cout<<"\n";
}