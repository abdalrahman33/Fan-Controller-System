/*
 * dc_motor.c
 *
 *  Created on: Feb 23, 2024
 *      Author: Abdelrahman Salem
 */

#include "common_macros.h" /* For GET_BIT Macro */
#include "dc_motor.h"
#include "gpio.h"
#include "std_types.h"
#include "pwm.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the DC Motor:
 * 1. Setup the DC Motor pins directions by use the GPIO driver.
 * 2. Enable Driver.
 * 3. Initialize DC Motor State as Idle.
 */
void DcMotor_Init(void)
{
	/* Configure Pins as OUTPUT */
	GPIO_setupPinDirection(DC_MOTOR_INPUT1_PORT_ID,DC_MOTOR_INPUT1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_INPUT2_PORT_ID,DC_MOTOR_INPUT2_PIN_ID,PIN_OUTPUT);


	/* Initialize Pins as LOGIC_LOW */
	GPIO_writePin(DC_MOTOR_INPUT1_PORT_ID,DC_MOTOR_INPUT1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_INPUT2_PORT_ID,DC_MOTOR_INPUT2_PIN_ID,LOGIC_LOW);
}

/*
 * Description :
 * Set Direction & Speed the DC Motor:
 * 1. Set Direction depending on argument.
 * 2. Set PWM using PWM Driver.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	switch(state)
	{
	case NO_ROTATION:
		GPIO_writePin(DC_MOTOR_INPUT1_PORT_ID,DC_MOTOR_INPUT1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_INPUT2_PORT_ID,DC_MOTOR_INPUT2_PIN_ID,LOGIC_LOW);
		break;
	case CW_ROTATION:
			GPIO_writePin(DC_MOTOR_INPUT1_PORT_ID,DC_MOTOR_INPUT1_PIN_ID,LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_INPUT2_PORT_ID,DC_MOTOR_INPUT2_PIN_ID,LOGIC_LOW);
			break;
	case CCW_ROTATION:
			GPIO_writePin(DC_MOTOR_INPUT1_PORT_ID,DC_MOTOR_INPUT1_PIN_ID,LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_INPUT2_PORT_ID,DC_MOTOR_INPUT2_PIN_ID,LOGIC_HIGH);
			break;
	}
	PWM_Timer0_Start(speed);
}
