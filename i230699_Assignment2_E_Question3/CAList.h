#pragma once
#include "Course.h"

class CAList
{
	Course* firstCourse;
	static constexpr int maximumKeysAllowed{ 7 };

	bool courseFoundInListIndex(Course&, Course* &);

public:
	CAList();
	~CAList();
	CAList(CAList&);

	int getCourseCount();
	Course & operator[](const char *);
	
	void operator=(CAList&);
	CAList& operator+(CAList&);
	CAList& operator-(CAList&);
	void operator-=(CAList&);
	


	friend std::ostream& operator<<(std::ostream&, CAList&);

};
