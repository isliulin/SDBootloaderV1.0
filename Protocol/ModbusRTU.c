#include "main.h"


u8 auchCRCHi[]=
{
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40

};

u8 auchCRCLo[] =
{
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
0x40
}; 

u16 CRC16(u8 * _data_buf,u16 len)
{
	u8 uchCRCHi=0xff;
	u8 uchCRCLo=0xff;
	u16 uindex;
	while(len--){
		uindex = uchCRCHi^ *_data_buf++;
		uchCRCHi = uchCRCLo^auchCRCHi[uindex];
		uchCRCLo = auchCRCLo[uindex];
	}
	return (uchCRCHi<<8|uchCRCLo);
} 



///////////////////////////////////////////////////////////

u8 RS485_TX_BUFF[256];//���ͻ�����
u16 RS485_TX_CNT=0;//���ͼ�����

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Modbus�Ĵ����͵�Ƭ���Ĵ�����ӳ���ϵ
static vu32 *Modbus_InputIO[MODBUS_INPUT_NUM];//���뿪�����Ĵ���ָ��(����ʹ�õ���λ������)
vu32 *Modbus_OutputIO[MODBUS_OUTPUT_NUM];//����������Ĵ���ָ��(����ʹ�õ���λ������)
u16 *Modbus_HoldReg[MODBUS_REG_NUM];//���ּĴ���

vu32 virtual_input[MODBUS_VIRTUAL_INPUT_NUM];

#define MAP_MODBUS_INPUT(D,PORT,S) Modbus_InputIO[D]=(vu32*)&P##PORT##in(S)
#define MAP_MODBUS_OUTPUT(D,PORT,S) Modbus_OutputIO[D]=(vu32*)&P##PORT##out(S)
#define MAP_MODBUS_HOLDREG(D,V) {Modbus_HoldReg[D] = &V;}

U16 Modbus_HoldReg_CPU_Usage = 0;
U16 Modbus_HoldReg_NULL = 0xFFFF;
U16 Modbus_com_error = 0;
U16 data_change_flag = 0;

void Modbus_RegMap(void) 
{
	int i;
	//���뿪�����Ĵ���ָ��ָ��
	MAP_MODBUS_INPUT (0, C, 6);
	MAP_MODBUS_INPUT (1, C, 7);
	MAP_MODBUS_INPUT (2, A, 8);
	MAP_MODBUS_INPUT (3, G, 11);
	MAP_MODBUS_INPUT (4, G, 0);
	MAP_MODBUS_INPUT (5, G, 1);
	MAP_MODBUS_INPUT (6, G, 2);
	MAP_MODBUS_INPUT (7, G, 3);
//	Modbus_InputIO[0]=(vu32*)&PCin(6);//KEY0
      
	//����������Ĵ���ָ��ָ��
	MAP_MODBUS_OUTPUT (0, F, 0);
	MAP_MODBUS_OUTPUT (1, F, 1);
	MAP_MODBUS_OUTPUT (2, F, 2);
	MAP_MODBUS_OUTPUT (3, F, 3);
	MAP_MODBUS_OUTPUT (4, F, 4);
	MAP_MODBUS_OUTPUT (5, F, 5);
	MAP_MODBUS_OUTPUT (6, F, 6);
	MAP_MODBUS_OUTPUT (7, F, 7);
	MAP_MODBUS_OUTPUT (8, F, 8);
	MAP_MODBUS_OUTPUT (9, F, 9);
	MAP_MODBUS_OUTPUT (10, F, 10);
	MAP_MODBUS_OUTPUT (11, F, 11);
	MAP_MODBUS_OUTPUT (12, F, 12);
	MAP_MODBUS_OUTPUT (13, F, 13);
	MAP_MODBUS_OUTPUT (14, F, 14);
	MAP_MODBUS_OUTPUT (15, F, 15);
	MAP_MODBUS_OUTPUT (16, E, 3);
	MAP_MODBUS_OUTPUT (17, E, 4);
	MAP_MODBUS_OUTPUT (18, E, 5);
	MAP_MODBUS_OUTPUT (19, E, 6);
//	Modbus_OutputIO[0]=(vu32*)&PFout(0);//LED0
	for (i = 0; i < MODBUS_VIRTUAL_INPUT_NUM; i++){
		virtual_input[i] = 1;
		Modbus_OutputIO[20 + i] = &virtual_input[i];
	}
       
	//��ʼ�����ּĴ���ָ��ָ��
	for (i = 0; i < MODBUS_REG_NUM; i++){
		Modbus_HoldReg[i] = &Modbus_HoldReg_NULL;
	}	
//	MAP_MODBUS_HOLDREG(0, OSCPUUsage);
	MAP_MODBUS_HOLDREG(14, tim2_irq_cycle);
	
	MAP_MODBUS_HOLDREG(21, Modbus_com_error);
	
	MAP_MODBUS_HOLDREG(29, Modbus_HoldReg_CPU_Usage);
	
	save_para (0); //save_para(1) �������save_para(0) ��ȡ����
	Modbus_HoldReg_NULL = 0xFFFF;
}

