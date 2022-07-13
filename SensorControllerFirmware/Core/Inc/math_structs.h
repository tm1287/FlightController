/*
 * 3dmath.h
 *
 *  Created on: 17. 3. 2022
 *      Author: z00486pr
 */

#ifndef I2CDEVLIB_MPU6050_MATH_STRUCTS_H_
#define I2CDEVLIB_MPU6050_MATH_STRUCTS_H_



typedef struct {
	float w;
	float x;
	float y;
	float z;
} Quaternion;

typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
}VectorInt16;

typedef struct{
	float x;
	float y;
	float z;
}VectorFloat;

#endif /* I2CDEVLIB_MPU6050_MATH_STRUCTS_H_ */
