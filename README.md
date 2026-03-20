# ⚡ NanoTekSpice

> A sophisticated **digital electronics simulator** that builds and executes logic circuits from configuration files. Simulates complex chipsets and their boolean logic interactions with support for undefined states and real-time command execution.

---

## Overview

NanoTekSpice is a logic circuit simulator that brings digital electronics to life. It reads circuit descriptions from configuration files, simulates signal propagation through interconnected components, and provides an interactive interface to control and observe circuit behavior.

### The Problem
Digital circuits are composed of interconnected logic gates and components. Understanding how signals flow through these circuits requires simulation, especially with complex components like counters, flip-flops, and multiplexers. Additionally, circuits rarely have all values immediately defined—some signals depend on others, creating an **undefined state** that must be properly tracked.

### The Solution
A **graph-based circuit simulator** that:
1. Parses circuit descriptions (components and connections)
2. Models each component as a node in a directed graph
3. Simulates clock cycles and signal propagation
4. Tracks three states: `True`, `False`, and `Undefined`
5. Provides interactive control over inputs and observation of outputs

---

##  Key Features

###  Component Library
- **Basic Logic Gates**: AND, OR, XOR, NOT
- **Integrated Circuits (ICs)**:
  - 4001 (NOR gates), 4011 (NAND gates), 4030 (XOR gates)
  - 4069 (Inverters), 4071 (OR gates), 4081 (AND gates)
- **Advanced Components**:
  - 4008 (4-bit adder), 4013 (Dual flip-flop)
  - 4017 (Johnson counter), 4040 (12-bit counter)
  - 4094 (8-bit shift register), 4512 (8-channel selector)
  - 4514 (4-bit decoder), 4801 (RAM), 2716 (ROM)
- **Special Components**:
  - `input` (controllable from CLI)
  - `clock` (auto-toggling on each simulation tick)
  - `true` / `false` (constant values)
  - `output` (circuit observation points)
  - `logger` (records output to binary file)

###  Tristate Logic
Proper handling of the undefined state (U) in all gate operations:
```
A | B | AND | OR | XOR
---------+----+-----+-----
0 | 0 |  0  |  0 |  0
0 | U |  0  |  U |  U
U | U |  U  |  U |  U
```

###  Interactive Command Interface
```
> display          # Show tick count and all I/O values
> simulate         # Run one simulation tick
> loop             # Continuous simulation (Ctrl+C to stop)
> input=value      # Set input to 0, 1, or U
> exit             # Clean shutdown
```

###  Robust Error Handling
- Parse errors with detailed messages
- Component validation
- Circuit integrity checking
- Proper exit codes (0 = success, 84 = error)

---

##  Technical Stack

| Component | Technology | Details |
|-----------|-----------|---------|
| **Language** | C++ | C++17 or later |
| **Build System** | Makefile/CMake | Flexible build configuration |
| **Architecture** | Graph-based | Node = component, Edge = connection |
| **Memory Model** | Smart pointers | `std::unique_ptr<nts::IComponent>` |
| **Exception Handling** | Custom classes | Inherits from `std::exception` |

### Architecture Highlights
- **IComponent Interface**: Polymorphic design for all components
- **Factory Pattern**: Generic `createComponent()` for extensibility
- **Tristate Enum**: `Undefined`, `True`, `False` states
- **Graph Simulation**: Propagates signals through interconnected nodes
- **State Management**: Tracks component state across clock cycles

---

##  Installation & Build

### Prerequisites
- **C++ compiler** supporting C++17 or later (g++, clang)
- **Make** or **CMake** (version 3.10+)
- **Standard libraries**

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/yourusername/nanotekspice.git
cd nanotekspice

# Build with Makefile
make

