# Task 1: Firmware Library Fundamentals

## Objective

The goal of Task 1 is to:

- Understand how firmware libraries are structured  
- Understand how application code uses APIs  
- Set up a basic development environment  
- Build and study a simple firmware-style library  

This task does **not** require the VSDSquadron Mini board.

---


## What to Do

### Step 1: Read the Code

- Open `gpio.h` and understand the exposed API  
- Open `gpio.c` and see how the API is implemented  
- Open `main.c` and observe how the API is used by the application  

---

### Step 2: Build the Code

From inside the `task1` directory, run:

```bash
gcc main.c gpio.c -o task1_demo
````

---

### Step 3: Run the Program

```bash
./task1_demo
```

---

## Expected Output

Console messages simulating GPIO behavior:

- Starting firmware application
- GPIO 5 initialized as OUTPUT
- GPIO 3 initialized as INPUT
- GPIO 5 write value: 1
- GPIO 3 read value
- Button state: 1
- GPIO 5 write value: 0
- Firmware application finished
---

## What is a firmware library?
A firmware library is a collection of pre-written software functions, data structures, and macros provided by hardware manufacturers to simplify the interaction between high-level application code and a device's low-level hardware peripherals. It acts as a Hardware Abstraction Layer (HAL), allowing developers to control complex hardware features without needing to program directly at the register level. 

It is a pre-written software functions and drivers that make it easier to control the hardware peripherals of a microcontroller (GPIO, UART, SPI, I2C, timers, ADC, etc.) without directly manipulating registers every time.

Layers in Embedded Software:

Your Application Code <br>
↓ <br>
Firmware Library (HAL / Driver / SDK) <br>
↓ <br>
Hardware Registers <br>
↓ <br>
Microcontroller Hardware


## Why are APIs important?


1. A short explanation (Markdown or PDF) covering:

   * What is a firmware library?
   * Why are APIs important?
   * What you understood from this task

2. Screenshots of:

   * Successful compilation
   * Program output

3. GitHub repository link (forked or personal)

---



