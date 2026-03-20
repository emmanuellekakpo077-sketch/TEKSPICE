
#ifndef ERRORS_LINK_HPP_
	#define ERRORS_LINK_HPP_

	#include "Error.hpp"

	class ErrorLink: public Errors {
	public:
		ErrorLink(std::ostream &, const std::string &) throw();
		~ErrorLink(void) throw();
	};

#endif 
