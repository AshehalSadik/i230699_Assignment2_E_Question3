#include "Instructor.h"


bool stringCompare(const char* string1, const char* string2)
{
	if (getStringLength(string1) != getStringLength(string2))
	{
		return false;
	}

	for (int i{ 0 }; string1[i] != '\0'; i++)
	{
		if (string1[i] != string2[i])
		{
			return false;
		}
	}

	return true;

}


char* getString(const char* string)
{
	int stringLength{ 0 };
	for (; string[stringLength] != '\0'; stringLength++);
	stringLength++;

	char* newString = new char[stringLength];
	for (int i{ 0 }; i != stringLength; i++)
	{
		newString[i] = string[i];
	}

	return newString;
}


int getStringLength(const char* string)
{
	int stringLength{ 0 };
	for (; string[stringLength] != '\0'; stringLength++);

	return stringLength;
}


std::ostream& operator<<(std::ostream& console, Instructor& object)
{
	console << object.name;
	return console;
}


Instructor::Instructor()
{
	name = nullptr;
	reference = nullptr;
}


Instructor::~Instructor()
{

}

Instructor::Instructor(const char* name)
{
	this->name = getString(name);
	this->reference = nullptr;
}


Instructor* &Instructor::getReference()
{
	return reference;
}

char* Instructor::getName()
{
	return getString(this->name);
}


void Instructor::setName(char* value)
{
	if (name == nullptr)
	{
		name = new char[getStringLength(value) + 1];
	}
	name = getString(value);
}


void Instructor::setReference(Instructor* newReference)
{
	this->reference = newReference;
}


void Instructor::operator=(Instructor& object2)
{
	this->name = getString(object2.name);
	this->reference = nullptr;
}
