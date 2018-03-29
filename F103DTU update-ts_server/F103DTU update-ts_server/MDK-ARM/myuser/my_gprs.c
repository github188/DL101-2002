#include "my_gprs.h"
#include "my_cc1101.h"
#include "my_globle_extern.h"

/*
GPRS������������  uint8_t my_at_senddata(uint8_t *string);
GPRS����������������
uint8_t my_usart_101frame(uint8_t usart_port);
void my_process_resive_101usart1(void); //M35ʹ��
*/

uint8_t  WDZ_GPRS_101FCB = 0X00;


extern  uint32_t TimingDelay;
extern uint16_t DTU_ADDRESS;

extern	uint16_t USART1_address_first;
extern	uint16_t USART1_address_second;
extern	uint8_t USART1_length;
extern	uint8_t USART1_FRAME_status;
extern	uint8_t USART1_my_frame[256];
extern	uint8_t USART1_TRANSMINT_STATUS;
extern	uint8_t USART1_RESIVER_STATUS;


extern uint8_t rsbuf1[];	  //USART1������
extern uint8_t txbuf1[];
extern uint16_t rsbuf1pt_write;
extern uint16_t rsbuf1pt_read;
extern uint16_t rsbuf1pt_TEMP_read;
extern uint16_t rsbuf1pt_COMM_read;

//=====
extern	uint16_t USART3_address_first;
extern	uint16_t USART3_address_second;
extern	uint8_t USART3_length;
extern	uint8_t USART3_FRAME_status;
extern	uint8_t USART3_my_frame[256];
extern	uint8_t USART3_TRANSMINT_STATUS;
extern	uint8_t USART3_RESIVER_STATUS;


extern uint8_t rsbuf3[];	  //USART1������
extern uint8_t txbuf3[];
extern uint16_t rsbuf3pt_write;
extern uint16_t rsbuf3pt_read;
extern uint16_t rsbuf3pt_TEMP_read;
extern uint16_t rsbuf3pt_COMM_read;


//=====



extern struct rtc_time systmtime;  //RTCʵʱʱ��ʹ��
extern u8 rtcbuffer[];

//-------------------
extern uint8_t MY_GPRS_MCU_RsBuf[8];  //�洢�������Ե�ص�ѹ��̫���ܵ�ѹ���¶ȡ�ʪ�ȹ�4��8���ֽڵ�����

extern uint8_t MY_GPRS_Call_Single_data_buf[40];
extern uint8_t MY_GPRS_Call_Analog_data_buf[110];
extern uint8_t MY_GPRS_Call_Time_data_buf[7];
extern uint8_t MY_GPRS_Call_Single_data_number;
extern uint8_t MY_GPRS_Call_Analog_data_number;
extern uint8_t MY_GPRS_Call_Status;    //�洢�����������״̬��Ϊ1��ʾ���������ݣ�Ϊ0��ʾû����������

extern uint8_t MY_EEPROM_Buf[256];  //�����洢EEPROM�У�����������
extern uint8_t MY_GPRS_Cycle_Transmintdata_status;  //�����洢��ȡ���������ݷ���״̬��1Ϊ�ѷ��ͣ�2Ϊδ����


extern uint8_t GPRS_Status;  //��ʶ�����ֻ�ģ�飬GPRS����״̬��1Ϊ�������������ӷ�������0Ϊ�����⣬��Ҫ����
extern uint8_t MESS_Status;  //��������״̬
extern uint8_t NET_Status;  //NET����״̬
extern uint8_t NET_Server_status; //Զ�˷�����server״̬

//-----------------
extern	uint8_t MY_433_Alarmdata_NOtimeBuf[256]; //�洢 ��ʱ�� ��������
extern	uint8_t MY_433_Alarmdata_TimeBuf[256];  //�洢����ʱ�꣬��������
extern	uint8_t MY_433_ALarmdata_number;  // �洢��������Ϣ�����


extern	uint8_t MY_433_ALarmdata_NOtime_status; //Ϊ1����ʾ�յ���ʱ�걨������
extern	uint8_t MY_433_ALarmdata_Time_status;   //Ϊ1����ʾ�յ���ʱ�걨������

//extern uint8_t AT_MESS_telphonenumber[];

extern  uint8_t MY_MCU_RsBuf[];
extern uint8_t MY_433_Call_Single_data_buf[];
extern uint8_t MY_433_Call_Analog_data_buf[];
extern uint8_t MY_433_Call_Time_data_buf[];
extern uint8_t MY_433_Call_Single_data_number;
extern uint8_t MY_433_Call_Analog_data_number;

//------------
extern uint32_t MY_Table1_Alarmdata_StartAddress;
extern uint32_t MY_Table1_Alarmdata_EndAddress;
extern uint32_t MY_Table1_Alarmdata_WriteAddress;
extern uint32_t MY_Table1_Alarmdata_ReadAddress;


extern  uint8_t RE_ALarmData_Status;

extern uint8_t MY_MCU_getdata_status;
extern uint8_t MY_433_Call_Status;

