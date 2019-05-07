
/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "ff_gen_drv.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Block Size in Bytes */
#define BLOCK_SIZE                512

/* Private variables ---------------------------------------------------------*/
/* Disk status */
static volatile DSTATUS Stat = STA_NOINIT;

/* Private function prototypes -----------------------------------------------*/
DSTATUS SD_initialize (void);
DSTATUS SD_status (void);
DRESULT SD_read (BYTE*, DWORD, BYTE);
#if _USE_WRITE == 1
  DRESULT SD_write (const BYTE*, DWORD, BYTE);
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1
  DRESULT SD_ioctl (BYTE, void*);
#endif  /* _USE_IOCTL == 1 */
  
Diskio_drvTypeDef  SD_Driver =
{
  SD_initialize,
  SD_status,
  SD_read, 
#if  _USE_WRITE == 1
  SD_write,
#endif /* _USE_WRITE == 1 */
  
#if  _USE_IOCTL == 1
  SD_ioctl,
#endif /* _USE_IOCTL == 1 */
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes a Drive
  * @param  None
  * @retval DSTATUS: Operation status
  */
DSTATUS SD_initialize(void)
{
  Stat = STA_NOINIT;
  
  /* Configure the uSD device */
  if(BSP_SD_Init() == MSD_OK)
  {
    Stat &= ~STA_NOINIT;
  }

  return Stat;
}

/**
  * @brief  Gets Disk Status
  * @param  None
  * @retval DSTATUS: Operation status
  */
DSTATUS SD_status(void)
{
  Stat = STA_NOINIT;

  if(BSP_SD_GetStatus() == MSD_OK)
  {
    Stat &= ~STA_NOINIT;
  }
  
  return Stat;
}

/**
  * @brief  Reads Sector(s)
  * @param  *buff: Data buffer to store read data
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to read (1..128)
  * @retval DRESULT: Operation result
  */
DRESULT SD_read(BYTE *buff, DWORD sector, BYTE count)
{
  DRESULT res = RES_OK;
  
  if(BSP_SD_ReadBlocks((uint32_t*)buff, 
                       (uint64_t) (sector * BLOCK_SIZE), 
                       BLOCK_SIZE, 
                       count) != MSD_OK)
  {
    res = RES_ERROR;
  }
  
  return res;
}

/**
  * @brief  Writes Sector(s)
  * @param  *buff: Data to be written
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to write (1..128)
  * @retval DRESULT: Operation result
  */
#if _USE_WRITE == 1
DRESULT SD_write(const BYTE *buff, DWORD sector, BYTE count)
{
  DRESULT res = RES_OK;
  
  if(BSP_SD_WriteBlocks((uint32_t*)buff, 
                        (uint64_t)(sector * BLOCK_SIZE), 
                        BLOCK_SIZE, count) != MSD_OK)
  {
    res = RES_ERROR;
  }
  
  return res;
}
#endif /* _USE_WRITE == 1 */

/**
  * @brief  I/O control operation
  * @param  cmd: Control code
  * @param  *buff: Buffer to send/receive control data
  * @retval DRESULT: Operation result
  */
#if _USE_IOCTL == 1
DRESULT SD_ioctl(BYTE cmd, void *buff)
{
  DRESULT res = RES_ERROR;
  SD_CardInfo CardInfo;
  
  if (Stat & STA_NOINIT) return RES_NOTRDY;
  
  switch (cmd)
  {
  /* Make sure that no pending write process */
  case CTRL_SYNC :
    res = RES_OK;
    break;
  
  /* Get number of sectors on the disk (DWORD) */
  case GET_SECTOR_COUNT :
    BSP_SD_GetCardInfo(&CardInfo);
    *(DWORD*)buff = CardInfo.CardCapacity / BLOCK_SIZE;
    res = RES_OK;
    break;
  
  /* Get R/W sector size (WORD) */
  case GET_SECTOR_SIZE :
    *(WORD*)buff = BLOCK_SIZE;
    res = RES_OK;
    break;
  
  /* Get erase block size in unit of sector (DWORD) */
  case GET_BLOCK_SIZE :
    *(DWORD*)buff = BLOCK_SIZE;
    break;
  
  default:
    res = RES_PARERR;
  }
  
  return res;
}
#endif /* _USE_IOCTL == 1 */
  

