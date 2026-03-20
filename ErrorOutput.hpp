
#ifndef ERRORS_OUTPUT_HPP_
	#define ERRORS_OUTPUT_HPP_

	#include "Error.hpp"

	class ErrorsOutput: public Errors {
	public:
		ErrorsOutput(std::ostream &, const std::string &) throw();
		~ErrorsOutput(void) throw();
	};

#endif 
