/**
  ******************************************************************************
  * @file    ov2640.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    19-June-2014
  * @brief   This file provides the OV2640 camera driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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
#include "ov2640.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup OV2640
  * @brief     This file provides a set of functions needed to drive the 
  *            OV2640 Camera module.
  * @{
  */

/** @defgroup OV2640_Private_TypesDefinitions
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup OV2640_Private_Defines
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup OV2640_Private_Macros
  * @{
  */
     
/**
  * @}
  */  
  
/** @defgroup OV2640_Private_FunctionPrototypes
  * @{
  */
static uint32_t ov2640_ConvertValue(uint32_t feature, uint32_t value);
/**
  * @}
  */ 
  
/** @defgroup OV2640_Private_Variables
  * @{
  */        

CAMERA_DrvTypeDef   ov2640_drv = 
{
  ov2640_Init,
  ov2640_ReadID,  
  ov2640_Config,
};

/* Initialization sequence for 480x272 resolution */
const unsigned char OV2640_480x272[][2]=
{
  {0xff, 0x00},  /* Device control register list Table 12 */
  {0x2c, 0xff},  /* Reserved                              */
  {0x2e, 0xdf},  /* Reserved                              */
  {0xff, 0x01},  /* Device control register list Table 13 */
  {0x3c, 0x32},  /* Reserved                              */
  {0x11, 0x00},  /* Clock Rate Control                    */
  {0x09, 0x02},  /* Common control 2                      */
  {0x04, 0xA8},  /* Mirror                                */
  {0x13, 0xe5},  /* Common control 8                      */
  {0x14, 0x48},  /* Common control 9                      */
  {0x2c, 0x0c},  /* Reserved                              */
  {0x33, 0x78},  /* Reserved                              */
  {0x3a, 0x33},  /* Reserved                              */
  {0x3b, 0xfB},  /* Reserved                              */
  {0x3e, 0x00},  /* Reserved                              */
  {0x43, 0x11},  /* Reserved                              */
  {0x16, 0x10},  /* Reserved                              */
  {0x4a, 0x81},  /* Reserved                              */
  {0x21, 0x99},  /* Reserved                              */
  {0x24, 0x40},  /* Luminance signal High range           */
  {0x25, 0x38},  /* Luminance signal low range            */
  {0x26, 0x82},  /*                                       */
  {0x5c, 0x00},  /* Reserved                              */
  {0x63, 0x00},  /* Reserved                              */
  {0x46, 0x3f},  /* Frame length adjustment               */
  {0x0c, 0x3c},  /* Common control 3                      */
  {0x61, 0x70},  /* Histogram algo low level              */
  {0x62, 0x80},  /* Histogram algo high level             */
  {0x7c, 0x05},  /* Reserved                              */
  {0x20, 0x80},  /* Reserved                              */
  {0x28, 0x30},  /* Reserved                              */
  {0x6c, 0x00},  /* Reserved                              */
  {0x6d, 0x80},  /* Reserved                              */
  {0x6e, 0x00},  /* Reserved                              */
  {0x70, 0x02},  /* Reserved                              */
  {0x71, 0x94},  /* Reserved                              */
  {0x73, 0xc1},  /* Reserved                              */
  {0x3d, 0x34},  /* Reserved                              */
  {0x5a, 0x57},  /* Reserved                              */
  {0x12, 0x00},  /* Common control 7                      */
  {0x11, 0x00},  /* Clock Rate Control                   2*/
  {0x17, 0x11},  /* Horiz window start MSB 8bits          */
  {0x18, 0x75},  /* Horiz window end MSB 8bits            */
  {0x19, 0x01},  /* Vert window line start MSB 8bits      */
  {0x1a, 0x97},  /* Vert window line end MSB 8bits        */
  {0x32, 0x36},
  {0x03, 0x0f},
  {0x37, 0x40},
  {0x4f, 0xbb},
  {0x50, 0x9c},
  {0x5a, 0x57},
  {0x6d, 0x80},
  {0x6d, 0x38},
  {0x39, 0x02},
  {0x35, 0x88},
  {0x22, 0x0a},
  {0x37, 0x40},
  {0x23, 0x00},
  {0x34, 0xa0},
  {0x36, 0x1a},
  {0x06, 0x02},
  {0x07, 0xc0},
  {0x0d, 0xb7},
  {0x0e, 0x01},
  {0x4c, 0x00},
  {0xff, 0x00},
  {0xe5, 0x7f},
  {0xf9, 0xc0},
  {0x41, 0x24},
  {0xe0, 0x14},
  {0x76, 0xff},
  {0x33, 0xa0},
  {0x42, 0x20},
  {0x43, 0x18},
  {0x4c, 0x00},
  {0x87, 0xd0},
  {0x88, 0x3f},
  {0xd7, 0x03},
  {0xd9, 0x10},
  {0xd3, 0x82},
  {0xc8, 0x08},
  {0xc9, 0x80},
  {0x7d, 0x00},
  {0x7c, 0x03},
  {0x7d, 0x48},
  {0x7c, 0x08},
  {0x7d, 0x20},
  {0x7d, 0x10},
  {0x7d, 0x0e},
  {0x90, 0x00},
  {0x91, 0x0e},
  {0x91, 0x1a},
  {0x91, 0x31},
  {0x91, 0x5a},
  {0x91, 0x69},
  {0x91, 0x75},
  {0x91, 0x7e},
  {0x91, 0x88},
  {0x91, 0x8f},
  {0x91, 0x96},
  {0x91, 0xa3},
  {0x91, 0xaf},
  {0x91, 0xc4},
  {0x91, 0xd7},
  {0x91, 0xe8},
  {0x91, 0x20},
  {0x92, 0x00},
  {0x93, 0x06},
  {0x93, 0xe3},
  {0x93, 0x02},
  {0x93, 0x02},
  {0x93, 0x00},
  {0x93, 0x04},
  {0x93, 0x00},
  {0x93, 0x03},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x96, 0x00},
  {0x97, 0x08},
  {0x97, 0x19},
  {0x97, 0x02},
  {0x97, 0x0c},
  {0x97, 0x24},
  {0x97, 0x30},
  {0x97, 0x28},
  {0x97, 0x26},
  {0x97, 0x02},
  {0x97, 0x98},
  {0x97, 0x80},
  {0x97, 0x00},
  {0x97, 0x00},
  {0xc3, 0xef},
  {0xff, 0x00},
  {0xba, 0xdc},
  {0xbb, 0x08},
  {0xb6, 0x24},
  {0xb8, 0x33},
  {0xb7, 0x20},
  {0xb9, 0x30},
  {0xb3, 0xb4},
  {0xb4, 0xca},
  {0xb5, 0x43},
  {0xb0, 0x5c},
  {0xb1, 0x4f},
  {0xb2, 0x06},
  {0xc7, 0x00},
  {0xc6, 0x51},
  {0xc5, 0x11},
  {0xc4, 0x9c},
  {0xbf, 0x00},
  {0xbc, 0x64},
  {0xa6, 0x00},
  {0xa7, 0x1e},
  {0xa7, 0x6b},
  {0xa7, 0x47},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x2e},
  {0xa7, 0x85},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x1b},
  {0xa7, 0x74},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xc0, 0xc8},
  {0xc1, 0x96},
  {0x8c, 0x00},
  {0x86, 0x3d},
  {0x50, 0x92},
  {0x51, 0x90},
  {0x52, 0x2c},
  {0x53, 0x00},
  {0x54, 0x00},
  {0x55, 0x88},
  {0x5a, 0x50},
  {0x5b, 0x3c},
  {0x5c, 0x00},
  {0xd3, 0x04},
  {0x7f, 0x00},
  {0xda, 0x00},
  {0xe5, 0x1f},
  {0xe1, 0x67},
  {0xe0, 0x00},
  {0xdd, 0x7f},
  {0x05, 0x00},
  {0xff, 0x00},
  {0xe0, 0x04},
  {0xc0, 0xc8},
  {0xc1, 0x96},
  {0x86, 0x3d},
  {0x50, 0x92},
  {0x51, 0x90},
  {0x52, 0x2c},
  {0x53, 0x00},
  {0x54, 0x00},
  {0x55, 0x88},
  {0x57, 0x00},
  {0x5a, 0x50},
  {0x5b, 0x3c},
  {0x5c, 0x00},
  {0xd3, 0x04},
  {0xe0, 0x00},
  {0xFF, 0x00},
  {0x05, 0x00},
  {0xDA, 0x08},
  {0xda, 0x09},
  {0x98, 0x00},
  {0x99, 0x00},
  {0x00, 0x00},
  {0xff, 0x00},
  {0xe0, 0x04},
  {0xc0, 0xc8},
  {0xc1, 0x96},
  {0x86, 0x35},
  {0x50, 0x80},
  {0x51, 0x90},
  {0x52, 0x2c},
  {0x53, 0x00},
  {0x54, 0x00},
  {0x55, 0x88},
  {0x57, 0x00},
  {0x5a, 0x78},
  {0x5b, 0x44},
  {0x5c, 0x00},
  {0xd3, 0x04},
  {0xe0, 0x00},
};

