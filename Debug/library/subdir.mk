################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../library/FW_Timertick.c \
../library/My_Uart.c \
../library/PLL.c \
../library/drv_base.c \
../library/handlerMotor.c \
../library/init.c \
../library/timer.c 

OBJS += \
./library/FW_Timertick.o \
./library/My_Uart.o \
./library/PLL.o \
./library/drv_base.o \
./library/handlerMotor.o \
./library/init.o \
./library/timer.o 

C_DEPS += \
./library/FW_Timertick.d \
./library/My_Uart.d \
./library/PLL.d \
./library/drv_base.d \
./library/handlerMotor.d \
./library/init.d \
./library/timer.d 


# Each subdirectory must supply rules for building sources it contributes
library/%.o: ../library/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/nafas/Documents/MCUXpresso_11.0.1_2563/workspace/TPO2019/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


