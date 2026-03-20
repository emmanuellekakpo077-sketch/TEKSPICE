#ifndef __FALSE_HPP__
#define __FALSE_HPP__



#include "../Icomponent.hpp"

namespace nts{

    class FalseComponent : public AComponent{
    
    public:
        FalseComponent(std::string name);     
        ~FalseComponent();
        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override ;
        std::string getType()  {
            return "false";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };
}
#endif