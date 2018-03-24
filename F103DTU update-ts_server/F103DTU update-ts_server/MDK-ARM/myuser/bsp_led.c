

#include "bsp_led.h"

/**
 * @brief  ��ʼ������LED��IO
 * @param  ��
 * @retval ��
 */

void my_speaker_long_voice(uint16_t mytime)
{
    //SPEAKER_OFF;
    SPEAKER_ON;
    HAL_Delay(mytime*10);
    SPEAKER_OFF;


}

void my_speaker_short_cycle_voice(uint8_t number,uint16_t shorttime)
{
    uint8_t k=0;
    for(k=0; k<number; k++)
    {
        SPEAKER_ON;
        HAL_Delay(shorttime*10);
        SPEAKER_OFF;
        HAL_Delay(shorttime*10);
    }

}