int save_para (int flag)
{
	int i;
	s_modbus_save_data *p_buf = NULL;
	
	FATFS *fs = NULL;
	FIL *file = NULL;
	FRESULT Res;
	unsigned int ByteWrite, ByteRead;

	if (flag == 1){
		if (data_change_flag == 0)
			return 0;
		else
			data_change_flag = 0;
	}
	
	fs = malloc (sizeof (FATFS));
	if (fs == NULL){
		my_println ("malloc (sizeof (FATFS)) failed!");
		return -1;
	}
	
	Res = f_mount(fs, "1:", 1);	
	if(Res == FR_NO_FILESYSTEM)//FLASH����,FAT�ļ�ϵͳ����,���¸�ʽ��FLASH
	{
		Res=f_mkfs("1:",1, 4096);//��ʽ��FLASH,1,�̷�;1,����Ҫ������,8������Ϊ1����
		if(Res == FR_OK){
			f_setlabel((const TCHAR *)"1:COUNTER");	//����Flash���̵�����Ϊ��COUNTER
			my_println("Flash Disk Format Finish");	//��ʽ�����
		}else{
			my_println("Flash Disk Format Error ");	//��ʽ��ʧ��
		}
	}	
	
	if (Res != FR_OK){
		my_println ("f_mount disk \"1:\" failed!");
	}else{
		file = malloc (sizeof (FIL));
		if (file == NULL){
			my_println ("malloc (sizeof (FIL)) failed!");
		}else{
			if (flag){//�������
				Res =  f_open(file, "1:/para.p", FA_WRITE);
				if (Res != FR_OK){
					Res =  f_open(file, "1:/para.p", FA_WRITE | FA_CREATE_ALWAYS);
					if (Res != FR_OK) {
						my_println("Open file 1:/para.p failed, Res = %d", Res);	
					}
				}
				if (Res == FR_OK){
					p_buf = malloc (sizeof (s_modbus_save_data));
					if (p_buf != NULL){
						for (i = 0; i < MODBUS_SAVE_DATA_NUM; i++){
							p_buf->data[i] = *Modbus_HoldReg[MODBUS_SAVE_DATA_START + i];
						}
						
						Res = f_write(file, (unsigned char *)p_buf, sizeof(s_modbus_save_data), &ByteWrite);	
						if (Res != FR_OK) {
							my_println ("Write file error, Res = %d", Res);
						}else{
							my_println("Save para.p Complete, Total %d byte", ByteWrite);	
						}
						f_close(file);
					}else{
						my_println ("malloc (sizeof (s_modbus_save_data)) failed! save para abort!");
					}
				}
			}else{//��ȡ����
				Res =  f_open(file, "1:/para.p", FA_READ | FA_OPEN_EXISTING);
				if(Res == FR_OK){
					p_buf = malloc (sizeof (s_modbus_save_data));
					if (p_buf != NULL){
						Res = f_read(file, (unsigned char *)p_buf, sizeof(s_modbus_save_data), &ByteRead);
						if (Res != FR_OK) {
							my_println ("Read file error, Res = %d", Res);	
						}else{
							my_println("Read 1:/para.p Complete, Total %d byte", ByteRead);	
						}
						f_close(file);
						for (i = 0; i < MODBUS_SAVE_DATA_NUM; i++){
							*Modbus_HoldReg[MODBUS_SAVE_DATA_START + i] = p_buf->data[i];
						}
					}else{
						my_println ("malloc (sizeof (s_modbus_save_data)) failed! load para abort!");
					}
				}
			}
		}
	}
	
	if (p_buf != NULL)
		free (p_buf);
	if (fs != NULL)
		free (fs);
	if (file != NULL)
		free (file);
	return 0;
}

