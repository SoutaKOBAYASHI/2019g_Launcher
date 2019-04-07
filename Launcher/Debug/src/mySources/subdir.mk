################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mySources/electric_valve.cpp \
../src/mySources/emergency.cpp \
../src/mySources/intrrupt.cpp \
../src/mySources/launcher.cpp \
../src/mySources/motor.cpp \
../src/mySources/move_angle.cpp \
../src/mySources/position_pid.cpp \
../src/mySources/rotary_encoder.cpp \
../src/mySources/speed_pid.cpp \
../src/mySources/uart.cpp 

OBJS += \
./src/mySources/electric_valve.o \
./src/mySources/emergency.o \
./src/mySources/intrrupt.o \
./src/mySources/launcher.o \
./src/mySources/motor.o \
./src/mySources/move_angle.o \
./src/mySources/position_pid.o \
./src/mySources/rotary_encoder.o \
./src/mySources/speed_pid.o \
./src/mySources/uart.o 

CPP_DEPS += \
./src/mySources/electric_valve.d \
./src/mySources/emergency.d \
./src/mySources/intrrupt.d \
./src/mySources/launcher.d \
./src/mySources/motor.d \
./src/mySources/move_angle.d \
./src/mySources/position_pid.d \
./src/mySources/rotary_encoder.d \
./src/mySources/speed_pid.d \
./src/mySources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/mySources/%.o: ../src/mySources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c++2a -DSTM32 -DSTM32F4 -DSTM32F405RGTx -DDEBUG -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -D__GXX_EXPERIMENTAL_CXX17__ -I"D:/Git/2019g/2019g_Launcher/Launcher/StdPeriph_Driver/inc" -I"D:/Git/2019g/2019g_Launcher/Launcher/inc" -I"D:/Git/2019g/2019g_Launcher/Launcher/CMSIS/device" -I"D:/Git/2019g/2019g_Launcher/Launcher/CMSIS/core" -I"D:/Git/2019g/2019g_Launcher/Launcher/inc/myHeaders" -I"D:/Git/Libraries/inc" -O0 -g3 -Wall -Wconversion -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


