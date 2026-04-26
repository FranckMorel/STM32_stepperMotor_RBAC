################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/font.c \
../Src/main.c \
../Src/motor_control.c \
../Src/spi.c \
../Src/stepper.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/tft.c \
../Src/timer.c \
../Src/ui.c 

OBJS += \
./Src/font.o \
./Src/main.o \
./Src/motor_control.o \
./Src/spi.o \
./Src/stepper.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/tft.o \
./Src/timer.o \
./Src/ui.o 

C_DEPS += \
./Src/font.d \
./Src/main.d \
./Src/motor_control.d \
./Src/spi.d \
./Src/stepper.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/tft.d \
./Src/timer.d \
./Src/ui.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/kzvvftre/Documents/STM32-Baremetal_Workspace/STM32F4_Projektdateien/F4_chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/kzvvftre/Documents/STM32-Baremetal_Workspace/STM32F4_Projektdateien/F4_chip_headers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/font.cyclo ./Src/font.d ./Src/font.o ./Src/font.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/motor_control.cyclo ./Src/motor_control.d ./Src/motor_control.o ./Src/motor_control.su ./Src/spi.cyclo ./Src/spi.d ./Src/spi.o ./Src/spi.su ./Src/stepper.cyclo ./Src/stepper.d ./Src/stepper.o ./Src/stepper.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/tft.cyclo ./Src/tft.d ./Src/tft.o ./Src/tft.su ./Src/timer.cyclo ./Src/timer.d ./Src/timer.o ./Src/timer.su ./Src/ui.cyclo ./Src/ui.d ./Src/ui.o ./Src/ui.su

.PHONY: clean-Src

