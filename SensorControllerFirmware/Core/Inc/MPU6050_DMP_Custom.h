/*
 * MPU6050_DMP.h
 *
 *  Created on: Jul 12, 2022
 *      Author: Tejas
 */

#ifndef INC_MPU6050_DMP_CUSTOM_H_
#define INC_MPU6050_DMP_CUSTOM_H_

#include <MPU6050_Custom.h>
#include "stm32f4xx_hal.h"

uint8_t MPU6050_InitializeDMP(MPU6050 *dev, I2C_HandleTypeDef *i2cHandle);




#endif /* INC_MPU6050_DMP_CUSTOM_H_ */
