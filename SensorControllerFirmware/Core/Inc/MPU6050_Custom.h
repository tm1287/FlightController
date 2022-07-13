/*
 * MPU6050.h
 *
 *  Created on: Jul 7, 2022
 *      Author: Tejas
 */

#ifndef INC_MPU6050_CUSTOM_H_
#define INC_MPU6050_CUSTOM_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

/*
 * DEFINES
 */
#define MPU6050_I2C_ADDR (0x68 << 1)

/*
 * REGISTERS
 */
#define MPU6050_REG_WHO_AM_I 0x75
#define MPU6050_REG_PWR_MGMT_1 0x6B
#define MPU6050_REG_SMPLRT_DIV 0x19
#define MPU6050_REG_GYRO_CONFIG 0x1B
#define MPU6050_REG_ACCEL_CONFIG 0x1C
#define MPU6050_REG_ACCEL_XOUT_H 0x3B
#define MPU6050_REG_GYRO_XOUT_H 0x43
#define MPU6050_RA_BANK_SEL 0x6D
#define MPU6050_RA_MEM_START_ADDR 0x6E
#define MPU6050_RA_I2C_SLV0_ADDR 0x25
#define MPU6050_RA_USER_CTRL 0x6A

/*
 * BIT POSITIONS
 */
#define MPU6050_USERCTRL_I2C_MST_EN_BIT 5
#define MPU6050_USERCTRL_I2C_MST_RESET_BIT 1

/*
 * SENSOR_STRUCT
 */
typedef struct {
	I2C_HandleTypeDef *i2cHandle;

	float acc_mps2[3];

	float gyr_rps[3];

} MPU6050;

/*
 * INIT
 */
uint8_t MPU6050_Initialize(MPU6050 *dev, I2C_HandleTypeDef *i2cHandle);
/*
 * DAQ
 */
HAL_StatusTypeDef MPU6050_ReadAccel(MPU6050 *dev);
HAL_StatusTypeDef MPU6050_ReadGyro(MPU6050 *dev);

/*
 * LOW-LEVEL FUNCTIONS
 */
HAL_StatusTypeDef MPU6050_ReadByte(MPU6050 *dev, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef MPU6050_ReadBytes(MPU6050 *dev, uint8_t reg, uint8_t *data, uint8_t length);
HAL_StatusTypeDef MPU6050_WriteByte(MPU6050 *dev, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef MPU6050_WriteBit(MPU6050 *dev, uint8_t reg, uint8_t bitNum, uint8_t data);
HAL_StatusTypeDef MPU6050_WriteBits(MPU6050 *dev, uint8_t reg, uint8_t bitStart, uint8_t length, uint8_t data);
void MPU6050_SetMemoryBank(MPU6050 *dev, uint8_t bank, bool prefetchEnabled, bool userBank);
void MPU6050_SetMemoryStartAddress(MPU6050 *dev, uint8_t address);
void MPU6050_SetSlaveAddress(MPU6050 *dev, uint8_t num, uint8_t address);
void MPU6050_SetI2CMasterModeEnabled(MPU6050 *dev, bool enabled);
void MPU6050_ResetI2CMaster(MPU6050 *dev);
void MPU6050_SetClockSource(MPU6050 *dev, uint8_t source);

#endif /* INC_MPU6050_CUSTOM_H_ */
