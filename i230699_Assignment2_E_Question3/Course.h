#pragma once
#include "Instructor.h"



class Course
{
	char* courseName;
	Instructor* firstInstructor;
	Course* nextCourse;
	const int maximumNumberOfInstructors{ 6 };
	Course **previousCourse;

	int totalInstructorStringLengths();
	bool InstructorFoundInCourseIndex(Instructor&, Instructor*&);

public:
	Course(Course ** = nullptr);
	Course(Course&);
	~Course();

	void refreshCourse();

	Instructor* getFirstInstructor();

	Course**& getPreviousCourse();
	char* &getCourseName();
	Course* &getNextCourse();
	int getInstructorCount();
	int totalCourseStringLength();

	Course& operator=(const char*);
	Course& operator=(Course const&);
	void operator+=(const char*);
	Course& operator-(Course&);
	Course& operator-(Instructor&);
	void operator-=(const char*);

	bool InstructorMissing(Instructor&);
	void appendMissingInstructors(Course&);

	friend std::ostream& operator<<(std::ostream&, Course &);
	
};

