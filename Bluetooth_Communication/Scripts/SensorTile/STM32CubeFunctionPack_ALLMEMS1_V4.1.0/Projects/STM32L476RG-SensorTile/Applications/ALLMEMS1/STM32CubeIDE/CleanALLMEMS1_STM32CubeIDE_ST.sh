#!/bin/bash

######## Modify this Section:
# 1) Set the Installation path for OpenOCD
# example:
#OpenOCD_DIR="C:/ST/STM32CubeIDE_1.3.0/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.openocd.win32_1.3.0.202002181050/tools"
OpenOCD_DIR=""

# 2) Set the installation path for stm32 OpenOCD scritps
# example:
#OpenOCD_CFC="C:/ST/STM32CubeIDE_1.3.0/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.debug.openocd_1.3.0.202002181050/resources/openocd/st_scripts"
OpenOCD_CFC=""

# 3) Only for Linux/iOS add openocd library path to _LIBRARY_PATH:
# For iOS example:
#export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${OpenOCD_DIR}"lib/"

# For Linux example:
#export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${OpenOCD_DIR}"lib/"

######## Don't change the following part

## Control Section

if [[ ! $OpenOCD_DIR ]];  then
	echo "Please add the rigth path to OpenOCD_DIR Variable"
	exit
fi

if [[ ! $OpenOCD_CFC ]];  then
	echo "Please add the rigth path to OpenOCD_CFC Variable"
	exit
fi


## Run section

# Board type
BOARDNAME="nucleo_l476rg"

# OpenOCD command
OpenOCD_CMD="${OpenOCD_DIR}/bin/openocd -s ${OpenOCD_CFC} -f nucleo_l476rg.cfg"


echo "/******************************************/"
echo "           Clean FP-SNS-ALLMEMS1"
echo "/******************************************/"
echo "             Full Chip Erase"
echo "/******************************************/"
${OpenOCD_CMD} -c "init" -c "mww" -c "reset halt" -c "flash erase_sector 0 511 511" -c "shutdown"
echo "/******************************************/"
echo "              Install BootLoader"
echo "/******************************************/"
${OpenOCD_CMD} -c "init" -c "mww" -c "reset halt" -c "flash write_image erase ../../../../../Utilities/BootLoader/STM32L476RG/BootLoaderL4.bin 0x08000000 bin" -c "shutdown"
echo "/******************************************/"
echo "           Install FP-SNS-ALLMEMS1"
echo "/******************************************/"
${OpenOCD_CMD} -c "init" -c "mww" -c "reset halt" -c "flash write_image erase  ./STM32L4xx-SensorTile/Debug/STM32L476RG-SensorTile_ALLMEMS1.bin 0x08004000 bin" -c "shutdown"
echo "/******************************************/"
echo "     Dump FP-SNS-ALLMEMS1 + BootLoader"
echo "/******************************************/"

SizeBinBL=`ls -l ./STM32L4xx-SensorTile/Debug/STM32L476RG-SensorTile_ALLMEMS1.bin | awk '{print $5+0x4000};'`
${OpenOCD_CMD} -c "init" \
			   -c "reset halt" \
			   -c "dump_image ./STM32L4xx-SensorTile/Debug/STM32L476RG-SensorTile_ALLMEMS1_BL.bin 0x08000000 ${SizeBinBL}" \
			   -c "shutdown"
			   
