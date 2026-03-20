#ifndef __4512_HPP__
#define __4512_HPP__



#include "../Icomponent.hpp"

namespace nts{

    class Component4512 : public AComponent{
    
    public:
        Component4512(){};     
        ~Component4512(){};
        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override {
            (void)pin;
            return Undefined;
        } ;
        std::string getType()  {
            return "4512";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };
}
#endif