extern	uint8_t my_433_anlag_buf[110];  //�洢433ģ��������������0�������洢��ֻҪ�б仯�����ñ�־λ����ת����
extern	uint8_t my_433_anlag_flag;  //��־λ��Ϊ0��ʾ�Ѿ������������ݣ�Ϊ1��ʾ�������ݵ��ǻ�û�з���



extern uint16_t MY_H_speed_cyc;  //����10����
extern uint16_t MY_H_speed_heart;  //����5����

extern uint16_t MY_M_speed_cyc;  //����15����
extern uint16_t MY_M_speed_heart;  //����9����

extern uint16_t MY_L_speed_cyc;  //����30����
extern uint16_t MY_L_speed_heart; //����7����

extern float MY_Speed_H_Gate;
extern float MY_Speed_L_Gate;

extern uint16_t my_tim6_count;

extern struct indicator_class my_indicator_data[];
extern uint8_t my_usart1_tx_buf1[];



extern uint8_t my_101_DIR ; //101��Լ��,�������DIRλ ���λD8
extern uint8_t my_101_PRM ; //101��Լ�У��������PRM  D7
extern uint8_t my_101_FCB ; //������D6
extern uint8_t my_101_FCV ; //������D5

extern uint8_t my_101_FC ; //�����򣬹�����
extern uint8_t my_101_add_low ;
extern uint8_t my_101_add_high ;
extern uint8_t my_101_TI ;
extern uint8_t my_101_VSQ_1_7 ;
extern uint8_t my_101_VSQ_8_SQ ;
extern uint8_t my_101_COT_low ;
extern uint8_t my_101_COT_high ;


extern uint8_t my_GPRS_all_count;










/*
У���ּ��
*/
uint8_t wdz_GPRS_101char_check(uint8_t *buffer)
{
    uint16_t k = 0;
    uint8_t status68 = 0;
    uint8_t temp = 0;
    uint8_t check_char = 0x00;

    if(buffer[0] == 0x10)
    {
        status68 = 1;
    }
    else if(buffer[0] == 0x68)
    {
        status68 = 2;
    }

    if(status68 == 1) //�̶�����У��λ���
    {
        check_char = buffer[1] + buffer[2] + buffer[3];
        if(check_char == buffer[4])
            temp = 1;
        else temp = 0;


    }
    else if(status68 == 2) //�ǹ̶�����У��λ���
    {
        for(k = 0; k < buffer[1]; k++)
        {
            check_char = check_char + buffer[k + 4];
        }

        if(check_char == buffer[buffer[1] + 4])
            temp = 1;
        else temp = 0;
    }
    return temp;


}







/*
����У����
*/
void wdz_GPRS_101check_generate(uint8_t *buffer)
{
    uint16_t k = 0;
    uint8_t status68 = 0;

    uint8_t check_char = 0x00;

    if(buffer[0] == 0x10)
    {
        status68 = 1;
    }
    else if(buffer[0] == 0x68)
    {
        status68 = 2;
    }


    if(status68 == 1) //�̶�����У��λ���
    {
        check_char = buffer[1] + buffer[2] + buffer[3];
        buffer[4] = check_char;
    }
    else if(status68 == 2) //�ǹ̶�����У��λ���
    {
        for(k = 0; k < buffer[1]; k++)
        {
            check_char = check_char + buffer[k + 4];
        }
        buffer[buffer[1] + 4] = check_char;
    }


}









