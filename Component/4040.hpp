#ifndef __4040_HPP__
#define __4040_HPP__



#include "../Icomponent.hpp"

namespace nts{

    class Component4040 : public AComponent{
    
    public:
        Component4040(){};     
        ~Component4040(){};
        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override {
            (void)pin;
            return Undefined;
        } ;
        std::string getType()  {
            return "4040";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };
}
#endif