################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mySources/electric_valve.cpp \
../src/mySources/led.cpp \
../src/mySources/motor.cpp \
../src/mySources/rotary_encoder.cpp \
../src/mySources/uart.cpp 

OBJS += \
./src/mySources/electric_valve.o \
./src/mySources/led.o \
./src/mySources/motor.o \
./src/mySources/rotary_encoder.o \
./src/mySources/uart.o 

CPP_DEPS += \
./src/mySources/electric_valve.d \
./src/mySources/led.d \
./src/mySources/motor.d \
./src/mySources/rotary_encoder.d \
./src/mySources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/mySources/%.o: ../src/mySources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c++2a -DSTM32 -DSTM32F4 -DSTM32F405RGTx -DDEBUG -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -I"D:/Git/2019g/2019g_Launcher/Launcher/StdPeriph_Driver/inc" -I"D:/Git/2019g/2019g_Launcher/Launcher/inc" -I"D:/Git/2019g/2019g_Launcher/Launcher/CMSIS/device" -I"D:/Git/2019g/2019g_Launcher/Launcher/CMSIS/core" -I"D:/Git/2019g/2019g_Launcher/Launcher/inc/myHeaders" -O0 -g3 -Wall -Wconversion -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


