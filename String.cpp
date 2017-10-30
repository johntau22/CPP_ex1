#include <iostream>
#include <fstream>
#include <ostream>
#include <cstring>
#pragma warning(disable : 4996)

using namespace std;

class String {
	char* _s;
	size_t _size;

	char* _resize(char*, const size_t);
	friend size_t s_len(const char*);
	friend int compare(const String&, const String&);
	friend String& SubStr(const String&, const int, const size_t);
	friend String& operator+(String&, const String&);
	friend istream& operator>>(istream&, String&);
	friend ostream& operator<<(ostream&, const String&);

public:
	String()
		:_s{ new char[1] }, _size{ 0 }	{ _s[0] = '\0'; };
	String(const char*);
	String(istream&);
	String(int);
	String(double);
	String(const String&);
	String(String&&);
	~String() { delete[] _s; };

	char operator[](const int) const;
	String& operator+=(String&);
	String& operator=(const String&);
	String& operator=(String&&);
	void WriteFile(ofstream&) const;
	String& ReadFile(ifstream&);
};

int main()
{
	int a = 12313213;
	double d = 32.321467865654;
	String A("hello");
	String B(a);
	String C(d);
	String D(C);
	String E;
	E = D + A;
	E += D;
	String F(cin);

	cout << A;
	cout << endl;
	cout << B;
	cout << endl;
	cout << C;
	cout << endl;
	cout << D;
	cout << endl;
	cout << E;
	cout << endl;
	cout << F;
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
	sprintf(buff, "%d", a);
	_size = s_len(buff);
	_s = new char[_size + 1];
	strcpy(_s, buff);
}

String::String(double d)
{
	const int b_len = 64;
	char buff[b_len];
	sprintf(buff, "%0.15f", d);
	_size = s_len(buff);
	_s = new char[_size + 1];
	strcpy(_s, buff);
}

// copy constructor
String::String(const String& other)
	:_s{ new char[s_len(other._s)] }, _size{ s_len(other._s) }
{
	strcpy(_s, other._s);
}

// move constructor
String::String(String&& other)
	:_s{ other._s }, _size{ other._size}
{
	other._s = nullptr;
}

char* String::_resize(char* oldstr, const size_t sz)
{
	if (sz <= _size)
	{
		cerr << "New size is not bigger than old, no resize needed." << endl;
		return oldstr;
	}
	else
	{
		char* newstr = new char[sz];
		strcpy(newstr, oldstr);
		delete[] oldstr;
		return newstr;
	}
}

char String::operator[](const int i) const
{
	if (i >= 0 && i < _size)
	{
		return _s[i];
	}
	else
	{
		cerr << "Out of bounds." << endl;
	}
}

istream& operator>>(istream& is, String& S)
{
	is >> S._s;
	return is;
}

ostream& operator<<(ostream& os, const String& S)
{
	os << S._s;
	return os;
}

String& String::operator+=(String& other)
{
	int oth_len = s_len(other._s);
	int new_len = _size + oth_len;
	_s = _resize(_s, new_len + 1);
	memcpy(&_s[_size], other._s, (oth_len + 1) * sizeof(char));

	return *this;
}

// copy assignment
String& String::operator=(const String& other)
{
	if (this != &other)
	{
		_s = new char[s_len(other._s + 1)];
		_size = s_len(_s);
		strcpy(_s, other._s);
	}
	else
	{
		cerr << "Warning: Copy assignment to self." << endl;
	}

	return *this;
}

// move assignment
String& String::operator=(String&& other)
{
	if (this != &other)
	{
		delete[] _s;
		_s = other._s;
		other._s = nullptr;
	}
	else
	{
		cerr << "Warning: Move assignment to self." << endl;
	}

	return *this;
}

void String::WriteFile(ofstream& ofs) const
{
	ofs << this->_s;
}

String& String::ReadFile(ifstream& ifs)
{
	ifs >> this->_s;
	return *this;
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

int compare(const String& str1, const String& str2)
{
	return strcmp(str1._s, str2._s);
}

String& SubStr(const String& str, const int i, const size_t sz)
{
	char* s = new char[sz + 1];
	strcpy(s, &(str._s[i]) );
	s[sz] = '\0';
	String SubStr(s);
	delete[] s;

	return SubStr;
}


String& operator+(String& Dest, const String& Src)
{
	int src_len = s_len(Src._s);
	int new_len = Dest._size + src_len;
	char* buff = new char[new_len + 1];
	memcpy(buff, Dest._s, Dest._size * sizeof(char));
	memcpy(&buff[Dest._size], Src._s, (src_len + 1) * sizeof(char));	// copy with null-terminator

	Dest._resize(Dest._s, new_len + 1);
	strcpy(Dest._s, buff);
	delete[] buff;

	return Dest;
}
