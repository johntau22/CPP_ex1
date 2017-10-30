#include <iostream>
#include <fstream>
#include <ostream>
#include <cstring>
#include <memory>
#pragma warning(disable : 4996)

using namespace std;

class String {

public:
	String()
		:_s{ new char[1] }, _size{ 0 } { _s[0] = '\0'; };
	String(const char*);
	String(istream&);
	String(int);
	String(double);
	String(const String&);	// copy constructor
	String(String&&);	// move constructor
	~String() { delete[] _s; };

	char operator[](const int) const;
	bool operator< (const String&) const;
	bool operator> (const String&) const;
	bool operator== (const String&) const;
	bool operator!= (const String&) const;
	String& operator+= (String&);
	String& operator= (const String&);	// copy assignment
	String& operator= (String&&);	// move assignment
	void WriteFile(char*) const;
	String ReadFile(char*);

	friend String operator+ (const String&, const String&);
	friend String SubStr(const String&, const int, const size_t);
	friend istream& operator >> (istream&, String&);
	friend ostream& operator<< (ostream&, const String&);

private:
	char* _s;
	size_t _size;

	String& _resize(const size_t);
	friend size_t s_len(const char*);
};

int main()
{
	int a = 12313213;
	double d = 32.321467865654;
	String A("hello");
	String B(a);
	String C(d);
	String D(B);
	String E;
	E = B;
	String F;
	F = B + A;
	E += D;
	String G(cin);

	cout << "A: \t\t" << A;
	cout << endl;
	cout << "B: \t\t" << B;
	cout << endl;
	cout << "C: \t\t" << C;
	cout << endl;
	cout << "D (B): \t\t" << D;
	cout << endl;
	cout << "E=B -> E+=D: \t" << E;
	cout << endl;
	cout << "F (B + A): \t" << F;
	cout << endl;
	cout << "G: \t\t" << G;
	cout << endl;
}

String::String(const char* str)
	:_s{ new char[s_len(str) + 1] }, _size{ s_len(str) }
{
	strcpy(_s, str);
}

String::String(istream& is)
{
	cout << "Enter a string: " << endl;
	char buff[1024];
	is >> buff;
	_size = s_len(buff);
	_s = new char[_size + 1];
	strcpy(_s, buff);
}

String::String(int a)
{
	const int b_len = 64;
	char buff[b_len];
	snprintf(buff, b_len, "%d", a);
	_size = s_len(buff);
	_s = new char[_size + 1];
	strcpy(_s, buff);
}

String::String(double d)
{
	const int b_len = 64;
	char buff[b_len];
	snprintf(buff, b_len, "%0.15f", d);
	_size = s_len(buff);
	_s = new char[_size + 1];
	strcpy(_s, buff);
}

// copy constructor
String::String(const String& other)
	:_s{ new char[s_len(other._s) + 1] }, _size{ s_len(other._s) }
{
	strcpy(_s, other._s);
}

// move constructor
String::String(String&& other)
	:_s{ other._s }, _size{ other._size }
{
	other._s = nullptr;
}

String& String::_resize(const size_t sz)
{
	if (sz <= _size)
	{
		cerr << "New size is not bigger than old, no resize needed." << endl;
		return *this;
	}
	else
	{
		char* new_s = new char[sz];
		strcpy(new_s, _s);
		char* old_s = _s;
		this->_s = new_s;
		delete[] old_s;
		return *this;
	}
}

char String::operator[] (const int i) const
{
	if (i >= 0 && i < _size)
		return _s[i];
	else
		throw out_of_range{"String::operator[]"};
}

bool String::operator< (const String& other) const
{
	if (strcmp(_s, other._s) < 0)
		return true;
	else
		return false;
}

bool String::operator> (const String& other) const
{
	if (strcmp(_s, other._s) > 0)
		return true;
	else
		return false;;
}

bool String::operator== (const String& other) const
{
	if (strcmp(_s, other._s) == 0)
		return true;
	else
		return false;;
}

bool String::operator!= (const String& other) const
{
	if (strcmp(_s, other._s) != 0)
		return true;
	else
		return false;;
}

istream& operator>> (istream& is, String& S)
{
	is >> S._s;
	return is;
}

ostream& operator<< (ostream& os, const String& S)
{
	os << S._s;
	return os;
}

String& String::operator+= (String& other)
{
	int oth_len = s_len(other._s);
	int new_len = _size + oth_len;
	_resize(new_len + 1);
	memcpy(&_s[_size], other._s, (oth_len + 1) * sizeof(char));
	_size = s_len(_s);

	return *this;
}

// copy assignment
String& String::operator= (const String& other)
{
	if (this != &other)
	{
		_s = new char[s_len(other._s) + 1];
		strcpy(_s, other._s);
		_size = s_len(_s);
	}
	else
	{
		cerr << "Warning: Copy assignment to self." << endl;
	}

	return *this;
}

// move assignment
String& String::operator= (String&& other)
{
	if (this != &other)
	{
		delete[] _s;
		_s = other._s;
		other._s = nullptr;
		_size = other._size;
	}
	else
	{
		cerr << "Warning: Move assignment to self." << endl;
	}

	return *this;
}

void String::WriteFile(char* name) const
{
	FILE* pFile = fopen(name, "w");
	if (pFile != NULL)
	{
		fputs(_s, pFile);
		fclose(pFile);
	}
	else
	{
		cout << "Error opening file." << endl;
	}
}

String String::ReadFile(char* name)
{
	FILE* pFile = fopen(name, "r");
	if (pFile != NULL)
	{
		char s[256];
		fgets(s, 256, pFile);
		String NewStr(s);

		return NewStr;	// new object by value
	}
	else
	{
		cout << "Error opening file." << endl;
	}
}

size_t s_len(const char* s)
{
	if (s[0] == '\0')
	{
		cerr << "Zero-length string passed in." << endl;
		return 0;
	}
	size_t len = 0;
	for (int i = 0; s[i] != '\0'; ++i)
		++len;

	return len;
}

String SubStr (const String& str, const int i, const size_t sz)
{
	char* s = new char[sz + 1];
	strcpy(s, &(str._s[i]));
	s[sz] = '\0';
	String SubStr(s);
	delete[] s;

	return SubStr;	// new object by value
}

String operator+ (const String& Str1, const String& Str2)
{
	int oth_len = s_len(Str2._s);
	int new_len = Str1._size + oth_len;
	char* buff = new char[new_len + 1];
	memcpy(buff, Str1._s, Str1._size * sizeof(char));
	memcpy(&buff[Str1._size], Str2._s, (oth_len + 1) * sizeof(char));	// copy with null-terminator
	String NewStr(buff);
	delete[] buff;

	return NewStr;	// new object by value
}
