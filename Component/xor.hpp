#ifndef __XOR__HPP__
#define __XOR__HPP__

#include "../Icomponent.hpp"

namespace nts {
    class XorComponent : public AComponent {
    public:
        XorComponent(){
        _initial[1] = Undefined;
        _initial[2] = Undefined;
        _initial[3] = Undefined;
        };
        ~XorComponent() override {};
        void simulate(std::size_t tick) override {
            (void)tick;
        }
        std::string getType()  {
            return "xor";
        }
        Tristate getLink(std::size_t pin) {
            return ( _link[pin].second->compute(_link[pin].first));
        }
        Tristate compute(std::size_t pin) override {
            if (pin != 3) {
                return _link[pin].second->compute(_link[pin].first);
            }
            nts::Tristate input1 =  _link[1].second->compute(_link[pin].first);
            nts::Tristate input2 =  _link[2].second->compute(_link[pin].first);

            if (input1 == Undefined || input2 == Undefined)
                return Undefined;
            else  if (input1 != input2)
                return True;
            else 
                return False;
        }
    private:
        Tristate state;  
    };
}



#endif