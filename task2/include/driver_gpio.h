#include <stddef.h>
#include <stdint.h>

#define FLASH_START               (0x00000000U)
#define SRAM_START                (0x20000000U)
#define PERIPHERALS_BASEADDR      (0x40000000U)

#define GPIOA_BASEADDR              (PERIPHERALS_BASEADDR + 0x010800U)
#define GPIOC_BASEADDR              (PERIPHERALS_BASEADDR + 0x011000U)
#define GPIOD_BASEADDR              (PERIPHERALS_BASEADDR + 0x011400U)

#define RCC_BASEADDR                (PERIPHERALS_BASEADDR + 0x021000U)



typedef struct 
{
    /* data */
    volatile uint32_t CFGLR;
    volatile uint32_t INDR;
    volatile uint32_t OUTDR;
    volatile uint32_t BSHR;
    volatile uint32_t BCR;
    volatile uint32_t LCKR;
}GPIO_RegDef_t;


typedef struct
{
    uint8_t GPIO_PinNumber;         /* Possible values from @GPIO_PIN_NUMBERS                           */
    uint8_t GPIO_PinMode;           /* Possible values from @GPIO_PIN_MODES                             */
    uint8_t GPIO_PinSpeed;          /* Possible values from @GPIO_PIN_SPEED                             */
    uint8_t GPIO_PinPuPdControl;    /* Possible values from @GPIO_PIN_PULL_UP_PULL_DOWN                 */
    uint8_t GPIO_PinOPType;         /* Possible values from @GPIO_PIN_OUTPUT_TYPE                       */
    uint8_t GPIO_PinAltFunMode;     /* Has value only when @GPIO_PIN_MODES is set to Alt functionality  */
}GPIO_PinConfig_t;



typedef struct 
{
    /* data */
    volatile uint32_t CTLR;
    volatile uint32_t CFGR0;
    volatile uint32_t INTR;
    volatile uint32_t APB2PRSTR;
    volatile uint32_t APB1PRSTR;
    volatile uint32_t AHBPCENR;
    volatile uint32_t APB2PCENR;
    volatile uint32_t APB1PCENR;
    volatile uint32_t RSTSCKR;
}RCC_RegDef_t;


void HAL_gpio_init();
void HAL_gpio_set();
void HAL_gpio_clear();
void HAL_gpio_toggle(GPIO_RegDef_t *pGPIOx , uint8_t PINnumber);
uint32_t HAL_gpio_read();



