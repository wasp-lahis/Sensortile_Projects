/**
******************************************************************************
* @file    SensorTile.box_env_sensors_ex.c
* @author  SRA - Central Labs
* @version V1.3.2
* @date    04-Feb-2020
* @brief   This file provides BSP Environment Sensors Extended interface
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2020 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "SensorTile.box_env_sensors_ex.h"

extern void *EnvCompObj[ENV_INSTANCES_NBR];

/**
 * @brief Enable DRDY Interrupt mode
 * @param Instance the device instance
 * @retval BSP_ERROR_NONE in case of success
 * @retval BSP_ERROR_COMPONENT_FAILURE in case of failure
 */
int32_t BSP_ENV_SENSOR_Enable_DRDY_Interrupt(uint32_t Instance)
{
  int32_t ret=BSP_ERROR_NONE;

  switch (Instance)
  {
#if (USE_ENV_SENSOR_LPS22HH_0 == 1)
   case LPS22HH_0:
     if(LPS22HH_Enable_DRDY_Interrupt(EnvCompObj[Instance]) != BSP_ERROR_NONE)
     {
       ret = BSP_ERROR_COMPONENT_FAILURE;
     }
     else
     {
       ret = BSP_ERROR_NONE;
     }
     break;
#endif
#if (USE_ENV_SENSOR_HTS221_0 == 1)
   case HTS221_0:
     if(HTS221_Enable_DRDY_Interrupt(EnvCompObj[Instance]) != BSP_ERROR_NONE)
     {
       ret = BSP_ERROR_COMPONENT_FAILURE;
     }
     else
     {
       ret = BSP_ERROR_NONE;
     }
     break;
#endif
#if (USE_ENV_SENSOR_STTS751_0 == 1)
   case STTS751_0:     
     ret = BSP_NOT_IMPLEMENTED;
    break;
#endif
    default:
      break;     
  }
  
  return ret;
}

/**
 * @brief Set the value of powerMode
 * @param Instance the device instance
 * @param powerMode: this is the value of the powerMode
 * @retval BSP_ERROR_NONE in case of success
 * @retval BSP_ERROR_COMPONENT_FAILURE in case of failure
 */
int32_t BSP_ENV_SENSOR_Set_PowerMode(uint32_t Instance, uint8_t powerMode)
{
  int32_t ret=BSP_ERROR_NONE;

  switch (Instance)
  {
#if (USE_ENV_SENSOR_LPS22HH_0 == 1)
   case LPS22HH_0:
     if(LPS22HH_Set_Power_Mode(EnvCompObj[Instance], powerMode) != BSP_ERROR_NONE)
     {
       ret = BSP_ERROR_COMPONENT_FAILURE;
     }
     else
     {
       ret = BSP_ERROR_NONE;
     }
     break;
#endif
#if (USE_ENV_SENSOR_STTS751_0 == 1)
     case STTS751_0:     
       ret = BSP_NOT_IMPLEMENTED;
     break;
#endif
#if (USE_ENV_SENSOR_HTS221_0 == 1)
    case HTS221_0:     
     ret = BSP_NOT_IMPLEMENTED;
    break;
#endif
    default:
      break;     
  }

  return ret;
}

/**
 * @brief Set the value of powerMode
 * @param Instance the device instance
 * @param filterMode: this is the value of the filterMode
 * @retval BSP_ERROR_NONE in case of success
 * @retval BSP_ERROR_COMPONENT_FAILURE in case of failure
 */
int32_t BSP_ENV_SENSOR_Set_FilterMode(uint32_t Instance, uint8_t filterMode)
{
  int32_t ret=BSP_ERROR_NONE;

  switch (Instance)
  {
#if (USE_ENV_SENSOR_LPS22HH_0 == 1)
   case LPS22HH_0:
     if(LPS22HH_Set_Filter_Mode(EnvCompObj[Instance], filterMode) != BSP_ERROR_NONE)
     {
       ret = BSP_ERROR_COMPONENT_FAILURE;
     }
     else
     {
       ret = BSP_ERROR_NONE;
     }
     break;
#endif
#if (USE_ENV_SENSOR_STTS751_0 == 1)
     case STTS751_0:     
       ret = BSP_NOT_IMPLEMENTED;
     break;
#endif
#if (USE_ENV_SENSOR_HTS221_0 == 1)
    case HTS221_0:     
     ret = BSP_NOT_IMPLEMENTED;
    break;
#endif
    default:
      break;     
  }

  return ret;
}

