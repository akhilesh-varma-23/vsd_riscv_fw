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

**Layers in Firmware**:

![alt text](<img2.jpeg>)

### Hardware Layer
This is the actual physical circuitry inside the RISC-V chip — CPU, GPIO, UART, timers, memories.

- For Example taken GPIO as reference:
It contains pullup/pulldown resistors and logic that drive a real pin high or low when a register bit is written.
  - GPIO registers
      DATA register
      DIR (direction) register
      ```
      0x40020000 → GPIO_DATA // for example I have taken for reference with dummy addresses
      0x40020004 → GPIO_DIR
      ```
    Suppose Pin 5 controls the physical LED

### Bootloader Layer
This is the first software that runs after reset.
It prepares the chip so that the main firmware can run.
Purpose: “Bring the hardware to a usable state and load the firmware.”
- For GPIO
It may turn on an LED or set pin directions to show that the system has powered up.

```
*(volatile uint32_t*)0x40020004 |= (1 << 5);   // Set pin 5 as OUTPUT
*(volatile uint32_t*)0x40020000 |= (1 << 5);   // Turn LED ON
```

### HAL / Driver Layer
This layer converts hardware registers into C functions.
It hides addresses and bit operations from higher software.

- For GPIO
```
#define GPIO_BASE 0x40020000

typedef struct {
    volatile uint32_t DATA;
    volatile uint32_t DIR;
} GPIO_Type;

#define GPIO ((GPIO_Type*)GPIO_BASE)

void gpio_set_output(int pin)
{
    GPIO->DIR |= (1 << pin);
}

void gpio_write(int pin, int value)
{
    if(value)
        GPIO->DATA |= (1 << pin);
    else
        GPIO->DATA &= ~(1 << pin);
}
```
Instead of writing to 0x40020000, you call gpio_write(5,1).
Now no one touches addresses directly.
Purpose: “Make hardware easy and safe to use.”

### Middleware Layer
This layer provides reusable system services built on drivers.
Uses drivers to provide services.

- For GPIO
LED Service
```
void LED_On()
{
    gpio_write(5, 1);
}

void LED_Off()
{
    gpio_write(5, 0);
}
```
Now application doesn’t know about GPIO pins.

### RTOS / Scheduler
This layer decides which code runs and when.
It manages tasks, delays, priorities, and timing.

- For GPIO
RTOS decides when LED blinks.
```
void LedTask(void *p)
{
    while(1)
    {
        LED_On();
        vTaskDelay(500);
        LED_Off();
        vTaskDelay(500);
    }
}
```
Purpose: “Manage timing and multitasking.”

### Application Layer
This is the actual product logic written by the developer.
- For GPIO
```
if (temperature > 80)
    LED_On();      // warning indicator
else
    LED_Off();
```
Application never touches registers or drivers.

---

## 2. Why are APIs important?

APIs (Application Programming Interfaces) act as a bridge between the application layer and the driver/firmware layer. They define a standard way for the application to request services from the drivers without needing to know hardware-specific details. This separation improves clarity, safety, and flexibility in embedded system design.

- Separate application logic from hardware control
- Improve code readability and clarity
- Enable portability across different hardware
- Prevent unsafe or invalid hardware access
- Support reuse of drivers and application code
- Make testing and debugging easier

API's used in the task1 are `gpio_init`, `gpio_write` and `gpio_read`.

---

## 3. What you understood from this task

- file `gpio.h` is the driver header file, where all the API's, macros are declared.
- file `gpio.c` is the driver source file, where all the API's are implemented. This code is actually interact with the hardware registers (GPIO Registers). We can modify (enable, disable, set, reset, read, write, mode change) the bits in that register. By changing the register values, we can actually control the hardware peripheral (GPIO).
- file `main.c` is our main application code. In this code, we are calling API's and passing our required input parameters (such as pin numbers, values to be written, mode input/output). Now in `gpio.c`, it will take the input parameters and execute the respective API code which is getting called in `main.c`. 
- Like this we can control our hardware registers, which are developed in driver source file `gpio.c`, by calling that API's and passing some parameters, in our application code `main.c`.

`main.c`(Your Application Code) <br>
↓ <br>
`gpio.h`, `gpio.c`(Firmware Library (HAL / Driver / SDK)) <br>
↓ <br>
Peripherals Hardware Registers <br>
↓ <br>
Microcontroller Peripherals Hardware


## Screenshots of:

   * Successful compilation
     
     ![alt text](image.png)

   * Program output

      ![alt text](<img1.png>)



---



