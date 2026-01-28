# CH32V00x Bare‑Metal Firmware (GPIO + RCC + UART + Delay)

This project is a **bare‑metal firmware framework** for **CH32V00x (RISC‑V)** MCUs.
It demonstrates how to build **clean, layered drivers** (RCC, GPIO, UART, Delay) and use them in a simple **LED blink application with UART debug prints**.

---

## Project Structure

```
Application (main.c)
│
├── driver_rcc.c / driver_rcc.h      → Clock control + SysTick delay
├── driver_gpio.c / driver_gpio.h    → GPIO configuration & control
├── driver_uart_debug.c / .h         → Debug UART (TX only)
└── startup / SystemInit             → Clock & reset setup
```

Dependency flow:

```
RCC  →  GPIO  →  UART  →  Application
```

---

##  RCC Driver (`driver_rcc`)

### Purpose

Controls **clock enabling** for peripherals and provides **delay utilities**.

---

###  APIs

#### `HAL_RCC_APB2_Enable(RCC_APB2Periph_t periph)`

**What it does**
Enables clock for an APB2 peripheral by setting the corresponding bit in `RCC->APB2PCENR`.

**Logic**

* ORs the peripheral bitmask into `APB2PCENR`
* Safe to call multiple times

**Used in application**

```c
HAL_RCC_APB2_Enable(RCC_GPIOD);
```

Enables the clock for **GPIOD** before configuring LED pins.

---

#### `HAL_RCC_APB2_Disable(RCC_APB2Periph_t periph)`

**What it does**
Disables clock for an APB2 peripheral.

**Logic**

* Clears the peripheral bitmask in `APB2PCENR`

**Used in application**
(Not used – but useful for power saving)

---

###  Delay APIs

#### `HAL_Delay_Init()`

**What it does**
Initializes the delay system (SysTick or busy‑wait based, depending on implementation).

**Logic**

* Prepares timing resources before delays are used

**Used in application**

```c
HAL_Delay_Init();
```

Called once during startup.

---

#### `HAL_Delay_ms(uint32_t ms)`

**What it does**
Provides a **blocking delay in milliseconds**.

**Logic**

* Busy‑wait loop calibrated for system clock

**Used in application**

```c
HAL_Delay_ms(50);
```

Creates visible LED blinking and readable UART output.

---

#### `HAL_Delay_us(uint32_t us)`

**What it does**
Provides a **blocking microsecond delay**.

**Logic**

* Uses NOP‑based loop scaled to CPU clock

**Used in application**
(Not directly used)

---

##  GPIO Driver (`driver_gpio`)

### Purpose

Configures and controls **GPIO pins** using direct register access.

---

###  APIs

#### `HAL_GPIO_Init(GPIO_RegDef_t *GPIOx, uint8_t pin, GPIO_Mode_t mode, GPIO_CNF_t cnf)`

**What it does**
Configures a GPIO pin’s **mode** and **configuration**.

**Logic**

* Each pin uses 4 bits in `CFGLR`
* Clears existing config
* Writes new MODE + CNF combination

**Used in application**

```c
HAL_GPIO_Init(GPIOD, 4,
              GPIO_MODE_OUTPUT_50MHz,
              GPIO_CNF_PUSH_PULL);
```

Configures **PD4 as LED output**.

---

#### `HAL_GPIO_WritePin(GPIO_RegDef_t *GPIOx, uint8_t pin, uint8_t state)`

**What it does**
Sets a GPIO pin HIGH or LOW.

**Logic**

* Writes to output data register

**Used in application**
(Not used – toggle used instead)

---

#### `HAL_GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t pin)`

**What it does**
Toggles the current output state of a pin.

**Logic**

* XOR operation on output data register

**Used in application**

```c
HAL_GPIO_TogglePin(GPIOD, 4);
```

Toggles LED state every loop iteration.

---

#### `HAL_GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t pin)`

**What it does**
Reads current logic level of a GPIO pin.

**Logic**

* Reads input data register
* Shifts and masks pin bit

**Used in application**
(Not used – available for buttons/sensors)

---

##  UART Debug Driver (`driver_uart_debug`)

### Purpose

Provides a **simple TX‑only debug UART** without `printf` or libc.

---

###  APIs

#### `HAL_UART_Init()`

