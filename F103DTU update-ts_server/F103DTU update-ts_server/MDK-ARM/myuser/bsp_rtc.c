#include "bsp_rtc.h"
#include "wdz_rtc_time.h"

/* ���жϱ�־���������ж�ʱ��1����ʱ�䱻ˢ��֮����0 */
__IO uint32_t TimeDisplay = 1;
extern u8 rtcbuffer[];



/*
 * ��������NVIC_Configuration
 * ����  ������RTC���жϵ����ж����ȼ�Ϊ1�������ȼ�Ϊ0
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 ����ǰû������жϹ��ܣ�
 */
void RTC_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

    /* Enable the RTC Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/*
 * ��������RTC_CheckAndConfig
 * ����  ����鲢����RTC
 * ����  �����ڶ�ȡRTCʱ��Ľṹ��ָ��
 * ���  ����
 * ����  ���ⲿ����
 */
void RTC_CheckAndConfig( )
{
    //***********����ʹ��

    //RTC_Configuration();
    //	Time_Adjust(tm);  //���뵱ǰʱ�䣬�޸ļ���RTC����ֵ
    //	BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    //***************����ʹ��

    /*������ʱ��鱸�ݼĴ���BKP_DR1��������ݲ���0xA5A5,
    ������������ʱ�䲢ѯ���û�����ʱ��*/
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        //������ڳ����������޸�RTC�ļ���ֵ������Ҫ�����������д������ǧ��Ҫ��ס����������� 2014.9.20 WDZ
        /* Enable PWR and BKP clocks */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
        /* Allow access to BKP Domain */
        PWR_BackupAccessCmd(ENABLE);


        /* RTC Configuration */
        RTC_Configuration();
        /* Adjust time by users typed on the hyperterminal */
        RTC_WaitForLastTask();
        my_EEPROM_TO_RTC(rtcbuffer,0); //��ȡEEPROM�е�ʱ�꣬�޸ļ���RTC����ֵ******************
        RTC_WaitForLastTask();

        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    }
    else
    {
        //������ڳ����������޸�RTC�ļ���ֵ������Ҫ�����������д������ǧ��Ҫ��ס����������� 2014.9.20 WDZ
        /* Enable PWR and BKP clocks */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
        /* Allow access to BKP Domain */
        PWR_BackupAccessCmd(ENABLE);

        /*��������������ʱ��*/
        /*����Ƿ��������*/
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
        {

        }
        /*����Ƿ�Reset��λ*/
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
        {

        }

        //printf("\r\n No need to configure RTC....");
        /* RTC Configuration */
        RTC_Configuration();

        /*�ȴ��Ĵ���ͬ��*/
        RTC_WaitForSynchro();

        /*����RTC���ж�*/
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        //RTC_ITConfig(RTC_IT_SEC, DISABLE);

        /*�ȴ��ϴ�RTC�Ĵ���д�������*/
        RTC_WaitForLastTask();
        /*��ȡ��ǰRTC��ֵд�뵽EEPROM��  ����������RTCû�м������������¿�ʼ������RTCʱ������*/
        //my_RTC_TO_EEPROM(rtcbuffer,0);
        //��ȡEEPROM�е�ʱ�꣬�޸ļ���RTC����ֵ******************
        my_EEPROM_TO_RTC(rtcbuffer,0);
        RTC_WaitForLastTask();


    }
    /* Clear reset flags */
    RCC_ClearFlag();

}




/*
 * ��������RTC_Configuration
 * ����  ������RTC
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void RTC_Configuration(void)
{
    int ii=0;
    int my_rcc_status=0;
    int my_status=0;
    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);

    /* Reset Backup Domain */
    BKP_DeInit();

    /* Enable LSE  ����ʹ���ⲿ����ʱ��32768HZ �ɰ���1���ε��ⲿ����ʱ�������⣬�����ã�ֻ�����ڲ�����ʱ��LSI*/
    RCC_LSEConfig(RCC_LSE_ON);
    /* Wait till LSE is ready */
    my_rcc_status=RCC_GetFlagStatus(RCC_FLAG_LSERDY);
    while (ii<20 && my_rcc_status==RESET)
    {
        Delay_us(50);
        my_rcc_status=RCC_GetFlagStatus(RCC_FLAG_LSERDY);
        ii++;
    }
    if(ii<20)  //Ӳ�������ɹ�
    {
        my_status=0;
    }
    else if(ii>=20) //Ӳ������ʧ��
        my_status=1;


    if(my_status==0)
    {
        /* Select LSE as RTC Clock Source */
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
        //USART_printf(&huart3,"LSE�ⲿ��Ƶʱ��\r\n");  //@@����ʹ��
    }

    else if(my_status==1)
    {
        RCC_LSEConfig(RCC_LSE_OFF);  //�ر��ⲿ����ʱ��
        /* Enable LSI ����ʹ���ڲ�����ʱ��*/
        RCC_LSICmd(ENABLE);
        /* Wait till LSI is ready */
        while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)	{}
        /* Select LSI as RTC Clock Source */
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
        //USART_printf(&huart3,"LSI�ڲ���Ƶʱ��\r\n");  //@@����ʹ��
    }

    //**********************************************************************
    /* Enable RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC registers synchronization
     * ��ΪRTCʱ���ǵ��ٵģ��ڻ�ʱ���Ǹ��ٵģ�����Ҫͬ��
     */
    RTC_WaitForSynchro();

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    //RTC_ITConfig(RTC_IT_SEC, DISABLE);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Set RTC prescaler: set RTC period to 1sec */
    if(my_status==0)  //���RTCʱ�ӹ��������⣬ԭ�����ⲿʱ�ӣ������ڲ�ʱ����ģ����ˣ�ʱ������
        RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) = 1HZ */
    else
        RTC_SetPrescaler(40000-1); /* RTC period = RTCCLK/RTC_PR = (40KHz)/(32767+1) = 1HZ */

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}




