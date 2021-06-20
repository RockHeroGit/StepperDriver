# StepperDriver
STM32 library to use the stepper motor drivers

> #### Download Normal Version : [StepMotor](https://github.com/Majid-Derhambakhsh/StepMotor)  

## Release
- #### Version : 1.0.0

- #### Type : Embedded Software

- #### Support :  
     ```diff  
     + ARM STM32 Series   
     ```

- #### Program Language : C++

- #### Properties :

- #### Changes :  

- #### Required Library/Driver :


## Overview 
### Initialization and de-initialization functions:
```c++
void Init(GPIO_TypeDef *enGPIO, uint32_t enPIN, GPIO_TypeDef *dirGPIO, uint32_t dirPIN, GPIO_TypeDef *clkGPIO, uint32_t clkPIN, uint16_t  numberOfSteps, uint16_t  rpm);
``` 

### Operation functions:
```c++
void SetSpeed(uint16_t rpm);
void Step(int16_t step);
void Step(int16_t step, StepperRun_T func);
void StepAngle(float ang);
void StepAngle(float ang, StepperRun_T func);
``` 

### Macros:
```diff  
non   
```
    
## Guide

#### This library can be used as follows:
#### 1.  Add .h and source file in project.      
#### 2.  Create Stepper object and initialize it, for example:  
- #### Mode 1 (constructor):  
   * Initializer:
      ```c++
      Stepper(GPIO_TypeDef *enGPIO, uint32_t enPIN, GPIO_TypeDef *dirGPIO, uint32_t dirPIN, GPIO_TypeDef *clkGPIO, uint32_t clkPIN, uint16_t  numberOfSteps, uint16_t  rpm);
      ``` 
   * Parameters:  
      * enGPIO : 'enable pin' GPIO 
      * enPIN : enable pin 
      * dirGPIO : 'direction pin' GPIO 
      * dirPIN : direction pin 
      * clkGPIO : 'pulse pin' GPIO 
      * clkPIN : pulse pin 
      * numberOfSteps : number of stepper motor steps  
      * rpm : speed of stepper motor  
          
          
   * Example:
      ```c++  
      Stepper myMotor(&GPIOA, GPIO_PIN_0, &GPIOA, GPIO_PIN_1, &GPIOA, GPIO_PIN_2, 400, 30);
      ``` 
- #### Mode 2 (initializer function):  
   * Initializer:
      ```c++
      Stepper::Init(GPIO_TypeDef *enGPIO, uint32_t enPIN, GPIO_TypeDef *dirGPIO, uint32_t dirPIN, GPIO_TypeDef *clkGPIO, uint32_t clkPIN, uint16_t  numberOfSteps, uint16_t  rpm);
      ``` 
   * Parameters:  
      * enGPIO : 'enable pin' GPIO 
      * enPIN : enable pin 
      * dirGPIO : 'direction pin' GPIO 
      * dirPIN : direction pin 
      * clkGPIO : 'pulse pin' GPIO 
      * clkPIN : pulse pin 
      * numberOfSteps : number of stepper motor steps  
      * rpm : speed of stepper motor  
          
          
   * Example:
      ```c++  
      Stepper myMotor;
      
      myMotor.Init(&GPIOA, GPIO_PIN_0, &GPIOA, GPIO_PIN_1, &GPIOA, GPIO_PIN_2, 400, 30);
      ``` 
     

#### 3.  Using operation methods, for example: 
        
```c++
myMotor.Step(10);
myMotor.StepAngle(-50);
```  
          
## Examples  

#### Example 1: Simple mode
   ```c++
   int main()
   {
      //Your codes
      GPIO_Init(); // Initialize gpio for connect to driver
      
      Stepper myMotor;
      myMotor.Init(&GPIOA, GPIO_PIN_0, &GPIOA, GPIO_PIN_1, &GPIOA, GPIO_PIN_2, 400, 30);
      
      while(1)
      {
         myMotor.StepAngle(60);
         HAL_Delay(100);
         myMotor.StepAngle(-50);
         HAL_Delay(100);
      }
   }
   ```
    
#### Example 2: Advanced mode
   ```c++
   
   void stepperEvent(uint16_t currentStep)
   {
      print(currentStep);
   }
   
   int main()
   {
      //Your codes
      GPIO_Init(); // Initialize gpio for connect to driver
      
      Stepper myMotor;
      myMotor.Init(&GPIOA, GPIO_PIN_0, &GPIOA, GPIO_PIN_1, &GPIOA, GPIO_PIN_2, 400, 30);
      
      while(1)
      {
         myMotor.Step(10, stepperEvent);
         HAL_Delay(100);
         myMotor.StepAngle(-9, stepperEvent);
         HAL_Delay(100);
      }
   }
   ```
    
## Tests performed:
- [x] Run on STM32 Fx cores

## Developers: 
- ### Majid Derhambakhsh