/**
 * @brief  Set environmental sensor one shot mode
 * @param  Instance environmental sensor instance to be used
 * @retval BSP status
 */
int32_t BSP_ENV_SENSOR_Set_One_Shot(uint32_t Instance)
{
   int32_t ret=BSP_ERROR_NONE;

  switch (Instance)
  {
#if (USE_ENV_SENSOR_HTS221_0 == 1)
    case HTS221_0:
      if (HTS221_Set_One_Shot(EnvCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_ENV_SENSOR_LPS22HH_0 == 1)
    case LPS22HH_0:
      if (LPS22HH_Set_One_Shot(EnvCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif
#if (USE_ENV_SENSOR_STTS751_0 == 1)
     case STTS751_0:     
       ret = BSP_NOT_IMPLEMENTED;
     break;
#endif
   default:
    break;
  }

  return ret;
}

/**
 * @brief  Get environmental sensor one shot status
 * @param  Instance environmental sensor instance to be used
 * @param  Status pointer to the one shot status (1 means measurements available, 0 means measurements not available yet)
 * @retval BSP status
 */
int32_t BSP_ENV_SENSOR_Get_One_Shot_Status(uint32_t Instance, uint8_t *Status)
{
   int32_t ret;

  switch (Instance)
  {
#if (USE_ENV_SENSOR_HTS221_0 == 1)
    case HTS221_0:
      if (HTS221_Get_One_Shot_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_ENV_SENSOR_LPS22HH_0 == 1)
    case LPS22HH_0:
      if (LPS22HH_Get_One_Shot_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif
#if (USE_ENV_SENSOR_STTS751_0 == 1)
     case STTS751_0:     
       ret = BSP_NOT_IMPLEMENTED;
     break;
#endif
    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get the status of data ready bit
 * @param  Instance the device instance
 * @param  Function Environmental sensor function
 * @param  Status the pointer to the status
 * @retval BSP status
 */
int32_t BSP_ENV_SENSOR_Get_DRDY_Status(uint32_t Instance, uint32_t Function, uint8_t *Status)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_ENV_SENSOR_LPS22HH_0 == 1)
    case LPS22HH_0:
      if ((Function & ENV_PRESSURE) == ENV_PRESSURE)
      {
        if (LPS22HH_PRESS_Get_DRDY_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else if ((Function & ENV_TEMPERATURE) == ENV_TEMPERATURE)
      {
        if (LPS22HH_TEMP_Get_DRDY_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      break;
#endif

#if (USE_ENV_SENSOR_HTS221_0 == 1)
    case HTS221_0:
      if ((Function & ENV_HUMIDITY) == ENV_HUMIDITY)
      {
        if (HTS221_HUM_Get_DRDY_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else if ((Function & ENV_TEMPERATURE) == ENV_TEMPERATURE)
      {
        if (HTS221_TEMP_Get_DRDY_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      break;
#endif
      
#if (USE_ENV_SENSOR_STTS751_0 == 1)
    case STTS751_0:
      if ((Function & ENV_TEMPERATURE) == ENV_TEMPERATURE)
      {
        if (STTS751_TEMP_Get_DRDY_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get the register value
 * @param  Instance the device instance
 * @param  Reg address to be read
 * @param  Data pointer where the value is written to
 * @retval BSP status
 */
int32_t BSP_ENV_SENSOR_Read_Register(uint32_t Instance, uint8_t Reg, uint8_t *Data)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_ENV_SENSOR_LPS22HH_0 == 1)
    case LPS22HH_0:
      if (LPS22HH_Read_Reg(EnvCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_ENV_SENSOR_HTS221_0 == 1)
    case HTS221_0:
      if (HTS221_Read_Reg(EnvCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_ENV_SENSOR_STTS751_0 == 1)
    case STTS751_0:
      if (STTS751_Read_Reg(EnvCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Set the register value
 * @param  Instance the device instance
 * @param  Reg address to be read
 * @param  Data value to be written
 * @retval BSP status
 */
int32_t BSP_ENV_SENSOR_Write_Register(uint32_t Instance, uint8_t Reg, uint8_t Data)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_ENV_SENSOR_LPS22HH_0 == 1)
    case LPS22HH_0:
      if (LPS22HH_Write_Reg(EnvCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_ENV_SENSOR_HTS221_0 == 1)
    case HTS221_0:
      if (HTS221_Write_Reg(EnvCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_ENV_SENSOR_STTS751_0 == 1)
    case STTS751_0:
      if (STTS751_Write_Reg(EnvCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
