################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LED/LED_Prog.c 

OBJS += \
./HAL/LED/LED_Prog.o 

C_DEPS += \
./HAL/LED/LED_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/LED/%.o: ../HAL/LED/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\SDK\ATMEGA_Drivers\APP" -I"D:\SDK\ATMEGA_Drivers\HAL\LED" -I"D:\SDK\ATMEGA_Drivers\HAL\Push_Button" -I"D:\SDK\ATMEGA_Drivers\MCAL\DIO" -Wall -g2 -gstabs+ -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