**What it does**
Initializes **USART1 TX** on **PD5** at **115200 baud**.

**Logic**

* Enables clocks for GPIOD, AFIO, and USART1
* Configures PD5 as AF push‑pull
* Sets baud rate register
* Enables transmitter and USART

**Used in application**

```c
HAL_UART_Init();
```

Initializes UART before any debug prints.

---

#### `HAL_UART_SendChar(char c)`

**What it does**
Sends a single character over UART.

**Logic**

* Waits for TXE flag
* Writes character to data register

**Used internally by**

* `HAL_UART_Print()`

---

#### `HAL_UART_Print(const char *str, int32_t val, uint8_t base)`

**What it does**
Prints a string and optionally a number (decimal or hex).

**Logic**

* Sends string character‑by‑character
* Converts integer to ASCII manually
* Supports negative decimal numbers

**Used in application**

```c
HAL_UART_Print("LED Toggle Count: ", UART_NO_NUMBER, 0);
HAL_UART_Print("", led_count, 10);
```

Used for banners and runtime debug logs.

---

##  Application (`main.c`)

### Purpose

Demonstrates **real hardware usage** of all drivers together.

---

### Application Flow

1. System initialization
2. UART initialization for debug
3. Delay system initialization
4. GPIO clock enable
5. LED pin configuration
6. Startup banner via UART
7. Infinite loop:

   * Toggle LED
   * Print counter
   * Delay

---

### Key Application Code

```c
HAL_UART_Init();
HAL_Delay_Init();
HAL_RCC_APB2_Enable(RCC_GPIOD);
HAL_GPIO_Init(GPIOD, 4,
              GPIO_MODE_OUTPUT_50MHz,
              GPIO_CNF_PUSH_PULL);
```

Inside loop:

```c
HAL_GPIO_TogglePin(GPIOD, 4);
HAL_UART_Print("LED Toggle Count: ", UART_NO_NUMBER, 0);
HAL_UART_Print("", led_count, 10);
HAL_UART_Print("\r\n", UART_NO_NUMBER, 0);
HAL_Delay_ms(50);
```

---

flowchart TB
    %% Application Layer
    A[main.c<br/>Application Layer] --> A1[SystemInit()]
    A --> A2[HAL_UART_Init()]
    A --> A3[HAL_Delay_Init()]
    A --> A4[HAL_RCC_APB2_Enable<br/>(RCC_GPIOD)]
    A --> A5[HAL_GPIO_Init<br/>(GPIOD, PD4)]
    A --> A6[while(1) Loop]

    %% Loop operations
    A6 --> L1[HAL_GPIO_TogglePin<br/>(GPIOD, PD4)]
    A6 --> L2[HAL_UART_Print<br/>(LED Toggle Count)]
    A6 --> L3[HAL_Delay_ms(50)]

    %% RCC Driver
    A2 --> R1[RCC Driver]
    A4 --> R1
    R1 --> RR1[RCC->APB2PCENR]

    %% GPIO Driver
    A5 --> G1[GPIO Driver]
    L1 --> G1
    G1 --> GR1[GPIOD->CFGLR]
    G1 --> GR2[GPIOD->OUTDR]

    %% UART Driver
    A2 --> U1[UART Debug Driver]
    L2 --> U1
    U1 --> UR1[USART1->BRR]
    U1 --> UR2[USART1->CTLR1]
    U1 --> UR3[USART1->DATAR]
    U1 --> UR4[USART1->STATR]

    %% Delay / SysTick
    A3 --> D1[Delay / SysTick Driver]
    L3 --> D1
    D1 --> DR1[SysTick->CMP]
    D1 --> DR2[SysTick->CNT]
    D1 --> DR3[SysTick->CTLR]

    %% Styling
    classDef app fill:#E3F2FD,stroke:#1565C0,stroke-width:2px;
    classDef driver fill:#E8F5E9,stroke:#2E7D32,stroke-width:2px;
    classDef reg fill:#FFF3E0,stroke:#EF6C00,stroke-width:2px;

    class A,A1,A2,A3,A4,A5,A6,L1,L2,L3 app;
    class R1,G1,U1,D1 driver;
    class RR1,GR1,GR2,UR1,UR2,UR3,UR4,DR1,DR2,DR3 reg;



