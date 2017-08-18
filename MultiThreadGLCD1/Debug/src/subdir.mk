################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fonts.c \
../src/glcdInit.c \
../src/glcdPrimitives.c \
../src/new_thread0_entry.c \
../src/new_thread1_entry.c 

OBJS += \
./src/fonts.o \
./src/glcdInit.o \
./src/glcdPrimitives.o \
./src/new_thread0_entry.o \
./src/new_thread1_entry.o 

C_DEPS += \
./src/fonts.d \
./src/glcdInit.d \
./src/glcdPrimitives.d \
./src/new_thread0_entry.d \
./src/new_thread1_entry.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\e2_studio\eclipse\../Utilities/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy_cfg\ssp_cfg\bsp" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy_cfg\ssp_cfg\driver" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc\bsp" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc\bsp\cmsis\Include" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc\driver\api" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc\driver\instances" -I"E:\ARM\Synergy\MultiThreadGLCD1\src" -I"E:\ARM\Synergy\MultiThreadGLCD1\src\synergy_gen" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy_cfg\ssp_cfg\framework\el" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc\framework\el" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\src\framework\el\tx" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


