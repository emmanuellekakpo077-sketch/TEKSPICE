#ifndef __COMMAND_EXECUTE_HPP__
#define __COMMAND_EXECUTE_HPP__
#include "Tristate.hpp"
#include "Icomponent.hpp"

#include "core/circuit.hpp"

class CommandExecute : public nts::Circuit  
{
    private:
    std::map<std::string, std::unique_ptr<IComponent>> Allcomp;  
        std::map<std::string, nts::Tristate>inputs;
    public:
        CommandExecute() {};
        ~CommandExecute() {};

   
    
};
#endif