void modbus_init(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����GPIOB��GPIOF������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOG, ENABLE); 
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
	/*���ÿ⺯������ʼ��GPIOG*/
	GPIO_Init(GPIOG, &GPIO_InitStructure);			
	/* �ر�����led��	*/
	GPIO_SetBits(GPIOG, GPIO_Pin_8);
	
	RS485_TX_EN=0;//��������ģʽ  
	
	Modbus_RegMap ();
}
void Modbus_01_Solve(u8 * _data_buf);
void Modbus_02_Solve(u8 * _data_buf);
void Modbus_03_Solve(u8 * _data_buf);
void Modbus_05_Solve(u8 * _data_buf);
void Modbus_06_Solve(u8 * _data_buf);
void Modbus_15_Solve(u8 * _data_buf);
void Modbus_16_Solve(u8 * _data_buf);

//////////////////////////////////////////////////////////////////////////////
//����n���ֽ�����
//buff:�������׵�ַ
//len�����͵��ֽ���
void RS485_SendData(u8 *buff, u8 len)
{
	if (RS485_TX_BUFF[1] & 0x80){
		Modbus_com_error++;
	}
	RS485_TX_EN = 1;//�л�Ϊ����ģʽ
#if (MODBUS_RTU_USE_UART == 1)
	start_uart1_dma ((u32)RS485_TX_BUFF, len);
#endif
#if (MODBUS_RTU_USE_UART == 3)
	start_uart3_dma ((u32)RS485_TX_BUFF, len);
#endif
}

void modbus_analyze(u8 * _data_buf)
{
	u16 crc;
	u16 startRegAddr;
	if((_data_buf[1]==01)||(_data_buf[1]==02)||(_data_buf[1]==03)||(_data_buf[1]==05)||(_data_buf[1]==06)||(_data_buf[1]==15)||(_data_buf[1]==16))//��������ȷ
	{
		startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//��ȡ�Ĵ�����ʼ��ַ
		if(startRegAddr < 1000){//�Ĵ�����ַ�ڷ�Χ��
			crc = cmd_analyze.rec_buf[rec_count - 2] << 8 | cmd_analyze.rec_buf[rec_count - 1];
			if (crc == CRC16 (cmd_analyze.rec_buf, rec_count - 2)){//CRCУ����ȷ                           
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				switch(_data_buf[1])//���ݲ�ͬ�Ĺ�������д���
				{
					case 1:{//�����������
						Modbus_01_Solve(_data_buf);
						break;
					}
					case 2:{//�����뿪����
						Modbus_02_Solve(_data_buf);
						break;
					}
					case 03:{//������Ĵ���
						Modbus_03_Solve(_data_buf);
						break;
					}
					case 5:{//д�������������
						Modbus_05_Solve(_data_buf);
						break;
					}       
					case 06: {//д�����Ĵ���
						Modbus_06_Solve(_data_buf);
						break;
					}
					case 15:{//д������������
						Modbus_15_Solve(_data_buf);
						break;
					}    
					case 16:{ //д����Ĵ���
						Modbus_16_Solve(_data_buf);
						break;
					}		                               
				}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
			else//CRCУ�����
			{
				RS485_TX_BUFF[0]=_data_buf[0];
				RS485_TX_BUFF[1]=_data_buf[1]| 0x80;
				RS485_TX_BUFF[2]=0x04; //�쳣��
				RS485_SendData(RS485_TX_BUFF,3);
			}       
		}
		else//�Ĵ�����ַ������Χ
		{
			RS485_TX_BUFF[0]=_data_buf[0];
			RS485_TX_BUFF[1]=_data_buf[1]|0x80;
			RS485_TX_BUFF[2]=0x02; //�쳣��
			RS485_SendData(RS485_TX_BUFF,3);
		}                                               
	}
	else//���������
	{
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1]|0x80;
		RS485_TX_BUFF[2]=0x01; //�쳣��
		RS485_SendData(RS485_TX_BUFF,3);
	}
}