/* Initialization sequence for VGA resolution (640x480)*/
const unsigned char OV2640_VGA[][2]=
{
  {0xff, 0x00},  /* Device control register list Table 12 */
  {0x2c, 0xff},  /* Reserved                              */
  {0x2e, 0xdf},  /* Reserved                              */
  {0xff, 0x01},  /* Device control register list Table 13 */
  {0x3c, 0x32},  /* Reserved                              */
  {0x11, 0x00},  /* Clock Rate Control                    */
  {0x09, 0x02},  /* Common control 2                      */
  {0x04, 0xA8},  /* Mirror                                */
  {0x13, 0xe5},  /* Common control 8                      */
  {0x14, 0x48},  /* Common control 9                      */
  {0x2c, 0x0c},  /* Reserved                              */
  {0x33, 0x78},  /* Reserved                              */
  {0x3a, 0x33},  /* Reserved                              */
  {0x3b, 0xfB},  /* Reserved                              */
  {0x3e, 0x00},  /* Reserved                              */
  {0x43, 0x11},  /* Reserved                              */
  {0x16, 0x10},  /* Reserved                              */
  {0x4a, 0x81},  /* Reserved                              */
  {0x21, 0x99},  /* Reserved                              */
  {0x24, 0x40},  /* Luminance signal High range           */
  {0x25, 0x38},  /* Luminance signal low range            */
  {0x26, 0x82},  /*                                       */
  {0x5c, 0x00},  /* Reserved                              */
  {0x63, 0x00},  /* Reserved                              */
  {0x46, 0x3f},  /* Frame length adjustment               */
  {0x0c, 0x3c},  /* Common control 3                      */
  {0x61, 0x70},  /* Histogram algo low level              */
  {0x62, 0x80},  /* Histogram algo high level             */
  {0x7c, 0x05},  /* Reserved                              */
  {0x20, 0x80},  /* Reserved                              */
  {0x28, 0x30},  /* Reserved                              */
  {0x6c, 0x00},  /* Reserved                              */
  {0x6d, 0x80},  /* Reserved                              */
  {0x6e, 0x00},  /* Reserved                              */
  {0x70, 0x02},  /* Reserved                              */
  {0x71, 0x94},  /* Reserved                              */
  {0x73, 0xc1},  /* Reserved                              */
  {0x3d, 0x34},  /* Reserved                              */
  {0x5a, 0x57},  /* Reserved                              */
  {0x12, 0x00},  /* Common control 7                      */
  {0x11, 0x00},  /* Clock Rate Control                   2*/
  {0x17, 0x11},  /* Horiz window start MSB 8bits          */
  {0x18, 0x75},  /* Horiz window end MSB 8bits            */
  {0x19, 0x01},  /* Vert window line start MSB 8bits      */
  {0x1a, 0x97},  /* Vert window line end MSB 8bits        */
  {0x32, 0x36},
  {0x03, 0x0f},
  {0x37, 0x40},
  {0x4f, 0xbb},
  {0x50, 0x9c},
  {0x5a, 0x57},
  {0x6d, 0x80},
  {0x6d, 0x38},
  {0x39, 0x02},
  {0x35, 0x88},
  {0x22, 0x0a},
  {0x37, 0x40},
  {0x23, 0x00},
  {0x34, 0xa0},
  {0x36, 0x1a},
  {0x06, 0x02},
  {0x07, 0xc0},
  {0x0d, 0xb7},
  {0x0e, 0x01},
  {0x4c, 0x00},
  {0xff, 0x00},
  {0xe5, 0x7f},
  {0xf9, 0xc0},
  {0x41, 0x24},
  {0xe0, 0x14},
  {0x76, 0xff},
  {0x33, 0xa0},
  {0x42, 0x20},
  {0x43, 0x18},
  {0x4c, 0x00},
  {0x87, 0xd0},
  {0x88, 0x3f},
  {0xd7, 0x03},
  {0xd9, 0x10},
  {0xd3, 0x82},
  {0xc8, 0x08},
  {0xc9, 0x80},
  {0x7d, 0x00},
  {0x7c, 0x03},
  {0x7d, 0x48},
  {0x7c, 0x08},
  {0x7d, 0x20},
  {0x7d, 0x10},
  {0x7d, 0x0e},
  {0x90, 0x00},
  {0x91, 0x0e},
  {0x91, 0x1a},
  {0x91, 0x31},
  {0x91, 0x5a},
  {0x91, 0x69},
  {0x91, 0x75},
  {0x91, 0x7e},
  {0x91, 0x88},
  {0x91, 0x8f},
  {0x91, 0x96},
  {0x91, 0xa3},
  {0x91, 0xaf},
  {0x91, 0xc4},
  {0x91, 0xd7},
  {0x91, 0xe8},
  {0x91, 0x20},
  {0x92, 0x00},
  {0x93, 0x06},
  {0x93, 0xe3},
  {0x93, 0x02},
  {0x93, 0x02},
  {0x93, 0x00},
  {0x93, 0x04},
  {0x93, 0x00},
  {0x93, 0x03},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x96, 0x00},
  {0x97, 0x08},
  {0x97, 0x19},
  {0x97, 0x02},
  {0x97, 0x0c},
  {0x97, 0x24},
  {0x97, 0x30},
  {0x97, 0x28},
  {0x97, 0x26},
  {0x97, 0x02},
  {0x97, 0x98},
  {0x97, 0x80},
  {0x97, 0x00},
  {0x97, 0x00},
  {0xc3, 0xef},
  {0xff, 0x00},
  {0xba, 0xdc},
  {0xbb, 0x08},
  {0xb6, 0x24},
  {0xb8, 0x33},
  {0xb7, 0x20},
  {0xb9, 0x30},
  {0xb3, 0xb4},
  {0xb4, 0xca},
  {0xb5, 0x43},
  {0xb0, 0x5c},
  {0xb1, 0x4f},
  {0xb2, 0x06},
  {0xc7, 0x00},
  {0xc6, 0x51},
  {0xc5, 0x11},
  {0xc4, 0x9c},
  {0xbf, 0x00},
  {0xbc, 0x64},
  {0xa6, 0x00},
  {0xa7, 0x1e},
  {0xa7, 0x6b},
  {0xa7, 0x47},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x2e},
  {0xa7, 0x85},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x1b},
  {0xa7, 0x74},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xc0, 0xc8},
  {0xc1, 0x96},
  {0x8c, 0x00},
  {0x86, 0x3d},
  {0x50, 0x92},
  {0x51, 0x90},
  {0x52, 0x2c},
  {0x53, 0x00},
  {0x54, 0x00},
  {0x55, 0x88},
  {0x5a, 0x50},
  {0x5b, 0x3c},
  {0x5c, 0x00},
  {0xd3, 0x04},
  {0x7f, 0x00},
  {0xda, 0x00},
  {0xe5, 0x1f},
  {0xe1, 0x67},
  {0xe0, 0x00},
  {0xdd, 0x7f},
  {0x05, 0x00},
  {0xff, 0x00},
  {0xe0, 0x04},
  {0xc0, 0xc8},
  {0xc1, 0x96},
  {0x86, 0x3d},
  {0x50, 0x92},
  {0x51, 0x90},
  {0x52, 0x2c},
  {0x53, 0x00},
  {0x54, 0x00},
  {0x55, 0x88},
  {0x57, 0x00},
  {0x5a, 0x50},
  {0x5b, 0x3c},
  {0x5c, 0x00},
  {0xd3, 0x04},
  {0xe0, 0x00},
  {0xFF, 0x00},
  {0x05, 0x00},
  {0xDA, 0x08},
  {0xda, 0x09},
  {0x98, 0x00},
  {0x99, 0x00},
  {0x00, 0x00},
  {0xff, 0x00},
  {0xe0, 0x04},
  {0xc0, 0xc8},
  {0xc1, 0x96},
  {0x86, 0x3d},
  {0x50, 0x89},
  {0x51, 0x90},
  {0x52, 0x2c},
  {0x53, 0x00},
  {0x54, 0x00},
  {0x55, 0x88},
  {0x57, 0x00},
  {0x5a, 0xA0},
  {0x5b, 0x78},
  {0x5c, 0x00},
  {0xd3, 0x02},
  {0xe0, 0x00},
};

