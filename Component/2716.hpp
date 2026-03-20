#ifndef __2716_HPP__
#define __2716_HPP__



#include "../Icomponent.hpp"

namespace nts{

    class Component2716 : public AComponent{
    
    public:
        Component2716(){};     
        ~Component2716(){};
        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override {
            (void)pin;
            return Undefined;
        } ;
        std::string getType()  {
            return "2716";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };
}
#endif