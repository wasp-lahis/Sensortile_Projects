/**
  ******************************************************************************
  * @file    TargetFeatures.h 
  * @author  System Research & Applications Team - Catania Lab.
  * @version V4.1.0
  * @date    26-May-2020
  * @brief   Specification of the HW Features for each target platform
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020  STMicroelectronics</center></h2>
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
  
/* Define to prevent recursive inclusion -------------------------------------*/  
#ifndef _TARGET_FEATURES_H_
#define _TARGET_FEATURES_H_

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
   
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_conf.h"
#include "stm32l4xx_hal_def.h"
#include "SensorTile.h"
#include "SensorTile_audio.h"
#include "SensorTile_env_sensors.h"
#include "SensorTile_gg.h"
#include "SensorTile_motion_sensors.h"
#include "SensorTile_motion_sensors_ex.h"
#include "SensorTile_sd.h"
   
#include "ALLMEMS1_config.h"
#include "MetaDataManager.h"

/* Code for MotionAR integration - Start Section */
#include "MotionAR_Manager.h"
#include "motion_ar.h"
/* Code for MotionAR integration - End Section */

#ifdef ALLMEMS1_MOTIONCP
#include "MotionCP_Manager.h"
#include "motion_cp.h"
#endif /*  ALLMEMS1_MOTIONCP */
   
#ifdef ALLMEMS1_MOTIONFA
#include "MotionFA_Manager.h"
#include "motion_fa.h"
#endif /* ALLMEMS1_MOTIONFA */
   
/* Code for MotionFX integration - Start Section */
#include "MotionFX_Manager.h"
#include "motion_fx.h"
/* Code for MotionFX integration - End Section */

/* Code for MotionGR integration - Start Section */
#include "MotionGR_Manager.h"
#include "motion_gr.h"
/* Code for MotionGR integration - End Section */
   
/* Code for MotionID integration - Start Section */
#include "MotionID_Manager.h"
#include "motion_id.h"
/* Code for MotionID integration - End Section */

/* Code for MotionPE integration - Start Section */
#include "MotionPE_Manager.h"
#include "motion_pe.h"
/* Code for MotionPE integration - End Section */
   
/* Code for MotionSD integration - Start Section */
#include "MotionSD_Manager.h"
#include "motion_sd.h"
/* Code for MotionSD integration - End Section */
   
/* Code for MotionTL integration - Start Section */
#include "MotionTL_Manager.h"
#include "motion_tl.h"
/* Code for MotionTL integration - End Section */
   
/* Code for MotionVC integration - Start Section */
#include "MotionVC_Manager.h"
#include "motion_vc.h"
/* Code for MotionVC integration - End Section */

/* Code for BlueVoice integration - Start Section */
#include "AudioBV_Manager.h"
#include "bluevoice_adpcm.h"
/* Code for BlueVoice integration - End Section */

/* Exported defines ------------------------------------------------------- */
#define MAX_TEMP_SENSORS 2

/* Exported macros ------------------------------------------------------- */

/* Exported types ------------------------------------------------------- */

/**
 * @brief  Target's Features data structure definition
 */
typedef struct
{
  int32_t NumTempSensors;
  
  uint8_t InitPressureSensor;
  uint8_t InitHumiditySensor;

  uint8_t LedStatus;
    
  void *HandleGGComponent;

  /* Code for MotionAR integration - Start Section */
  uint32_t MotionARIsInitalized;
  /* Code for MotionAR integration - End Section */

  #ifdef ALLMEMS1_MOTIONCP
  uint32_t MotionCPIsInitalized;
  #endif /*  ALLMEMS1_MOTIONCP */
  
  #ifdef ALLMEMS1_MOTIONFA
  uint32_t MotionFAIsInitalized;
  #endif /* ALLMEMS1_MOTIONFA */
  
  /* Code for MotionFX integration - Start Section */
  uint32_t MotionFXIsInitalized;
  /* Code for MotionFX integration - End Section */
  
  /* Code for MotionGR integration - Start Section */
  uint32_t MotionGRIsInitalized;
  /* Code for MotionGR integration - End Section */
  
  /* Code for MotionID integration - Start Section */
  uint32_t MotionIDIsInitalized;
  /* Code for MotionID integration - End Section */
  
  /* Code for MotionPE integration - Start Section */
  uint32_t MotionPEIsInitalized;
  /* Code for MotionPE integration - End Section */
  
  /* Code for MotionSD integration - Start Section */
  uint32_t MotionSDIsInitalized;
  /* Code for MotionSD integration - End Section */

  /* Code for MotionTL integration - Start Section */
  uint32_t MotionTLIsInitalized;
  /* Code for MotionTL integration - End Section */
  
  /* Code for MotionVC integration - Start Section */
  uint32_t MotionVCIsInitalized;
  /* Code for MotionVC integration - End Section */
  
  /* Code for BlueVoice integration - Start Section */
  uint32_t AudioBVIsInitalized;
  /* Code for BlueVoice integration - End Section */  
} TargetFeatures_t;

/* Exported variables ------------------------------------------------------- */
extern TargetFeatures_t TargetBoardFeatures;

/* Exported functions ------------------------------------------------------- */
extern void InitTargetPlatform(void);

extern void InitMics(uint32_t AudioFreq, uint32_t AudioVolume, uint16_t AudioInSamples);
extern void DeInitMics(void);

extern void LedOnTargetPlatform(void);
extern void LedOffTargetPlatform(void);
extern void LedToggleTargetPlatform(void);

#ifdef __cplusplus
}
#endif

#endif /* _TARGET_FEATURES_H_ */

/******************* (C) COPYRIGHT 2020  STMicroelectronics *****END OF FILE****/

