#include <iostream>
#include <string>

//Enum to speed up the checking process. OPS->Operator
enum OPS{PLUS, MINUS, MULTIPLY, 
	DIVIDE, POWER, MODULO, 
	LEFTP, RIGHTP, ERROR,
	SIN, COS, TAN,
	CSC, SEC, COT,
	LOG10, LB, LN,
	SQRT, HEAVI,
	ABS, FLOOR, CEIL, ROUND,
	SAW, SIGN, SQUARE, TRI};

double round(const float& a)
{
	return static_cast<int>(a+.5);
}

double sign(const float& a)
{
	if(a<0)
		return -1;
	return 1;
}

double heaviside(const float& a)
{
	if(a<0)
		return 0;
	return 1;
}

/*
	Takes the tokens inside and returns an enum
	from OPS.
	@param: token to be OPS
	@return: an OPS value
*/
OPS isOperator(const std::string& token)
{
	if(!token.compare("+"))
		return PLUS;
	else if(!token.compare("-"))
		return MINUS;
	else if(!token.compare("*"))
		return MULTIPLY;
	else if(!token.compare("/"))
		return DIVIDE;
	else if(!token.compare("^"))
		return POWER;
	else if(!token.compare("^"))
		return POWER;
	else if(!token.compare("("))
		return LEFTP;
	else if(!token.compare(")"))
		return RIGHTP;
	else if(!token.compare("%"))
		return MODULO;
	else if(!token.compare("sqrt"))
		return SQRT;
	else if(!token.compare("sin"))
		return SIN;
	else if(!token.compare("cos"))
		return COS;
	else if(!token.compare("tan"))
		return TAN;
	else if(!token.compare("csc"))
		return CSC;
	else if(!token.compare("sec"))
		return SEC;
	else if(!token.compare("cot"))
		return COT;
	else if(!token.compare("log"))
		return LOG10;
	else if(!token.compare("lb"))
		return LB;
	else if(!token.compare("ln"))
		return LN;
	else if(!token.compare("abs"))
		return ABS;
	else if(!token.compare("floor"))
		return FLOOR;
	else if(!token.compare("ceil"))
		return CEIL;
	else if(!token.compare("round"))
		return ROUND;
	else if(!token.compare("saw"))
		return SAW;
	else if(!token.compare("sign"))
		return SIGN;
	else if(!token.compare("square"))
		return SQUARE;
	else if(!token.compare("tri"))
		return TRI;
	else if(!token.compare("heaviside"))
		return HEAVI;
	else 
		return ERROR;
}

/*
	Take your OPS and convert it to a string.
	TO BE implemented in a method that converts
	an infix operators to postfix or RPN operators
	as a string. In the meantime,
	@param: op to turn into a string, will not be
	destroyed though.
	@return: A string containing the operation to be applied
*/
std::string toStr(const OPS op)
{
	switch(op)
	{
	case MULTIPLY:
		return "*";
	case POWER:
		return "^";
	case DIVIDE:
		return "/";
	case PLUS:
		return "+";
	case MINUS:
		return "-";
	case MODULO:
		return "&";
	case SQRT:
		return "sqrt";
	case SIN:
		return "sin";
	case COS:
		return "cos";
	case TAN:
		return "tan";
	case CSC:
		return "csc";
	case SEC:
		return "sec";
	case COT:
		return "cot";
	case LOG10:
		return "log";
	case LB:
		return "ln";
	case LN:
		return "lb";
	case ABS:
		return "abs";
	case FLOOR:
		return "floor";
	case CEIL:
		return "ceil";
	case ROUND:
		return "round";
	case SAW:
		return "saw";
	case SIGN:
		return "sign";
	case SQUARE:
		return "square";
	case TRI:
		return "triangle";
	case HEAVI:
		return "heaviside";
	case LEFTP:
		return "(";
	case RIGHTP:
		return ")";
	}
	return "UND";
}

/*
	Returns the precedence of an operator in the function
	@param: op to be characterized. Will not be destroyed
	@return: a Number from 4-2 Indicating the importance
	TO DO: Will be changed in the future as more functions
	are added.
*/
int getPrec(const OPS& op)
{
	switch(op)
	{
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
		return 4;
	case MODULO:
	case MULTIPLY:
	case DIVIDE:
		return 3;
	case PLUS:
	case MINUS:
		return 2;
	default:
		return NULL;
	}
}

bool isUnary(const OPS& op)
{
	return op == SIN ||
		op == COS ||
		op == TAN ||
		op == SQRT ||
		op == CSC ||
		op == SEC ||
		op == COT ||
		op == LOG10 ||
		op == LN ||
		op == LB ||
		op == ABS ||
		op == CEIL ||
		op == ROUND ||
		op == FLOOR ||
		op == SAW ||
		op == SIGN ||
		op == SQUARE ||
		op == TRI ||
		op == HEAVI;
}

/*
	Helper method for Eval, applies operation op to a1 and a2.
	@params: To be operated on, will not be destroyed
	@return: value of the operation on the two
*/
float applyOpp(const float& a1,const float& a2,const OPS& op)
{
	switch(op)
	{
	case POWER:
		return std::pow(a2, a1); //Has to be operated like this because of how
								 //the operators in eval are popped
	case MULTIPLY:
		return a2*a1;
	case DIVIDE:
		try{
		return a2/a1; //same
		}
		catch(std::exception& e)
		{
			std::cout<<"Bad input"; //no division by zero
			throw e;
		}
	case PLUS:
		return a2+a1;
	case MINUS:
		return a2-a1;
	case MODULO:
		try{
		return fmod(a2, a1);
		}
		catch(std::exception& e)
		{
			std::cout<<"Bad input"; //no division by zero
			throw e;
		}
	default:
		return 0;
	}
}

float applyOppU(const float& a1, const OPS& op)
{
	switch(op)
	{
	case SIN:
		return static_cast<float>(sin(a1));
	case COS:
		return static_cast<float>(cos(a1));
	case TAN:
		return static_cast<float>(tan(a1));
	case CSC:
		return static_cast<float>(1/sin(a1));
	case SEC:
		return static_cast<float>(1/cos(a1));
	case COT:
		return static_cast<float>(1/tan(a1));
	case SQRT:
		return static_cast<float>(sqrt(a1));
	case LOG10:
		return static_cast<float>(log(a1));
	case LN:
		return static_cast<float>(log(a1)/log(2.71828182845));
	case LB:
		return static_cast<float>(log(a1)/log(2));
	case ABS:
		return static_cast<float>(abs(a1));
	case CEIL:
		return static_cast<float>(ceil(a1));
	case FLOOR:
		return static_cast<float>(floor(a1));
	case ROUND:
		return static_cast<float>(round(a1));
	case SAW:
		return static_cast<float>(a1-floor(a1));
	case SIGN:
		return static_cast<float>(sign(a1));
	case SQUARE:
		return static_cast<float>(sign(sin(a1)));
	case TRI:
		return static_cast<float>(2*a1-floor(a1+.5)*pow(-1, floor(a1+.5)));
	case HEAVI:
		return static_cast<float>(heaviside(a1));
	default:
		return NULL;
	}
}