/*
���ܣ����ݽ��շ������˲���Ϊ����101Э�����ݣ���֡ͷ����֡β����֡������������������Ҫ��ȡ������һ֡���ݡ�
������������ں�
��������� ȡ֡���ݳɹ�����1��ȡ֡����ʧ�ܷ���0
*/
uint8_t my_usart_GPRS_101frame(uint8_t usart_port)
{
    uint8_t *rsbuf = 0;
    uint16_t *rsbufpt_read = 0;
    uint16_t *rsbufpt_COMM_read = 0;
    uint16_t *rsbufpt_write = 0;
    uint8_t *my_frame = 0;
    uint8_t *USART_FRAME = 0;


    uint16_t *address_first = 0;
    uint16_t *address_second = 0;
    uint8_t *length = 0;

    uint8_t ch1 = 0;
    uint16_t pt = 0;
    uint8_t tmp_status = 0;
    uint8_t status = 0;
    uint16_t ii = 0;

    uint8_t my_temp_status = 0;



//******���ڵ�ѡ��****************
    if(usart_port == 1)
    {
        rsbuf = rsbuf1;
        rsbufpt_read = &rsbuf1pt_read;
        rsbufpt_COMM_read = &rsbuf1pt_COMM_read;
        rsbufpt_write = &rsbuf1pt_write;
        address_first = &USART1_address_first;
        address_second = &USART1_address_second;
        length = &USART1_length;
        my_frame = USART1_my_frame;
        USART_FRAME = &USART1_FRAME_status;

        *rsbufpt_COMM_read = *rsbufpt_read;

    }

    if(usart_port == 3)
    {
        rsbuf = rsbuf3;
        rsbufpt_read = &rsbuf3pt_read;
        rsbufpt_COMM_read = &rsbuf3pt_COMM_read;
        rsbufpt_write = &rsbuf3pt_write;
        address_first = &USART3_address_first;
        address_second = &USART3_address_second;
        length = &USART3_length;
        my_frame = USART3_my_frame;
        USART_FRAME = &USART3_FRAME_status;

        *rsbufpt_COMM_read = *rsbufpt_read;

    }

////////****����ѡ�����***************



    while(*USART_FRAME == 0 && *rsbufpt_COMM_read != *rsbufpt_write) //ǰһ��ָ�����ɣ�����δ������ַ�������д���������������������һ��ָ����������ַ��������
    {

        //ȡһ��δ������ַ�
        if(*rsbufpt_COMM_read == rsbuf_max - 1)
        {
            ch1 = rsbuf[*rsbufpt_COMM_read];
            *rsbufpt_COMM_read = 0;
            pt = *rsbufpt_COMM_read;
        }
        else
        {
            ch1 = rsbuf[*rsbufpt_COMM_read];
            *rsbufpt_COMM_read = *rsbufpt_COMM_read + 1;
            pt = *rsbufpt_COMM_read;
        }

        //����0X68֡ͷ��֡β���
        if(ch1 == 0x68)
        {
            tmp_status = 1;
        }
        else if(ch1 == 0x16)
        {
            tmp_status = 2;
        }
        else
        {
            *USART_FRAME = 0;
            my_temp_status = 0;
            tmp_status = 0;
        }


        //����0X68֡ͷ����
        if(tmp_status == 1)
        {

            //
            if((pt > 0 && pt < 4) && ch1 == rsbuf[rsbuf_max + pt - 4] && ch1 == 0x68)
            {

                *address_first = rsbuf_max + pt - 4;
                if(pt - 3 == 0)*length = rsbuf[pt - 3];
                else *length = rsbuf[rsbuf_max + pt - 3];

            }
            else if(pt >= 4 && ch1 == rsbuf[pt - 4] && ch1 == 0x68)
            {

                *address_first = pt - 4;
                *length = rsbuf[pt - 3];
            }
            else if(pt == 0 && ch1 == rsbuf[rsbuf_max - 4] && ch1 == 0x68)
            {

                *address_first = rsbuf_max - 4;
                *length = rsbuf[rsbuf_max - 3];
            }

            else
            {
                *USART_FRAME = 0;
                my_temp_status = 0;
                tmp_status = 0;
            }

        }
        //������֡β��֡ͷ�ķ���
        if(tmp_status == 2)
        {

            //�̶�����֡
            if(pt > 0 && pt < 6 && rsbuf[rsbuf_max + pt - 6] == 0x10)
            {

                *address_first = rsbuf_max + pt - 6;
                *length = 6;
                *address_second = pt - 1;
                *USART_FRAME = 1;
                my_temp_status = 1;

            }
            else if(pt >= 6 && rsbuf[pt - 6] == 0x10)
            {

                *address_first = pt - 6;
                *length = 6;
                *address_second = pt - 1;
                *USART_FRAME = 1;
                my_temp_status = 1;
            }
            else if(pt == 0 && rsbuf[rsbuf_max - 6] == 0x10)
            {

                *address_first = rsbuf_max - 6;
                *length = 6;
                *address_second = pt - 1;
                *USART_FRAME = 1;
                my_temp_status = 1;
            }
            //�ǹ̶�����֡
            if(pt - 6 - *address_first == (*length) && *address_first < pt)
            {
                *address_second = pt - 1;
                *USART_FRAME = 2;
                my_temp_status = 2;
            }
            else if(*address_first > pt && pt != 0)
            {
                if((pt + rsbuf_max - *address_first - 6) == (*length))
                {   *address_second = pt - 1;
                    *USART_FRAME = 2;
                    my_temp_status = 2;
                }
            }
            else if(pt == 0)
            {
                if((rsbuf_max - *address_first - 6) == (*length))
                {   *address_second = rsbuf_max - 1;
                    *USART_FRAME = 2;
                    my_temp_status = 2;
                }
            }
            //


        }
    }
//ȡһ֡���ݴ��뵽ָ��������



    if(my_temp_status > 0)	 //���������һ֡���ݣ��Ϳ�ʼ�������򷵻أ�������
    {
        //�������������
        for(ii = 0; ii < 256; ii++)
        {
            my_frame[ii] = 0;
        }

        //ȡ�̶�����ָ��
        if(rsbuf[*address_first] == 0x10)
        {
            for(ii = 0; ii < 6; ii++)
            {
                my_frame[ii] = rsbuf[*address_first];
                *address_first = *address_first + 1;
                if(*address_first >= rsbuf_max) *address_first = 0;
            }

            *rsbufpt_read = *address_second + 1;
            if(*rsbufpt_read >= rsbuf_max)*rsbufpt_read = 0;

            status = 1;
        }
        //ȡ�ǹ̶�����ָ��
        else if(rsbuf[*address_first] == 0x68)
        {
            for(ii = 0; ii < 6 + *length; ii++)
            {
                my_frame[ii] = rsbuf[*address_first];
                *address_first = *address_first + 1;
                if(*address_first >= rsbuf_max) *address_first = 0;
            }

            *rsbufpt_read = *address_second + 1;
            if(*rsbufpt_read >= rsbuf_max)*rsbufpt_read = 0;
            status = 1;
        }
        else
        {
            status = 0;
        }
    }

    //���з��ش���
    if(status == 1)
    {
        //*USART_FRAME=0;  //ȡ��һָ֡����б��
        //printf("\r\nOK=%s",my_frame);
        //USART_printf(USARTx,"\r\nOK=%s",my_frame);
        //USART_printf(USARTx,"%s",my_frame);
        return(1);
    }
    else
    {
        //USART_FRAME=0;  //ȡ��һָ֡����б��
        //printf("\r\nERROR");
        return(0);
    }

}









