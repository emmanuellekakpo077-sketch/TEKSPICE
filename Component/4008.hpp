#ifndef __4008_HPP__
#define __4008_HPP__



#include "../Icomponent.hpp"

namespace nts{

    class Component4008 : public AComponent{
    
    public:
        Component4008(){};     
        ~Component4008(){};
        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override {
            (void)pin;
            return Undefined;} ;
        std::string getType()  {
            return "4008";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };
}
#endif