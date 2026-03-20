#ifndef __CLOCK__HPP__
#define __CLOCK__HPP__

#include "../Icomponent.hpp"
#include <vector>
namespace nts {

    class clockComponent : public nts::AComponent {
    private:
        Tristate state;
        std::vector<std::pair<size_t, IComponent*>>LinkInput;
    
    public:

        clockComponent(std::string name);

        ~clockComponent() {};
        void simulate(std::size_t tick) override {
            (void)tick;
            for (auto& [pin, component] : LinkInput) {
                component->compute(pin);
            }
           
        }
        std::string getType()  {
            return "input";
        }
        void setvalue(Tristate new_value){
            _value = new_value;
        }
        
        Tristate getState() const {
            return state;
        }
        Tristate compute(std::size_t pin) override ;
        private:
            std::string	_name;
		    nts::Tristate	_value;
    };

}

#endif