//Modbus������01�������
//�����������
void Modbus_01_Solve(u8 * _data_buf)
{
	u16 ByteNum;
	u16 i;
	u16 calCRC;
	u16 RegNum;
	u16 startRegAddr;
	
	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//��ȡ�Ĵ�����ʼ��ַ
	RegNum= (((u16)_data_buf[4])<<8)|_data_buf[5];//��ȡ�Ĵ�������
	if((startRegAddr+RegNum - 1)<MODBUS_OUTPUT_NUM)//�Ĵ�����ַ+�����ڷ�Χ��
	{
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1];
		ByteNum=RegNum/8;//�ֽ���
		if(RegNum%8) ByteNum+=1;//���λ���������������ֽ���+1
		RS485_TX_BUFF[2]=ByteNum;//����Ҫ��ȡ���ֽ���
		for(i=0;i<RegNum;i++)
		{
			if(i%8==0) RS485_TX_BUFF[3+i/8]=0x00; //���ֽڿ�ʼ
			RS485_TX_BUFF[3+i/8] >>= 1;//��λ�ȷ���
			RS485_TX_BUFF[3+i/8] |= ((*Modbus_OutputIO[startRegAddr+i])<<7)&0x80;
			if(i==RegNum-1)//���͵����һ��λ��
			{
				if(RegNum%8) RS485_TX_BUFF[3+i/8] >>= 8-(RegNum%8);//������һ���ֽڻ�����������ʣ��MSB���0
			}
		}
		calCRC=CRC16(RS485_TX_BUFF,ByteNum+3);
		RS485_TX_BUFF[ByteNum+3]=(calCRC>>8)&0xFF;
		RS485_TX_BUFF[ByteNum+4]=calCRC&0xFF;
		RS485_SendData(RS485_TX_BUFF,ByteNum+5);
	}
	else//�Ĵ�����ַ+����������Χ
	{
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1]|0x80;
		RS485_TX_BUFF[2]=0x02; //�쳣��
		RS485_SendData(RS485_TX_BUFF,3);
	}
}


//Modbus������02�������
//�����뿪����
void Modbus_02_Solve(u8 * _data_buf)
{
	u16 ByteNum;
	u16 i;
	u16 calCRC;
	u16 RegNum;
	u16 startRegAddr;
	
	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//��ȡ�Ĵ�����ʼ��ַ
	RegNum= (((u16)_data_buf[4])<<8)|_data_buf[5];//��ȡ�Ĵ�������
	if((startRegAddr+RegNum - 1)<MODBUS_INPUT_NUM)//�Ĵ�����ַ+�����ڷ�Χ��
	{
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1];
		ByteNum=RegNum/8;//�ֽ���
		if(RegNum%8) ByteNum+=1;//���λ���������������ֽ���+1
		RS485_TX_BUFF[2]=ByteNum;//����Ҫ��ȡ���ֽ���
		for(i=0;i<RegNum;i++)
		{
			if(i%8==0) RS485_TX_BUFF[3+i/8]=0x00;
			RS485_TX_BUFF[3+i/8]>>=1;//��λ�ȷ���
			RS485_TX_BUFF[3+i/8]|=((*Modbus_InputIO[startRegAddr+i])<<7)&0x80;
			if(i==RegNum-1)//���͵����һ��λ��
			{
				if(RegNum%8) RS485_TX_BUFF[3+i/8]>>=8-(RegNum%8);//������һ���ֽڻ�����������ʣ��MSB���0
			}
		}
		calCRC=CRC16(RS485_TX_BUFF,ByteNum+3);
		RS485_TX_BUFF[ByteNum+3]=(calCRC>>8)&0xFF;
		RS485_TX_BUFF[ByteNum+4]=calCRC&0xFF;
		RS485_SendData(RS485_TX_BUFF,ByteNum+5);
	}
	else//�Ĵ�����ַ+����������Χ
	{
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1]|0x80;
		RS485_TX_BUFF[2]=0x02; //�쳣��
		RS485_SendData(RS485_TX_BUFF,3);
	}
}


