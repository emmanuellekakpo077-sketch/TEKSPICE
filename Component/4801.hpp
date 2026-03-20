#ifndef __4801_HPP__
#define __4801_HPP__



#include "../Icomponent.hpp"

namespace nts{

    class Component4801 : public AComponent{
    
    public:
        Component4801(){};     
        ~Component4801(){};
        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override {
            (void)pin;
            return Undefined;
        } ;
        std::string getType()  {
            return "4801";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };
}
#endif