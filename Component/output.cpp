#include "output.hpp"
#include "../ErrorLink.hpp"

nts::OutputComponent::OutputComponent(const std::string &name) : _name(name)
{

}

nts::OutputComponent::~OutputComponent()
{

}


nts::Tristate nts::OutputComponent::compute(std::size_t pin) 
{   
    nts::Tristate input1 =  _link[1].second->compute(_link[pin].first);
        return input1;
}
