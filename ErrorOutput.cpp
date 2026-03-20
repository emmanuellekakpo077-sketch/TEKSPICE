#include "ErrorOutput.hpp"

ErrorsOutput::ErrorsOutput(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorsOutput::~ErrorsOutput(void) throw()
{

}
