/*
 * EEPROM.h
 *
 *  Created on: Jul 10, 2022
 *      Author: Tejas
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "stm32f4xx_hal.h"

/*
 * DEFINES
 */
#define CS_PORT GPIOB
#define CS_PIN GPIO_PIN_8


/*
 * REGISTERS
 */
#define EEPROM_REG_JEDEC_ID 0x9F

typedef struct {
	SPI_HandleTypeDef *spiHandle;
} EEPROM;

/*
 * INIT
 */
uint8_t EEPROM_Initialize(EEPROM *dev, SPI_HandleTypeDef *spiHandle);

/*
 * ACTIONS
 */
void EEPROM_SetCS(GPIO_PinState pinState);

uint8_t EEPROM_ReadId(EEPROM *dev, uint8_t *data);

#endif /* INC_EEPROM_H_ */
