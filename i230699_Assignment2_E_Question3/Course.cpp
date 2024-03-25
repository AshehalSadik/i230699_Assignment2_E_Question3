#include "Course.h"


Course::Course(Course ** editingPointer)
{
	courseName = nullptr;
	firstInstructor = nullptr;
	nextCourse = nullptr;
	previousCourse = editingPointer;
}

Course::Course(Course& course2)
{
	*this = course2;
}


Course::~Course()
{
	this->refreshCourse();
	
	if (this->courseName != nullptr)
	{
		delete[] this->courseName;
	}
	
	
}


void Course::refreshCourse()
{
	Instructor** deletingPointer{ &firstInstructor };

	while (firstInstructor != nullptr)
	{
		while ((*deletingPointer)->getReference() != nullptr)
		{
			deletingPointer = &((*deletingPointer)->getReference());
		}

		delete* deletingPointer;

		*deletingPointer = nullptr;

		deletingPointer = &firstInstructor;
	}

}


Instructor* Course::getFirstInstructor()
{
	return firstInstructor;
}


Course**& Course::getPreviousCourse()
{
	return previousCourse;
}


char*& Course::getCourseName()
{
	return courseName;
}

Course* &Course::getNextCourse()
{
	return nextCourse;
}

int Course::getInstructorCount()
{
	Instructor* navigatingPointer{ firstInstructor };
	int count{ 0 };

	while (navigatingPointer != nullptr)
	{
		count++;
		navigatingPointer = navigatingPointer->getReference();
	}

	return count;
}


int Course::totalCourseStringLength()
{
	int count{ totalInstructorStringLengths() + getStringLength(courseName) + 7 + (getInstructorCount() - 1) * 2};
	
	return count;
}


int Course::totalInstructorStringLengths()
{
	Instructor* navigatingPointer{ firstInstructor };
	int count{ 0 };

	while (navigatingPointer != nullptr)
	{
		count += getStringLength(navigatingPointer->getName());

		navigatingPointer = navigatingPointer->getReference();
	}

	return count;
}


bool Course::InstructorFoundInCourseIndex(Instructor& instructor, Instructor*& returnPointer)
{
	Instructor* navigatingPointer{ this->getFirstInstructor()};

	while (navigatingPointer != nullptr)
	{
		if (stringCompare(navigatingPointer->getName(), instructor.getName()) == true)
		{
			returnPointer = navigatingPointer;
			return true;
		}

		navigatingPointer = navigatingPointer->getReference();
	}

	return false;
}


Course& Course::operator=(const char* value)
{
	if (previousCourse != nullptr)
	{
		Course** editingPointer = previousCourse;
		delete *previousCourse;
		*editingPointer = nullptr;

		return *this;
	}

	if (getInstructorCount() == maximumNumberOfInstructors)
	{
		return *this;
	}

	Instructor* navigatingPointer{ firstInstructor }, ** editingPointer{&firstInstructor};

	while (navigatingPointer != nullptr && stringCompare(navigatingPointer->getName(), value) != true)
	{
		navigatingPointer = navigatingPointer->getReference();
		editingPointer = &((*editingPointer)->getReference());
	}

	if (navigatingPointer == nullptr)
	{
		*editingPointer = new Instructor;
		navigatingPointer = *editingPointer;
		navigatingPointer->setReference(nullptr);
	}

	if (navigatingPointer->getName() != nullptr)
	{
		delete navigatingPointer->getName();
		navigatingPointer->setName(nullptr);
	}

	navigatingPointer->setName(getString(value));

    return *this;
}


Course& Course::operator=(Course const & object2)
{
	if (this != &object2)
    {
        Instructor* navigatingPointer{ object2.firstInstructor }, ** editingPointer{ &(firstInstructor) };

        if (*editingPointer != nullptr)
        {
            this->refreshCourse();
            editingPointer = &(this->firstInstructor);
        }

        this->courseName = getString(object2.courseName);

        while (navigatingPointer != nullptr)
        {
            *editingPointer = new Instructor;
            **editingPointer = *navigatingPointer;

            editingPointer = &((*editingPointer)->getReference());
            navigatingPointer = navigatingPointer->getReference();
        }
    }

    return *this;
}


void Course::operator+=(const char* value)
{
	*this = value;
}


Course& Course::operator-(Course& course2)
{
	Instructor* navigatingPointer{ firstInstructor }, ** editingPointer{ &firstInstructor };

	while (navigatingPointer != nullptr)
	{
		Instructor* instructorFoundIndex{ nullptr };
		if (course2.InstructorFoundInCourseIndex(*navigatingPointer, instructorFoundIndex))
		{
			Instructor* temporaryPointer{ navigatingPointer->getReference() };

			delete* editingPointer;

			*editingPointer = nullptr;

			*editingPointer = temporaryPointer;

			navigatingPointer = temporaryPointer;
		}
		else
		{
			navigatingPointer = navigatingPointer->getReference();
			editingPointer = &((*editingPointer)->getReference());
		}


	}



	return *this;
}


Course& Course::operator-(Instructor& removedInstructor)
{
	Course withRemovedInstructor;
	withRemovedInstructor.courseName = getString(courseName);
	withRemovedInstructor.firstInstructor = &removedInstructor;

	*this - withRemovedInstructor;

	return *this;
}


void Course::operator-=(const char* name)
{
	Instructor * removed = new Instructor(name);

	*this - *removed;


}


bool Course::InstructorMissing(Instructor& instructor)
{
	Instructor* navigatingPointer = firstInstructor;

	while (navigatingPointer != nullptr)
	{
		if (stringCompare(navigatingPointer->getName(), instructor.getName()) == true)
		{
			return false;
		}

		navigatingPointer = navigatingPointer->getReference();
	}

	return true;
}


void Course::appendMissingInstructors(Course& similarCourse)
{
	if (getInstructorCount() == maximumNumberOfInstructors)
	{
		return;
	}

	Instructor* navigatingPointer{ similarCourse.firstInstructor }, ** editingPointer{&firstInstructor};

	while (*editingPointer != nullptr)
	{
		editingPointer = &((*editingPointer)->getReference());
	}
	
	while (navigatingPointer != nullptr)
	{
		if (this->InstructorMissing(*navigatingPointer) && getInstructorCount() < maximumNumberOfInstructors)
		{
			*editingPointer = new Instructor;

			**editingPointer = *navigatingPointer;

			editingPointer = &((*editingPointer)->getReference());
		}

		navigatingPointer = navigatingPointer->getReference();
	}
}


std::ostream& operator<<(std::ostream& console, Course& object)
{
	console << object.courseName << " : { ";

	Instructor* navigatingPointer{ object.firstInstructor };
	while (navigatingPointer != nullptr)
	{
		console << *navigatingPointer;

		if (navigatingPointer->getReference() != nullptr)
		{
			console << ", ";
		}

		navigatingPointer = navigatingPointer->getReference();
	}

	console << " }";

	return console;
}
