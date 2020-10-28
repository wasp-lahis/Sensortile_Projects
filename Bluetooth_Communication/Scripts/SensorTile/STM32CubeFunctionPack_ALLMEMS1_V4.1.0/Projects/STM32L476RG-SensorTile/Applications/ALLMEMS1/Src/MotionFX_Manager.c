/**
  ******************************************************************************
  * @file    MotionFX_Manager.c
  * @author  System Research & Applications Team - Catania Lab.
  * @version V4.1.0
  * @date    26-May-2020
  * @brief   Header for MotionFX_Manager.c
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
#include <stdio.h>
#include "TargetFeatures.h"
#include "main.h"

/* Private defines -----------------------------------------------------------*/
#define FROM_MDPS_TO_DPS    0.001
#define FROM_MGAUSS_TO_UT50 (0.1f/50.0f)
#define SAMPLETODISCARD 15
#define GBIAS_ACC_TH_SC_6X (2.0f*0.000765f)
#define GBIAS_GYRO_TH_SC_6X (2.0f*0.002f)
#define GBIAS_MAG_TH_SC_6X (2.0f*0.001500f)
#define GBIAS_ACC_TH_SC_9X (2.0f*0.000765f)
#define GBIAS_GYRO_TH_SC_9X (2.0f*0.002f)
#define GBIAS_MAG_TH_SC_9X (2.0f*0.001500f)

/* Delta time mSec for Deltafusion */
#define MOTIONFX_ENGINE_DELTATIME       0.01f

/* Exported Variables -------------------------------------------------------------*/
MFX_output_t iDataOUT;
MFX_input_t iDataIN;

/* Imported Variables -------------------------------------------------------------*/
extern float sensitivity_Mul;

extern BSP_MOTION_SENSOR_Axes_t MAG_Offset;

/* Private Variables -------------------------------------------------------------*/
static int discardedCount = 0;

static MFX_knobs_t iKnobs;
static MFX_knobs_t* ipKnobs;

/* Private function prototypes -----------------------------------------------*/


/**
  * @brief  Initialize MotionFX engine
  * @retval None
  */
void MotionFX_manager_init(void)
{
  char LibVersion[36];
  
  MotionFX_initialize();
  MotionFX_GetLibVersion(LibVersion);

  //ST MotionFX Engine Initializations
  ipKnobs = &iKnobs;

  MotionFX_getKnobs(ipKnobs);

  ipKnobs->gbias_acc_th_sc_6X = GBIAS_ACC_TH_SC_6X;
  ipKnobs->gbias_gyro_th_sc_6X = GBIAS_GYRO_TH_SC_6X;
  ipKnobs->gbias_mag_th_sc_6X = GBIAS_MAG_TH_SC_6X;

  ipKnobs->gbias_acc_th_sc_9X = GBIAS_ACC_TH_SC_9X;
  ipKnobs->gbias_gyro_th_sc_9X = GBIAS_GYRO_TH_SC_9X;
  ipKnobs->gbias_mag_th_sc_9X = GBIAS_MAG_TH_SC_9X;
  
  ipKnobs->acc_orientation[0] ='w';
  ipKnobs->acc_orientation[1] ='s';
  ipKnobs->acc_orientation[2] ='u';

  ipKnobs->gyro_orientation[0] = 'w';
  ipKnobs->gyro_orientation[1] = 's';
  ipKnobs->gyro_orientation[2] = 'u';
  
  ipKnobs->mag_orientation[0] = 's';
  ipKnobs->mag_orientation[1] = 'w';
  ipKnobs->mag_orientation[2] = 'u';

  ipKnobs->output_type = MFX_ENGINE_OUTPUT_ENU;
  ipKnobs->LMode = 1;
  ipKnobs->modx  = 1;

  MotionFX_setKnobs(ipKnobs);
  
  MotionFX_enable_6X(MFX_ENGINE_DISABLE);
  MotionFX_enable_9X(MFX_ENGINE_DISABLE);

  discardedCount = 0;

  TargetBoardFeatures.MotionFXIsInitalized=1;
  ALLMEMS1_PRINTF("Initialized %s\n\r", LibVersion);
}

/**
  * @brief  Run sensor fusion algorithm
  * @param BSP_MOTION_SENSOR_AxesRaw_t ACC_Value_Raw Acceleration value (x/y/z)
  * @param BSP_MOTION_SENSOR_Axes_t GYR_Value Gyroscope value (x/y/z)
  * @param BSP_MOTION_SENSOR_Axes_t MAG_Value Magneto value (x/y/z)
  * @retval None
  */
