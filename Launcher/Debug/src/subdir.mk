################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/syscalls.c \
../src/system_stm32f4xx.c 

CPP_SRCS += \
../src/main.cpp 

OBJS += \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/syscalls.d \
./src/system_stm32f4xx.d 

CPP_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c++2a -DSTM32 -DSTM32F4 -DSTM32F405RGTx -DDEBUG -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -I"C:/Users/SotaKobayashi/Google ドライブ/user/Git/2019g/2019g_Launcher/Launcher/StdPeriph_Driver/inc" -I"C:/Users/SotaKobayashi/Google ドライブ/user/Git/2019g/2019g_Launcher/Launcher/inc" -I"C:/Users/SotaKobayashi/Google ドライブ/user/Git/2019g/2019g_Launcher/Launcher/CMSIS/device" -I"C:/Users/SotaKobayashi/Google ドライブ/user/Git/2019g/2019g_Launcher/Launcher/CMSIS/core" -I"C:/Users/SotaKobayashi/Google ドライブ/user/Git/2019g/2019g_Launcher/Launcher/inc/myHeaders" -I"C:/Users/SotaKobayashi/Google ドライブ/user/Git/Libraries/inc" -O0 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F405RGTx -DDEBUG -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -I"C:/Users/SotaKobayashi/Google ドライブ/user/Git/2019g/2019g_Launcher/Launcher/StdPeriph_Driver/inc" -I"C:/Users/SotaKobayashi/Google ドライブ/user/Git/2019g/2019g_Launcher/Launcher/inc" -I"C:/Users/SotaKobayashi/Google ドライブ/user/Git/2019g/2019g_Launcher/Launcher/CMSIS/device" -I"C:/Users/SotaKobayashi/Google ドライブ/user/Git/2019g/2019g_Launcher/Launcher/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