/* Initialization sequence for QVGA resolution (320x240) */
const unsigned char OV2640_QVGA[][2]=
{
  {0xff, 0x00},
  {0x2c, 0xff},
  {0x2e, 0xdf},
  {0xff, 0x01},
  {0x3c, 0x32},
  {0x11, 0x00},
  {0x09, 0x02},
  {0x04, 0xA8},
  {0x13, 0xe5},
  {0x14, 0x48},
  {0x2c, 0x0c},
  {0x33, 0x78},
  {0x3a, 0x33},
  {0x3b, 0xfB},
  {0x3e, 0x00},
  {0x43, 0x11},
  {0x16, 0x10},
  {0x4a, 0x81},
  {0x21, 0x99},
  {0x24, 0x40},
  {0x25, 0x38},
  {0x26, 0x82},
  {0x5c, 0x00},
  {0x63, 0x00},
  {0x46, 0x3f},
  {0x0c, 0x3c},
  {0x61, 0x70},
  {0x62, 0x80},
  {0x7c, 0x05},
  {0x20, 0x80},
  {0x28, 0x30},
  {0x6c, 0x00},
  {0x6d, 0x80},
  {0x6e, 0x00},
  {0x70, 0x02},
  {0x71, 0x94},
  {0x73, 0xc1},
  {0x3d, 0x34},
  {0x5a, 0x57},
  {0x12, 0x00},
  {0x11, 0x00},
  {0x17, 0x11},
  {0x18, 0x75},
  {0x19, 0x01},
  {0x1a, 0x97},
  {0x32, 0x36},
  {0x03, 0x0f},
  {0x37, 0x40},
  {0x4f, 0xbb},
  {0x50, 0x9c},
  {0x5a, 0x57},
  {0x6d, 0x80},
  {0x6d, 0x38},
  {0x39, 0x02},
  {0x35, 0x88},
  {0x22, 0x0a},
  {0x37, 0x40},
  {0x23, 0x00},
  {0x34, 0xa0},
  {0x36, 0x1a},
  {0x06, 0x02},
  {0x07, 0xc0},
  {0x0d, 0xb7},
  {0x0e, 0x01},
  {0x4c, 0x00},
  {0xff, 0x00},
  {0xe5, 0x7f},
  {0xf9, 0xc0},
  {0x41, 0x24},
  {0xe0, 0x14},
  {0x76, 0xff},
  {0x33, 0xa0},
  {0x42, 0x20},
  {0x43, 0x18},
  {0x4c, 0x00},
  {0x87, 0xd0},
  {0x88, 0x3f},
  {0xd7, 0x03},
  {0xd9, 0x10},
  {0xd3, 0x82},
  {0xc8, 0x08},
  {0xc9, 0x80},
  {0x7d, 0x00},
  {0x7c, 0x03},
  {0x7d, 0x48},
  {0x7c, 0x08},
  {0x7d, 0x20},
  {0x7d, 0x10},
  {0x7d, 0x0e},
  {0x90, 0x00},
  {0x91, 0x0e},
  {0x91, 0x1a},
  {0x91, 0x31},
  {0x91, 0x5a},
  {0x91, 0x69},
  {0x91, 0x75},
  {0x91, 0x7e},
  {0x91, 0x88},
  {0x91, 0x8f},
  {0x91, 0x96},
  {0x91, 0xa3},
  {0x91, 0xaf},
  {0x91, 0xc4},
  {0x91, 0xd7},
  {0x91, 0xe8},
  {0x91, 0x20},
  {0x92, 0x00},
  {0x93, 0x06},
  {0x93, 0xe3},
  {0x93, 0x02},
  {0x93, 0x02},
  {0x93, 0x00},
  {0x93, 0x04},
  {0x93, 0x00},
  {0x93, 0x03},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x96, 0x00},
  {0x97, 0x08},
  {0x97, 0x19},
  {0x97, 0x02},
  {0x97, 0x0c},
  {0x97, 0x24},
  {0x97, 0x30},
  {0x97, 0x28},
  {0x97, 0x26},
  {0x97, 0x02},
  {0x97, 0x98},
  {0x97, 0x80},
  {0x97, 0x00},
  {0x97, 0x00},
  {0xc3, 0xef},
  {0xff, 0x00},
  {0xba, 0xdc},
  {0xbb, 0x08},
  {0xb6, 0x24},
  {0xb8, 0x33},
  {0xb7, 0x20},
  {0xb9, 0x30},
  {0xb3, 0xb4},
  {0xb4, 0xca},
  {0xb5, 0x43},
  {0xb0, 0x5c},
  {0xb1, 0x4f},
  {0xb2, 0x06},
  {0xc7, 0x00},
  {0xc6, 0x51},
  {0xc5, 0x11},
  {0xc4, 0x9c},
  {0xbf, 0x00},
  {0xbc, 0x64},
  {0xa6, 0x00},
  {0xa7, 0x1e},
  {0xa7, 0x6b},
  {0xa7, 0x47},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x2e},
  {0xa7, 0x85},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x1b},
  {0xa7, 0x74},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xc0, 0xc8},
  {0xc1, 0x96},
  {0x8c, 0x00},
  {0x86, 0x3d},
  {0x50, 0x92},
  {0x51, 0x90},
  {0x52, 0x2c},
  {0x53, 0x00},
  {0x54, 0x00},
  {0x55, 0x88},
  {0x5a, 0x50},
  {0x5b, 0x3c},
  {0x5c, 0x00},
  {0xd3, 0x04},
  {0x7f, 0x00},
  {0xda, 0x00},
  {0xe5, 0x1f},
  {0xe1, 0x67},
  {0xe0, 0x00},
  {0xdd, 0x7f},
  {0x05, 0x00},
  {0xff, 0x00},
  {0xe0, 0x04},
  {0xc0, 0xc8},
  {0xc1, 0x96},
  {0x86, 0x3d},
  {0x50, 0x92},
  {0x51, 0x90},
  {0x52, 0x2c},
  {0x53, 0x00},
  {0x54, 0x00},
  {0x55, 0x88},
  {0x57, 0x00},
  {0x5a, 0x50},
  {0x5b, 0x3C},
  {0x5c, 0x00},
  {0xd3, 0x08},
  {0xe0, 0x00},
  {0xFF, 0x00},
  {0x05, 0x00},
  {0xDA, 0x08},
  {0xda, 0x09},
  {0x98, 0x00},
  {0x99, 0x00},
  {0x00, 0x00},
};

