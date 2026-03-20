#ifndef __4081_HPP__
#define __4081_HPP__


#include "../Tristate.hpp"
#include "../Icomponent.hpp"

namespace nts{

    class Component4081 : public AComponent{
    
        private:
            std::string _name;
            Tristate _value;
            
        public:
            Component4081(){
                _initial[1] = Undefined;
                _initial[2] = Undefined;
                _initial[3] = Undefined;
                _initial[5] = Undefined;
                _initial[6] = Undefined;
                _initial[4] = Undefined;
                _initial[12] = Undefined;
                _initial[13] = Undefined;
                _initial[11] = Undefined;
                _initial[8] = Undefined;
                _initial[9] = Undefined;
                _initial[10] = Undefined;
            };     
            ~Component4081(){};
            void simulate(std::size_t tick) {
                (void)tick;
            }
            Tristate compute(size_t pin)  {
                if (pin == 1 || pin == 2 || pin == 5 || pin == 6 || pin == 13 || pin == 12 || pin == 8 || pin == 9)
                return getLink(pin);
                if (pin == 3)
                    return computeAnd(1, 2);
                if (pin == 4)
                    return computeAnd(5, 6);
                if (pin == 10)
                    return computeAnd(8, 9);
                if (pin == 11)
                    return computeAnd(12, 13);
                return Undefined;
            }
            
            Tristate getLink(std::size_t pin)  {
                return ( _link[pin].second->compute(_link[pin].first));
            }

            Tristate computeAnd(std::size_t pin1, std::size_t pin2) {
                Tristate input1 = _link[pin1].second->compute(_link[pin1].first);
                Tristate input2 = _link[pin2].second->compute(_link[pin2].first);
                if ((input1 == Undefined && (input2 == Undefined || input2 == True )) || (input2 == Undefined && input1 == True))
                    return Undefined;
                if ((input1 == False || input1 == Undefined) && (input2 == False || input2 == Undefined))
                    return False;
                if (input1 == True && input2 == True)
                    return True;
                return False;
            }
            std::string getType()  {
                return "4081";
            }
        };
}
#endif