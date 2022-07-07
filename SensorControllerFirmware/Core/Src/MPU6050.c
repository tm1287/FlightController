#include "MPU6050.h"
#include "constants.h"
#include <math.h>

uint8_t MPU6050_Initialize(MPU6050 *dev, I2C_HandleTypeDef *i2cHandle) {

	dev->i2cHandle = i2cHandle;

	dev->acc_mps2[0] = 0.0f;
	dev->acc_mps2[1] = 0.0f;
	dev->acc_mps2[2] = 0.0f;

	uint8_t errNum = 0;
	HAL_StatusTypeDef status;

	uint8_t regData;

	status = MPU6050_ReadRegister(dev, MPU6050_REG_WHO_AM_I, &regData);
	errNum += (status != HAL_OK);

	if (regData != 0x68) {
		return 255;
	}

	regData = 0;
	status = MPU6050_WriteRegister(dev, MPU6050_REG_PWR_MGMT_1, &regData);
	errNum += (status != HAL_OK);

	regData = 0x07;
	status = MPU6050_WriteRegister(dev, MPU6050_REG_SMPLRT_DIV, &regData);
	errNum += (status != HAL_OK);

	regData = 0x00;
	status = MPU6050_WriteRegister(dev, MPU6050_REG_GYRO_CONFIG, &regData);
	errNum += (status != HAL_OK);

	status = MPU6050_WriteRegister(dev, MPU6050_REG_ACCEL_CONFIG, &regData);
	errNum += (status != HAL_OK);

	return errNum;
}

HAL_StatusTypeDef MPU6050_ReadAccel(MPU6050 *dev) {
	uint8_t accelData[6];
	int16_t Accel_X_RAW = 0;
	int16_t Accel_Y_RAW = 0;
	int16_t Accel_Z_RAW = 0;
	HAL_StatusTypeDef status;

	status = MPU6050_ReadRegisters(dev, MPU6050_REG_ACCEL_XOUT_H, accelData, 6);

	Accel_X_RAW = (int16_t)(accelData[0] << 8 | accelData [1]);
	Accel_Y_RAW = (int16_t)(accelData[2] << 8 | accelData [3]);
	Accel_Z_RAW = (int16_t)(accelData[4] << 8 | accelData [5]);

	//Get approximate acceleration in m/s^2
	dev->acc_mps2[0] = Accel_X_RAW/16384.0 * G_MS2;
	dev->acc_mps2[1] = Accel_Y_RAW/16384.0 * G_MS2;
	dev->acc_mps2[2] = Accel_Z_RAW/16384.0 * G_MS2;

	return status;
}

HAL_StatusTypeDef MPU6050_ReadGyro(MPU6050 *dev) {
	uint8_t gyroData[6];
	int16_t Gyro_X_RAW = 0;
	int16_t Gyro_Y_RAW = 0;
	int16_t Gyro_Z_RAW = 0;
	HAL_StatusTypeDef status;

	status = MPU6050_ReadRegisters(dev, MPU6050_REG_GYRO_XOUT_H, gyroData, 6);

	Gyro_X_RAW = (int16_t)(gyroData[0] << 8 | gyroData [1]);
	Gyro_Y_RAW = (int16_t)(gyroData[2] << 8 | gyroData [3]);
	Gyro_Z_RAW = (int16_t)(gyroData[4] << 8 | gyroData [5]);

	//Convert to rads per second
	dev->gyr_rps[0] = Gyro_X_RAW/131.0 * M_PI / 180;
	dev->gyr_rps[1] = -1 * Gyro_Y_RAW/131.0 * M_PI / 180;
	dev->gyr_rps[2] = -1 * Gyro_Z_RAW/131.0 * M_PI / 180;

	return status;
}

HAL_StatusTypeDef MPU6050_ReadRegister(MPU6050 *dev, uint8_t reg, uint8_t *data) {
	return HAL_I2C_Mem_Read(dev->i2cHandle, MPU6050_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, 1000);
}

HAL_StatusTypeDef MPU6050_ReadRegisters(MPU6050 *dev, uint8_t reg, uint8_t *data, uint8_t length){
	return HAL_I2C_Mem_Read(dev->i2cHandle, MPU6050_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, length, 1000);
}
HAL_StatusTypeDef MPU6050_WriteRegister(MPU6050 *dev, uint8_t reg, uint8_t *data){
	return HAL_I2C_Mem_Write(dev->i2cHandle, MPU6050_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, 1000);
}


