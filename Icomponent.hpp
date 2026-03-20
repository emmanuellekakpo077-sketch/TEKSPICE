#ifndef __ICOMPONENT_HPP__
#define __ICOMPONENT_HPP__
#include <iostream>
#include <string.h>
#include <map>
#include "Tristate.hpp"

namespace nts
{
    
    class IComponent
    {
        public :
            virtual ~ IComponent () = default ;
            virtual void simulate (std::size_t tick ) = 0;
            virtual nts :: Tristate compute (std::size_t pin ) = 0;
            virtual void setLink (std::size_t pin , nts::IComponent& other, std::size_t
                otherPin) = 0;
            virtual std::string getType() = 0;
};

    class AComponent : public IComponent {
        protected :
        std::map<std::size_t, std::pair<std::size_t, IComponent*>> _link;
        std:: map<std::size_t, nts :: Tristate> _initial;
        public:
        virtual std::string getType() = 0;
        virtual nts :: Tristate compute ( std :: size_t pin ) = 0;
        virtual void simulate(std :: size_t tick) = 0;
        Tristate getLink(size_t pin);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override {
            _link[pin] = {otherPin, &other};
        }
    };
};

#endif