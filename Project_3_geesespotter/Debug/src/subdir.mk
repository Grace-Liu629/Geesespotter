################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/geesespotter.cpp \
../src/geesespotter_lib.cpp 

CPP_DEPS += \
./src/geesespotter.d \
./src/geesespotter_lib.d 

OBJS += \
./src/geesespotter.o \
./src/geesespotter_lib.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/geesespotter.d ./src/geesespotter.o ./src/geesespotter_lib.d ./src/geesespotter_lib.o

.PHONY: clean-src

