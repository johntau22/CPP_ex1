#include <iostream>
#include <fstream>
#include <ostream>
#include <cstring>

size_t slen(const char*);

class String
{
	char* s;
	size_t len;

	char* resize(char*, const size_t);

	friend size_t slen(const char*);
	
public:
	String() :s{ new char[] }, len{ 0 } {};
	String(char*);
	String(int);
	String(double);
	~String() { delete[] s; };

	int compare(String&) const;
	char operator[](const int) const;
	String& operator+(String&);
	String& operator+=(String&);
	String& operator=(String&);
	String& operator=(String&&);
	String& SubStr(int, size_t) const;

	void WriteFile(std::ofstream&);
	String& ReadFile(std::ifstream&) const;
};

String::String(char* str)
{
	s = new char[];
	s = str;
	len = slen(str);
}

String::String(int a)
{
	s = new char[];
	const int blen = 100;
	char buff[blen];
	sprintf_s(buff, blen, "%d", a);
	s = buff;
	len = slen(s);
}

String::String(double d)
{
	s = new char[];
	const int blen = 100;
	char buff[blen];
	sprintf_s(buff, blen, "%f", d);
	s = buff;
	len = slen(s);
}

char* String::resize(char* oldstr, const size_t sz)
{
	if (sz <= len)
	{
		std::cerr << "New size is not bigger than old, no resize needed." << std::endl;
		return oldstr;
	}
	else
	{
		char* newstr = new char[sz];
		*newstr = *oldstr;
		delete oldstr;
		return newstr;
	}
}

int String::compare(String& other) const
{
	return strcmp(this->s, other.s);		 
}

char String::operator[](const int i) const
{
	if (i < 0 && i < len)
	{
		return s[i];
	}
	else
	{
		std::cerr << "Out of bounds." << std::endl;
	}
}

String& String::operator+(String& other)
{
	char buff[1024];
	buff = this->s;
	buff = 1;
}

String& String::operator+=(String& other)
{
	;
}

String& String::operator=(String& other)
{
	;
}

String& String::operator=(String&& other)
{
	;
}

String& String::SubStr(int i, size_t sz) const
{
	;
}

void String::WriteFile(std::ofstream& os)
{
	;
}

String& String::ReadFile(std::ifstream& is) const
{
	;
}



// TO_REMOVE: keep slen at the end

size_t slen(const char* s)
{
	if (s[0] == '\0')
	{
		std::cerr << "Zero-length string passed in." << std::endl;
		return 0;
	}
	size_t len = 0;
	for (int i = 0; s[i] != '\0'; ++i)
		++len;
	
	return len;
}
