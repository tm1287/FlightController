/*
 * MPU6050.h
 *
 *  Created on: Jul 7, 2022
 *      Author: Tejas
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "stm32f4xx_hal.h"

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
HAL_StatusTypeDef MPU6050_ReadRegister(MPU6050 *dev, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef MPU6050_ReadRegisters(MPU6050 *dev, uint8_t reg, uint8_t *data, uint8_t length);
HAL_StatusTypeDef MPU6050_WriteRegister(MPU6050 *dev, uint8_t reg, uint8_t *data);

#endif /* INC_MPU6050_H_ */
