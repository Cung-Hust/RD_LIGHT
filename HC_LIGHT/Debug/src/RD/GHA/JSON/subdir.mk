################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/RD/GHA/JSON/JSON_GHA.cpp 

OBJS += \
./src/RD/GHA/JSON/JSON_GHA.o 

CPP_DEPS += \
./src/RD/GHA/JSON/JSON_GHA.d 


# Each subdirectory must supply rules for building sources it contributes
src/RD/GHA/JSON/%.o: ../src/RD/GHA/JSON/%.cpp src/RD/GHA/JSON/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-openwrt-linux-musl-g++ -I/home/rd/Desktop/RD_AI7688/staging_dir/target-mipsel_24kc_musl/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


