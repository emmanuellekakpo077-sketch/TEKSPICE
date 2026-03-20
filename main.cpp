/*
** EPITECH PROJECT, 2025
** Droid
** File description:
** c++
*/

#include <iostream>
#include "Icomponent.hpp"
#include "./core/ComponentFactory.hpp"
#include "./core/circuit.hpp"
#include <exception>
#include "Error.hpp"
#include "command.hpp"
int main(int ac, char *av[]) 
{
    CommandExecute com;
    std::string command;
    nts::Circuit circuit;

    if (ac == 1 || ac > 2) {
        std::cerr << "error" + '\n';
        return 84;
    }    
    try  {
        circuit.parseFile(av[1]); 
        circuit.execute_command(command);
        
    }
    catch (const Errors& e) {
        std::cerr << "Erreur détectée : " << e.what() << std::endl;
        return 84;
    }
    
}