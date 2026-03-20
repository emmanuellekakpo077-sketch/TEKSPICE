#include "clock.hpp"
#include "../ErrorLink.hpp"

nts::clockComponent::clockComponent(std::string name) : _name(name), _value(Undefined) {}



nts::Tristate nts::clockComponent::compute(std::size_t pin) 
{
    (void)pin;
    if (state == False)
    return True;
        else if (state == True)
    return False;
    else
        return Undefined;
}
