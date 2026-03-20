#define __4011_HPP__
#define __4011_HPP__



#include "../Icomponent.hpp"
#include "../Icomponent.hpp"

namespace nts {

    class Component4011 : public AComponent {
    public:
        Component4011() {
            _initial[1] = Undefined;
            _initial[2] = Undefined;
            _initial[3] = Undefined;
            _initial[4] = Undefined;
            _initial[5] = Undefined;
            _initial[6] = Undefined;
            _initial[7] = Undefined;
            _initial[8] = Undefined;
        }

        ~Component4011() {}

        void simulate(std::size_t tick) override {
            (void) tick;
        }
        
        Tristate getLink(std::size_t pin)  {
            return ( _link[pin].second->compute(_link[pin].first));
        }

        Tristate compute(std::size_t pin) override {
            if (pin == 1 || pin == 2 || pin == 5 || pin == 6 || pin == 8 || pin == 9 || pin == 12 || pin == 13)
                return getLink(pin);
            if (pin == 3)
                return computeNand(1, 2); 
            if (pin == 4)
                return computeNand(5, 6); 
            if (pin == 10)
                return computeNand(9, 8); 
            if (pin == 11)
                return computeNand(12, 13); 
            return getLink(pin);
        }

        Tristate computeNand(std::size_t pin1, std::size_t pin2) {
            Tristate input1 = _link[pin1].second->compute(_link[pin1].first);
            Tristate input2 = _link[pin2].second->compute(_link[pin2].first);
            
           if (input1 == False && input2 == False)
                return True;
            if (input1 == True && input2 == False)
                return True;
            if (input1 == False && input2 == True)
                return True;
            if (input1 == True && input2 == True)
                return False;
            if (input1 == True && input2 ==False)
                return False;
            if (input1 == False && input2 ==Undefined)
                return Undefined;
            if (input1 == True && input2 ==Undefined)
                return Undefined;
            if (input1 == Undefined && input2 == False)
                return True;
            if (input1 == Undefined && input2 ==Undefined)
                return Undefined;
            return Undefined;
        }

        std::string getType() {
            return "4011"; 
        }

    private:
        std::string _name;
        nts::Tristate _value;
    };

}