void MotionFX_manager_run( BSP_MOTION_SENSOR_AxesRaw_t ACC_Value_Raw,BSP_MOTION_SENSOR_Axes_t GYR_Value,BSP_MOTION_SENSOR_Axes_t MAG_Value)
{
  float delta_time= MOTIONFX_ENGINE_DELTATIME;
  
  iDataIN.gyro[0] = GYR_Value.x  * FROM_MDPS_TO_DPS;
  iDataIN.gyro[1] = GYR_Value.y  * FROM_MDPS_TO_DPS;
  iDataIN.gyro[2] = GYR_Value.z  * FROM_MDPS_TO_DPS; 

  iDataIN.acc[0] = ACC_Value_Raw.x * sensitivity_Mul;
  iDataIN.acc[1] = ACC_Value_Raw.y * sensitivity_Mul;
  iDataIN.acc[2] = ACC_Value_Raw.z * sensitivity_Mul;
  
  iDataIN.mag[0] = (MAG_Value.x - MAG_Offset.x) * FROM_MGAUSS_TO_UT50;
  iDataIN.mag[1] = (MAG_Value.y - MAG_Offset.y) * FROM_MGAUSS_TO_UT50;
  iDataIN.mag[2] = (MAG_Value.z - MAG_Offset.z) * FROM_MGAUSS_TO_UT50;

  if(discardedCount == SAMPLETODISCARD) {
    MotionFX_propagate(&iDataOUT, &iDataIN, &delta_time);
    MotionFX_update(&iDataOUT, &iDataIN, &delta_time, NULL);
  } else  {
    discardedCount++;
  }  
}

/**
 * @brief  Start 6 axes MotionFX engine
 * @retval None
 */
void MotionFX_manager_start_6X(void)
{
  MotionFX_enable_6X(MFX_ENGINE_ENABLE);
}

/**
 * @brief  Stop 6 axes MotionFX engine
 * @retval None
 */
void MotionFX_manager_stop_6X(void)
{
  MotionFX_enable_6X(MFX_ENGINE_DISABLE);
}

/**
 * @brief  Start 9 axes MotionFX engine
 * @retval None
 */
void MotionFX_manager_start_9X(void)
{
  MotionFX_enable_9X(MFX_ENGINE_ENABLE);
}

/**
 * @brief  Stop 9 axes MotionFX engine
 * @retval None
 */
void MotionFX_manager_stop_9X(void)
{
  MotionFX_enable_9X(MFX_ENGINE_DISABLE);
}

/**
* @brief  Get MotionFX Engine data Out
* @param  None
* @retval MFX_output *iDataOUT MotionFX Engine data Out
*/
MFX_output_t* MotionFX_manager_getDataOUT(void)
{
  return &iDataOUT;
}

/**
* @brief  Get MotionFX Engine data IN
* @param  None
* @retval MFX_input *iDataIN MotionFX Engine data IN
*/
MFX_input_t* MotionFX_manager_getDataIN(void)
{
  return &iDataIN;
}

/**
  * @brief  Run magnetometer calibration algorithm
  * @param  None
  * @retval None
  */
void MotionFX_manager_MagCal_run(MFX_MagCal_input_t *data_in, MFX_MagCal_output_t *data_out)
{
   MotionFX_MagCal_run(data_in);
   MotionFX_MagCal_getParams(data_out);
}


/**
 * @brief  Start magnetometer calibration
 * @param  None
 * @retval None
 */
void MotionFX_manager_MagCal_start(int sampletime)
{
  MotionFX_MagCal_init(sampletime, 1);
}


/**
 * @brief  Stop magnetometer calibration
 * @param  None
 * @retval None
 */
void MotionFX_manager_MagCal_stop(int sampletime)
{
  MotionFX_MagCal_init(sampletime, 0);
}


/**
 * @brief  Load calibration parameter from memory
 * @param  dataSize length ot the data
 * @param  data pointer to the data
 * @retval (1) fail, (0) success
 */
char MotionFX_LoadMagCalFromNVM(unsigned short int dataSize, unsigned int *data)
{
   char Success=0;
   Success= ReCallMagnetoCalibrationFromMemory(dataSize / 4, (uint32_t*) data);
   return Success;
}

/**
 * @brief  Save calibration parameter to memory
 * @param  dataSize length ot the data
 * @param  data pointer to the data
 * @retval (1) fail, (0) success
 */
char MotionFX_SaveMagCalInNVM(unsigned short int dataSize, unsigned int *data)
{
  char Success=0;
  Success= SaveMagnetoCalibrationToMemory(dataSize / 4, (uint32_t*) data);
  return Success;
}

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
