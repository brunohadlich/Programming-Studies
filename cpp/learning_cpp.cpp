#include <iostream>
#include <string>
#include <sstream>

using namespace std;

inline string concatenate_inline(string a, string b)
{
	return a + b;
}

string concatenate(string a, string b)
{
	return a + b;
}

inline string concatenate_using_address_inline(const string& a, const string& b)
{
	return a + b;
}

string concatenate_using_address(const string& a, const string& b)
{
	return a + b;
}

int divide_with_default(int a, int b = 2)
{
	return a / b;
}

void protofunction (int first, int second);
int protofunction_with_no_name (int, int = 2);
double divide(double a, double b);
int divide(int a, int b);
long factorial(long number);
template<typename SomeType>
SomeType multiply(SomeType a, SomeType b);

template<typename T, int N>
T sum(T);

int main()
{
	cout << "Hello world!" << endl;

	//Fundamental types

	//Character types

	char _char;			//Exactly one byte in size. At least 8 bits.
	char16_t _char16_t;	//Not smaller than char. At least 16 bits.
	char32_t _char32_t;	//Not smaller than char16_t. At least 32 bits.
	wchar_t _wchar_t;	//Can represent the largest supported character set.

	//Integer types(signed)

	signed char _signed_char;					//Same size as char. At least 8 bits.
	signed short int _signed_short_int;			//Not smaller than char. At least 16 bits. short = signed short int = short int = signed short
	signed int _signed_int;						//Not smaller than short. At least 16 bits. int = signed int
	signed long int _signed_long_int;			//Not smaller than int. At least 32 bits. long = signed long int = long int = signed long
	signed long long int _signed_long_long_int;	//Not smaller than long. At least 64 bits. long long = long long int = signed long long

	//Integer types (unsigned)

	unsigned char _unsigned_char;					//(same size as their signed counterparts)
	unsigned short int _unsigned_short_int;			//(same size as their signed counterparts)
	unsigned int _unsigned_int;						//(same size as their signed counterparts)
	unsigned long int _unsigned_long_int;			//(same size as their signed counterparts)
	unsigned long long int _unsigned_long_long_int;	//(same size as their signed counterparts)

	//Floating-point types

	float _float;
	double _double;				//Precision not less than float
	long double _long_double;	//Precision not less than double

	//Boolean type

	bool _bool;

	//Void type

	//void _void;	//no storage

	//Null pointer

	decltype(nullptr)	_decltype(nullptr);

	//Declaration

	int a;
	int b;
	int c,d,e;

	//Initialization

	a = 5;
	int f(4);
	int g{2};

	//Type deduction

	auto h = g;//h gets g type
	decltype(h) i;//i gets h type

	a = 2;		//Decimal
	b = 07;		//Octal
	c = 0xF5F;	//Hexadecimal

	d = 5;		//int
	d = 5u;		//unsigned int
	d = 5U;		//unsigned int
	d = 5l;		//long
	d = 5L;		//long
	d = 5ul;	//unsigned long
	d = 5lu;	//unsigned long

	float j = 3.14159;	//3.14159
	j = 6.02e23;		//6.02 x 10^23
	j = 1.6e-19;		//1.6 x 10^-19
	j = 3.0;			//3.0

	float k = 6.02e23f;	//float
	k = 6.02e23F;		//float

	double l = 6.02e23l;//long double
	l = 6.02e23L;		//long double

	/*
	Escape code	Description
	\n	newline
	\r	carriage return
	\t	tab
	\v	vertical tab
	\b	backspace
	\f	form feed (page feed)
	\a	alert (beep)
	\'	single quote (')
	\"	double quote (")
	\?	question mark (?)
	\\	backslash (\)
	*/

	char16_t m = u'a';	//Same as char16_t x = 'a';
	char32_t n = U'a';	//Same as char32_t x = 'a';
	wchar_t o = L'a';	//Same as wchar_t x = 'a';

	string p = u8"asd";	//The string literal is encoded in the executable using UTF-8
	//string q = R"asd";	//The string literal is a raw string

	bool r = true || false;
	int* s = nullptr;

	//Constant

	const double pi = 3.1415926;
	#define NEWLINE '\n'

	if (5)
		int* s = nullptr;

	//Operators

	//Assignment
	int q = 5;
	q = q + 3;
	q = r = 2;

	//Arithmetic
	q = 5 + 3 - 2 * 7 / 2 % 3;

	//Compound assignment
	q += 3;
	q -= 3;
	q *= 3;
	q /= 3;
	q %= 3;
	q >>= 3;
	q <<= 3;
	q &= 3;
	q ^= 3;
	q |= 3;

	//Increment and decrement (++, --)

	q = q++ + ++q;

	//Relational and comparison operators ( ==, !=, >, <, >=, <= )

	if (q == q)
		q = q;

	if (q != q)
		q = q;

	if (q < q)
		q = q;

	if (q > q)
		q = q;

	if (q <= q)
		q = q;

	if (q >= q)
		q = q;

	//Logical operators ( !, &&, || )

	if (!true || false && true)
		q = q;

	//Conditional ternary operator ( ? )

	q = 2 != 3 ? 3 : 5;

	//Comma operator ( , )

	int t = (q=3, q+2);

	//Explicit type casting operator

	float u = 3.14;
	t = (int) f;
	t = int(f);

	//sizeof

	cout << "char " << sizeof (char) << endl
		 << "short " << sizeof (short) << endl
		 << "int " << sizeof (int) << endl
		 << "long " << sizeof (long) << endl
		 << "long long " << sizeof (long long) << endl
		 << "float " << sizeof (float) << endl
		 << "double " << sizeof (double) << endl
		 << "long double " << sizeof (long double) << endl
		 << "bool " << sizeof (bool) << endl
		 << "decltype(nullptr) " << sizeof (decltype(nullptr)) << endl
		 << "nullptr " << sizeof (nullptr) << endl
		 << "void " << sizeof (void) << endl;

	//IO

	cin >> u;
	cout << u << endl;
	cout << "cout" << endl;
	cerr << "cerr" << endl;
	clog << "clog" << endl;
	
	//stringstream
	
	string mystr = "58";
	int z;
	stringstream(mystr) >> z;
	cout << z << endl;
	
	//Selection statements: if and else
	
	if (true)
	{
		cout << "true" << endl;
	} else
	{
		cout << "false" << endl;
	}
	
	if (true)
		cout << "true" << endl;
	else
		cout << "false" << endl;
	
	//Iteration statements (loops)
	
	int a1 = 0;
	
	while (a1 < 10)
	{
		a1++;
		cout << "a1: " << a1 << endl;		
	}
	
	do
	{
		a1++;
		cout << "a1: " << a1 << endl;
	} while (a1 < 20);
	
	for (int a2 = 0, a3; a2 < 10; a2++, a3++)
	{
		cout << "a3: " << a2 << endl;
		cout << "a2: " << a2 << endl;
	}
	
	string str = "Hello world!";
	
	for (char c : str)
		cout << '[' << c << ']' << endl;

	for (auto c : str)
		cout << "[" << c << "]";

	cout << endl;

	for (int a4=10; a4>0; a4--)
	{
		cout << a4 << ", ";
		if (a4==3)
		{
			cout << "countdown aborted!";
			break;
		}
	}

	cout << endl;

	for (int a5=10; a5>0; a5--)
	{
		if (a5==5) continue;
		cout << a5 << ", ";
	}

	cout << endl;

	int a6=10;
	mylabel:
	cout << a6 << ", ";
	a6--;
	if (a6>0) goto mylabel;
	cout << "liftoff!\n";

	switch (a6)
	{
		case 1:
			cout << 1 << endl;
			break;
		case 0:
			cout << 0 << endl;
			break;
		default:
			cout << "default" << endl;
	}
	
	cout << concatenate("hello", "world") << endl;
	cout << concatenate_inline("hello", "world") << endl;
	cout << concatenate_using_address("hello", "world") << endl;
	cout << concatenate_using_address_inline("hello", "world") << endl;
	cout << divide_with_default(6) << endl;
	protofunction(4, 3);
	protofunction_with_no_name (7);//using default parameter estabilished in the prototype
	int a7 = 9;
	cout << a7 << "! = " << factorial(a7) << endl;//Recursivity
	cout << "Divide 7 by 3 with integer: " << divide(7,3) << endl;		//overload
	cout << "Divide 7 by 3 with double: " << divide(7.0,3.0) << endl;	//overload
	cout << "Multiply 7.5 by 3.2 with integer: " << multiply<int>(7.5,3.2) << endl;		//using templates
	cout << "Multiply 7.5 by 3.2 with double: " << multiply<double>(7.5,3.2) << endl;	//using templates
	cout << "Sum 7.5 and 3 using int as template: " << sum<int, 3>(7.5) << endl;		//using non-type template
	
	asm("");
	
	return 0;
}
template<typename SomeType>
SomeType multiply(SomeType a, SomeType b)
{
	return a * b;
}

void protofunction(int first, int second)
{
	cout << "first: " << first << endl;
	cout << "second: " << second << endl;
}

int protofunction_with_no_name(int first, int second)
{
	cout << "first: " << first << endl;
	cout << "second: " << second << endl;
	return 3;
}

long factorial (long number)
{
  if (number > 1)
   return (number * factorial (number-1));
  else
   return 1;
}

int divide(int a, int b)
{
	return a / b;
}

double divide(double a, double b)
{
	return a / b;
}

template<typename T, int N>
T sum(T value)
{
	return value + N;
}
