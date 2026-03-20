#ifndef __COMPONENTFACTORY__HPP__
#define __COMPONENTFACTORY__HPP__

#include <exception>
#include <memory>
#include <iostream>
#include "../Component/And.hpp"
#include "../Component/or.hpp"
#include "../Component/true.hpp"
#include "../Component/Not.hpp"
#include "../Component/xor.hpp"
#include "../Component/clock.hpp"
#include "../Component/false.hpp"
#include "../Component/input.hpp"
#include "../Component/output.hpp"
#include "../ErrorChip.hpp"
#include "../Tristate.hpp"
#include "../Component/2716.hpp"
#include "../Component/4001.hpp"
#include "../Component/4008.hpp"
#include "../Component/4011.hpp"
#include "../Component/4013.hpp"
#include "../Component/4017.hpp"
#include "../Component/4030.hpp"
#include "../Component/4081.hpp"
#include "../Component/4040.hpp"
#include "../Component/4069.hpp"
#include "../Component/4071.hpp"
#include "../Component/4094.hpp"
#include "../Component/4512.hpp"
#include "../Component/4514.hpp"
#include "../Component/4801.hpp"



class ComponentFactory
{

public:
    std::unique_ptr<nts::IComponent> createComponent(const std::string type, const std::string str) {
        (void) str;
        if (type == "input")
            return std::make_unique<nts::InputComponent>(str);
        else if (type == "output")
            return std::make_unique<nts::OutputComponent>(str);
        else if (type == "false")
            return std::make_unique<nts::FalseComponent>(str);
        else if (type == "true")
            return std::make_unique<nts::TrueComponent>(str);
        else if (type == "clock")
            return std::make_unique<nts::clockComponent>(str);
        else if (type == "not")
            return std::make_unique<nts::NotComponent>();
        else if (type == "xor")
            return std::make_unique<nts::XorComponent>();
        else if (type == "and")
            return std::make_unique<nts::AndComponent>();
        else if (type == "or")
            return std::make_unique<nts::OrComponent>();
        else if (type == "or")
            return std::make_unique<nts::OrComponent>();
        else if (type == "2716")
            return std::make_unique<nts::Component2716>();
        else if (type == "4001")
            return std::make_unique<nts::Component4001>();
        else if (type == "4008")
            return std::make_unique<nts::Component4008>();
        else if (type == "4011")
            return std::make_unique<nts::Component4011>();
        else if (type == "4013")
            return std::make_unique<nts::Component4013>();
        else if (type == "4017")
            return std::make_unique<nts::Component4017>();
        else if (type == "4030")
            return std::make_unique<nts::Component4030>();
        else if (type == "4040")
            return std::make_unique<nts::Component4040>();
        else if (type == "4069")
            return std::make_unique<nts::Component4069>();
        else if (type == "4071")
            return std::make_unique<nts::Component4071>();
         else if (type == "4081")
            return std::make_unique<nts::Component4081>();
        else if (type == "4094")
            return std::make_unique<nts::Component4094>();
        else if (type == "4512")
            return std::make_unique<nts::Component4512>();
        else if (type == "4514")
            return std::make_unique<nts::Component4514>();
        else if (type == "4801")
            return std::make_unique<nts::Component4801>();
        else throw  ErrorsChipset(std::cerr, "Unknown component type");
    }
};
//ftp
//nano
//kyt cat
//defense asm



#endif