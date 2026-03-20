#ifndef __4514_HPP__
#define __4514_HPP__



#include "../Icomponent.hpp"

namespace nts{

    class Component4514 : public AComponent{
    
    public:
        Component4514(){};     
        ~Component4514(){};
        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override {
            (void)pin;
            return Undefined;
        } ;
        std::string getType()  {
            return "4514";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };
}
#endif