/* Initialization sequence for QQVGA resolution (160x120) */
const char OV2640_QQVGA[][2]=
{
  {0xff, 0x00},
  {0x2c, 0xff},
  {0x2e, 0xdf},
  {0xff, 0x01},
  {0x3c, 0x32},
  {0x11, 0x00},
  {0x09, 0x02},
  {0x04, 0xA8},
  {0x13, 0xe5},
  {0x14, 0x48},
  {0x2c, 0x0c},
  {0x33, 0x78},
  {0x3a, 0x33},
  {0x3b, 0xfB},
  {0x3e, 0x00},
  {0x43, 0x11},
  {0x16, 0x10},
  {0x4a, 0x81},
  {0x21, 0x99},
  {0x24, 0x40},
  {0x25, 0x38},
  {0x26, 0x82},
  {0x5c, 0x00},
  {0x63, 0x00},
  {0x46, 0x3f},
  {0x0c, 0x3c},
  {0x61, 0x70},
  {0x62, 0x80},
  {0x7c, 0x05},
  {0x20, 0x80},
  {0x28, 0x30},
  {0x6c, 0x00},
  {0x6d, 0x80},
  {0x6e, 0x00},
  {0x70, 0x02},
  {0x71, 0x94},
  {0x73, 0xc1},
  {0x3d, 0x34},
  {0x5a, 0x57},
  {0x12, 0x00},
  {0x11, 0x00},
  {0x17, 0x11},
  {0x18, 0x75},
  {0x19, 0x01},
  {0x1a, 0x97},
  {0x32, 0x36},
  {0x03, 0x0f},
  {0x37, 0x40},
  {0x4f, 0xbb},
  {0x50, 0x9c},
  {0x5a, 0x57},
  {0x6d, 0x80},
  {0x6d, 0x38},
  {0x39, 0x02},
  {0x35, 0x88},
  {0x22, 0x0a},
  {0x37, 0x40},
  {0x23, 0x00},
  {0x34, 0xa0},
  {0x36, 0x1a},
  {0x06, 0x02},
  {0x07, 0xc0},
  {0x0d, 0xb7},
  {0x0e, 0x01},
  {0x4c, 0x00},
  {0xff, 0x00},
  {0xe5, 0x7f},
  {0xf9, 0xc0},
  {0x41, 0x24},
  {0xe0, 0x14},
  {0x76, 0xff},
  {0x33, 0xa0},
  {0x42, 0x20},
  {0x43, 0x18},
  {0x4c, 0x00},
  {0x87, 0xd0},
  {0x88, 0x3f},
  {0xd7, 0x03},
  {0xd9, 0x10},
  {0xd3, 0x82},
  {0xc8, 0x08},
  {0xc9, 0x80},
  {0x7d, 0x00},
  {0x7c, 0x03},
  {0x7d, 0x48},
  {0x7c, 0x08},
  {0x7d, 0x20},
  {0x7d, 0x10},
  {0x7d, 0x0e},
  {0x90, 0x00},
  {0x91, 0x0e},
  {0x91, 0x1a},
  {0x91, 0x31},
  {0x91, 0x5a},
  {0x91, 0x69},
  {0x91, 0x75},
  {0x91, 0x7e},
  {0x91, 0x88},
  {0x91, 0x8f},
  {0x91, 0x96},
  {0x91, 0xa3},
  {0x91, 0xaf},
  {0x91, 0xc4},
  {0x91, 0xd7},
  {0x91, 0xe8},
  {0x91, 0x20},
  {0x92, 0x00},
  {0x93, 0x06},
  {0x93, 0xe3},
  {0x93, 0x02},
  {0x93, 0x02},
  {0x93, 0x00},
  {0x93, 0x04},
  {0x93, 0x00},
  {0x93, 0x03},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x96, 0x00},
  {0x97, 0x08},
  {0x97, 0x19},
  {0x97, 0x02},
  {0x97, 0x0c},
  {0x97, 0x24},
  {0x97, 0x30},
  {0x97, 0x28},
  {0x97, 0x26},
  {0x97, 0x02},
  {0x97, 0x98},
  {0x97, 0x80},
  {0x97, 0x00},
  {0x97, 0x00},
  {0xc3, 0xef},
  {0xff, 0x00},
  {0xba, 0xdc},
  {0xbb, 0x08},
  {0xb6, 0x24},
  {0xb8, 0x33},
  {0xb7, 0x20},
  {0xb9, 0x30},
  {0xb3, 0xb4},
  {0xb4, 0xca},
  {0xb5, 0x43},
  {0xb0, 0x5c},
  {0xb1, 0x4f},
  {0xb2, 0x06},
  {0xc7, 0x00},
  {0xc6, 0x51},
  {0xc5, 0x11},
  {0xc4, 0x9c},
  {0xbf, 0x00},
  {0xbc, 0x64},
  {0xa6, 0x00},
  {0xa7, 0x1e},
  {0xa7, 0x6b},
  {0xa7, 0x47},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x2e},
  {0xa7, 0x85},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x1b},
  {0xa7, 0x74},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xc0, 0xc8},
  {0xc1, 0x96},
  {0x8c, 0x00},
  {0x86, 0x3d},
  {0x50, 0x92},
  {0x51, 0x90},
  {0x52, 0x2c},
  {0x53, 0x00},
  {0x54, 0x00},
  {0x55, 0x88},
  {0x5a, 0x50},
  {0x5b, 0x3c},
  {0x5c, 0x00},
  {0xd3, 0x04},
  {0x7f, 0x00},
  {0xda, 0x00},
  {0xe5, 0x1f},
  {0xe1, 0x67},
  {0xe0, 0x00},
  {0xdd, 0x7f},
  {0x05, 0x00},
  {0xff, 0x00},
  {0xe0, 0x04},
  {0xc0, 0xc8},
  {0xc1, 0x96},
  {0x86, 0x3d},
  {0x50, 0x92},
  {0x51, 0x90},
  {0x52, 0x2c},
  {0x53, 0x00},
  {0x54, 0x00},
  {0x55, 0x88},
  {0x57, 0x00},
  {0x5a, 0x28}, 
  {0x5b, 0x1E}, 
  {0x5c, 0x00},
  {0xd3, 0x08},
  {0xe0, 0x00},
  {0xFF, 0x00},
  {0x05, 0x00},
  {0xDA, 0x08},
  {0xda, 0x09},
  {0x98, 0x00},
  {0x99, 0x00},
  {0x00, 0x00},
};

