#ifndef __CIRCUIT_HPP__
#define __CIRCUIT_HPP__

#include <memory>
#include <map>
#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include "../Component/input.hpp"
#include "../ErrorChip.hpp"
#include "../ErrorLink.hpp"
#include "ComponentFactory.hpp"
#include <bits/stdc++.h>


namespace nts {

    class Circuit : public AComponent {
    protected:
    std::map<std::string, size_t> compPin = {
        {"input", 1},
        {"output", 1},
        {"and", 3},
        {"or", 3},
        {"true", 1},
        {"false", 1},
        {"xor", 3},
        {"not", 2},
        {"clock", 1},
        {"2716", 24},
        {"4001", 14},
        {"4008", 16},
        {"4011", 14},
        {"4013", 11},
        {"4017", 15},
        {"4030", 14},
        {"4040", 16},
        {"4069", 14},
        {"4071", 14},
        {"4081", 14},
        {"4094", 15},
        {"4512", 15},
        {"4514", 24},   
        {"4801", 24}
    };    
        std::map<std::string, std::unique_ptr<IComponent>> Allcomponents;
        std::map<std::string, std::string>Recup;
        std::vector<std::tuple<std::pair<std::string, std::size_t>, std::pair<std::string, std::size_t>>>links;
        
    public:
        std::string inputValue;
        std::string inputName;
        size_t tick;
        size_t tick1;
        Circuit() {tick=0;}
        ~Circuit() {}
        const std::map<std::string, std::unique_ptr<IComponent>>& getAllComponents() const {
            return Allcomponents;
        }
        const std::vector<std::tuple<std::pair<std::string, std::size_t>, std::pair<std::string, std::size_t>>>& getLinks() const {
            return links;
        }
        
        const std::map<std::string, std::string>& getRecup() const {
                return Recup;
        }        
        size_t getTick()
        {
            return tick1;
        }
        void handleSimulate() {
            for (const auto& [name1, comp1] : Recup) {
                if (InputComponent *input = dynamic_cast <InputComponent*>(Allcomponents[name1].get())) {
                    input->setvalue((comp1 == "1") ? True : (comp1 == "0") ? False : Undefined);
                }
                if (clockComponent *clock = dynamic_cast <clockComponent*>(Allcomponents[name1].get())) {
                     clock->setvalue((comp1 == "1") ? True : (comp1 == "0") ? False : Undefined);
                }
            }
            //Recup.clear();
            tick++;
            for (const auto& [name, comp] : Allcomponents) {
                comp->simulate(tick);
            }
        }

        std::string convertInput(nts::Tristate val) {
            if (val == nts::Tristate::False) {
                return "0";
            }
            if (val == nts::Tristate::True) {
                return "1";
            }
            else {
                return "U";
          }
        }
        void handleInput(std::string command) {
            size_t position = command.find('=');
            
            if (position != std::string::npos) {
                inputName = command.substr(0, position);            
                if (Allcomponents.find(inputName) != Allcomponents.end()) {
                    inputValue = command.substr(position + 1);
                    Recup[inputName] = inputValue;
                    return;
                }
                throw ErrorLink(std::cerr, "This name is not in the file");
            }
        }
        void handleDisplay() {
            printf("tick: %ld\ninput(s):\n", tick);
            for (const auto& [name, comp] : Allcomponents) {
                if (dynamic_cast<InputComponent*>(comp.get())) {
                    nts::Tristate val1 = comp->compute(1);
                    std::cout << "  " << name << ": " << convertInput(val1) + '\n';
                }
                if (clockComponent* clock = dynamic_cast<clockComponent*>(comp.get())) {
                    (void)clock;
                    nts::Tristate val1 = comp->compute(1);
                    std::cout << "  " + name + ": " + convertInput(val1) + '\n';
                }
            }

            printf("output(s):\n");
            for (const auto& [name, comp] : Allcomponents) {
                if (dynamic_cast<OutputComponent*>(comp.get())) {
                    nts::Tristate val3 = comp->compute(1);     
                        std::cout << "  " << name << ": " << convertInput(val3) + '\n';
                   
                }
            }
        }
        
         
        void execute_command(std::string command)
        {      
            while(std::cout << "> " && std::getline(std::cin, command)) {
                command.erase(std::remove_if(command.begin(), command.end(), ::isspace),command.end());
                if (command.empty())
                    continue;
                if (command == "exit") {
                    exit(0);
                }
                handleInput(command);
                if (command == "simulate") {    
                    handleSimulate();
                }
                if (command == "display") {
                    handleDisplay();
                }
            }
        }
        void addComponent(std::string name, std::string type) {
            ComponentFactory comp;
                auto component = comp.createComponent(type, name);
                Allcomponents[name] = std::move(component);
                /*for (const auto &link : Allcomponents) {
                    std::cout << "Component Name: " << link.first << ", Type: " << link.second->getType() << std::endl; 
                }*/
        }
            