/*
�����ַ������Ƶ�������
*/
void wdz_GPRS_string_to_array(uint8_t *my_string, uint8_t *txbuf)
{
    uint32_t k = 0;
    uint32_t length = 0;
    if(my_string[0] == 0x10)
    {
        length = 6;
    }
    else if(my_string[0] == 0x68)
    {
        length = my_string[1] + 6;
    }
    //=================

    for(k = 0; k < length; k++)
    {
        txbuf[k] = my_string[k];
    }
    //===========
    if(my_string[0] == 0x10)
    {
        txbuf[2] = DTU_ADDRESS;
        txbuf[3] = (DTU_ADDRESS >> 8);
    }
    else if(my_string[0] == 0x68)
    {
        txbuf[5] = DTU_ADDRESS;
        txbuf[6] = (DTU_ADDRESS >> 8);

        txbuf[10] = DTU_ADDRESS; //
        txbuf[11] = (DTU_ADDRESS >> 8);


    }
    txbuf[length - 2] = my_fun_101check_generate(txbuf, 0);
    txbuf[k] = 0;
}








//*************�������������*******
/*
���ܣ��������������ȴ�Ӧ�����

������������10 D2 01 00 D3 16 ���� 10 F2 01 00 F3 16
����ȷ�ϰ�  10 80 01 00 81 16 ���� 10 82 01 00 83 16
*/
extern uint8_t link_status_GPRS;
extern uint8_t GPRS_Heartdata_error_count;  //�ж�������ʧ�ܵĴ����������5���ˣ��ͱ�ʶGPRS������ϣ�Ȼ�������������ֵ����M35�������ж�




//*************���Ͳ���������������*************

/*
68 0C 0C 68 73 01 00 68 01 06 00 01 00 00 AA 55 E3 16��������(����)
        ���϶�ȷ�ϣ�10 80 01 00 81 16
 68 23 23 68 73 01 00 01 98 14 00 01 00 01 00 00 00 00 00 00 00 00 23 16(ң�����ݰ�)
 ��ң�����ݰ���
  ���������ݰ���
				���϶�ȷ�ϣ�10 80 01 00 81 16
*/

extern uint32_t MY_Table2_Cycledata_StartAddress;
extern uint32_t MY_Table2_Cycledata_EndAddress;
extern uint32_t MY_Table2_Cycledata_WriteAddress;
extern uint32_t MY_Table2_Cycledata_ReadAddress;
extern uint8_t MY_GPRS_Call_Single_data_number;
extern uint8_t MY_GPRS_Call_Analog_data_number;




/*
���ܣ�����ң�����ݰ�  68 23 23 68 73 01 00 02 ?? 14 01 00 01 00 ?? ??  ??  ** 16
*/

#define my_single_inf_num 2   //ң��ʹ�õĵ�����ϢΪ1��˫����ϢΪ2
void my_gprs_generate_101single_data(uint8_t temp, uint8_t *my_rsbuf,uint8_t my_shibiao_time,uint8_t my_cot)
{
    uint8_t length = 0;


    if(temp == 1) //�������ݰ�
    {
        length = MY_GPRS_Call_Single_data_number; //56����Ϣ�壬ÿ����1���ֽڣ�˫����Ϣ��
        my_rsbuf[0] = 0x68;
        my_rsbuf[3] = 0x68;
        my_rsbuf[1] = length + 11 + my_shibiao_time; //����ʱ��7���ֽ�
        my_rsbuf[2] = length + 11 + my_shibiao_time;

        //�������봦��
        my_101_DIR = 0X80;
        my_101_PRM = 0X40;
        if(my_GPRS_all_count == 1)
            my_101_FCB = (~my_101_FCB) & 0X20;
        my_101_FCV = 0X10;
        my_101_FC = 0X03;

        my_usart1_tx_buf1[4] = (my_101_DIR | my_101_PRM | my_101_FCB | my_101_FCV | my_101_FC); //��������Ϊ53/73



        my_rsbuf[5] = DTU_ADDRESS;
        my_rsbuf[6] = (DTU_ADDRESS >> 8);
				
				if(my_shibiao_time==7)
        my_rsbuf[7] = 31; //TI  ң�ţ�˫����Ϣ����ʱ��
				else
				my_rsbuf[7] = 3;
				
        my_rsbuf[8] = length + 0x80; //��Ϣ�����
        my_rsbuf[9] = my_cot; //����ԭ��
				my_rsbuf[10] = 0; //����ԭ��

        my_rsbuf[11] = DTU_ADDRESS; //�������ַ
        my_rsbuf[12] = (DTU_ADDRESS >> 8);

        my_rsbuf[13] = 0x01; //ң����Ϣ���׵�ַ
        my_rsbuf[14] = 0x00;



        my_rsbuf[4+11 + length + my_shibiao_time ] = 0XFF;
        my_rsbuf[4+11 + length + my_shibiao_time + 1 ] = 0x16;

    }
    //����ʹ��
    else if(temp == 0) //����0���������ݰ�
    {
      
    }


}