/**
  * @}
  */
  
/** @defgroup OV2640_Private_Functions
  * @{
  */ 
  
/**
  * @brief  Initializes the OV2640 CAMERA component.
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  resolution: Camera resolution
  * @retval None
  */
void ov2640_Init(uint16_t DeviceAddr, uint32_t resolution)
{
  uint32_t index;
  
  /* Initialize I2C */
  CAMERA_IO_Init();    
  
  /* Prepare the camera to be configured */
  CAMERA_IO_Write(DeviceAddr, OV2640_DSP_RA_DLMT, 0x01);
  CAMERA_IO_Write(DeviceAddr, OV2640_SENSOR_COM7, 0x80);
  CAMERA_Delay(200);
  
  /* Initialize OV2640 */
  switch (resolution)
  {
  case CAMERA_R160x120:
    {
      for(index=0; index<(sizeof(OV2640_QQVGA)/2); index++)
      {
        CAMERA_IO_Write(DeviceAddr, OV2640_QQVGA[index][0], OV2640_QQVGA[index][1]);
        CAMERA_Delay(1);
      } 
      break;
    }    
  case CAMERA_R320x240:
    {
      for(index=0; index<(sizeof(OV2640_QVGA)/2); index++)
      {
        CAMERA_IO_Write(DeviceAddr, OV2640_QVGA[index][0], OV2640_QVGA[index][1]);
        CAMERA_Delay(1);
      } 
      break;
    }
  case CAMERA_R480x272:
    {
      for(index=0; index<(sizeof(OV2640_480x272)/2); index++)
      {
        CAMERA_IO_Write(DeviceAddr, OV2640_480x272[index][0], OV2640_480x272[index][1]);
        CAMERA_Delay(2);
      }
      break;
    }
  case CAMERA_R640x480:
    {
      for(index=0; index<(sizeof(OV2640_VGA)/2); index++)
      {
        CAMERA_IO_Write(DeviceAddr, OV2640_VGA[index][0], OV2640_VGA[index][1]);
        CAMERA_Delay(2);
      }
      break;
    }    
  default:
    {
      break;
    }
  }
}

