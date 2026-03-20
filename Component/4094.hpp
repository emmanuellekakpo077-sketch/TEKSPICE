#ifndef __4094_HPP__
#define __4094_HPP__



#include "../Icomponent.hpp"

namespace nts{

    class Component4094 : public AComponent{
    
    public:
        Component4094(){};     
        ~Component4094(){};
        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override {
            (void)pin;
            return Undefined;
        } ;
        std::string getType()  {
            return "4094";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };
}
#endif