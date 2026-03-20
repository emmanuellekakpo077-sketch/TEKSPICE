#include "ErrorChip.hpp"

ErrorsChipset::ErrorsChipset(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorsChipset::~ErrorsChipset(void) throw()
{}
