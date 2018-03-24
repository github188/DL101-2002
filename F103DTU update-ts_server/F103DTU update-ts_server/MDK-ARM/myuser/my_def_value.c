#include "my_def_value.h"





uint8_t my_sys_init_flash=1  ;  //1ϵͳ�ϵ���ղ���eepromȡĬ��ֵ��0Ϊ��


//�������ݲ���
uint8_t rsbuf1[rsbuf_max];	 //���ڽ��ջ�����
uint8_t rsbuf2[rsbuf_max];
uint8_t rsbuf3[rsbuf_max];
uint8_t rsbuf4[rsbuf_max];
uint8_t rsbuf5[rsbuf_max];

uint8_t txbuf1[256];
uint8_t txbuf2[256];
uint8_t txbuf3[256];
uint8_t txbuf4[256];
uint8_t txbuf5[256];

uint16_t rsbuf1pt_write=0;
uint16_t rsbuf1pt_read=0;
uint16_t rsbuf1pt_TEMP_read=0;
uint16_t rsbuf1pt_COMM_read=0;


uint16_t rsbuf2pt_write=0;
uint16_t rsbuf2pt_read=0;
uint16_t rsbuf2pt_TEMP_read=0;
uint16_t rsbuf2pt_COMM_read=0;

uint16_t rsbuf3pt_write=0;
uint16_t rsbuf3pt_read=0;
uint16_t rsbuf3pt_TEMP_read=0;
uint16_t rsbuf3pt_COMM_read=0;

uint16_t rsbuf4pt_write=0;
uint16_t rsbuf4pt_read=0;
uint16_t rsbuf4pt_TEMP_read=0;
uint16_t rsbuf4pt_COMM_read=0;

uint16_t rsbuf5pt_write=0;
uint16_t rsbuf5pt_read=0;
uint16_t rsbuf5pt_TEMP_read=0;
uint16_t rsbuf5pt_COMM_read=0;



//-----SPI ����ʹ��
uint8_t SPI_TXBuffer[256]= {0};
uint8_t SPI_RXBuffer[256]= {0};
//-----SPI OVER

//===M35
//uint8_t AT_MESS_buf[256]= {"IP123.45.6.246:54321"}; //����Ϣ�洢��
//uint8_t AT_MESS_sendbuf[256]= {"\x01 error 345 and 123\x1A"};
//uint8_t AT_MESS_telphonenumber[7][16]= {"+8618630401372"};
//uint8_t AT_MESS_telphonenumber2[4][16]= {"+8618630401372"};
//===
uint8_t RE_ALarmData_Status=0;  //������������״̬����ӦEEPROM��200��ַ�ֽڵ����ݣ�1Ϊ������2Ϊ��Ҫ��������
uint8_t RE_CycleData_Status=0;

//----------over
//==HAL�������Ӵ����жϽ�������ʹ��
//uint8_t  my_usart3_re_buf[200]={0};
//uint16_t my_usart3_re_count=0;
//END

//=======EEPROM====

uint8_t MY_433_Alarmdata_NOtimeBuf[256]= {0}; //�洢 ��ʱ�� ��������
uint8_t MY_433_Alarmdata_TimeBuf[256]= {0}; //�洢����ʱ�꣬��������
uint8_t MY_433_ALarmdata_number=0;  // �洢��������Ϣ�����


uint8_t MY_433_ALarmdata_NOtime_status=0; //Ϊ1����ʾ�յ���ʱ�걨������
uint8_t MY_433_ALarmdata_Time_status=0;   //Ϊ1����ʾ�յ���ʱ�걨������



uint8_t MY_433_Alarmdata_NOtime_WriteAddress=0;



//============


//==101
uint8_t MY_433_Call_Single_data_buf[256]= {0xff};
uint8_t MY_433_Call_Analog_data_buf[256]= {0xff};
uint8_t MY_433_Call_Time_data_buf[7]= {0};
uint8_t MY_433_Call_Single_data_number=0;
uint8_t MY_433_Call_Analog_data_number=0;
uint8_t MY_433_Call_Status=0;  //433ģ����������״̬��Ϊ1��ʾ�յ����ݲ����뵽���黺�����У�0Ϊû������


