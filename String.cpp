#include <iostream>
#include <fstream>
#include <ostream>
#include <cstring>

size_t s_len(const char*);

class String
{
	char* s;
	size_t len;

	char* resize(char*, const size_t);

	friend size_t s_len(const char*);
	
public:
	String() :s{ new char[0] }, len{ 0 } {};
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
	int new_len = s_len(str);
	s = new char[new_len];
	s = str;
	len = new_len;
}

String::String(int a)
{
	const int blen = 100;
	char buff[blen];
	sprintf_s(buff, blen, "%d", a);
	int new_len = s_len(buff);
	s = new char[new_len];
	s = buff;
	len = new_len;
}

String::String(double d)
{
	const int blen = 100;
	char buff[blen];
	sprintf_s(buff, blen, "%f", d);
	int new_len = s_len(buff);
	s = new char[new_len];
	s = buff;
	len = new_len;
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
		for (int i = 0; i < len; ++i)
		{
			newstr[i] = oldstr[i];
		}
		newstr[len] = '\0';

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
	strcpy_s(buff, (len+1) * sizeof(char), this->s);
	strcpy_s(buff+(len+1), (s_len(other.s) + 1) * sizeof(char), other.s);
	String NewStr(buff);

	return NewStr;
}

String& String::operator+=(String& other)
{
	;
}

// copy assignment
String& String::operator=(String& other)
{
	;
}

// move assignment
String& String::operator=(String&& other)
{
	;
}

String& String::SubStr(int i, size_t sz) const
{
	String NewStr(14);
	NewStr.resize();
	for (int j = 0; j < sz; ++j)
		NewStr.s[j] = this->s[i + j];
}

void String::WriteFile(std::ofstream& os)
{
	;
}

String& String::ReadFile(std::ifstream& is) const
{
	;
}



// TO_REMOVE: keep s_len at the end

size_t s_len(const char* s)
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
