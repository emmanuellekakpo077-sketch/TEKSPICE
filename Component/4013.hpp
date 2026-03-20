#ifndef __4013_HPP__
#define __4013_HPP__



#include "../Icomponent.hpp"

namespace nts{

    class Component4013 : public AComponent{
    
    public:
        Component4013(){};     
        ~Component4013(){};
        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override {
            (void)pin;
            return Undefined;
        } ;
        std::string getType()  {
            return "4013";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };
}
#endif