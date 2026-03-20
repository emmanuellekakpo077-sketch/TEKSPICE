
#ifndef ERRORS_CHIPSET_HPP_
	#define ERRORS_CHIPSET_HPP_

	#include "Error.hpp"

	class ErrorsChipset: public Errors {
	public:
		ErrorsChipset(std::ostream &, const std::string &) throw();
		~ErrorsChipset(void) throw();
	};

#endif 