# Or with CMake
mkdir build && cd build
cmake ..
make
```

### Build Targets
```bash
make        # Build executable
make clean  # Remove object files
make fclean # Remove all generated files
make re     # Rebuild from scratch
```

The executable `nanotekspice` will be created in the project root.

---

##  Usage Guide

### Basic Syntax

```bash
./nanotekspice <circuit_file.nts>
```

### Interactive Commands

| Command | Effect | Example |
|---------|--------|---------|
| `display` | Show all I/O values | `> display` |
| `simulate` | Run one clock cycle | `> simulate` |
| `loop` | Continuous simulation | `> loop` |
| `input=value` | Set input pin value | `> a=1` or `> clk=U` |
| `exit` | Clean shutdown | `> exit` |

### Values
- `0` = False (0V)
- `1` = True (VCC, ~5V)
- `U` = Undefined (unknown)

### Example Session

```bash
$ ./nanotekspice or_gate.nts
> b=0
> a=1
> simulate
> display
tick: 1
input(s):
a: 1
b: 0
output(s):
s: 1
> exit
```

---

##  Configuration File Format

### Structure

```nts
# Comment: describes the circuit

.chipsets:
    [component_type] [component_name]
    ...

.links:
    [name1]:[pin1] [name2]:[pin2]
    ...
```

### Elements

**`.chipsets:` Section**
```nts
.chipsets:
input a              # Input pin named 'a'
input b              # Input pin named 'b'
4071 or_gate         # 4071 IC, named 'or_gate'
output result        # Output pin named 'result'
```

**`.links:` Section**
```nts
.links:
a:1 or_gate:1        # Connect 'a' pin 1 to 'or_gate' pin 1
b:1 or_gate:2        # Connect 'b' pin 1 to 'or_gate' pin 2
or_gate:3 result:1   # Connect 'or_gate' pin 3 to 'result' pin 1
```

### Example: OR Gate Circuit

```nts
# Simple OR gate circuit
.chipsets:
input a
input b
4071 or
output s

.links:
a:1 or:1
b:1 or:2
or:3 s:1
```

### Example: Full Adder Circuit

```nts
# 4-bit adder circuit
.chipsets:
input a0
input a1
input a2
input a3
input b0
input b1
input b2
input b3
4008 adder
output s0
output s1
output s2
output s3
output carry

.links:
a0:1 adder:1
b0:1 adder:2
a1:1 adder:3
b1:1 adder:4
a2:1 adder:5
b2:1 adder:6
a3:1 adder:7
b3:1 adder:8
adder:9 s0:1
adder:10 s1:1
adder:11 s2:1
adder:12 s3:1
adder:13 carry:1
```

---

##  Component Reference

### Special Components

| Component | Pins | Behavior |
|-----------|------|----------|
| `input` | 1 | Controllable via CLI; initially Undefined |
| `output` | 1 | Observation point; displays circuit state |
| `true` | 1 | Always outputs True |
| `false` | 1 | Always outputs False |
| `clock` | 1 | Toggles value each simulation tick |
| `logger` | 8 input + 1 clock + 1 inhibit | Records 8-bit char to `./log.bin` |

### Elementary Gates

| Component | Pins | Function |
|-----------|------|----------|
| `and` | 2 in, 1 out | AND logic |
| `or` | 2 in, 1 out | OR logic |
| `xor` | 2 in, 1 out | XOR logic |
| `not` | 1 in, 1 out | NOT (inverter) |

### IC Families

#### Quadruple Gates (4001, 4011, 4030, 4069, 4071, 4081)
- 4 independent gate instances
- Pins 7 (VSS) and 14 (VDD) ignored
- Example 4081 (AND gates):
  - Gate 1: pins 1,2 (in) → pin 3 (out)
  - Gate 2: pins 5,6 (in) → pin 4 (out)
  - Gate 3: pins 8,9 (in) → pin 10 (out)
  - Gate 4: pins 12,13 (in) → pin 11 (out)

#### 4008: 4-Bit Adder
- Pins 1-8: Inputs (A0-A3, B0-B3)
- Pins 9-12: Sum outputs (S0-S3)
- Pin 13: Carry output
- 2 power pins (ignored)

#### 4013: Dual D Flip-Flop
- Two independent flip-flops
- D input, CLK, Q, Q-bar outputs
- State persistence across cycles

#### 4017: Johnson Decade Counter
- 10-stage shift register
- Clock input, 10 decoded outputs
- Useful for sequencing

#### 4040: 12-Bit Counter
- Cascadable binary counter
- Clock input, 12 bit outputs
- MSB useful for prescaling

#### 4094: 8-Bit Shift Register
- Serial input, 8 parallel outputs
- Clock and latch pins
- Data serialization

#### 4512: 8-Channel Multiplexer
- 8 data inputs, select lines (3 bits)
- Single output
- Channel selection by binary code

#### 4514: 4-Bit Decoder
- 4 binary inputs
- 16 decoded outputs (one-hot)
- Chip inhibit pin

#### 4801: RAM (Random Access Memory)
- Address lines: 10 (1024 addresses)
- Data pins: 8 bits
- Read/Write control
- Addresses 0x00-0x3FF

#### 2716: ROM (Read-Only Memory)
- Address lines: 11 (2048 addresses)
- Data pins: 8 bits
- Read-only operation
- Initialized from `./rom.bin` file

---

##  Simulation Details

### Clock Cycles
Each `simulate` command advances the circuit by one tick:
- All components compute outputs based on current inputs
- `clock` components toggle their value
- State updates propagate through the graph

### Signal Propagation
1. **Set Input**: User sets an input value via CLI
2. **Compute Phase**: Each component calculates output
3. **Propagation**: Signals flow through connected pins
4. **Display**: User observes outputs

### Undefined Behavior
When a component's input is undefined, its output reflects that uncertainty:
- AND gate: `AND(U, 0) = 0`, `AND(U, 1) = U`
- OR gate: `OR(U, 0) = U`, `OR(U, 1) = 1`
- XOR gate: `XOR(U, anything) = U`

This prevents false positive signals in indeterminate circuits.

---

##  Algorithm Overview

### Tristate Logic Implementation

```cpp
enum Tristate {
    Undefined = (-true),  // ~1 = -2
    True = true,          // 1
    False = false         // 0
};
```

### Component Interface

```cpp
class IComponent {
public:
    virtual ~IComponent() = default;
    
