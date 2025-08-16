/*
------------------------------------------------------------------------------
~ File   : stepper_driver.cpp
~ Author : Majid Derhambakhsh
~ Version: V1.0.0
~ Created: Jun 12, 2021 12:13:43 AM
~ Brief  :
~ Support: 
           E-Mail : Majid.do16@gmail.com (subject : Embedded Library Support)
		   
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    

~ Attention  :    

~ Changes    :
------------------------------------------------------------------------------
*/

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "stepper_driver.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variable ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Object ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* :::::::::::::: Constructor ::::::::::::: */
Stepper::Stepper(){}
Stepper::Stepper(GPIO_TypeDef *enGPIO, uint32_t enPIN, GPIO_TypeDef *dirGPIO,
		uint32_t dirPIN, GPIO_TypeDef *clkGPIO, uint32_t clkPIN,
		uint16_t  numberOfSteps, uint16_t  rpm): CallBackFunk(nullptr)
{

	/* ~~~~~~~~~~~~~~~ Stepper param ~~~~~~~~~~~~~~~ */
	_numberOfSteps = numberOfSteps;
	_stepDelay     = ((60L * 1000L) / _numberOfSteps) / rpm;

	/* ~~~~~~~~~~~~~~~~ Calculation ~~~~~~~~~~~~~~~~ */
	_angRatio      = 360.0F / _numberOfSteps;

	/* ~~~~~~~~~~~~~~~~ Stepper GPIO ~~~~~~~~~~~~~~~ */
	_enGPIO        = enGPIO;
	_enPIN         = enPIN;
	_dirGPIO       = dirGPIO;
	_dirPIN        = dirPIN;
	_clkGPIO       = clkGPIO;
	_clkPIN        = clkPIN;

}

/* ::::::::::::::::: Init ::::::::::::::::: */
void Stepper::Init(GPIO_TypeDef *enGPIO, uint32_t enPIN, GPIO_TypeDef *dirGPIO, uint32_t dirPIN, GPIO_TypeDef *clkGPIO, uint32_t clkPIN, uint16_t  numberOfSteps, uint16_t  rpm)
{

	/* ~~~~~~~~~~~~~~~ Stepper param ~~~~~~~~~~~~~~~ */
	_numberOfSteps = numberOfSteps;
	_stepDelay     = ((60L * 1000L) / _numberOfSteps) / rpm;

	/* ~~~~~~~~~~~~~~~~ Calculation ~~~~~~~~~~~~~~~~ */
	_angRatio      = 360.0F / _numberOfSteps;

	/* ~~~~~~~~~~~~~~~~ Stepper GPIO ~~~~~~~~~~~~~~~ */
	_enGPIO        = enGPIO;
	_enPIN         = enPIN;
	_dirGPIO       = dirGPIO;
	_dirPIN        = dirPIN;
	_clkGPIO       = clkGPIO;
	_clkPIN        = clkPIN;

}
void Stepper::SetSpeed(uint16_t rpm)
{
	_stepDelay = ((60L * 1000L) / _numberOfSteps) / rpm;
}

/* ::::::::::::::: Position ::::::::::::::: */
void Stepper::Step(int32_t step)
{

	/* ~~~~~~~~~~~~~~~ Check direction ~~~~~~~~~~~~~~~ */
	if (step > 0)
	{
		HAL_GPIO_WritePin(_dirGPIO, _dirPIN, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(_dirGPIO, _dirPIN, GPIO_PIN_SET);
	}

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	step = abs(step);

	while (step > 0)
	{

		HAL_GPIO_WritePin(_clkGPIO, _clkPIN, GPIO_PIN_RESET);
		HAL_Delay((_stepDelay / 2));
		HAL_GPIO_WritePin(_clkGPIO, _clkPIN, GPIO_PIN_SET);
		HAL_Delay((_stepDelay / 2));

		step--;

	}

	if(CallBackFunk != nullptr)
		CallBackFunk();

}
void Stepper::Step(int32_t step, StepperRun_T func)
{

	uint16_t count = 0;

	/* ~~~~~~~~~~~~~~~ Check direction ~~~~~~~~~~~~~~~ */
	if (step > 0)
	{
		HAL_GPIO_WritePin(_dirGPIO, _dirPIN, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(_dirGPIO, _dirPIN, GPIO_PIN_SET);
	}

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	step = abs(step);

	while (count < step)
	{

		HAL_GPIO_WritePin(_clkGPIO, _clkPIN, GPIO_PIN_RESET);
		HAL_Delay((_stepDelay / 2));
		HAL_GPIO_WritePin(_clkGPIO, _clkPIN, GPIO_PIN_SET);
		HAL_Delay((_stepDelay / 2));

		/* ::::::::::::::: Run function ::::::::::::::: */
		func(count);

		count++;

	}

	if(CallBackFunk != nullptr)
		CallBackFunk();

}
void Stepper::StepAngle(float ang)
{
	Stepper::Step((int32_t)(ang / _angRatio));
}

void Stepper::SetCallBackAfterMovement(void (*CallBackFunk)())
{
	this->CallBackFunk = CallBackFunk;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~ */
