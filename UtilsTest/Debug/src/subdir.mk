################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FileTest.cpp \
../src/MTCPListenerTest.cpp \
../src/TcpSocketTest.cpp \
../src/UdpSocketTest.cpp \
../src/main.cpp 

OBJS += \
./src/FileTest.o \
./src/MTCPListenerTest.o \
./src/TcpSocketTest.o \
./src/UdpSocketTest.o \
./src/main.o 

CPP_DEPS += \
./src/FileTest.d \
./src/MTCPListenerTest.d \
./src/TcpSocketTest.d \
./src/UdpSocketTest.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/FinalProj/SocketUtils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


