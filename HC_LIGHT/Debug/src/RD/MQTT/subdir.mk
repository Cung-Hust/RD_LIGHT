################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/RD/MQTT/MQTT.cpp 

OBJS += \
./src/RD/MQTT/MQTT.o 

CPP_DEPS += \
./src/RD/MQTT/MQTT.d 


# Each subdirectory must supply rules for building sources it contributes
src/RD/MQTT/%.o: ../src/RD/MQTT/%.cpp src/RD/MQTT/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-openwrt-linux-musl-g++ -I/home/rd/Desktop/RD_AI7688/staging_dir/target-mipsel_24kc_musl/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


