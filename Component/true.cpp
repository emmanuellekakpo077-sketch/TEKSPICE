#include "true.hpp"

nts::Tristate nts::TrueComponent::compute(std::size_t pin)  
{
    (void) pin;
    if (pin == 1) {
        return True;
    }
    return Undefined;
}

std::string nts::TrueComponent::getType()
{
    return "true";
}

nts::TrueComponent::TrueComponent(std::string name) : _name(name), _value(Undefined) {

}

nts::TrueComponent::~TrueComponent()
{

}