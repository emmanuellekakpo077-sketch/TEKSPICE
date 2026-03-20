#include "input.hpp"
#include "../ErrorLink.hpp"

nts::InputComponent::InputComponent(std::string name) : _name(name), _value(Undefined) {}


void nts::InputComponent::setvalue(nts::Tristate new_value)
{
    _value = new_value;
}


nts::Tristate nts::InputComponent::compute(std::size_t pin) 
{
    if (pin > 1)
        throw ErrorLink(std::cerr, "There is one pin for Input");
    return _value;
}
