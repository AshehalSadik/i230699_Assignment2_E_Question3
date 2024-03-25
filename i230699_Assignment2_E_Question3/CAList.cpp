#include "CAList.h"


char* makeSpacesString(int numberOfSpaces)
{
	char* string = new char[numberOfSpaces + 1] {'\0'};

	for (int i{ 0 }; i != numberOfSpaces; i++)
	{
		string[i] = ' ';
	}

	return string;
}


bool CAList::courseFoundInListIndex(Course& course, Course* &returnPointer)
{
	Course* navigatingPointer{ firstCourse };

	while (navigatingPointer != nullptr)
	{
		if (stringCompare(navigatingPointer->getCourseName(), course.getCourseName()) == true)
		{
			returnPointer = navigatingPointer;
			return true;
		}

		navigatingPointer = navigatingPointer->getNextCourse();
	}

	return false;
}


CAList::CAList()
{
	firstCourse = nullptr;
}


CAList::~CAList()
{
	Course** deletingPointer{ &firstCourse };

	while (firstCourse != nullptr)
	{
		while ((*deletingPointer)->getNextCourse() != nullptr)
		{
			deletingPointer = &((*deletingPointer)->getNextCourse());
		}

		delete* deletingPointer;

		*deletingPointer = nullptr;

		deletingPointer = &firstCourse;
	}
}


CAList::CAList(CAList& object2)
{
	firstCourse = nullptr;

	*this = object2;
}



int CAList::getCourseCount()
{
	Course* navigatingPointer{ firstCourse };
	int count{ 0 };

	while (navigatingPointer != nullptr)
	{
		count++;
		navigatingPointer = navigatingPointer->getNextCourse();
	}

	return count;
}


Course & CAList::operator[](const char* courseName)
{
	Course* navigatingPointer = firstCourse, **editingPointer = &firstCourse;

	while (navigatingPointer != nullptr && stringCompare(navigatingPointer->getCourseName(), courseName) != true)
	{
		navigatingPointer = navigatingPointer->getNextCourse();
		editingPointer = &((*editingPointer)->getNextCourse());
	}

	if (navigatingPointer == nullptr)
	{
		*editingPointer = new Course;
		navigatingPointer = *editingPointer;

		navigatingPointer->getCourseName() = getString(courseName);
		navigatingPointer->getNextCourse() = nullptr;
	}


	return *navigatingPointer;
}


void CAList::operator=(CAList &object2)
{
	Course* navigatingPointer{ object2.firstCourse }, ** editingPointer{ &(this->firstCourse) };

	if (*editingPointer != nullptr)
	{
		delete* editingPointer;
	}

	while (navigatingPointer != nullptr)
	{
		*editingPointer = new Course;
		**editingPointer = *navigatingPointer;

		editingPointer = &((*editingPointer)->getNextCourse());
		navigatingPointer = navigatingPointer->getNextCourse();
	}
}


CAList& CAList::operator+(CAList& list2)
{
	CAList *sum = new CAList;
	*sum = *this;

	Course** editingPointer(&(sum->firstCourse));
	while (*editingPointer != nullptr)
	{
		editingPointer = &((*editingPointer)->getNextCourse());
	}
	
	Course* navigatingPointer2{ list2.firstCourse }, *courseFoundInSecondListIndex{ nullptr };
	while (sum->getCourseCount() < maximumKeysAllowed && navigatingPointer2 != nullptr)
	{
		if (!sum->courseFoundInListIndex(*navigatingPointer2, courseFoundInSecondListIndex))
		{
			*editingPointer = new Course;

			**editingPointer = *navigatingPointer2;

			editingPointer = &((*editingPointer)->getNextCourse());
		}
		else if (sum->courseFoundInListIndex(*navigatingPointer2, courseFoundInSecondListIndex))
		{
			courseFoundInSecondListIndex->appendMissingInstructors(*navigatingPointer2);
		}

		navigatingPointer2 = navigatingPointer2->getNextCourse();
	}

	return *sum;

}


CAList& CAList::operator-(CAList& list2)
{
	CAList* difference = new CAList;
	*difference = *this;

	Course* navigatingPointer{ difference->firstCourse }, ** editingPointer{ &(difference->firstCourse)};

	while (navigatingPointer != nullptr)
	{
		Course* courseFoundPointer{ nullptr };

		if (list2.courseFoundInListIndex(*navigatingPointer, courseFoundPointer) == true)
		{
			*navigatingPointer - *courseFoundPointer;

			if ((*navigatingPointer).getFirstInstructor() == nullptr)
			{
				Course* temporaryPointer = navigatingPointer->getNextCourse();

				delete* editingPointer;

				*editingPointer = temporaryPointer;

				navigatingPointer = temporaryPointer;
			}
			else
			{
				navigatingPointer = navigatingPointer->getNextCourse();
				editingPointer = &((*editingPointer)->getNextCourse());
			}
		}
		else
		{
			navigatingPointer = navigatingPointer->getNextCourse();
			editingPointer = &((*editingPointer)->getNextCourse());
		}
		

	}

	return *difference;
}


void CAList::operator-=(CAList& list2)
{
	*this = *this - list2;
}


void CAList::deleteEmptyCourses()
{
	Course* navigatingPointer1{ this->firstCourse}, ** editingPointer{&(this->firstCourse)};
	while (navigatingPointer1 != nullptr)
	{
		if ((*navigatingPointer1).getFirstInstructor() == nullptr)
		{
			Course* temporaryPointer = navigatingPointer1->getNextCourse();

			delete* editingPointer;

			*editingPointer = temporaryPointer;

			navigatingPointer1 = temporaryPointer;
		}
		else
		{
			navigatingPointer1 = navigatingPointer1->getNextCourse();
			editingPointer = &((*editingPointer)->getNextCourse());
		}
	}
}

std::ostream& operator<<(std::ostream& console, CAList& object)
{
	object.deleteEmptyCourses();
	


	const int consoleWindow = 80;
	Course* navigatingPointer{ object.firstCourse };

	while (navigatingPointer != nullptr)
	{
		int spacesBeforeCourse = (consoleWindow - navigatingPointer->totalCourseStringLength()) / 2;
		char* spaceString = makeSpacesString(spacesBeforeCourse);

		console << spaceString; 
		
		if (navigatingPointer == object.firstCourse)
		{
			console << "[ ";
		}

		console << *navigatingPointer;

		if (navigatingPointer->getNextCourse() == nullptr)
		{
			console << " ]" << endl;
		}
		else
		{
			console << "," << endl;
		}

		navigatingPointer = navigatingPointer->getNextCourse();

	}

	return console;

}
