#include "ErrorLink.hpp"

ErrorLink::ErrorLink(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorLink::~ErrorLink(void) throw()
{}