/*
����;����ң�����ݰ�

//68 53 53 68 53 01 00 09 98 14 00 01 00 01 40 00 00 00 00 00 00 00 00 00 00 4B 16
*/
void my_gprs_generate_101analog_data(uint8_t temp, uint8_t *my_rsbuf,uint8_t shibiao,uint8_t my_cot)
{
    uint8_t length = 0;


    if(temp == 1) //�������ݰ�
    {
        length = MY_GPRS_Call_Analog_data_number;

        my_rsbuf[0] = 0x68;
        my_rsbuf[3] = 0x68;
        my_rsbuf[1] = length * 5 + 11+shibiao; //12*5+11=61
        my_rsbuf[2] = length * 5 + 11+shibiao;

        //�������봦��
        my_101_DIR = 0X80;
        my_101_PRM = 0X40;
        if(my_GPRS_all_count == 1)
            my_101_FCB = (~my_101_FCB) & 0X20;
        my_101_FCV = 0X10;
        my_101_FC = 0X03;

        my_usart1_tx_buf1[4] = (my_101_DIR | my_101_PRM | my_101_FCB | my_101_FCV | my_101_FC); //��������Ϊ53/73

        my_rsbuf[5] = DTU_ADDRESS;
        my_rsbuf[6] = (DTU_ADDRESS >> 8);

        my_rsbuf[7] = 13; //���������̸�����
        my_rsbuf[8] = length + 0x80; //��Ϣ�����
        my_rsbuf[9] = my_cot; //����ԭ��
				my_rsbuf[10] = 00; //����ԭ��

        my_rsbuf[11] = DTU_ADDRESS; //�������ַ
        my_rsbuf[12] = (DTU_ADDRESS >> 8);;

        my_rsbuf[13] = 0x11; //ң����Ϣ���׵�ַ
        my_rsbuf[14] = 0x40;

      
        my_rsbuf[4+11 + length * 5 +shibiao] = 0XFF;
        my_rsbuf[4+11  + length * 5 +shibiao+ 1 ] = 0x16;


    }
    else if(temp == 0) //����0���������ݰ�
    {
        
    }



}







/*
����;���ɻ������ݰ�,tempΪ1���������ݵ����ݰ���0����0���ݵ����ݰ�
*/
void my_gprs_generate_101MCU_data(uint8_t temp, uint8_t *my_rsbuf,uint8_t my_cot)
{
    uint8_t length = 0;

    if(temp == 1) //�������ݰ�
    {
        length = 1;

        my_rsbuf[0] = 0x68;
        my_rsbuf[3] = 0x68;
        my_rsbuf[1] = length * 5 + 11;
        my_rsbuf[2] = length * 5 + 11;

         //�������봦��
        my_101_DIR = 0X80;
        my_101_PRM = 0X40;
        if(my_GPRS_all_count == 1)
            my_101_FCB = (~my_101_FCB) & 0X20;
        my_101_FCV = 0X10;
        my_101_FC = 0X03;

        my_usart1_tx_buf1[4] = (my_101_DIR | my_101_PRM | my_101_FCB | my_101_FCV | my_101_FC); //��������Ϊ53/73

        my_rsbuf[5] = DTU_ADDRESS;
        my_rsbuf[6] = (DTU_ADDRESS >> 8);

        my_rsbuf[7] = 13; //���������̸�����
        my_rsbuf[8] = length + 0x80; //��Ϣ�����
        my_rsbuf[9] = my_cot; //����ԭ��
				my_rsbuf[10] = 00; //����ԭ��

        my_rsbuf[12] = 0x01; //ң����Ϣ���׵�ַ
        my_rsbuf[13] = 0x40;

        

        my_rsbuf[4+11 + length * 5 ] = 0XFF;
        my_rsbuf[4+11 + length * 5 + 1 ] = 0x16;

        


    }
    else if(temp == 0) //����0���������ݰ�
    {
       
    }


}







/*
������������
*/
void my_GPRS_101_geneate_FCBword(uint8_t *my_rsbuf)
{   uint8_t FCB = 0X20;

    if(my_rsbuf[0] == 0x68)
    {
        //�������봦��
        if(WDZ_GPRS_101FCB == 0x00)
            my_rsbuf[4] = my_rsbuf[4] & (~FCB);
        else if(WDZ_GPRS_101FCB == 0x20)
            my_rsbuf[4] = my_rsbuf[4] | (FCB);
    }
    else if(my_rsbuf[0] == 0x10)
    {
        //�������봦��
        if(WDZ_GPRS_101FCB == 0x00)
            my_rsbuf[1] = my_rsbuf[1] & (~FCB);
        else if(WDZ_GPRS_101FCB == 0x20)
            my_rsbuf[1] = my_rsbuf[1] | (FCB);
    }

    //��¼���ͱ仯֡
    WDZ_GPRS_101FCB = WDZ_GPRS_101FCB ^ 0x20;

}