//Modbus������03�������
//�����ּĴ���
void Modbus_03_Solve(u8 * _data_buf)
{
	u8 i;
	u16 calCRC;
	u16 RegNum;
	u16 startRegAddr;
	
	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//��ȡ�Ĵ�����ʼ��ַ
	RegNum= (((u16)_data_buf[4])<<8)|_data_buf[5];//��ȡ�Ĵ�������
	if((startRegAddr+RegNum - 1)<MODBUS_REG_NUM)//�Ĵ�����ַ+�����ڷ�Χ��
	{
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1];
		RS485_TX_BUFF[2]=RegNum * 2;
		for(i=0;i<RegNum;i++)
		{
			RS485_TX_BUFF[3+i*2] = (*Modbus_HoldReg[startRegAddr+i] >> 8) & 0xFF; //�ȷ��͸��ֽ�
			RS485_TX_BUFF[4+i*2] = *Modbus_HoldReg[startRegAddr+i] & 0xFF;//���͵��ֽ�
		}
		calCRC=CRC16(RS485_TX_BUFF,RegNum*2+3);
		
        RS485_TX_BUFF[RegNum*2+3]=(calCRC>>8)&0xFF;
        RS485_TX_BUFF[RegNum*2+4]=calCRC&0xFF;
		RS485_SendData(RS485_TX_BUFF,RegNum*2+5);
	}
	else//�Ĵ�����ַ+����������Χ
	{
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1]|0x80;
		RS485_TX_BUFF[2]=0x02; //�쳣��
		RS485_SendData(RS485_TX_BUFF,3);
	}
}



//Modbus������05�������
//д�������������
void Modbus_05_Solve(u8 * _data_buf)
{
	u16 calCRC;
	u16 startRegAddr;
	
	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//��ȡ�Ĵ�����ʼ��ַ
	if(startRegAddr < MODBUS_OUTPUT_NUM)//�Ĵ�����ַ�ڷ�Χ��
	{
		if((_data_buf[4]==0xFF)||(_data_buf[5]==0xFF)) *Modbus_OutputIO[startRegAddr]=0x01;
		else *Modbus_OutputIO[startRegAddr]=0x00;
               
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1];
		RS485_TX_BUFF[2]=_data_buf[2];
		RS485_TX_BUFF[3]=_data_buf[3];
		RS485_TX_BUFF[4]=_data_buf[4];
		RS485_TX_BUFF[5]=_data_buf[5];
               
		calCRC=CRC16(RS485_TX_BUFF,6);
		RS485_TX_BUFF[6]=(calCRC>>8)&0xFF;
		RS485_TX_BUFF[7]=calCRC&0xFF;
		RS485_SendData(RS485_TX_BUFF,8);
	}
	else//�Ĵ�����ַ������Χ
	{
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1]|0x80;
		RS485_TX_BUFF[2]=0x02; //�쳣��
		RS485_SendData(RS485_TX_BUFF,3);
	}
}

