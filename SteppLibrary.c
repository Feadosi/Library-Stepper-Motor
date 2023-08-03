/*
 * SteppLibrary.c
 *
 *  Created on: Dec 8, 2022
 *      Author: feodosiy
 */

/**
  ******************************************************************************
  * @file           : SteppLibrary.c
  * @brief          : step body
  ******************************************************************************
  */


#include "SteppLibrary.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim7;
extern uint32_t cnt;
extern uint8_t accessFlag;
extern uint8_t Package_Data[4000][2];
uint8_t c=0;

//******************FUNCTIONS************************
//------------------------------------------------------------------------------------------
void StepMotorInit()
{
	HAL_GPIO_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_RED_PORT, LED_RED_PIN, GPIO_PIN_RESET);

	HAL_TIM_Base_Start_IT(&htim2);
	StartingPoint();
	HAL_TIM_Base_Stop_IT(&htim2);

	HAL_GPIO_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_RED_PORT, LED_RED_PIN, GPIO_PIN_RESET);
}
//------------------------------------------------------------------------------------------
void StartingPoint()
{
	c=0;
	while(1)
	{
		if(HAL_GPIO_ReadPin(LIMIT_SWITCH_VECTOR_PORT, LIMIT_SWITCH_VECTOR_PIN) == GPIO_PIN_RESET)
		{
			StepMotorVector(1, MOVE_FROM_CENTER, SPEED_DELAY_FOR_VECTOR);
		}
		if(HAL_GPIO_ReadPin(LIMIT_SWITCH_UPDOWN_PORT, LIMIT_SWITCH_UPDOWN_PIN) == GPIO_PIN_RESET)
		{
			StepMotorUpDown(1, UP, SPEED_DELAY_FOR_UP_DOWN);
			c++;
		}
		if(HAL_GPIO_ReadPin(LIMIT_SWITCH_VECTOR_PORT, LIMIT_SWITCH_VECTOR_PIN) == GPIO_PIN_SET && HAL_GPIO_ReadPin(LIMIT_SWITCH_UPDOWN_PORT, LIMIT_SWITCH_UPDOWN_PIN) == GPIO_PIN_SET)
		{
			break;
		}
	}
	printf("C = %d\n", c);
}
//------------------------------------------------------------------------------------------
void Pump(uint8_t state)
{
	if(state == ENABLE_PUMP)
	{
		HAL_GPIO_WritePin(PUMP_PORT, PUMP_PIN, GPIO_PIN_SET);
	}
	else if(state == DISABLE_PUMP)
	{
		HAL_GPIO_WritePin(PUMP_PORT, PUMP_PIN, GPIO_PIN_RESET);
	}
}
//------------------------------------------------------------------------------------------
void MicroDelay(uint16_t delay)
{
  __HAL_TIM_SET_COUNTER(&htim7, 0);
  while (__HAL_TIM_GET_COUNTER(&htim7) < delay);
}
//------------------------------------------------------------------------------------------
void StepMotorRotation(uint32_t steps, uint8_t direction, uint16_t delay)
{
	uint32_t k;
	if (direction == 0)
		HAL_GPIO_WritePin(DIR_PORT_AN, DIR_PIN_AN, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(DIR_PORT_AN, DIR_PIN_AN, GPIO_PIN_RESET);

	for(k = 0; k < steps; k++)
	{
		HAL_GPIO_WritePin(STEP_PORT_AN, STEP_PIN_AN, GPIO_PIN_SET);
		MicroDelay(delay);
		HAL_GPIO_WritePin(STEP_PORT_AN, STEP_PIN_AN, GPIO_PIN_RESET);
		MicroDelay(delay);
	}
}
//------------------------------------------------------------------------------------------
void StepMotorVector(uint32_t steps, uint8_t direction, uint16_t delay)
{
	uint32_t k;
	if (direction == 0)
		HAL_GPIO_WritePin(DIR_PORT_RV, DIR_PIN_RV, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(DIR_PORT_RV, DIR_PIN_RV, GPIO_PIN_RESET);

	for(k = 0; k < steps; k++)
	{
		HAL_GPIO_WritePin(STEP_PORT_RV, STEP_PIN_RV, GPIO_PIN_SET);
		MicroDelay(delay);
		HAL_GPIO_WritePin(STEP_PORT_RV, STEP_PIN_RV, GPIO_PIN_RESET);
		MicroDelay(delay);
	}
}
//------------------------------------------------------------------------------------------
void StepMotorUpDown(uint32_t steps, uint8_t direction, uint16_t delay)
{
	uint32_t k;
	if (direction == 0)
		HAL_GPIO_WritePin(DIR_PORT_UD, DIR_PIN_UD, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(DIR_PORT_UD, DIR_PIN_UD, GPIO_PIN_RESET);

	//steps = steps / 5;
	for(k = 0; k < steps; k++)
	{
		HAL_GPIO_WritePin(STEP_PORT_UD, STEP_PIN_UD, GPIO_PIN_SET);
		MicroDelay(delay);
    	HAL_GPIO_WritePin(STEP_PORT_UD, STEP_PIN_UD, GPIO_PIN_RESET);
    	MicroDelay(delay);
	}
}
//------------------------------------------------------------------------------------------
void ConvertStepsAndCommand(uint8_t *data, uint16_t *steps, uint8_t *command)
{
    *command = (data[0] & MASK_FOR_COMMAND)>>4;
    *steps = ((data[0] & MASK_FOR_STEPS)<<8) | data[1];
}
//------------------------------------------------------------------------------------------
void CommandHandler(uint16_t steps, uint8_t command)
{
	switch (command) {
	case CMD_MOVE_TO_STARTING_POINT:
		StartingPoint();
		printf("Case CMD_MOVE_TO_STARTING_POINT!!! \n");
	  break;
	case CMD_UP_THE_NEEDLE:
		printf("Case CMD_UP_THE_NEEDLE!!! \n");
		StepMotorUpDown(steps, UP, SPEED_DELAY_FOR_UP_DOWN);
	  break;
	case CMD_DOWN_THE_NEEDLE:
		printf("Case CMD_DOWN_THE_NEEDLE!!! \n");
		StepMotorUpDown(steps, DOWN, SPEED_DELAY_FOR_UP_DOWN);
	  break;
	case CMD_ROTATION_CLOCKWISE:
		printf("Case CMD_ROTATION_CLOCKWISE!!! \n");
		StepMotorRotation(steps, ROTATION_CLOCKWISE, SPEED_DELAY_FOR_ROTATION);
	  break;
	case CMD_ROTATION_ANTICLOCKWISE:
		printf("Case CMD_ROTATION_ANTICLOCKWISE!!! \n");
		StepMotorRotation(steps, ROTATION_ANTICLOCKWISE, SPEED_DELAY_FOR_ROTATION);
	  break;
	case CMD_MOVE_TO_CENTER:
		printf("Case CMD_MOVE_TO_CENTER!!! \n");
		StepMotorVector(steps, MOVE_TO_CENTER, SPEED_DELAY_FOR_VECTOR);
	  break;
	case CMD_MOVE_FROM_CENTER:
		printf("Case CMD_MOVE_FROM_CENTER!!! \n");
		StepMotorVector(steps, MOVE_FROM_CENTER, SPEED_DELAY_FOR_VECTOR);
	  break;
	case CMD_END_PROGRAMM:
		HAL_TIM_Base_Stop_IT(&htim2);
		cnt = 0;
		accessFlag = 0;
		HAL_GPIO_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_RED_PORT, LED_RED_PIN, GPIO_PIN_RESET);
		memset(Package_Data, 0, sizeof(Package_Data));
	  break;
	}
}
//------------------------------------------------------------------------------------------
