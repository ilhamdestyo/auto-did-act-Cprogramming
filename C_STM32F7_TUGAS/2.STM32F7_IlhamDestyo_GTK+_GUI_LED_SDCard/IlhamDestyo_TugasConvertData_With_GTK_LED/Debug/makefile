################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FatFs/src/option/subdir.mk
-include Middlewares/Third_Party/FatFs/src/subdir.mk
-include GUI\ files/subdir.mk
-include FATFS/Target/subdir.mk
-include FATFS/App/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := IlhamDestyo_TugasConvertData_With_GTK_LED
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
IlhamDestyo_TugasConvertData_With_GTK_LED.elf \

MAP_FILES += \
IlhamDestyo_TugasConvertData_With_GTK_LED.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
IlhamDestyo_TugasConvertData_With_GTK_LED.list \


# All Target
all: main-build

# Main-build Target
main-build: IlhamDestyo_TugasConvertData_With_GTK_LED.elf secondary-outputs

# Tool invocations
IlhamDestyo_TugasConvertData_With_GTK_LED.elf IlhamDestyo_TugasConvertData_With_GTK_LED.map: $(OBJS) $(USER_OBJS) /home/lime/Documents/Delameta_Work/source-code/C_STM32F7_TUGAS/2.STM32F7_IlhamDestyo_GTK+_GUI_LED_SDCard/IlhamDestyo_TugasConvertData_With_GTK_LED/STM32F746NGHX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "IlhamDestyo_TugasConvertData_With_GTK_LED.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"/home/lime/Documents/Delameta_Work/source-code/C_STM32F7_TUGAS/2.STM32F7_IlhamDestyo_GTK+_GUI_LED_SDCard/IlhamDestyo_TugasConvertData_With_GTK_LED/STM32F746NGHX_FLASH.ld" --specs=nosys.specs -Wl,-Map="IlhamDestyo_TugasConvertData_With_GTK_LED.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

IlhamDestyo_TugasConvertData_With_GTK_LED.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "IlhamDestyo_TugasConvertData_With_GTK_LED.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) IlhamDestyo_TugasConvertData_With_GTK_LED.elf IlhamDestyo_TugasConvertData_With_GTK_LED.list IlhamDestyo_TugasConvertData_With_GTK_LED.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
