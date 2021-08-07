#ifndef __ADS1292R_H
#define __ADS1292R_H

#include "stm32h7xx_hal.h"
#include "arm_math.h"

//#include "arm_math.h"
//#include "sys.h"
////#include "tftlcd.h"
//#include <stdio.h>
//#include "arm_math.h"
//#include "math_helper.h"
//#include "arm_fir_example_f32.h"

//#define ADS1292R_CS_PORT                GPIOF
//#define ADS1292R_CS_PIN                 GPIO_PIN_6
//#define ADS1292R_START_PORT             GPIOB
//#define ADS1292R_START_PIN              GPIO_PIN_1
//#define ADS1292R_PWDN_PORT              GPIOB
//#define ADS1292R_PWDN_PIN               GPIO_PIN_0
//#define ADS1292R_ADC_RDY_PORT           GPIOB
//#define ADS1292R_ADC_RDY_PIN            GPIO_PIN_11
#define ADS1292R_CS_PORT                GPIOA
#define ADS1292R_CS_PIN                 GPIO_PIN_4
#define ADS1292R_START_PORT             GPIOF
#define ADS1292R_START_PIN              GPIO_PIN_10
#define ADS1292R_PWDN_PORT              GPIOF
#define ADS1292R_PWDN_PIN               GPIO_PIN_6
#define ADS1292R_ADC_RDY_PORT           GPIOF
#define ADS1292R_ADC_RDY_PIN            GPIO_PIN_8

#define ADS1292R_CS_H				HAL_GPIO_WritePin(ADS1292R_CS_PORT, ADS1292R_CS_PIN,GPIO_PIN_SET)
#define ADS1292R_CS_L				HAL_GPIO_WritePin(ADS1292R_CS_PORT, ADS1292R_CS_PIN,GPIO_PIN_RESET)
#define ADS1292R_PWDN_H			HAL_GPIO_WritePin(ADS1292R_PWDN_PORT, ADS1292R_PWDN_PIN,GPIO_PIN_SET)
#define ADS1292R_PWDN_L			HAL_GPIO_WritePin(ADS1292R_PWDN_PORT, ADS1292R_PWDN_PIN,GPIO_PIN_RESET)
#define ADS1292R_START_H		HAL_GPIO_WritePin(ADS1292R_START_PORT, ADS1292R_START_PIN,GPIO_PIN_SET)
#define ADS1292R_START_L		HAL_GPIO_WritePin(ADS1292R_START_PORT, ADS1292R_START_PIN,GPIO_PIN_RESET)

/*ADS1292R�����*/
/*ϵͳ����*/
#define ADS1292R_WAKEUP	        	0X02	//�Ӵ���ģʽ����
#define ADS1292R_STANDBY	        0X04	//�������ģʽ
#define ADS1292R_ADSRESET        	0X06	//��λADS1292R
#define ADS1292R_START	        	0X08	//������ת��
#define ADS1292R_STOP	        		0X0A	//ֹͣת��
#define ADS1292R_OFFSETCAL				0X1A	//ͨ��ƫ��У׼
/*���ݶ�ȡ����*/
#define ADS1292R_RDATAC	        	0X10	//�������������ݶ�ȡģʽ,Ĭ��ʹ�ô�ģʽ
#define ADS1292R_SDATAC	        	0X11	//ֹͣ���������ݶ�ȡģʽ
#define ADS1292R_RDATA	        	0X12	//ͨ�������ȡ����;֧�ֶ��ֶ��ء�
/*�Ĵ�����ȡ����*/
#define	ADS1292R_RREG	        		0X20	//��ȡ001r rrrr 000n nnnn  ���ﶨ���ֻ�и߰�λ����8λ�ڷ�������ʱ����
#define ADS1292R_WREG	        		0X40	//д��010r rrrr 000n nnnn
/*	r rrrr=Ҫ����д�ļĴ�����ַ
		n nnnn=Ҫ����д������		*/