//-------------�������ճ���Уʱ������----






/*
���ܣ����յ��Ĳ����������������Ӧ��������صĲ�������Ҫ����DTU��ַ5001��������ʱ��5002���������ݷ���ʱ��5003��Server��ַ6�ֽ�5004��
      �����ֻ���8�ֽ�5005��ɾ���ֻ�����5006
*/
extern uint16_t Transmint_to_GPRS_hearttime;
extern uint16_t Transmint_to_GPRS_Cycledata;

extern uint8_t MY_IP[4]; //222.222.118.3
extern uint16_t MY_PORT;  //8080  16λ����










/*
	���ܣ��洢mypt��ֵַ�ĵ�3���ֽڵ�EEPROM��tabladdress��ʼ�ĵ�ַ
	*/
void my_save_PTTO_EEROM(uint32_t mypt, uint32_t tableaddress)
{   uint8_t tempbuf[3] = {0};
    uint32_t first_address = mypt;
    tempbuf[0] = first_address & 0x0000ff;
    tempbuf[1] = (first_address >> 8) & 0x0000ff;
    tempbuf[2] = (first_address >> 16) & 0x0000ff;
    SPI_EE_BufferWrite2(tempbuf, tableaddress, 3);
}




void my_reset_mcu()  //����MCUͨ��������
{
    __disable_fault_irq();
    NVIC_SystemReset();
}




/*
���յ����ַ�ת����ASCII�������ʾ
*/

void my_display_ASCIIdata(uint8_t *rsbuf)
{
//	int tt=0;
    int length = 0;
//	uint8_t *mypt=rsbuf;
//	uint8_t my_temp1,my_temp2;
    uint8_t desbuf[512] = {0};

    if(*rsbuf == 0x10) length = 6;
    else if(*rsbuf == 0x68) length = *(rsbuf + 1) + 6;


    HexToStr2(desbuf, rsbuf, length);
    USART_printf(&huart3, desbuf);

    /*
    for(tt=0;tt<length;tt++)
    {
    	my_temp1=*mypt/16;
    	my_temp2=*mypt%16;
    	USART_printf(&huart3,"%d%d-",my_temp1,my_temp2);
    mypt++;
    }
    */
    USART_printf(&huart3, "\r\n");

}



/*
���ܣ�����AT+CSQ�������ź�����

*/

extern uint8_t MY_AT_CSQ_Value;

/*
���ܣ�����GPRS�ź�����
*/
void my_gprs_generate_101CSQ_data(uint8_t temp, uint8_t *my_rsbuf)
{
    uint8_t length = 0;

    if(temp == 1) //�������ݰ�
    {
        length = 1;

        my_rsbuf[0] = 0x68;
        my_rsbuf[3] = 0x68;
        my_rsbuf[1] = length * 2 + 10;
        my_rsbuf[2] = length * 2 + 10;

        my_rsbuf[4] = 0x73; //��������Ϊ53/73
        my_GPRS_101_geneate_FCBword(my_rsbuf);


        my_rsbuf[5] = DTU_ADDRESS & 0X00FF;
        my_rsbuf[6] = (DTU_ADDRESS >> 8) & 0X00FF;

        my_rsbuf[7] = 0X09; //���ͱ�ʶ����ʱ��ĵ�����Ϣ��
        my_rsbuf[8] = length + 0x80; //��Ϣ�����
        my_rsbuf[9] = 0x14; //����ԭ��

        my_rsbuf[10] = DTU_ADDRESS & 0X00FF; //�������ַ
        my_rsbuf[11] = (DTU_ADDRESS >> 8) & 0X00FF;;

        my_rsbuf[12] = 0x00; //ң����Ϣ���׵�ַ
        my_rsbuf[13] = 0x42;

        //my_buf1_to_buf2(MY_GPRS_MCU_RsBuf,0,my_rsbuf,14,length*2);

        my_rsbuf[14] = MY_AT_CSQ_Value;
        my_rsbuf[15] = 0X00;

        //
        my_rsbuf[13 + length * 2 + 1] = 0XFF;
        my_rsbuf[13 + length * 2 + 1 + 1] = 0x16;

        wdz_GPRS_101check_generate(my_rsbuf); //����У���ֽ�



    }
    else if(temp == 0) //����0���������ݰ�
    {
        length = 2;
        my_rsbuf[0] = 0x68;
        my_rsbuf[3] = 0x68;
        my_rsbuf[1] = length + 10;
        my_rsbuf[2] = length + 10;

        my_rsbuf[4] = 0x73; //��������Ϊ53/73
        my_GPRS_101_geneate_FCBword(my_rsbuf);

        my_rsbuf[5] = DTU_ADDRESS & 0X00FF;
        my_rsbuf[6] = (DTU_ADDRESS >> 8) & 0X00FF;

        my_rsbuf[7] = 0X09; //���ͱ�ʶ����ʱ��ĵ�����Ϣ��
        my_rsbuf[8] = 0x84; //��Ϣ�����
        my_rsbuf[9] = 0x14; //����ԭ��

        my_rsbuf[10] = DTU_ADDRESS & 0X00FF; //�������ַ
        my_rsbuf[11] = (DTU_ADDRESS >> 8) & 0X00FF;;

        my_rsbuf[12] = 0x00; //ң����Ϣ���׵�ַ
        my_rsbuf[13] = 0x42;

        my_rsbuf[14] = 0x00;
        my_rsbuf[15] = 0x00;

        my_rsbuf[16] = 0XFF;
        my_rsbuf[17] = 0x16;

        wdz_GPRS_101check_generate(my_rsbuf); //����У���ֽ�
    }


}

