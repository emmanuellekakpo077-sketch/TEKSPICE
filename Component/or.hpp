#ifndef __OR__HPP__
#define __OR__HPP__

#include "../Icomponent.hpp"

namespace nts {
    class OrComponent : public AComponent {
    public:
        OrComponent(){
        _initial[1] = Undefined;
        _initial[2] = Undefined;
        _initial[3] = Undefined;
        };
        ~OrComponent() override {};
        void simulate(std::size_t tick) override {
            (void)tick;
        }
        std::string getType()  {
            return "or";
        }

        Tristate getLink(std::size_t pin)  {
            return ( _link[pin].second->compute(_link[pin].first));
        }

        Tristate compute(std::size_t pin) override {
            if (pin != 3) {
                return getLink(pin);
            }
            nts::Tristate input1 =  _link[1].second->compute(_link[pin].first);
            nts::Tristate input2 =  _link[2].second->compute(_link[pin].first);
            if (input1 == True || input2 == True)
                return True;
            if (input1 == False && input2 == False)
                return False;
            return Undefined;
        }

        private:
        Tristate state;  
        
    };
}

#endif