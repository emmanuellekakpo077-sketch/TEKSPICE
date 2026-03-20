#ifndef __INPUT__HPP__
#define __INPUT__HPP__

#include "../Icomponent.hpp"
#include <vector>
namespace nts {

    class InputComponent : public nts::AComponent {
    private:
        Tristate state;
        std::vector<std::pair<size_t, IComponent*>>LinkInput;
    public:

        InputComponent(std::string name);

        ~InputComponent() {};
        void simulate(std::size_t tick) override {
            (void)tick;
            for (auto& [pin, component] : LinkInput) {
                component->compute(pin);
            }
        }
        std::string getType()  {
            return "input";
        }
        void setvalue(Tristate new_value);

        Tristate compute(std::size_t pin) override ;
        private:
            std::string	_name;
		    nts::Tristate	_value;
    };

}

#endif