/*
���ܣ�ң�ⲹ��
*/
void my_gprs_generate_101yaoce2_data(uint8_t *my_rsbuf)
{
    uint8_t length = 12; //��Ϣ�����
    uint8_t jj = 0;
    //֡ͷ
    my_rsbuf[0] = 0x68;
    my_rsbuf[3] = 0x68;
    my_rsbuf[1] = length * 2 + 10;
    my_rsbuf[2] = length * 2 + 10;
    //�����򲿷�
    my_rsbuf[4] = 0x73; //��������Ϊ53/73
    //my_GPRS_101_geneate_FCBword(my_rsbuf);
    my_rsbuf[5] = DTU_ADDRESS;
    my_rsbuf[6] = (DTU_ADDRESS >> 8);
    my_rsbuf[7] = 0X09; //���ͱ�ʶ����ʱ��ĵ�����Ϣ��
    my_rsbuf[8] = length + 0x80; //��Ϣ�����
    my_rsbuf[9] = 0x67; //����ԭ��
    my_rsbuf[10] = DTU_ADDRESS; //�������ַ
    my_rsbuf[11] = (DTU_ADDRESS >> 8);;
    my_rsbuf[12] = 0x01; //ң����Ϣ���׵�ַ
    my_rsbuf[13] = 0x42;
    //֡β
    my_rsbuf[13 + length * 2 + 1] = 0XFF;
    my_rsbuf[13 + length * 2 + 1 + 1] = 0x16;
    //���ݲ���
    for(jj = 0; jj < 3; jj++)
    {   //1�¶ȣ�2��Դ��3�ο���ѹ��4�ɵ�أ�5���ϵ�ѹ��6̫���ܣ�7﮵��
        my_rsbuf[14 + 8 * jj] = my_indicator_data[jj].DC_data_buf[5 * 2]; //6̫����
        my_rsbuf[15 + 8 * jj] = my_indicator_data[jj].DC_data_buf[5 * 2 + 1];

        my_rsbuf[16 + 8 * jj] = my_indicator_data[jj].DC_data_buf[4 * 2]; //5���ϵ�ѹ
        my_rsbuf[17 + 8 * jj] = my_indicator_data[jj].DC_data_buf[4 * 2 + 1];

        //�ɵ������ת���ɣ�ָʾ����Ӧ��TIMER
        //my_rsbuf[18 + 8 * jj] = my_indicator_data[jj].DC_data_buf[3 * 2]; //4�ɵ��
        //my_rsbuf[19 + 8 * jj] = my_indicator_data[jj].DC_data_buf[3 * 2 + 1];

        my_rsbuf[18 + 8 * jj] = my_indicator_data[jj].count_time[0]; //4�ɵ��
        my_rsbuf[19 + 8 * jj] = my_indicator_data[jj].count_time[1];


        my_rsbuf[20 + 8 * jj] = my_indicator_data[jj].AC_data_buf[4]; //�벨����ֵ
        my_rsbuf[21 + 8 * jj] = my_indicator_data[jj].AC_data_buf[5];

    }

    wdz_GPRS_101check_generate(my_rsbuf); //����У���ֽ�

}