/*ADS1292R�ڲ��Ĵ�����ַ����	*/
#define ADS1292R_ID								0X00	//ID���ƼĴ���
#define ADS1292R_CONFIG1					0X01	//���üĴ���1
#define ADS1292R_CONFIG2					0X02	//���üĴ���2
#define ADS1292R_LOFF							0X03	//����������ƼĴ���
#define ADS1292R_CH1SET						0X04	//ͨ��1���üĴ���
#define ADS1292R_CH2SET						0X05	//ͨ��2���üĴ���
#define ADS1292R_RLD_SENS					0X06	//��������ѡ��Ĵ���
#define ADS1292R_LOFF_SENS				0X07	//����������ѡ��Ĵ���
#define ADS1292R_LOFF_STAT				0X08	//����������״̬�Ĵ���
#define	ADS1292R_RESP1						0X09	//���������ƼĴ���1
#define	ADS1292R_RESP2						0X0A	//���������ƼĴ���2
#define	ADS1292R_GPIO							0X0B	//GPIO���ƼĴ���

extern uint8_t ads1292r_data_buff[];
extern SPI_HandleTypeDef SPI5_Handler; 
extern uint8_t ads1292_recive_flag;	//���ݶ�ȡ��ɱ�־
extern uint8_t device_id;

extern uint8_t ads1292_Cache[9] ; //���ݻ�����
extern uint8_t temp1292r[9];

extern uint8_t Flag_HALF_Full;
extern float32_t filter_result[1000];
extern float32_t Process_Data[2048];
extern float32_t filter_Highpass[1000];
extern float32_t filter_Lowpass[1000];
extern float32_t ban_data[1000];
extern float32_t Half_data[500];
extern float32_t Full_data[500];
extern uint8_t flag_filter_begin;
extern  uint8_t Flag_Store;

extern float32_t Store_Data_1[512];
extern float32_t Store_Data_2[512];
extern float32_t Get_Data[512];


void AD1292_Init(void); //��ʼ��ADS1292����
void AD1292_PowerOnInit(void);//�ϵ��ʼ��
uint8_t ADS1292R_SPI_RW(uint8_t data);
void ADS1292R_CMD(uint8_t cmd);
void ADS1292R_Work(void);
void ADS1292R_Halt(void);
void ADS1292R_ReadData(void);
uint8_t ADS1292R_REG(uint8_t cmd, uint8_t data);	
uint32_t data_han1(void);
uint32_t data_han2();
int uhexTodec(uint32_t dataIn);
float32_t Data_Filter_DT(float32_t DT_data);
void Data_Filter_HD(void);
void Data_Filter_Medium(void);
void Data_Store(void);
void Heart_Rate_Cal(void);
void Data_Filter_HighPass(void);
#endif


//�ֲἰ��̳���ϣ�
//����CLK����ʹ���ڲ�ʱ�ӻ���ʹ���ⲿʱ�ӣ����ʹ���ڲ�ʱ�ӣ����Խ���ӵء����ʹ���ⲿʱ�ӣ����Խ���Դ�������MCU��ʱ��������Ÿ�ADS1292 �ṩʱ�ӡ�
//ʹ���ڲ�����Ļ����Ĵ���CONFIG2��bit3 �������Ϊ1�Ļ�����ôCLK�������Ƶ�ʼ�Ϊ�ڲ�ʱ�Ӳ�����Ƶ�ʣ��������Ϊ0�Ļ�����ôCLK���disable
//SCLK ��ΪSPI��Ƶ�ʣ����Ĵ�Сdatasheet�Ѿ���������2.7 V �� DVDD �� 3.6 V������tSCLK��min��=50ns�� ��1.7 V �� DVDD �� 2 Vʱ��tSCLK��min��=66.6ns

//1. ��������ģʽ�£����ܶ�д�Ĵ�������������ģʽ�£�����Ҫ������ֹͣ SDATAC ��Ȼ����ܷ����������
//2. �ֲ���������������1292 ���ն��ֽ�����ʱ������һ���ֽ���Ҫ 7.2us������㷢�Ͷ��ֽ�����ʱ�������ֽ�֮��ļ������Ҫ��8us
//��������
//	���� CLKSEL =1 	ʹ���ڲ�ʱ�ӣ�
//	���� PWDN/RESET = 1  �ȴ�1�� ������λ�͵ȴ�����
//	����SDATAC����  ���üĴ���
//	����WREG CONFIG2 A0h	ʹ���ڲ��ο���ѹ��
//	����START = 1		����ת��
//	����RDATAC����	���豸�ָ���RDATACģʽ
//	�������ݲ��������
//	�������ݲ������ź�

