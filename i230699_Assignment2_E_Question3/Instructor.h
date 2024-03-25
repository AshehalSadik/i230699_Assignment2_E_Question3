#pragma once
#include <iostream>
using namespace std;

char* getString(const char* string);
int getStringLength(const char* string);
bool stringCompare(const char* string1, const char* string2);

class Instructor
{
	char* name;
	Instructor* reference;

public:
	Instructor();
	~Instructor();
	Instructor(const char*);

	Instructor* &getReference();
	char* getName();
	
	void setName(char *);
	void setReference(Instructor*);

	void operator=(Instructor&);

	friend std::ostream& operator<<(std::ostream&, Instructor&);
};

