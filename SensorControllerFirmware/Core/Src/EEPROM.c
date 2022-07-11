/*
 * EEPROM.c
 *
 *  Created on: Jul 10, 2022
 *      Author: Tejas
 */

#include "EEPROM.h"

uint8_t EEPROM_Initialize(EEPROM *dev, SPI_HandleTypeDef *spiHandle) {
	dev->spiHandle = spiHandle;

	uint8_t errNum = 0;

	return errNum;
}

void EEPROM_SetCS(GPIO_PinState pinState) {
	HAL_GPIO_WritePin(CS_PORT, CS_PIN, pinState);
}

uint8_t EEPROM_ReadId(EEPROM *dev, uint8_t *data) {
	EEPROM_SetCS(GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(dev->spiHandle, (uint8_t *)0x9f, data, 1, 1000);
	EEPROM_SetCS(GPIO_PIN_SET);
	return 0;
}