        void addLink(std::string string1, std::size_t pin1, std::string string2, std::size_t pin2) {
            if (Allcomponents.find(string1) == Allcomponents.end()) 
                throw ErrorLink(std::cerr, "Name not in chipset\n");    
            if (Allcomponents.find(string2) == Allcomponents.end())
                throw ErrorLink(std::cerr, "Name not in chipset\n"); 

            std::string type1 = Allcomponents[string1]->getType();
            std::string type2 = Allcomponents[string2]->getType();
            
            if ((type1 == "input" && type2 == "input") || 
                (type1 == "output" && type2 == "output") || 
                (type1 == "clock" && type2 == "clock") || 
                (type1 == "true" && type2 == "true") || 
                (type1 == "false" && type2 == "false")) {
                    throw ErrorLink(std::cerr, "Cannot link two components of the same type");
            }
            if ((type1 == "4801" || type2 == "4801") && ( pin1== 12 || pin2 == 12 || pin1 == 19 || pin2 == 19 || pin1 == 24 || pin2== 24))
                throw ErrorLink(std::cerr, "pin1 or pin2 must be ignored");
            if ((type1 == "4514" || type2 == "4514") && ( pin1== 12 || pin2 == 12 || pin1 == 24 || pin2 == 24))
                throw ErrorLink(std::cerr, "pin1 or pin2 must be ignored");
            if ((type1 == "4081" || type2 == "4081") && ( pin1== 14 || pin2 == 14 || pin1 == 7 || pin2 == 7))
                throw ErrorLink(std::cerr, "pin1 or pin2 must be ignored");
            if ((type1 == "4071" || type2 == "4071") && ( pin1== 14 || pin2 == 14 || pin1 == 7 || pin2 == 7))
                throw ErrorLink(std::cerr, "pin1 or pin2 must be ignored");
            if ((type1 == "4069" || type2 == "4069") && ( pin1== 14 || pin2 == 14 || pin1 == 7 || pin2 == 7))
                throw ErrorLink(std::cerr, "pin1 or pin2 must be ignored");
            if ((type1 == "4040" || type2 == "4040") && ( pin1== 16 || pin2 == 16 || pin1 == 8 || pin2 == 8))
                throw ErrorLink(std::cerr, "pin1 or pin2 must be ignored");
            if ((type1 == "4030" || type2 == "4030") && ( pin1== 14 || pin2 == 14 || pin1 == 7 || pin2 == 7))
                throw ErrorLink(std::cerr, "pin1 or pin2 must be ignored");
            if ((type1 == "4011" || type2 == "4011") && ( pin1== 14 || pin2 == 14 || pin1 == 7 || pin2 == 7))
                throw ErrorLink(std::cerr, "pin1 or pin2 must be ignored");
            if ((type1 == "4008" || type2 == "4008") && ( pin1== 8 || pin2 == 8 || pin1 == 16 || pin2 == 16))
                throw ErrorLink(std::cerr, "pin1 or pin2 must be ignored");
            if ((type1 == "4001" || type2 == "4001") && ( pin1== 14 || pin2 == 14 || pin1 == 7 || pin2 == 7))
                throw ErrorLink(std::cerr, "pin1 or pin2 must be ignored");
            if ((type1 == "2716" || type2 == "2716") && ( pin1== 21 || pin2 == 21 || pin1 == 12 || pin2 == 12 || pin1 == 19 ||  pin2 == 19 ||  pin1 == 24 ||  pin2 == 24) ){
                throw ErrorLink(std::cerr, "pin1 or pin2 must be ignored");    
            }
            
            if (pin1 > compPin[type1] || pin1 == 0)
                throw ErrorLink(std::cerr, "pin1 invalide");
            
            if (pin2 > compPin[type2] || pin2 == 0)
                throw ErrorLink(std::cerr, "pin2 invalide");
            Allcomponents[string1]->setLink(pin1, *Allcomponents[string2], pin2);
            Allcomponents[string2]->setLink(pin2, *Allcomponents[string1], pin1);
            links.push_back({{string1, pin1}, {string2, pin2}});
            
        }
        