    // Compute output for a given pin
    virtual Tristate compute(size_t pin) = 0;
    
    // Run one simulation step
    virtual void simulate(size_t tick) = 0;
    
    // Create connection to another component
    virtual void setLink(size_t pin, IComponent& other, size_t otherPin) = 0;
};
```

### Factory Pattern

```cpp
std::unique_ptr<IComponent> createComponent(const std::string& type) {
    if (type == "input") return std::make_unique<Input>();
    if (type == "4081") return std::make_unique<IC4081>();
    // ... more components
    throw UnknownComponentException(type);
}
```

---

##  Error Handling

| Error | Exit Code | Example |
|-------|-----------|---------|
| Success | 0 | Normal program completion |
| Parse error | 84 | Malformed .nts file |
| Unknown component type | 84 | "Unknown component 'xyz'" |
| Unknown component name | 84 | "Unknown reference 'undefined_pin'" |
| Duplicate component name | 84 | "Component 'a' already defined" |
| No chipsets | 84 | Empty circuit |
| File not found | 84 | Circuit file missing |

### Exception Hierarchy

```cpp
std::exception
└── ComponentException (custom)
    ├── ParseException
    ├── UnknownComponentException
    ├── DuplicateComponentException
    └── InvalidCircuitException
```

---

## Example Workflows

### Example 1: OR Gate Simulation

**Circuit File** (`or_gate.nts`):
```nts
.chipsets:
input a
input b
4071 or
output s

.links:
a:1 or:1
b:1 or:2
or:3 s:1
```

**Execution**:
```bash
$ ./nanotekspice or_gate.nts
> a=0
> b=0
> simulate
> display
tick: 1
input(s):
a: 0
b: 0
output(s):
s: 0
> a=1
> simulate
> display
tick: 2
input(s):
a: 1
b: 0
output(s):
s: 1
> exit
```

### Example 2: Clock-Driven Counter

**Circuit File** (`counter.nts`):
```nts
.chipsets:
clock clk
4040 counter
output q0
output q1
output q2