/**
  * @brief  Configures the OV2640 camera feature.
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  feature: Camera feature to be configured
  * @param  value: Value to be configured
  * @param  brightness_value: Brightness value to be configured
  * @retval None
  */
void ov2640_Config(uint16_t DeviceAddr, uint32_t feature, uint32_t value, uint32_t brightness_value)
{
  uint8_t value1, value2;
  uint32_t value_tmp;
  uint32_t br_value;
  
  /* Convert the input value into ov2640 parameters */
  value_tmp = ov2640_ConvertValue(feature, value); 
  br_value = ov2640_ConvertValue(CAMERA_CONTRAST_BRIGHTNESS, brightness_value); 
    
  switch(feature)
  {
  case CAMERA_BLACK_WHITE:
    {  
      CAMERA_IO_Write(DeviceAddr, 0xff, 0x00);
      CAMERA_IO_Write(DeviceAddr, 0x7c, 0x00);
      CAMERA_IO_Write(DeviceAddr, 0x7d, value_tmp);
      CAMERA_IO_Write(DeviceAddr, 0x7c, 0x05);
      CAMERA_IO_Write(DeviceAddr, 0x7d, 0x80);
      CAMERA_IO_Write(DeviceAddr, 0x7d, 0x80);
      break;
    }
  case CAMERA_CONTRAST_BRIGHTNESS:
    {
      value1 = (uint8_t)(value_tmp);
      value2 = (uint8_t)(value_tmp >> 8);
      CAMERA_IO_Write(DeviceAddr, 0xff, 0x00);     
      CAMERA_IO_Write(DeviceAddr, 0x7c, 0x00);
      CAMERA_IO_Write(DeviceAddr, 0x7d, 0x04);
      CAMERA_IO_Write(DeviceAddr, 0x7c, 0x07);
      CAMERA_IO_Write(DeviceAddr, 0x7d, br_value);
      CAMERA_IO_Write(DeviceAddr, 0x7d, value1);
      CAMERA_IO_Write(DeviceAddr, 0x7d, value2);
      CAMERA_IO_Write(DeviceAddr, 0x7d, 0x06);
      break;
    }
  case CAMERA_COLOR_EFFECT:
    {     
      value1 = (uint8_t)(value_tmp);
      value2 = (uint8_t)(value_tmp >> 8);
      CAMERA_IO_Write(DeviceAddr, 0xff, 0x00);
      CAMERA_IO_Write(DeviceAddr, 0x7c, 0x00);
      CAMERA_IO_Write(DeviceAddr, 0x7d, 0x18);
      CAMERA_IO_Write(DeviceAddr, 0x7c, 0x05);
      CAMERA_IO_Write(DeviceAddr, 0x7d, value1);
      CAMERA_IO_Write(DeviceAddr, 0x7d, value2);
      break;
    }     
  default:
    {
      break;
    }
  }
}

