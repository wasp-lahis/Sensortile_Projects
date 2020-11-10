# SensorTile Code

In my BLE experiments, I used the package `STM32CubeFunctionPack_ALLMEMS1_V4.1.0`. This can be found <a href="https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32-ode-function-pack-sw/fp-sns-allmems1.html" target="_blank"> here</a>


**Firmware settings:**

- **Sampling Frequency**: 20 Hz
- **Range ACC**:  +- 8 g
- **Range GYRO**: +- 2000 dps
- **Range MAG**:  +- 50 gauss 
  
</br>

## To flash the binaries on SensorTile:

- Follow the diagram and make the connections. Equal colors represent the connections between SensorTile and ST Link, as shown in the image given below:


![BlueST_SDK-flash_firmware](https://user-images.githubusercontent.com/7443249/98619630-66f1ad80-22e2-11eb-99a5-50c1a1178db6.png)

   

- Use the `STM32 ST-LINK Utility` software to flash the binaries and follow the next steps:

    - Firstly, on `Target` tab, click on `Connect`

    - After, select `Erase chip` on `Target` tab

    - Loading the `BootLoaderL4.bin` file and flash it at address 0x08000000, data width 32 bits 

    - Loading the `STM32L476RG-SensorTile_ALLMEMS1_V4.1.0.bin` and flash it at address 0x08004000, size 0x1000, data width 32 bits 		

    - Desmonte o ckt de gravação (opcional)

</br>

## References:

- STMicroeletronics. User manual UM2496: Getting started with the BlueST protocol and SDK. Rev 2. Fevereiro 2020.

- STMicroeletronics. User manual UM2101: Getting started with the STEVAL-STLKT01V1 SensorTile integrated development platform. Rev 5. Março 2019.

- UCLA. <a href="https://sites.google.com/view/ucla-stmicroelectronics-iot/home" target="_blank">STMicroelectronics SensorTile Internet of Things Curriculum</a>