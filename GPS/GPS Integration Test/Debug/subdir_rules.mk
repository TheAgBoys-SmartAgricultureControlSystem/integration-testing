################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/HeinzBoehmer/workspace_v8/GPS Integration Test" --include_path="/Users/HeinzBoehmer/ti/simplelink_cc13x2_26x2_sdk_2_40_00_81/source" --include_path="/Users/HeinzBoehmer/ti/simplelink_cc13x2_26x2_sdk_2_40_00_81/kernel/nortos" --include_path="/Users/HeinzBoehmer/ti/simplelink_cc13x2_26x2_sdk_2_40_00_81/kernel/nortos/posix" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --define=DeviceFamily_CC13X2 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


