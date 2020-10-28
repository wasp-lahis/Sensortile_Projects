/**
  ******************************************************************************
  * @file    MotionFA_Manager.c
  * @author  MEMS Software Solutions Team
  * @version V4.1.0
  * @date    26-May-2020
  * @brief   This file contains Fitness Activities interface functions
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
#include "TargetFeatures.h"

#ifdef ALLMEMS1_MOTIONFA
/** @addtogroup MOTION_APPLICATIONS MOTION APPLICATIONS
 * @{
 */

/** @addtogroup FITNESS_ACTIVITIES FITNESS ACTIVITIES
 * @{
 */

/* Private variables ---------------------------------------------------------*/
MFA_activity_t SelectedActivity = MFA_BICEPCURL;

/* Private typedef -----------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 * @brief  Initialisze MotionFA algorithm
 * @param  None
 * @retval None
 */
void MotionFA_manager_init(void)
{
  char LibVersion[36];
  char acc_orientation[3];
  char gyr_orientation[3];

  MotionFA_Initialize();
  MotionFA_GetLibVersion(LibVersion);

  acc_orientation[0] ='w';
  acc_orientation[1] ='s';
  acc_orientation[2] ='u';

  gyr_orientation[0] = 'w';
  gyr_orientation[1] = 's';
  gyr_orientation[2] = 'u';

  MotionFA_SetOrientation_Acc(acc_orientation);
  MotionFA_SetOrientation_Gyr(gyr_orientation);
  
  TargetBoardFeatures.MotionFAIsInitalized=1;
  ALLMEMS1_PRINTF("Initialized %s\r\n", LibVersion);
}

/**
 * @brief  Run Fitness Activities algorithm
 * @param  data_in Structure containing input data
 * @param  data_out Structure containing ouput data
 * @retval None
 */
void MotionFA_manager_run(MFA_input_t *data_in, MFA_output_t *data_out)
{
  switch (SelectedActivity)
  {
    case MFA_BICEPCURL:
      MotionFA_BicepCurl_Update(data_in, data_out);
      break;

    case MFA_SQUAT:
      MotionFA_Squat_Update(data_in, data_out);
      break;

    case MFA_PUSHUP:
      MotionFA_Pushup_Update(data_in, data_out);
      break;

    default:
      break;
  }
}

/**
 * @brief  Get the library version
 * @param  version  Library version string (must be array of 35 char)
 * @param  length  Library version string length
 * @retval None
 */
void MotionFA_manager_get_version(char *version, int *length)
{
  *length = (int)MotionFA_GetLibVersion(version);
}

/**
 * @brief  Reset counter or current activity
 * @param  None
 * @retval None
 */
void MotionFA_manager_reset_counter(void)
{
  switch (SelectedActivity)
  {
    case MFA_BICEPCURL:
      MotionFA_BicepCurl_Reset();
      break;

    case MFA_SQUAT:
      MotionFA_Squat_Reset();
      break;

    case MFA_PUSHUP:
      MotionFA_Pushup_Reset();
      break;

    default:
      break;
  }
}

/**
 * @brief  Set activity
 * @param  activity Activity type
 * @retval None
 */
void MotionFA_manager_set_activity(MFA_activity_t activity)
{
  SelectedActivity = activity;
}

/**
 * @brief  Get activity
 * @param  None
 * @retval activity type
 */
void MotionFA_manager_get_activity(MFA_activity_t *activity)
{
  *activity = SelectedActivity;
}

/**
 * @}
 */

/**
 * @}
 */

#endif /* ALLMEMS1_MOTIONFA */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
