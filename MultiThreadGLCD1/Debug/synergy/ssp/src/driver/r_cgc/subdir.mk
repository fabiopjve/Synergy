################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../synergy/ssp/src/driver/r_cgc/r_cgc.c 

OBJS += \
./synergy/ssp/src/driver/r_cgc/r_cgc.o 

C_DEPS += \
./synergy/ssp/src/driver/r_cgc/r_cgc.d 


# Each subdirectory must supply rules for building sources it contributes
synergy/ssp/src/driver/r_cgc/%.o: ../synergy/ssp/src/driver/r_cgc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\e2_studio\eclipse\../Utilities/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy_cfg\ssp_cfg\bsp" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy_cfg\ssp_cfg\driver" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc\bsp" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc\bsp\cmsis\Include" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc\driver\api" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc\driver\instances" -I"E:\ARM\Synergy\MultiThreadGLCD1\src" -I"E:\ARM\Synergy\MultiThreadGLCD1\src\synergy_gen" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy_cfg\ssp_cfg\framework\el" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\inc\framework\el" -I"E:\ARM\Synergy\MultiThreadGLCD1\synergy\ssp\src\framework\el\tx" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


