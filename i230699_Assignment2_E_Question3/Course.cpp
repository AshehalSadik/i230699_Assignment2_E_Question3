#include "Course.h"


Course::Course(Course ** editingPointer)
{

	courseName = nullptr;
	firstInstructor = nullptr;
	nextCourse = nullptr;
	firstCourse = editingPointer;
}

Course::Course(Course& course2)
{
	*this = course2;
}


Course::~Course()
{
	this->refreshCourse();

    delete[] this->courseName;

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


Course**& Course::getFirstCourse()
{
	return firstCourse;
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

    if (getCourseCount() < totalCoursesAllowed)
    {
        this->addCourse();
    }

    Course *newCourse{nullptr};

    if (this->courseFoundInListIndex(newCourse))
    {
        if (newCourse->getInstructorCount() < totalInstructorsAllowed)
        {
            newCourse->addInstructor(value);
        }
    }
    ;



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

    Course *course{nullptr};

    if (this->courseFoundInListIndex(course))
    {
        *course - *removed;
        course->firstCourse = this->firstCourse;
        course->removeEmptyCourses();
    }




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
	if (getInstructorCount() == totalInstructorsAllowed)
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
		if (this->InstructorMissing(*navigatingPointer) && getInstructorCount() < totalInstructorsAllowed)
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

void Course::addCourse() {

    Course* navigatingPointer = *firstCourse, **editingPointer = firstCourse;

    while (navigatingPointer != nullptr && !stringCompare(navigatingPointer->getCourseName(), courseName))
    {
        navigatingPointer = navigatingPointer->getNextCourse();
        editingPointer = &((*editingPointer)->getNextCourse());
    }

    if (navigatingPointer == nullptr)
    {
        *editingPointer = new Course{firstCourse};
        navigatingPointer = *editingPointer;

        *navigatingPointer = *this;

    }

}

void Course::addInstructor(const char * value) {

    Instructor* navigatingPointer{ firstInstructor }, ** editingPointer{&firstInstructor};

    while (navigatingPointer != nullptr && !stringCompare(navigatingPointer->getName(), value))
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

}

int Course::getCourseCount() {

    int numberOfCourses{0};
    Course *navigatingPointer = *firstCourse;

    while (navigatingPointer != nullptr)
    {
        numberOfCourses++;
        navigatingPointer = navigatingPointer->getNextCourse();
    }

    return numberOfCourses;
}

bool Course::courseFoundInListIndex(Course *& returnPointer) {
    Course* navigatingPointer{ *firstCourse };

    while (navigatingPointer != nullptr)
    {
        if (stringCompare(navigatingPointer->getCourseName(), this->getCourseName()))
        {
            returnPointer = navigatingPointer;
            return true;
        }

        navigatingPointer = navigatingPointer->getNextCourse();
    }

    return false;
}

void Course::removeEmptyCourses() {

    Course* navigatingPointer1{ *(this->firstCourse)}, ** editingPointer{this->firstCourse};
    while (navigatingPointer1 != nullptr)
    {
        if ((*navigatingPointer1).getFirstInstructor() == nullptr)
        {
            Course* temporaryPointer = navigatingPointer1->getNextCourse();

            delete *editingPointer;

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
