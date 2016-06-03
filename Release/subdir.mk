################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ConfigurationManager.cpp \
../Driver.cpp \
../Graph.cpp \
../LocalizationManager.cpp \
../Main.cpp \
../Map.cpp \
../Node.cpp \
../Particle.cpp \
../PathPlanner.cpp \
../WaypointsManager.cpp \
../lodepng.cpp \
../robot.cpp 

OBJS += \
./ConfigurationManager.o \
./Driver.o \
./Graph.o \
./LocalizationManager.o \
./Main.o \
./Map.o \
./Node.o \
./Particle.o \
./PathPlanner.o \
./WaypointsManager.o \
./lodepng.o \
./robot.o 

CPP_DEPS += \
./ConfigurationManager.d \
./Driver.d \
./Graph.d \
./LocalizationManager.d \
./Main.d \
./Map.d \
./Node.d \
./Particle.d \
./PathPlanner.d \
./WaypointsManager.d \
./lodepng.d \
./robot.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