//===DTU����ʱ�����




//==

uint8_t MY_IP[4]= {106,14,41,25}; //211,81,174,30   120,27,48,70   118.26.119.118 106.14.41.25   106,14,41,25
uint16_t MY_PORT=2216;  //5655   2204  8266 2205��,216



//===tim
uint32_t MY_Table1_Alarmdata_StartAddress=1024*1;
uint32_t MY_Table1_Alarmdata_EndAddress=EEPROM_Chip_size-1;
uint32_t MY_Table1_Alarmdata_WriteAddress=1024*1;
uint32_t MY_Table1_Alarmdata_ReadAddress=1024*1;

uint32_t MY_Table2_Cycledata_StartAddress=EEPROM_Chip_size;
uint32_t MY_Table2_Cycledata_EndAddress=EEPROM_Chip_size*2-1;
uint32_t MY_Table2_Cycledata_WriteAddress=EEPROM_Chip_size;
uint32_t MY_Table2_Cycledata_ReadAddress=EEPROM_Chip_size;

uint8_t MY_Table2_Newdata_status=0; //EEPROM��Table2���ٲ��������ݱ�ʶ��Ϊ1��ʾ��������д�룬Ϊ0��ʾ������д��
uint8_t MY_Table1_Newdata_status=0; //EEPROM��Table1���������ݱ�ʶ��Ϊ1��ʾ��������д�룬Ϊ0��ʾ������д��

//===MCU
uint8_t MY_MCU_RsBuf[8]= {0};
uint8_t MY_MCU_getdata_status=0;


//==TIM6
__IO uint32_t TimingDelay;

uint8_t GPRS_Heartdata_error_count=0;  //�ж�������ʧ�ܵĴ����������5���ˣ��ͱ�ʶGPRS������ϣ�Ȼ�������������ֵ����M35�������ж�
uint16_t Transmint_to_GPRS_hearttime=60*5;  //  GPRS���������� �� Server��ʱ����������1����λΪ5�룬10����λ��Ϊ50��
uint16_t Transmint_to_GPRS_Cycledata=60*15;  //


//==========
uint16_t USART1_address_first=0;
uint16_t USART1_address_second=0;
uint8_t USART1_length=0;
uint8_t USART1_FRAME_status=0;
uint8_t USART1_my_frame[256]= {0};
uint8_t USART1_TRANSMINT_STATUS=0;
uint8_t USART1_RESIVER_STATUS=0;


uint8_t link_status_GPRS=0; //GPRS������·����״̬��1Ϊ�����ɹ���0Ϊ�Ͽ���
uint8_t link_status_433=0; //��ʾ433ģ����·����״̬��Ϊ1��ʾ������·�ɹ���Ϊ0��ʾ��·�Ͽ�����Ҫ���½�������
uint8_t  wdz_433_heart_count=0;






//RTC���ݲ���
//struct rtc_time systmtime;
int T_year=2014,T_month=11,T_day=5,T_hh=21,T_mm=30,T_ss=00;
uint8_t rtcbuffer[]= {00,00,06,21,10,07,15}; //2014-10-5 23��33��00

uint16_t MY_H_speed_cyc=23;  //����5���� //��λΪ��
uint16_t MY_H_speed_heart=17;  //����3����

uint16_t MY_M_speed_cyc=23;  //����15����
uint16_t MY_M_speed_heart=17;  //����6����

uint16_t MY_L_speed_cyc=23;  //����30����
uint16_t MY_L_speed_heart=17; //����8����

float MY_Speed_H_Gate=12.0;
float MY_Speed_L_Gate=10.5;

uint16_t MY_ACT_CYC_DTU=181;
uint16_t MY_ACT_Heart_DTU=67;
uint8_t my_act_cyc_dtu_delay=0;

float  my_AD_value=0;
float  my_AD_SUN_value=0;