.links:
clk:1 counter:1
counter:3 q0:1
counter:4 q1:1
counter:5 q2:1
```

**Execution**:
```bash
$ ./nanotekspice counter.nts
> display
tick: 0
input(s):
clk: U
output(s):
q0: U
q1: U
q2: U
> simulate
> display
tick: 1
input(s):
clk: 1
output(s):
q0: 0
q1: 0
q2: 0
> loop
```

---

## 💡 Design Decisions

1. **Graph-Based Architecture**: Components as nodes, pins as edges enable flexible topology
2. **Smart Pointers**: Automatic memory management with `std::unique_ptr`
3. **Tristate Enum**: Type-safe representation of undefined state
4. **Factory Pattern**: Easy component extensibility
5. **Pure Virtual Interface**: Forces consistent implementation across all components
6. **Exception Hierarchy**: Precise error categorization and handling

---

## 🌟 Key Competencies Demonstrated

✅ **Object-Oriented Design**
- Polymorphism through IComponent interface
- Abstract factory pattern
- Clean separation of concerns

✅ **C++ Mastery**
- Smart pointers and memory management
- Exception handling and custom exceptions
- STL containers and algorithms

✅ **Digital Electronics Knowledge**
- Boolean logic and tristate systems
- IC pin configurations and behaviors
- Sequential vs. combinational circuits
- Signal propagation and state management

✅ **Software Architecture**
- Graph data structures for circuit representation
- Simulation algorithms and state machines
- Extensible component system

✅ **Parser Development**
- Lexical and syntactic analysis
- Grammar-based file parsing
- Error reporting and recovery

✅ **Systems Programming**
- Interactive command interface
- Signal handling (SIGINT for loop break)
- Binary file I/O (ROM/logger)
- Exit code conventions

---

##  Bonus Features

### Implemented Bonuses (Optional)
- **Graphical Display**: SVG/PNG circuit visualization (using SFML or SDL)
- **7-Segment Display**: Component displaying hexadecimal digits
- **Pixel Matrix**: 64×64 LED matrix component
- **i4004 Support**: Vintage microprocessor simulation (Turing-complete)
- **Mini Computer**: Full functional computer simulation

### Extension Ideas
```cpp
// Generic component for custom logic
class CustomLogic : public IComponent {
    std::function<Tristate(const std::vector<Tristate>&)> logic;
    // ...
};
```

---

##  References

- **Digital Electronics**: [Wikipedia - Logic Gate](https://en.wikipedia.org/wiki/Logic_gate)
- **IC Datasheets**: Classic CMOS 4000 series documentation
- **C++ Design Patterns**: [Refactoring.guru](https://refactoring.guru/design-patterns/cpp)
- **Graph Algorithms**: [GeeksforGeeks](https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/)

---

##  Troubleshooting

### Build Issues

```bash
# Compiler version too old
# Solution: Ensure C++17 or later support
g++ --version

# Missing dependencies
# Solution: Install build-essential
sudo apt-get install build-essential
```

### Runtime Issues

```bash
# "Unknown component 'xyz'"
# Check: Verify component names match .chipsets section

# Undefined propagation everywhere
# Expected: Normal for circuits with incomplete inputs

# Infinite loops
# Solution: Press Ctrl+C to break from 'loop' command

# ROM not loading
# Check: Ensure ./rom.bin exists in working directory
```

### Testing Circuits

```bash
# Validate circuit file
cat circuit.nts

# Test simple component
echo -e "input a\noutput b\n.links:\na:1 b:1" > test.nts
./nanotekspice test.nts
```

---

##  License

This project is part of an academic exercise. See LICENSE for details.


---

##  Contributing

While this is a completed academic project, contributions and improvements welcome:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing`)
3. Commit changes (`git commit -am 'Add amazing component'`)
4. Push to branch (`git push origin feature/amazing`)
5. Open a Pull Request

---

<div align="center">

**Made with ⚡ and boolean logic**

⭐ If you found this simulator useful, please consider starring the repo!

</div>