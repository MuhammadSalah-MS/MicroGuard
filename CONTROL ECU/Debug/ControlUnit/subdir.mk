################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ControlUnit/application.c \
../ControlUnit/buzzer.c \
../ControlUnit/dcmotor.c \
../ControlUnit/external_eeprom.c \
../ControlUnit/gpio.c \
../ControlUnit/pwm.c \
../ControlUnit/timer1.c \
../ControlUnit/twi.c \
../ControlUnit/uart.c 

OBJS += \
./ControlUnit/application.o \
./ControlUnit/buzzer.o \
./ControlUnit/dcmotor.o \
./ControlUnit/external_eeprom.o \
./ControlUnit/gpio.o \
./ControlUnit/pwm.o \
./ControlUnit/timer1.o \
./ControlUnit/twi.o \
./ControlUnit/uart.o 

C_DEPS += \
./ControlUnit/application.d \
./ControlUnit/buzzer.d \
./ControlUnit/dcmotor.d \
./ControlUnit/external_eeprom.d \
./ControlUnit/gpio.d \
./ControlUnit/pwm.d \
./ControlUnit/timer1.d \
./ControlUnit/twi.d \
./ControlUnit/uart.d 


# Each subdirectory must supply rules for building sources it contributes
ControlUnit/%.o: ../ControlUnit/%.c ControlUnit/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


