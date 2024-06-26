#pragma once
#include "Course.h"

class CAList
{
	Course* firstCourse{};
	static constexpr int maximumKeysAllowed{ 7 };

	bool courseFoundInListIndex(Course&, Course* &);
	void deleteEmptyCourses();

public:
	CAList();
	~CAList();
	CAList(CAList&);
    CAList(CAList&&) noexcept;

	void refreshList();
	int getMaximumKeysAllowed();
	int getCourseCount();
	Course operator[](const char *);


	CAList& operator=(CAList const &);
	CAList operator+(CAList&) const;
	CAList operator-(CAList&) const;
	void operator-=(CAList&);
	


	friend std::ostream& operator<<(std::ostream&, CAList&);

};

