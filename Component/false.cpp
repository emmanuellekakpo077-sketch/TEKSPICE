#include "false.hpp"

nts::FalseComponent::FalseComponent(std::string name) : _name(name), _value(nts::Undefined) {}

nts::FalseComponent::~FalseComponent() {}

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    (void)pin;
    if (pin == 1)
        return False;
    return Undefined;
}