/**
  * @brief  Read the OV2640 Camera identity.
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval the OV2640 ID
  */
uint16_t ov2640_ReadID(uint16_t DeviceAddr)
{
  /* Initialize I2C */
  CAMERA_IO_Init();
  
  /* Prepare the sensor to read the Camera ID */
  CAMERA_IO_Write(DeviceAddr, OV2640_DSP_RA_DLMT, 0x01);
  
  /* Get the camera ID */
  return (CAMERA_IO_Read(DeviceAddr, OV2640_SENSOR_PIDH));
}

/******************************************************************************
                            Static Functions
*******************************************************************************/
/**
  * @brief  Convert input values into ov2640 parameters.
  * @param  feature: Camera feature to be configured
  * @param  value: Value to be configured
  * @retval The converted value
  */
static uint32_t ov2640_ConvertValue(uint32_t feature, uint32_t value)
{
  uint32_t ret = 0;
  
  switch(feature)
  {
  case CAMERA_BLACK_WHITE:
    {
      switch(value)
      {
      case CAMERA_BLACK_WHITE_BW:
        {
          ret =  OV2640_BLACK_WHITE_BW;
          break;
        }
      case CAMERA_BLACK_WHITE_NEGATIVE:
        {
          ret =  OV2640_BLACK_WHITE_NEGATIVE;
          break;
        }
      case CAMERA_BLACK_WHITE_BW_NEGATIVE:
        {
          ret =  OV2640_BLACK_WHITE_BW_NEGATIVE;
          break;
        }
      case CAMERA_BLACK_WHITE_NORMAL:
        {
          ret =  OV2640_BLACK_WHITE_NORMAL;
          break;
        }
      default:
        {
          ret =  OV2640_BLACK_WHITE_NORMAL;
          break;
        }
      }
      break;
    }
  case CAMERA_CONTRAST_BRIGHTNESS:
    {
      switch(value)
      {
      case CAMERA_BRIGHTNESS_LEVEL0:
        {
          ret =  OV2640_BRIGHTNESS_LEVEL0;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL1:
        {
          ret =  OV2640_BRIGHTNESS_LEVEL1;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL2:
        {
          ret =  OV2640_BRIGHTNESS_LEVEL2;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL3:
        {
          ret =  OV2640_BRIGHTNESS_LEVEL3;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL4:
        {
          ret =  OV2640_BRIGHTNESS_LEVEL4;
          break;
        }        
      case CAMERA_CONTRAST_LEVEL0:
        {
          ret =  OV2640_CONTRAST_LEVEL0;
          break;
        }
      case CAMERA_CONTRAST_LEVEL1:
        {
          ret =  OV2640_CONTRAST_LEVEL1;
          break;
        }
      case CAMERA_CONTRAST_LEVEL2:
        {
          ret =  OV2640_CONTRAST_LEVEL2;
          break;
        }
      case CAMERA_CONTRAST_LEVEL3:
        {
          ret =  OV2640_CONTRAST_LEVEL3;
          break;
        }
      case CAMERA_CONTRAST_LEVEL4:
        {
          ret =  OV2640_CONTRAST_LEVEL4;
          break;
        }
      default:
        {
          ret =  OV2640_CONTRAST_LEVEL0;
          break;
        }
      }
      break;
    }
  case CAMERA_COLOR_EFFECT:
    {
      switch(value)
      {
      case CAMERA_COLOR_EFFECT_ANTIQUE:
        {
          ret =  OV2640_COLOR_EFFECT_ANTIQUE;
          break;
        }
      case CAMERA_COLOR_EFFECT_BLUE:
        {
          ret =  OV2640_COLOR_EFFECT_BLUE;
          break;
        }
      case CAMERA_COLOR_EFFECT_GREEN:
        {
          ret =  OV2640_COLOR_EFFECT_GREEN;
          break;
        }
      case CAMERA_COLOR_EFFECT_RED:
        {
          ret =  OV2640_COLOR_EFFECT_RED;
          break;
        }
      default:
        {
          ret =  OV2640_COLOR_EFFECT_RED;
          break;
        }
      }
      break;
    default:
      {
        ret = 0;
        break;
      }    
    }
  }
  
  return ret;
}
         
/**
  * @}
  */ 
  
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/**
  * @}
  */  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
