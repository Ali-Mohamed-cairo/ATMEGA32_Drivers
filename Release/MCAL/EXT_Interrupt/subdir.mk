################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/EXT_Interrupt/EXT_Interrupt_Prog.c 

OBJS += \
./MCAL/EXT_Interrupt/EXT_Interrupt_Prog.o 

C_DEPS += \
./MCAL/EXT_Interrupt/EXT_Interrupt_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/EXT_Interrupt/%.o: ../MCAL/EXT_Interrupt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


