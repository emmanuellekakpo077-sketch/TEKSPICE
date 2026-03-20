#ifndef __NOT_HPP__
#define __NOT_HPP__


#include "../Icomponent.hpp"

namespace nts{

    class NotComponent : public AComponent
    {
    private:
        Tristate state;
    public:
        NotComponent() : state(Undefined) {};
        ~NotComponent() {};
        void simulate(std::size_t tick) override {
            (void)tick;;
        }
        std::string getType()  {
            return "not";
        }
        void setValue(Tristate value) {
            state = value;
        }
       
        Tristate getLink(std::size_t pin)  {
            return ( _link[pin].second->compute(_link[pin].first));
        }

        Tristate Notlogic(Tristate a) {
            if (a == Undefined)
                return Undefined;
            return (a == True) ? False : True;
        }
        
        nts::Tristate compute(std::size_t pin) {
            if (pin == 1)
                return getLink(pin);
            else if (pin == 2) {
                Tristate a = getLink(1);
                return Notlogic(a);
            }
            return Undefined;
        }
       
    };
}

#endif