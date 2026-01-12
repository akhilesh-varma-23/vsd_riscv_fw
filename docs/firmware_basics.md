# Embedded Firmware Basics

This document provides background concepts required for the internship.

---

## What is Embedded Firmware?

Embedded firmware is low-level software that runs directly on a microcontroller or SoC.  
It controls hardware peripherals such as GPIO, timers, serial interfaces, and sensors.

Firmware sits between:
- the hardware (registers, peripherals)
- and higher-level application logic

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
