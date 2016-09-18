#pragma once
#include <exception>

class exc_base :
	public std::exception
{
protected:
	char* problem;
public:
	exc_base() : problem("An exception occured.\n") {}
	exc_base(char* _problem) : problem(_problem) {}
	~exc_base(){}
	const char* what() const throw()
	{
		return problem;
	}
};

