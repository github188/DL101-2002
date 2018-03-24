#include "gpio.h"
#include "my_usart.h"
//#include "my_cc_TX_RX.h"
#include "my_OS.h"

//extern uint32_t ADC_ConvertedValue[N][M];//���ڱ���ɼ���ֵ,M��ͨ��,N��
uint16_t my_pb1_count=0;
uint16_t my_pb0_count=0;
uint16_t my_pc13_count=0;
extern uint8_t Cmd_CC1101_RX[];
extern uint8_t my_CC1101_chip_address;  //оƬ��ַ��Ĭ��Ϊ0x05
extern uint8_t MY_TX_RX_STEP;   //����Ĳ���
extern EventGroupHandle_t xCreatedEventGroup ;

uint8_t my_get_count=0; //��õ��ַ�����
void HAL_GPIO_EXTI_Callback ( uint16_t GPIO_Pin)
{

    uint8_t temp_status=0;
    //--------   CC1101�ж� ������������--
    BaseType_t xResult;
    BaseType_t xHigherPriorityTaskWoken=pdFAIL;

    if(GPIO_Pin==PIN_CC_IRQ)
    {

        uint32_t my_temp32=0;
        while (CC_IRQ_READ() == 1)
        {
            my_temp32++;
            if(my_temp32>=0x003FFFFF)
            {
                printf("\n*****EXIT CC_IRQ_READ() == 1 ******\n");
                CC1101ClrRXBuff( );
                my_fun_CC1101_init_reum();
                return;
            }

        }



        // printf("before rx_count=%d\n",	my_get_count);//����ʹ�ã����յ����ַ�����
        temp_status=CC1101GetRXCnt();
        my_get_count=temp_status;
        if(temp_status>0)
        {
            //����״̬��ʶ0X08����״̬��ʶ����
            xResult=	xEventGroupSetBitsFromISR(xCreatedEventGroup, 0X08,&xHigherPriorityTaskWoken);
            if(xResult!=pdFAIL)
            {
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
            my_pb0_count++;

        }
        else
        {
            my_pb0_count++;

        }
        //printf("CC_IRQ=%d -- rx_count=%d\r\n",my_pb0_count,temp_status);//��ʾ���յ���������


    }


    if(GPIO_Pin==GPIO_PIN_1)
    {
        my_pb1_count++;
        printf("PC7 INT=%d-\n",my_pb1_count);

    }


}