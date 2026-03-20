#include "../Icomponent.hpp"
namespace nts {

    class AndComponent : public AComponent {
        public:
            AndComponent() {
            _initial[1] = Undefined;
            _initial[2] = Undefined;
            _initial[3] = Undefined;
            };
            ~AndComponent(){};
            void simulate(std::size_t tick) override {
                (void)tick;
            
            }
            void setvalue(nts::Tristate new_value)
            {
                state = new_value;
            }

            Tristate compute(std::size_t pin) override {
                if (pin != 3) {
                    return _link[pin].second->compute(_link[pin].first);
                }
                nts::Tristate input1 =  _link[1].second->compute(_link[pin].first);
                nts::Tristate input2 =  _link[2].second->compute(_link[pin].first);
                if (input1 == False || input2 == False)
                    return False;
                if (input1 == True && input2 == True)
                    return True;
                else 
                    return Undefined;
            }
            std::string getType()  {
                return "and";
            }
            Tristate getLink(std::size_t pin)  {
                return ( _link[pin].second->compute(_link[pin].first));
            }
        private:
          Tristate state;
        };
}
