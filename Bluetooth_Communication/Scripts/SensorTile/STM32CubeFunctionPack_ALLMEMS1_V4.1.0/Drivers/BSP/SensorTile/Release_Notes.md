---
pagetitle: Release Notes for STEVAL-STLKT01V1 Board Drivers 
lang: en
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

::: {.card .fluid}

::: {.sectione .dark}
<center>
# <small>Release Notes for</small> **STEVAL-STLKT01V1 Board Drivers**
Copyright &copy; 2020  STMicroelectronics\
    
[![ST logo](_htmresc/st_logo.png)](https://www.st.com){.logo}
</center>
:::
:::

# License

Licensed by ST under BSD-3-Clause license (the "License"). You may not use this package except in compliance with the License. You may obtain a copy of the License at: [BSD-3-Clause](https://opensource.org/licenses/BSD-3-Clause)

# Purpose

The BSP (Board Specific Package) STEVAL-STLKT01V1 Board Drivers are based on the HAL drivers and provide a set of high level APIs relative to the hardware components and features in the evaluation board for a given STM32 processor

The BSP drivers allow a quick access to the boards’ services using high level APIs and without any specific configuration as the link with the HAL and the external components is done in intrinsic within the drivers. 

Here is the list of references to user documents:

- [UM2090](https://www.st.com/resource/en/user_manual/dm00311355.pdf) : Getting started with the software package for STEVAL-STLKT01V1 based on STM32Cube
- [STM32Cube](https://www.st.com/stm32cube) : STM32Cube
:::

::: {.col-sm-12 .col-lg-8}
# Update History

::: {.collapse}
<input type="checkbox" id="collapse-section13" checked aria-hidden="true">
<label for="collapse-section13" aria-hidden="true">__v2.1.4 / 22-Apr-2020__</label>
<div>			

## Main Changes

### Patch Release

- Solving Chip Select init issue: Sensor_IO_SPI_CS_Init_All must be called before any sensor SPI read/write

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section12" checked aria-hidden="true">
<label for="collapse-section12" aria-hidden="true">__v2.1.3 / 20-Sep-2019__</label>
<div>			

## Main Changes

### Patch Release

- Issue fixed in BSP_SD_WriteBlocks function in SensorTile_sd.c

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section11" checked aria-hidden="true">
<label for="collapse-section11" aria-hidden="true">__v2.1.2 / 11-Jun-2019__</label>
<div>			

## Main Changes

### Patch Release

- Bug fixed: added support for SDSC, SDHC and SDXC in SensorTile_sd

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section10" checked aria-hidden="true">
<label for="collapse-section10" aria-hidden="true">__v2.1.1 / 11-Jun-2019__</label>
<div>			

## Main Changes

### Patch Release

- Bug fixed: updated multi-byte read function in SensorTile_env_sensors and SensorTile_motion_sensors.
- Minor in SensorTile_bus

</div>
:::


::: {.collapse}
<input type="checkbox" id="collapse-section9" aria-hidden="true">
<label for="collapse-section9" aria-hidden="true">__v2.1.0 / 5-Apr-2019__</label>
<div>			

## Main Changes

### Maintenance and patch release

- Updated SensorTile_audio
- Bug fixed for pedometer and other minor fixed in SensorTile_motion_sensors
- Added One Shot support in SensorTile_env_sensors
- Updated SensorTile_conf_template

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section8" aria-hidden="true">
<label for="collapse-section8" aria-hidden="true">__v2.0.0 / 5-Feb-2019__</label>
<div>			

## Main Changes

### Product update

- Source Code Refactoring according new BSP v2.6 specifications

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section7" aria-hidden="true">
<label for="collapse-section7" aria-hidden="true">__v1.3.3 / 27-Sep-2017__</label>
<div>			

## Main Changes

### Patch Release

- Updated 3D Accelerometer drivers

</div>
:::
::: {.collapse}
<input type="checkbox" id="collapse-section6" aria-hidden="true">
<label for="collapse-section6" aria-hidden="true">__v1.3.2 / 11-Jul-2017__</label>
<div>			

## Main Changes

### Patch Release

- Minor fixes

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section5" aria-hidden="true">
<label for="collapse-section5" aria-hidden="true">__v1.3.1 / 27-Apr-2017__</label>
<div>			

## Main Changes

### Patch Release

-  Updated 3D Accelerometer and 3D Magnetometer drivers
-  Updated drivers for sensors I2C and SPI access
-  Updated SD Card support drivers

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section4" aria-hidden="true">
<label for="collapse-section4" aria-hidden="true">__v1.3.0 / 13-Mar-2017__</label>
<div>			

## Main Changes

### Maintenance Release

-  Updated 3D Accelerometer and 3D Magnetometer drivers
-  Updated SD Card support drivers

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section3"  aria-hidden="true">
<label for="collapse-section3" aria-hidden="true">__v1.2.0 / 04-Nov-2016__</label>
<div>			

## Main Changes

### Maintenance release

-  Updated 3D Accelerometer and 3D Magnetometer drivers
-  Updated Humidity drivers
-  Updated Temperature drivers
-  Updated Pressure drivers

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section2"  aria-hidden="true">
<label for="collapse-section2" aria-hidden="true">__v1.1.0 / 12-Sep-2016__</label>
<div>			

## Main Changes

### Maintenance release

-  Improved SD Card support
-  Added GG drivers

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section1"  aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">__v1.0.0 / 01-Jun-2016__</label>
<div>			

## Main Changes

### First official release

- First official release

</div>
:::

:::
:::

<footer class="sticky">
For complete documentation on **STEVAL-STLKT01V1** ,
visit: [www.st.com](https://www.st.com/en/evaluation-tools/steval-stlkt01v1.html)

This release note uses up to date web standards and, for this reason, should not
be opened with Internet Explorer but preferably with popular browsers such as
Google Chrome, Mozilla Firefox, Opera or Microsoft Edge.
</footer>
