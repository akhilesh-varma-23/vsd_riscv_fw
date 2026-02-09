# UART Command Console + GPIO Control Panel

## Project Description
A bare-metal embedded firmware project that implements a **UART-based Command Line Interface (CLI)** to control and monitor GPIO pins on a microcontroller board. Users interact through a serial terminal to turn LEDs on/off, blink with configurable delay and count, and read pin states. The goal is to demonstrate modular driver design, command parsing, and real-time hardware control without an RTOS.

---

## Drivers Used
- **GPIO Driver** – Pin configuration, read/write, toggle operations.
- **UART Driver** – Serial communication for CLI input/output.
- **Timer / Delay Driver** – Millisecond and microsecond delays.
- **PWM Driver (Optional)** – Can be extended for brightness control or buzzer output.

---

## API Summary (Key Functions)

### GPIO
- `HAL_GPIO_Init(port, pin, mode, cnf)`
- `HAL_GPIO_WritePin(port, pin, state)`
- `HAL_GPIO_TogglePin(port, pin)`
- `HAL_GPIO_ReadPin(port, pin)`

### UART
- `HAL_UART_Init()`
- `HAL_UART_SendChar(c)`
- `HAL_UART_SendString(str)`
- `HAL_UART_ReadChar()`
- `HAL_UART_ReadLine(buf, len)`
- `HAL_UART_Print(str, val, base)`

### Timer / Delay
- `HAL_Delay_Init()`
- `HAL_Delay_ms(ms)`
- `HAL_Delay_us(us)`

### CLI
- `CLI_Process(cmd)`

---

## main.c – Brief Explanation

- **Header Includes**
  - `driver_rcc.h` – Clock control functions.
  - `driver_gpio.h` – GPIO configuration and control.
  - `driver_usart_debug.h` – UART communication.
  - `cli.h` – Command Line Interface logic.

- **LED Configuration Macros**
  - `LED_PORT` and `LED_PIN` define which GPIO pin the LED is connected to.
  - Makes hardware changes easy without modifying logic.

- **Command Buffer**
  - `char cmd_buffer[64];`
  - Stores user input received from UART.
  - Limits command length to prevent overflow.

- **System Initialization**
  - `SystemInit();`
  - Configures system clock and core MCU setup.

- **Delay Initialization**
  - `HAL_Delay_Init();`
  - Prepares millisecond/microsecond delay functions.

- **UART Initialization**
  - `HAL_UART_Init();`
  - Sets baud rate, configures TX/RX pins, enables USART.
  - Allows communication with PC serial terminal.

- **Enable GPIO Clock**
  - `HAL_RCC_APB2_Enable(RCC_GPIOD);`
  - Turns on clock for the GPIO port used by LED.

- **GPIO Configuration**
  - `HAL_GPIO_Init(LED_PORT, LED_PIN, ...)`
  - Sets LED pin as output so it can be controlled.

- **Startup Banner**
  - Sends welcome messages via UART.
  - Confirms firmware boot and CLI readiness.

- **Infinite Loop (`while(1)`)**
  - Runs forever (standard embedded pattern).
  - Inside loop:
    - Prints prompt `"> "`.
    - `HAL_UART_ReadLine()` waits for user command.
    - `CLI_Process(cmd_buffer)` parses and executes command.

- **`return 0;`**
  - Never reached in practice.
  - Present only to satisfy C `main` function structure.

**Overall Role:**  
`main.c` is the **entry point** that initializes drivers and continuously runs the UART CLI to control GPIO through user commands.
---
## cli.c – Brief Explanation

- **Header Include**
  - `cli.h` – Contains function declarations and required macros.
  - Also depends on UART, GPIO, and Delay drivers indirectly.

- **`str_to_lower()` Function**
  - Converts the entire command string to lowercase.
  - Ensures **case-insensitive command matching** (e.g., `LED ON` = `led on`).
  - Modifies the original buffer in place.
  - Declared `static` so it is used only inside `cli.c`.

- **`CLI_Process(char *cmd)` Function**
  - Core function that **parses and executes user commands**.
  - Receives a null-terminated string from UART input.

---

### Command Handling Flow

- **Normalize Input**
  - Calls `str_to_lower(cmd)` before comparisons.

- **`help` Command**
  - Prints list of all supported commands over UART.

- **`led on`**
  - Sets LED GPIO pin HIGH.
  - Sends confirmation message.

- **`led off`**
  - Sets LED GPIO pin LOW.
  - Sends confirmation message.

- **`blink <ms> <count>`**
  - Uses `sscanf()` to extract delay and blink count.
  - Validates input values.
  - Toggles LED with specified delay and repetitions.
  - Blocking operation (no other commands accepted during blink).

- **`read <pin>`**
  - Converts pin number using `atoi()`.
  - Validates pin range (0–15).
  - Reads GPIO input state.
  - Prints HIGH/LOW value via UART.

- **Unknown Command**
  - Displays `"Error: Unknown command"` if no match found.

---

### Overall Role
`cli.c` acts as the **command interpreter layer**, sitting between UART input and hardware drivers.  
It translates user text commands into GPIO actions and UART responses, forming the interactive control interface of the project.
---

## Build and Flash Instructions

1. Open the PlatformIO project
2. Connect the VSDSquadron Mini board
3. Build the project
4. Upload the firmware using USB 2.0 to TTL UART serial converter
5. Open a serial terminal in PuTTY to view UART logs

---

## UART Configuration

1. UART Port: UART1
2. Baud Rate: 115200
3. Data Format: 8 data bits, No parity, 1 stop bit (8N1)
4. UART output displays timestamped logs confirming correct timer operation.
