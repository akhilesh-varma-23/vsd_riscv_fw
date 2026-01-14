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

## 1. What is a firmware library?
A firmware library is a collection of pre-written software functions, data structures, and macros provided by hardware manufacturers to simplify the interaction between high-level application code and a device's low-level hardware peripherals. It acts as a Hardware Abstraction Layer (HAL), allowing developers to control complex hardware features without needing to program directly at the register level. 

It is a pre-written software functions and drivers that make it easier to control the hardware peripherals of a microcontroller (GPIO, UART, SPI, I2C, timers, ADC, etc.) without directly manipulating registers every time.

**Layers in Embedded Software**:

Your Application Code <br>
↓ <br>
Firmware Library (HAL / Driver / SDK) <br>
↓ <br>
Hardware Registers <br>
↓ <br>
Microcontroller Hardware


## 2. Why are APIs important?

APIs (Application Programming Interfaces) act as a bridge between the application layer and the driver/firmware layer. They define a standard way for the application to request services from the drivers without needing to know hardware-specific details. This separation improves clarity, safety, and flexibility in embedded system design.

- Separate application logic from hardware control
- Improve code readability and clarity
- Enable portability across different hardware
- Prevent unsafe or invalid hardware access
- Support reuse of drivers and application code
- Make testing and debugging easier

API's used in the task1 are `gpio_init`, `gpio_write` and `gpio_read`.

## 3. What you understood from this task

- file `gpio.h` is the driver header file, where all the API's, macros are declared.
- file `gpio.c` is the driver source file, where all the API's are implemented. This code is actually interact with the hardware registers (GPIO Registers). We can modify (enable, disable, set, reset, read, write, mode change) the bits in that register. By changing the register values, we can actually control the hardware peripheral (GPIO).
- file `main.c` is our main application code. In this code, we are calling API's and passing our required input parameters (such as pin numbers, values to be written, mode input/output). Now in `gpio.c`, it will take the input parameters and execute the respective API code which is getting called in `main.c`. 
- Like this we can control our hardware registers, which are developed in driver source file `gpio.c`, by calling that API's and passing some parameters, in our application code `main.c`.

`main.c`(Your Application Code) <br>
↓ <br>
`gpio.h`, `gpio.c`(Firmware Library (HAL / Driver / SDK)) <br>
↓ <br>
Hardware Registers <br>
↓ <br>
Microcontroller Hardware


## Screenshots of:

   * Successful compilation
     
     ![alt text](image.png)

   * Program output

      ![alt text](<img1.png>)



---



