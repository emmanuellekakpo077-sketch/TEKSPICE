#ifndef __OUTPUT__HPP__
#define __OUTPUT__HPP__

#include "../Icomponent.hpp"

namespace nts {
    class OutputComponent : public nts::AComponent {
    public:
        OutputComponent(const std::string &name);
        ~OutputComponent();
        void simulate(std::size_t tick) override {
            (void) tick;
        };
        Tristate compute(std::size_t pin) override;
        
        std::string getType()  {
            return "output";
        }
    private:
       Tristate state;
       std::string _name;
      
    };
}



#endif