/*
���ܣ�ң��12T
*/
void my_gprs_generate_101yaoce12T_data(uint8_t *my_rsbuf)
{
    uint8_t length = 3; //��Ϣ�����
    uint8_t jj = 0, ii = 0;
    //֡ͷ
    my_rsbuf[0] = 0x68;
    my_rsbuf[3] = 0x68;
    my_rsbuf[1] = length * 48 + 10;
    my_rsbuf[2] = length * 48 + 10;
    //�����򲿷�
    my_rsbuf[4] = 0x73; //��������Ϊ53/73
    //my_GPRS_101_geneate_FCBword(my_rsbuf);
    my_rsbuf[5] = DTU_ADDRESS;
    my_rsbuf[6] = (DTU_ADDRESS >> 8);
    my_rsbuf[7] = 0X09; //���ͱ�ʶ����ʱ��ĵ�����Ϣ��
    my_rsbuf[8] = length + 0x80; //��Ϣ�����
    my_rsbuf[9] = 0x68; //����ԭ��
    my_rsbuf[10] = DTU_ADDRESS; //�������ַ
    my_rsbuf[11] = (DTU_ADDRESS >> 8);;
    my_rsbuf[12] = 0x01; //ң����Ϣ���׵�ַ
    my_rsbuf[13] = 0x43;
    //֡β
    my_rsbuf[13 + length * 2 + 1] = 0XFF;
    my_rsbuf[13 + length * 2 + 1 + 1] = 0x16;
    //���ݲ���
    for(jj = 0; jj < 3; jj++)
    {   //12T ����+�糡
        for(ii = 0; ii < 24; ii++)
        {
            my_rsbuf[14 + 48 * jj + ii] = my_indicator_data[jj].AC12T_ALL_Current_data_buf[ii ]; //����

        }
        for(ii = 0; ii < 24; ii++)
        {
            my_rsbuf[14 + 48 * jj + ii + 24] = my_indicator_data[jj].AC12T_ALL_dianchang_data_buf[ii]; //�糡

        }

    }

    wdz_GPRS_101check_generate(my_rsbuf); //����У���ֽ�

}
/*
���ܣ�����ͬ��ֵ
*/
extern uint16_t my_gprs_count_time; //GPRSͨ�ţ��������ݣ����ݸ�SERVER��DTU�յ���zsq�ļ���ֵ
extern uint8_t  my_gprs_RTC_buf[];

void my_gprs_generate_101yaoce1_COUNTSYN_data(uint8_t *my_rsbuf)
{
    uint8_t length = 1; //��Ϣ�����

    //֡ͷ
    my_rsbuf[0] = 0x68;
    my_rsbuf[3] = 0x68;
    my_rsbuf[1] = length * 9 + 10;
    my_rsbuf[2] = length * 9 + 10;
    //�����򲿷�
    my_rsbuf[4] = 0x73; //��������Ϊ53/73
    //my_GPRS_101_geneate_FCBword(my_rsbuf);
    my_rsbuf[5] = DTU_ADDRESS;
    my_rsbuf[6] = (DTU_ADDRESS >> 8);
    my_rsbuf[7] = 0XDC; //���ͱ�ʶ����ʱ��ĵ�����Ϣ��
    my_rsbuf[8] = length + 0x80; //��Ϣ�����
    my_rsbuf[9] = 0x69; //����ԭ��
    my_rsbuf[10] = DTU_ADDRESS; //�������ַ
    my_rsbuf[11] = (DTU_ADDRESS >> 8);;
    my_rsbuf[12] = 0x01; //ң����Ϣ���׵�ַ
    my_rsbuf[13] = 0x4F;
    //֡β
    my_rsbuf[13 + length * 9 + 1] = 0XFF;
    my_rsbuf[13 + length * 9 + 1 + 1] = 0x16;
    //���ݲ���


    my_rsbuf[14] = my_gprs_count_time;
    my_rsbuf[15] = (my_gprs_count_time >> 8);

    my_rsbuf[16] = my_gprs_RTC_buf[0];
    my_rsbuf[17] = my_gprs_RTC_buf[1];
    my_rsbuf[18] = my_gprs_RTC_buf[2];
    my_rsbuf[19] = my_gprs_RTC_buf[3];
    my_rsbuf[20] = my_gprs_RTC_buf[4];
    my_rsbuf[21] = my_gprs_RTC_buf[5];
    my_rsbuf[22] = my_gprs_RTC_buf[6];




    wdz_GPRS_101check_generate(my_rsbuf); //����У���ֽ�

}


/*
���ܣ�������������ʹ�õ�12���ַ�
*/
extern uint8_t my_indicator_tx_index;

extern struct indicator_alarm_class my_indicator_alarm_data[];
void my_fun_gprs_generate_12T_data(uint8_t *txbuf)
{
    uint8_t ii = 0, jj = 0;

    wdz_GPRS_string_to_array(TX_GPRS_101_ALarm_single_12T_data, my_usart1_tx_buf1);
    for(ii = 0; ii < 3; ii++) //�������12T����
    {
        if(ii == my_indicator_tx_index)
        {
            for(jj = 0; jj < 24; jj++)
            {
                my_usart1_tx_buf1[14 + ii * 48 + jj] = my_indicator_alarm_data[ii].AC12T_ALL_Current_data_buf[jj];		//����
            }
            for(jj = 0; jj < 24; jj++)
            {
                my_usart1_tx_buf1[14 + ii * 48 + jj + 24] = my_indicator_alarm_data[ii].AC12T_ALL_dianchang_data_buf[jj];	//�糡
            }
        }
        else //���������������������
        {
            for(jj = 0; jj < 24; jj++)
            {
                my_usart1_tx_buf1[14 + ii * 48 + jj] = my_indicator_data[ii].AC12T_ALL_Current_data_buf[jj];		//����
            }
            for(jj = 0; jj < 24; jj++)
            {
                my_usart1_tx_buf1[14 + ii * 48 + jj + 24] = my_indicator_data[ii].AC12T_ALL_dianchang_data_buf[jj];			//�糡
            }



        }


    }







}
