#pragma once
#include "Instructor.h"


class Course
{
	char* courseName;
	Instructor* firstInstructor;
	Course* nextCourse;
	const int maximumNumberOfInstructors{ 6 };

	int totalInstructorStringLengths();
	bool InstructorFoundInCourseIndex(Instructor&, Instructor*&);

public:
	Course();
	Course(Instructor&);
	~Course();

	void refreshCourse();

	Instructor* getFirstInstructor();

	char* &getCourseName();
	Course* &getNextCourse();
	int getInstructorCount();
	int totalCourseStringLength();

	void operator=(const char*);
	void operator=(Course&);
	void operator+=(const char*);
	Course& operator-(Course&);
	Course& operator-(Instructor&);
	void operator-=(const char*);

	bool InstructorMissing(Instructor&);
	void appendMissingInstructors(Course&);

	friend std::ostream& operator<<(std::ostream&, Course &);
	
};