        std::string getType()  {
            return "";
        }
        void displayLinks(const std::vector<std::tuple<std::pair<std::string, std::size_t>, std::pair<std::string, std::size_t>>>& links) {
            for (const auto& link : links) {
                const auto& comp1 = std::get<0>(link);
                const auto& comp2 = std::get<1>(link);

                std::cout << "Composant 1 : " << comp1.first << ", Pin : " << comp1.second << " <-> ";
                std::cout << "Composant 2 : " << comp2.first << ", Pin : " << comp2.second << std::endl;
            }
        }

        void simulate(std::size_t tick) override {
            (void) tick;
        }
        Tristate compute(std::size_t pin) override {
            (void) pin;
        return Undefined;
        }    
        
        std::string cleanLine(const std::string &line) {
            std::string cleanedLine = line;
            
            size_t commentPos = cleanedLine.find('#');
            if (commentPos != std::string::npos) {
                cleanedLine = cleanedLine.substr(0, commentPos);
            }
            cleanedLine = std::regex_replace(cleanedLine, std::regex("^\\s+|\\s+$"), "");
            cleanedLine = std::regex_replace(cleanedLine, std::regex("\\s+"), " ");
            return cleanedLine;
        }
       
        void parseFile(const std::string &filename) {
            std::ifstream file(filename);
            std::string name, type;
            std::string line;
            std::regex link_pattern("([a-zA-Z0-9_$]+):(\\d+)");
            std::string str (filename);
            bool linkFound = false;
            
            if (!file.is_open()) {
                throw ErrorsChipset(std::cerr, "File not exist");
            }
            std::string ext = str.substr(str.find_last_of(".") + 1);
            if (ext != "nts")  {
                throw ErrorsChipset(std::cerr, "Bad format file");
            } 
            while (std::getline(file, line)) {
                std::string cleanedLine = cleanLine(line);
                if (cleanedLine.empty()) {
                    continue;
                }
                if (cleanedLine == ".chipsets:") {
                    while (std::getline(file, line)) {
                        cleanedLine = cleanLine(line);
                        if (cleanedLine.empty() || cleanedLine[0] == '#') {
                            continue;
                        }
                        if (cleanedLine == ".links:") {
                            break;
                        }
                        std::istringstream ss(cleanedLine);
                        ss >> type >> name;
                        if (name.empty() || type.empty()) {
                            throw ErrorsChipset(std::cerr, "Error: Missing name or type");
                        }
                        if (Allcomponents.find(name) != Allcomponents.end()) {
                            throw ErrorsChipset(std::cerr, "Name Already exists");
                        }
                        addComponent(name, type);
                    }
                }
                if (cleanedLine == ".links:") {
                    std::string comp1, pin1, comp2, pin2;
                    while (std::getline(file, cleanedLine)) {
                        cleanedLine = cleanLine(cleanedLine);
                        if (cleanedLine.empty() || cleanedLine[0] == '#') {
                            continue;
                        }
                        std::istringstream ss(cleanedLine);
                        std::string link1, link2;
                        ss >> link1 >> link2;
                        if (!std::regex_match(link1, link_pattern) || !std::regex_match(link2, link_pattern)) {
                            throw ErrorLink(std::cerr, "Invalid link format. Expected format: component:pin.");
                        }
                        size_t pos = link1.find(':');
                        size_t position = link2.find(':');
        
                        if (pos != std::string::npos) {
                            comp1 = link1.substr(0, pos);
                            pin1 = link1.substr(pos + 1);
                        }
                        size_t a, b;
                        if (position != std::string::npos) {
                            comp2 = link2.substr(0, position); 
                            pin2 = link2.substr(position + 1);  
                            try {
                                a = std::stoi(pin1);
                                b = std::stoi(pin2);
                            } catch (std::invalid_argument const& ex) {
                                throw ErrorLink(std::cerr, "Pin not exist");                                
                            } catch (std::out_of_range const &ex) {
                                throw ErrorLink(std::cerr, "Out of range");
                            }
                        }
                        addLink(comp1, a, comp2, b);
                        
                        linkFound = true;
                    }
                    if (!linkFound) 
                        throw ErrorLink(std::cerr, "Link not found");    
                }
            }
            if (Allcomponents.empty())
            throw ErrorsChipset(std::cerr, "No chipsets found");
        }        
    };
}

#endif