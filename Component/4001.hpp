#ifndef __4001_HPP__
#define __4001_HPP__

#include "../Icomponent.hpp"

namespace nts {

    class Component4001 : public AComponent {
    public:
        Component4001() {
        }

        ~Component4001() {}

        void simulate(std::size_t tick) override {
            (void)tick;
        }

        Tristate compute(std::size_t pin) override {
            (void)pin;        
            return Undefined;
        }
        
        std::string getType() override {
            return "4001";
        }
    private:
        std::string _name;
        nts::Tristate _value;
    };

} // namespace nts

#endif
