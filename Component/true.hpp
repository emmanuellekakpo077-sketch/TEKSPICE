#ifndef __TRUE_HPP__
#define __TRUE_HPP__


#include "../Icomponent.hpp"

namespace nts{

    class TrueComponent : public AComponent{
    
    private:
    std::string _name;
    Tristate _value;
    public:
        TrueComponent(std::string name); 
        ~TrueComponent();     
        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override;
        std::string getType();
    };

}
#endif