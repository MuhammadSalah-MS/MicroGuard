################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI_Unit/application2.c \
../HMI_Unit/gpio.c \
../HMI_Unit/keypad.c \
../HMI_Unit/lcd.c \
../HMI_Unit/timer1.c \
../HMI_Unit/uart.c 

OBJS += \
./HMI_Unit/application2.o \
./HMI_Unit/gpio.o \
./HMI_Unit/keypad.o \
./HMI_Unit/lcd.o \
./HMI_Unit/timer1.o \
./HMI_Unit/uart.o 

C_DEPS += \
./HMI_Unit/application2.d \
./HMI_Unit/gpio.d \
./HMI_Unit/keypad.d \
./HMI_Unit/lcd.d \
./HMI_Unit/timer1.d \
./HMI_Unit/uart.d 


# Each subdirectory must supply rules for building sources it contributes
HMI_Unit/%.o: ../HMI_Unit/%.c HMI_Unit/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


