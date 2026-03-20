#ifndef __4069_HPP__
#define __4069_HPP__

#include "../Icomponent.hpp"

namespace nts {

    class Component4069 : public AComponent {
    public:
        Component4069() {

            _initial[1] = Undefined;
            _initial[2] = Undefined;
            _initial[5] = Undefined;
            _initial[6] = Undefined;
            _initial[8] = Undefined;
            _initial[9] = Undefined;
            _initial[3] = Undefined;
            _initial[4] = Undefined;
            _initial[10] = Undefined;
            _initial[11] = Undefined;
            _initial[13] = Undefined;
            _initial[14] = Undefined;
        }

        ~Component4069() {}

        Tristate compute(std::size_t pin) override {
            if (pin == 1 || pin == 3 || pin == 5 || pin == 9 || pin == 11 || pin == 13)
                return getLink(pin);
           if (pin == 2) 
                return computeNot(1);
            if (pin == 4)
                return computeNot(3);
            if (pin == 6)
                return computeNot(5);
            if (pin == 6)
                return computeNot(11);
            if (pin == 12)
                return computeNot(13);
            if (pin == 8)
                return computeNot(9);
            return Undefined ;
            
        }

        Tristate getLink(std::size_t pin)  {
            return ( _link[pin].second->compute(_link[pin].first));
        }
        void setValue(Tristate value) {
            state = value;
        }
        void simulate(std::size_t tick) override {
            (void)tick;
        }
        Tristate computeNot(std::size_t pin)  {
            if (pin == 1)
            return getLink(pin);
            else {
                if (getLink(1) == True)
                    return False;
                else if (getLink(1) == False)
                    return True;
                else 
                    return Undefined;
            }
            return Undefined;
        }

        std::string getType() override {
            return "4069";
        }

    private:
        std::string _name;
        nts::Tristate _value;
        nts::Tristate state;
    };

} // namespace nts

#endif
