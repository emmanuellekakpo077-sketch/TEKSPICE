#ifndef __4030_HPP__
#define __4030_HPP__

#include "../Icomponent.hpp"

namespace nts {

    class Component4030 : public AComponent {
    public:
        Component4030() {
            _initial[1] = Undefined;
            _initial[2] = Undefined;
            _initial[3] = Undefined;
            _initial[4] = Undefined;
            _initial[5] = Undefined;
            _initial[6] = Undefined;
            _initial[8] = Undefined;
            _initial[9] = Undefined;
            _initial[10] = Undefined;
            _initial[11] = Undefined;
            _initial[12] = Undefined;
            _initial[13] = Undefined;
        }

        ~Component4030() {}

        void simulate(std::size_t tick) override {
            (void)tick;
        }

        Tristate getLink(std::size_t pin)  {
            return ( _link[pin].second->compute(_link[pin].first));
        }
        
        Tristate compute(std::size_t pin) override {
            if (pin == 1 || pin == 2 || pin == 5 || pin == 6 || pin == 13 || pin == 12 || pin == 8 || pin == 9)
                return getLink(pin);
            switch (pin) {
                case 3:
                    return computeXor(1, 2);
                case 4:
                    return computeXor(5, 6);
                case 10:
                    return computeXor(8, 9);
                case 11:
                    return computeXor(12, 13);
                default:
                    return Undefined;
            }
        }

        Tristate computeXor(std::size_t pin1, std::size_t pin2) {
            Tristate input1 = _link[pin1].second->compute(_link[pin1].first);
            Tristate input2 = _link[pin2].second->compute(_link[pin2].first);

            if (input1 == Undefined || input2 == Undefined)
                return Undefined;

            if (input1 == True && input2 == False)
                return True;
            if (input1 == False && input2 == True)
                return True;

            return False;
        }

        std::string getType() override {
            return "4030";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };

} // namespace nts

#endif
