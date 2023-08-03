/*
 * SteppLibrary.h
 *
 *  Created on: Dec 8, 2022
 *      Author: feodosiy
 */

#ifndef INC_STEPPLIBRARY_H_
#define INC_STEPPLIBRARY_H_

//******************INCLUDES************************
#include "stm32l4xx_hal.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"


//******************DEFINES************************
/*--------Motor №1 -- ROTATION MOTOR---------------*/
#define EN_PIN_AN GPIO_PIN_8
#define EN_PORT_AN GPIOA

#define MS1_PIN_AN GPIO_PIN_9
#define MS1_PORT_AN GPIOC

#define MS2_PIN_AN GPIO_PIN_8
#define MS2_PORT_AN GPIOC

#define SPREAD_PIN_AN GPIO_PIN_7
#define SPREAD_PORT_AN GPIOC

#define STEP_PIN_AN GPIO_PIN_6
#define STEP_PORT_AN GPIOC

#define DIR_PIN_AN GPIO_PIN_15
#define DIR_PORT_AN GPIOB

#define INDEX_PIN_AN GPIO_PIN_14
#define INDEX_PORT_AN GPIOB

#define DIAG_PIN_AN GPIO_PIN_13
#define DIAG_PORT_AN GPIOB

#define STEPS_MOTOR_FULL_ROTATE 4472
#define ROTATION_CLOCKWISE 0
#define ROTATION_ANTICLOCKWISE 1
#define SPEED_DELAY_FOR_ROTATION 500
//-------------------------------------------------


/*--------Motor №2 -- RADIUS-VECTOR MOTOR---------------*/
#define EN_PIN_RV GPIO_PIN_6
#define EN_PORT_RV GPIOB

#define MS1_PIN_RV GPIO_PIN_5
#define MS1_PORT_RV GPIOB

#define MS2_PIN_RV GPIO_PIN_4
#define MS2_PORT_RV GPIOB

#define SPREAD_PIN_RV GPIO_PIN_2
#define SPREAD_PORT_RV GPIOD

#define STEP_PIN_RV GPIO_PIN_12
#define STEP_PORT_RV GPIOC

#define DIR_PIN_RV GPIO_PIN_11
#define DIR_PORT_RV GPIOC

#define INDEX_PIN_RV GPIO_PIN_10
#define INDEX_PORT_RV GPIOC

#define DIAG_PIN_RV GPIO_PIN_15
#define DIAG_PORT_RV GPIOA

#define MOVE_TO_CENTER 0
#define MOVE_FROM_CENTER 1
#define SPEED_DELAY_FOR_VECTOR 500
//-------------------------------------------------


/*--------Motor №3 -- UP DOWN MOTOR---------------*/
#define EN_PIN_UD GPIO_PIN_4
#define EN_PORT_UD GPIOA

#define MS1_PIN_UD GPIO_PIN_5
#define MS1_PORT_UD GPIOA

#define MS2_PIN_UD GPIO_PIN_6
#define MS2_PORT_UD GPIOA

#define SPREAD_PIN_UD GPIO_PIN_7
#define SPREAD_PORT_UD GPIOA

#define STEP_PIN_UD GPIO_PIN_0
#define STEP_PORT_UD GPIOB

#define DIR_PIN_UD GPIO_PIN_1
#define DIR_PORT_UD GPIOB

#define INDEX_PIN_UD GPIO_PIN_2
#define INDEX_PORT_UD GPIOB

#define DIAG_PIN_UD GPIO_PIN_10
#define DIAG_PORT_UD GPIOB

#define UP 1
#define DOWN 0
#define SPEED_DELAY_FOR_UP_DOWN 200
//-------------------------------------------------

//----------Recieve and handling data--------------
#define MASK_FOR_COMMAND 0xF0
#define MASK_FOR_STEPS 0x0F
//-------------------------------------------------

//------------Commands from phone------------------
#define CMD_MOVE_TO_STARTING_POINT 0x0F
#define CMD_UP_THE_NEEDLE 0x0C
#define CMD_DOWN_THE_NEEDLE 0x03
#define CMD_ROTATION_CLOCKWISE 0x0A
#define CMD_ROTATION_ANTICLOCKWISE 0x05
#define CMD_MOVE_TO_CENTER 0x06
#define CMD_MOVE_FROM_CENTER 0x09
#define CMD_END_PROGRAMM 0x00
//-------------------------------------------------

//---------------------LEDs------------------------
#define LED_GREEN_PIN GPIO_PIN_2
#define LED_GREEN_PORT GPIOC
#define LED_RED_PIN GPIO_PIN_3
#define LED_RED_PORT GPIOC
//-------------------------------------------------

//---------------------Pump------------------------
#define PUMP_PIN GPIO_PIN_13
#define PUMP_PORT GPIOC
#define ENABLE_PUMP 1
#define DISABLE_PUMP 0
//-------------------------------------------------

//------------------Limit switch-------------------
#define LIMIT_SWITCH_VECTOR_PIN GPIO_PIN_12
#define LIMIT_SWITCH_VECTOR_PORT GPIOA
#define LIMIT_SWITCH_UPDOWN_PIN GPIO_PIN_11
#define LIMIT_SWITCH_UPDOWN_PORT GPIOA
//-------------------------------------------------

//-------------------Fluid level-------------------
#define FLUID_LEVEL_PIN GPIO_PIN_9
#define FLUID_LEVEL_PORT GPIOB
//-------------------------------------------------

#endif /* INC_STEPPLIBRARY_H_ */

//******************FUNCTIONS************************
void StepMotorInit();
void StartingPoint();
void Pump(uint8_t state);
void MicroDelay(uint16_t delay);
void StepMotorRotation(uint32_t steps, uint8_t direction, uint16_t delay);
void StepMotorVector(uint32_t steps, uint8_t direction, uint16_t delay);
void StepMotorUpDown(uint32_t steps, uint8_t direction, uint16_t delay);
void ConvertStepsAndCommand(uint8_t *data, uint16_t *steps, uint8_t *command);
void CommandHandler(uint16_t steps, uint8_t command);
//***************************************************

