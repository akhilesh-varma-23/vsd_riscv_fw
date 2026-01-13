# Embedded Firmware Basics

This document provides background concepts required for the internship.

---

## What is Embedded Firmware?

Embedded firmware is low-level software that runs directly on a microcontroller or SoC.  
It controls hardware peripherals such as GPIO, timers, serial interfaces, and sensors.

Firmware sits between:
- the hardware (registers, peripherals)
- and higher-level application logic

**Different types of firmware development** are :
There are several ways to develop the firmware for a particular microcontroller depending on the
resources provided by the microcontroller’s manufacturer.

- **Hardware Abstraction Layer (HAL)**: 
    It simplifies the process by offering high-level APIs for configuring every aspect of the microcontroller.

    - **Level of abstraction**: High
    - **Ease of use**: Easier for beginners due to its high-level abstraction
    - **Code verbosity**: More verbose, with several lines of code required for simple tasks
    - **Portability**: Excellent across different RISC-V devices
    - **Performance**: Slightly slower due to additional abstraction layers

- **Low Layer (LL)**:
    The LL library is a leaner alternative to HAL, offering a faster, more expert-oriented approach that’s closer to the hardware.

    - **Level of abstraction**: Medium
    - **Ease of use**: Moderate, with a balance between abstraction and direct control
    - **Code verbosity**: Less verbose than HAL, offering a more straightforward approach to hardware    interaction.
    - **Portability**: Good, but slightly less than HAL
    - **Performance**: Faster than HAL, as it’s closer to the hardware

- **Bare-Metal C programming**: 
    With this approach, we dive right into the hardware, accessing the microcontroller’s registers directly using the C language. It’s more involved but offers a deeper understanding of the microcontroller’s workings.

    - **Level of abstraction**: Low
    - **Ease of use**: Challenging for beginners, as it requires in-depth hardware knowledge
    - **Code verbosity**: Less verbose, direct
    - **Portability**: Limited, as the code is often specific to a particular hardware setup
    - **Performance**: Very high, as it allows for direct and optimized hardware manipulation

- **Assembly language**: 
    This is similar to Bare-Metal C, but instead of C, we use assembly language to interact directly with the microcontroller’s registers.

    - **Level of abstraction**: Lowest
    - **Ease of use**: Most challenging, requiring a thorough understanding of the microcontroller’s architecture
    - **Code verbosity**: Can be verbose for complex tasks, due to low-level nature
    - **Portability**: Very limited, as it is highly specific to the microcontroller’s architecture
    - **Performance**: Highest, as it allows for the most optimized and direct control possible

---

## What is a Firmware Library or API?

A firmware library is a collection of reusable functions that provide a clean interface to hardware.

Example:
```c
gpio_write(LED_PIN, 1);
```

Internally, this function may:
- configure registers
- set or clear bits
- handle hardware-specific details

The application code does not need to know those details.

---
## Why APIs Matter
In industry:
- firmware is reused across projects
- hardware may change, APIs should not
- clear APIs reduce bugs and development time

This internship focuses on **building such APIs**

---

## Bare-Metal Firmware

Bare-metal firmware runs without an operating system.

Characteristics:
- No scheduler
- No tasks or threads
- Code runs directly from main()

This approach helps engineers:
- understand timing clearly
- debug hardware interactions
- build strong fundamentals

---

## What You Will Build in This Internship
- Core firmware APIs (GPIO, timing, serial)
- One complete peripheral driver or library
- Hardware-tested examples