/*
 * ��������Time_Adjust
 * ����  ��ʱ�����
 * ����  �����ڶ�ȡRTCʱ��Ľṹ��ָ��
 * ���  ����
 * ����  ���ⲿ����
 */
void Time_Adjust(struct rtc_time *tm)
{
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Get time entred by the user on the hyperterminal */
    Time_Regulate(tm);  //���뵱ǰ��ʱ�䣬�꣬�£��գ�Сʱ�����ӣ��룬�ŵ��ṹ����

    /* Get wday */
    // GregorianDay(tm);   //���ýṹ������ݼ������ǰ�����ڼ���

    /* �޸ĵ�ǰRTC�����Ĵ������� */
    RTC_SetCounter(mktimev(tm));  //  �޸ļ���ֵ���������Ҫ�������1970������ļ�����ֵ��mktimev()�������м���ֵ�ļ���

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}

/*
 * ��������Time_Regulate
 * ����  �������û��ڳ����ն��������ʱ��ֵ������ֵ������
 *         RTC �����Ĵ����С�
 * ����  �����ڶ�ȡRTCʱ��Ľṹ��ָ��
 * ���  ���û��ڳ����ն��������ʱ��ֵ����λΪ s
 * ����  ���ڲ�����
 */
extern int T_year,T_month,T_day,T_hh,T_mm,T_ss;
void Time_Regulate(struct rtc_time *tm)
{
    tm->tm_year=T_year;
    tm->tm_mon=T_month;
    tm->tm_mday=T_day;
    tm->tm_hour=T_hh;
    tm->tm_min=T_mm;
    tm->tm_sec=T_ss;

}



/*
 * ��������Time_Show
 * ����  ���ڳ����ն�����ʾ��ǰʱ��ֵ
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void Time_Show(void)
{   struct rtc_time tm;
    uint32_t TimeVar=0;

    if (TimeDisplay == 1)
    {
        /* Display current time */
        TimeVar=RTC_GetCounter();
        Time_Display( TimeVar,&tm); 		 //����RTC������õ�ǰ�ļ���ֵRTC_GetCounter()
        TimeDisplay = 1;
    }

}
/*
 * ��������Time_Display
 * ����  ����ʾ��ǰʱ��ֵ
 * ����  ��-TimeVar RTC����ֵ����λΪ s
 * ���  ����
 * ����  ���ڲ�����
 */
void Time_Display(uint32_t TimeVar,struct rtc_time *tm)
{
//	   static uint32_t FirstDisplay = 1;
    uint32_t BJ_TimeVar;
//	   uint8_t str[15]; // �ַ����ݴ�

    /*  �ѱ�׼ʱ��ת��Ϊ����ʱ��*/
    //BJ_TimeVar =TimeVar + 8*60*60;

    BJ_TimeVar =TimeVar;  //����ʱ�����⣬����Ϊ��ǰ�� ��ʱ����������ʱ�䣩

    to_tm(BJ_TimeVar, tm);/*�Ѷ�ʱ����ֵת��Ϊ����ʱ��,����tm��*/


    /* ���ʱ���������ʱ�䣬���ô���1������� */
    // printf(" UNIX time = %d  now time: %d-%d-%d(week-%d)  %0.2d:%0.2d:%0.2d \r\n",
    //TimeVar,tm->tm_year,tm->tm_mon,tm->tm_mday,tm->tm_wday,tm->tm_hour,tm->tm_min,tm->tm_sec);


    //���ʱ���������ʱ��
    USART_printf(&huart3,"\r\n TIME-%d=%d-%d-%d  %d:%d:%d",TimeVar,tm->tm_year,tm->tm_mon,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);



}




/************************END OF FILE***************************************/