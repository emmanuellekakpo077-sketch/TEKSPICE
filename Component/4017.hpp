#ifndef __4017_HPP__
#define __4017_HPP__



#include "../Icomponent.hpp"

namespace nts{

    class Component4017 : public AComponent{
    
    public:
        Component4017(){};     
        ~Component4017(){};
        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override {
            (void)pin;
            return Undefined;
        } ;
        std::string getType()  {
            return "4017";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };
}
#endif