//Modbus������06�������
//д�������ּĴ���
void Modbus_06_Solve(u8 * _data_buf)
{
	u16 calCRC;
	u16 startRegAddr;
	
	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//��ȡ�Ĵ�����ʼ��ַ
	if(startRegAddr < MODBUS_REG_NUM)//�Ĵ�����ַ�ڷ�Χ��
	{
		*Modbus_HoldReg[startRegAddr] = ((u16)_data_buf[4]) << 8;//���ֽ���ǰ
		*Modbus_HoldReg[startRegAddr] |= _data_buf[5];//���ֽ��ں�
		if ((startRegAddr < MODBUS_SAVE_DATA_START + MODBUS_SAVE_DATA_NUM + 1) && (startRegAddr >= MODBUS_SAVE_DATA_START))
		{
			data_change_flag = 1;
			save_para (1); //save_para(1) �������save_para(0) ��ȡ����
		}
		   
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1];
		RS485_TX_BUFF[2]=_data_buf[2];
		RS485_TX_BUFF[3]=_data_buf[3];
		RS485_TX_BUFF[4]=_data_buf[4];
		RS485_TX_BUFF[5]=_data_buf[5];
		   
		calCRC=CRC16(RS485_TX_BUFF,6);
		RS485_TX_BUFF[6]=(calCRC>>8)&0xFF;
		RS485_TX_BUFF[7]=calCRC&0xFF;
		RS485_SendData(RS485_TX_BUFF,8);
	}
	else//�Ĵ�����ַ������Χ
	{
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1]|0x80;
		RS485_TX_BUFF[2]=0x02; //�쳣��
		RS485_SendData(RS485_TX_BUFF,3);
	}
}
//Modbus������15�������
//д������������
void Modbus_15_Solve(u8 * _data_buf)
{
	u16 i;
	u16 calCRC;
	u16 RegNum;
	u16 startRegAddr;
	
	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//��ȡ�Ĵ�����ʼ��ַ
	RegNum=(((u16)_data_buf[4])<<8)|_data_buf[5];//��ȡ�Ĵ�������
	if((startRegAddr+RegNum - 1)<MODBUS_OUTPUT_NUM)//�Ĵ�����ַ+�����ڷ�Χ��
	{       
		for(i=0;i<RegNum;i++)
		{
		        if(_data_buf[7+i/8]&0x01) *Modbus_OutputIO[startRegAddr+i]=0x01;
		        else *Modbus_OutputIO[startRegAddr+i]=0x00;
		        _data_buf[7+i/8]>>=1;//�ӵ�λ��ʼ
		}
               
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1];
		RS485_TX_BUFF[2]=_data_buf[2];
		RS485_TX_BUFF[3]=_data_buf[3];
		RS485_TX_BUFF[4]=_data_buf[4];
		RS485_TX_BUFF[5]=_data_buf[5];
		calCRC=CRC16(RS485_TX_BUFF,6);
		RS485_TX_BUFF[6]=(calCRC>>8)&0xFF;
		RS485_TX_BUFF[7]=calCRC&0xFF;
		RS485_SendData(RS485_TX_BUFF,8);
	}
	else//�Ĵ�����ַ+����������Χ
	{
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1]|0x80;
		RS485_TX_BUFF[2]=0x02; //�쳣��
		RS485_SendData(RS485_TX_BUFF,3);
	}
}
//Modbus������16�������
//д������ּĴ���
void Modbus_16_Solve(u8 * _data_buf)
{
	u8 i;
	u16 calCRC;
	u16 RegNum;
	u16 startRegAddr;
	
	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//��ȡ�Ĵ�����ʼ��ַ
	RegNum= (((u16)_data_buf[4])<<8)|_data_buf[5];//��ȡ�Ĵ�������
	if((startRegAddr+RegNum - 1)<MODBUS_REG_NUM)//�Ĵ�����ַ+�����ڷ�Χ��
	{
		for(i=0;i<RegNum;i++)
		{
			*Modbus_HoldReg[startRegAddr+i]=((u16)_data_buf[7+i*2])<<8; //���ֽ���ǰ
			*Modbus_HoldReg[startRegAddr+i]|=_data_buf[8+i*2]; //���ֽ��ں�
			if ((startRegAddr+i < MODBUS_SAVE_DATA_START + MODBUS_SAVE_DATA_NUM + 1) && (startRegAddr+i >= MODBUS_SAVE_DATA_START))
			{
				data_change_flag = 1;
			}
		}
		if (data_change_flag == 1){
			save_para (1); //save_para(1) �������save_para(0) ��ȡ����
		}
               
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1];
		RS485_TX_BUFF[2]=_data_buf[2];
		RS485_TX_BUFF[3]=_data_buf[3];
		RS485_TX_BUFF[4]=_data_buf[4];
		RS485_TX_BUFF[5]=_data_buf[5];
               
		calCRC=CRC16(RS485_TX_BUFF,6);
		RS485_TX_BUFF[6]=(calCRC>>8)&0xFF;
		RS485_TX_BUFF[7]=calCRC&0xFF;
		RS485_SendData(RS485_TX_BUFF,8);
		
		data_change_flag = 1;
	}
	else//�Ĵ�����ַ+����������Χ
	{
		RS485_TX_BUFF[0]=_data_buf[0];
		RS485_TX_BUFF[1]=_data_buf[1]|0x80;
		RS485_TX_BUFF[2]=0x02; //�쳣��
		RS485_SendData(RS485_TX_BUFF,3);
	}
}

void HardFault_Handler (void)
{
	while (1);
}










