# Driver Public API Documentation

---

# GPIO Driver

## `HAL_GPIO_Init`

```
void HAL_GPIO_Init(GPIO_RegDef_t *GPIOx, uint8_t pin, GPIO_Mode_t mode, GPIO_CNF_t cnf);
###Purpose
Configures a GPIO pin with selected mode and configuration.

###Parameters

GPIOx – GPIO port (GPIOA, GPIOC, GPIOD…)

pin – Pin number (0–15)

mode – Input/Output speed mode

cnf – Push-pull, open-drain, floating, etc.

###Return Values
None

###Constraints / Notes

RCC clock for the port must be enabled first.

Only valid pin numbers (0–15).

###Example

HAL_GPIO_Init(GPIOD, 4, GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_PUSH_PULL);
```
## `HAL_GPIO_WritePin`
```
void HAL_GPIO_WritePin(GPIO_RegDef_t *GPIOx, uint8_t pin, uint8_t state);


Purpose
Sets GPIO pin HIGH or LOW.

Parameters

state – 1 = HIGH, 0 = LOW

Notes

Pin must be configured as output.

Example

HAL_GPIO_WritePin(GPIOD, 4, 1);
```

## `HAL_GPIO_TogglePin`
```
void HAL_GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t pin);


Purpose
Flips the current output state of the pin.

Example

HAL_GPIO_TogglePin(GPIOD, 4);
```
## `HAL_GPIO_ReadPin`
```
uint8_t HAL_GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t pin);


Purpose
Reads logic level of a pin.

Return

0 = LOW, 1 = HIGH
```

# UART Driver
## `HAL_UART_Init`
```
void HAL_UART_Init(void);


Purpose
Initializes USART peripheral and configures TX/RX pins.

Notes

Sets baud rate and enables TX/RX.
```
## `HAL_UART_SendChar`
```
void HAL_UART_SendChar(char c);


Purpose
Transmits one character.
```
## `HAL_UART_SendString`
```
void HAL_UART_SendString(const char *s);


Purpose
Sends null-terminated string over UART.

Example

HAL_UART_SendString("Hello\r\n");
```

## `HAL_UART_ReadChar`
```
char HAL_UART_ReadChar(void);


Purpose
Receives a single character (blocking).
```
## `HAL_UART_ReadLine`
```
void HAL_UART_ReadLine(char *buf, uint8_t maxLen);


Purpose
Reads a full line from terminal until ENTER.

Notes

Handles backspace and echo.
```
## `HAL_UART_Print`
```
void HAL_UART_Print(const char *str, int32_t val, uint8_t base);


Purpose
Prints string + optional number (decimal/hex).
```
# RCC / Delay Driver
## `HAL_RCC_APB2_Enable`
```
void HAL_RCC_APB2_Enable(RCC_APB2Periph_t periph);


Purpose
Enables peripheral clock.
```
## `HAL_RCC_APB2_Disable`
```
void HAL_RCC_APB2_Disable(RCC_APB2Periph_t periph);


Purpose
Disables peripheral clock.
```
## `HAL_Delay_Init`
```
void HAL_Delay_Init(void);


Purpose
Initializes delay system.
```

## `HAL_Delay_ms`
```
void HAL_Delay_ms(uint32_t ms);


Purpose
Blocking millisecond delay.
```
## `HAL_Delay_us`
```
void HAL_Delay_us(uint32_t us);


Purpose
Blocking microsecond delay.
```
# CLI Driver
## `CLI_Process`
```
void CLI_Process(char *cmd);


Purpose
Parses and executes user command string.

Supported Commands

help

led on

led off

blink <ms> <count>

read <pin>

Notes

Case-insensitive.

Blocking during blink.

Example

CLI_Process("led on");
```
