#include "tca6424.h"
#include "usart.h"
static void tca6424_reg_read(uint8_t addr,uint8_t reg,uint8_t* data,uint8_t len) 
{

    HAL_I2C_Mem_Read(TCA6424A_I2C, addr, reg,
                     1, data, len, TCA6424_I2C_TIMEOUT);
}

static void tca6424_reg_write(uint8_t addr,uint8_t reg, uint8_t data) 
{
    uint8_t tmp;
	tmp = data;
    HAL_I2C_Mem_Write(TCA6424A_I2C, addr, reg,
                      1, &tmp, 1, TCA6424_I2C_TIMEOUT);
}
 
void tca6424_init(void)
{
	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET);
	
	tca6424_reg_write(TCA6424A_ADDR_LOW,TCA6424A_RA_CONFIG0,0xFF);
	tca6424_reg_write(TCA6424A_ADDR_LOW,TCA6424A_RA_CONFIG1,0xFF);
	tca6424_reg_write(TCA6424A_ADDR_LOW,TCA6424A_RA_CONFIG2,0xFF);
	tca6424_reg_write(TCA6424A_ADDR_LOW,TCA6424A_RA_POLARITY0,0x00);
	tca6424_reg_write(TCA6424A_ADDR_LOW,TCA6424A_RA_POLARITY1,0x00);
	tca6424_reg_write(TCA6424A_ADDR_LOW,TCA6424A_RA_POLARITY2,0x00);	
	
	tca6424_reg_write(TCA6424A_ADDR_HIGH,TCA6424A_RA_CONFIG0,0xFF);
	tca6424_reg_write(TCA6424A_ADDR_HIGH,TCA6424A_RA_CONFIG1,0xFF);
	tca6424_reg_write(TCA6424A_ADDR_HIGH,TCA6424A_RA_CONFIG2,0xFF);
	tca6424_reg_write(TCA6424A_ADDR_HIGH,TCA6424A_RA_POLARITY0,0x00);
	tca6424_reg_write(TCA6424A_ADDR_HIGH,TCA6424A_RA_POLARITY1,0x00);
	tca6424_reg_write(TCA6424A_ADDR_HIGH,TCA6424A_RA_POLARITY2,0x00);
}
uint8_t SW_PORT0 = 0;
uint8_t SW_PORT1 = 0;
uint8_t SW_PORT2 = 0;
uint8_t KEY_PORT0 = 0;
uint8_t KEY_PORT1 = 0;
uint8_t KEY_PORT2 = 0;
tca6424_key_t Key;
tca6424_switch_t Switch;
tca6424_trim_t Trim;

void read_tca6424_key(void)
{

	tca6424_reg_read(TCA6424A_ADDR_LOW,TCA6424A_RA_INPUT0,&KEY_PORT0,1);
	tca6424_reg_read(TCA6424A_ADDR_LOW,TCA6424A_RA_INPUT1,&KEY_PORT1,1);
	tca6424_reg_read(TCA6424A_ADDR_LOW,TCA6424A_RA_INPUT2,&KEY_PORT2,1);
//		debug_tx1("PORT0 = %d\n",KEY_PORT0);
//		debug_tx1("PORT1 = %d\n",KEY_PORT1);
//		debug_tx1("PORT2 = %d\n",KEY_PORT2);
		           
    Trim.T4_R =  KEY_PORT0 & 0x01;
	Trim.T4_L = (KEY_PORT0 & 0x02) >> 1;
	Key.SYS = (KEY_PORT0 & 0x04) >> 2;
	Key.RTN = (KEY_PORT0 & 0x08) >> 3;	
	Key.PAGE_R = (KEY_PORT0 & 0x10) >> 4;
	Key.PAGE_L = (KEY_PORT0 & 0x20) >> 5;
	Key.TELE = (KEY_PORT0 & 0x40) >> 6;
	Key.MDL = (KEY_PORT0 & 0x80) >> 7;

	Key.ENTER =  KEY_PORT1 & 0x01;
	Key.k6 = (KEY_PORT1 & 0x20) >> 5;
	Key.k5 = (KEY_PORT1 & 0x40) >> 6;
	Key.k4 = (KEY_PORT1 & 0x80) >> 7;

    Key.k3 =  KEY_PORT2 & 0x01;
	Key.k2 = (KEY_PORT2 & 0x02) >> 1;
	Key.k1 = (KEY_PORT2 & 0x04) >> 2;
	Trim.T6_U = (KEY_PORT2 & 0x08) >> 3;	
	Trim.T6_D = (KEY_PORT2 & 0x10) >> 4;
	Trim.T3_U = (KEY_PORT2 & 0x20) >> 5;
	Trim.T3_D = (KEY_PORT2 & 0x40) >> 6;
	Switch.SI = (KEY_PORT2 & 0x80) >> 7;


}

void read_tca6424_switch(void)
{
	tca6424_reg_read(TCA6424A_ADDR_HIGH,TCA6424A_RA_INPUT0,&SW_PORT0,1);
	tca6424_reg_read(TCA6424A_ADDR_HIGH,TCA6424A_RA_INPUT1,&SW_PORT1,1);
	tca6424_reg_read(TCA6424A_ADDR_HIGH,TCA6424A_RA_INPUT2,&SW_PORT2,1);
//	debug_tx1("PORT0 = %d\n",SW_PORT0);
//	debug_tx1("PORT1 = %d\n",SW_PORT1);
//	debug_tx1("PORT2 = %d\n",SW_PORT2);
	
	Switch.SBL =  SW_PORT0 & 0x01;
	Switch.SBH = (SW_PORT0 & 0x02) >> 1;
	Switch.SAL = (SW_PORT0 & 0x04) >> 2;
	Switch.SAH = (SW_PORT0 & 0x08) >> 3;
	Switch.SFL = (SW_PORT0 & 0x10) >> 4;
	Switch.SFH = (SW_PORT0 & 0x20) >> 5;
	Switch.SEL = (SW_PORT0 & 0x40) >> 6;
	Switch.SEH = (SW_PORT0 & 0x80) >> 7;   
	Switch.SA = (Switch.SAL == 0 ? 1 : (Switch.SAH == 0 ? 3 : 2));
	Switch.SB = (Switch.SBL == 0 ? 1 : (Switch.SBH == 0 ? 3 : 2));
	Switch.SE = (Switch.SEL == 0 ? 1 : (Switch.SEH == 0 ? 3 : 2));
	Switch.SF = (Switch.SFL == 0 ? 1 : (Switch.SFH == 0 ? 3 : 2));


	Trim.T1_L = (SW_PORT1 & 0x02) >> 1;
	Trim.T1_R = (SW_PORT1 & 0x04) >> 2;
	Trim.T2_D = (SW_PORT1 & 0x08) >> 3;
	Trim.T2_U = (SW_PORT1 & 0x10) >> 4;
	Trim.T5_D = (SW_PORT1 & 0x20) >> 5;
	Trim.T5_U = (SW_PORT1 & 0x40) >> 6;
	Switch.SJ = (SW_PORT1 & 0x80) >> 7;   

	Switch.SHL =  SW_PORT2 & 0x01;
	Switch.SHH = (SW_PORT2 & 0x02) >> 1;
	Switch.SGL = (SW_PORT2 & 0x04) >> 2;
	Switch.SGH = (SW_PORT2 & 0x08) >> 3;
	Switch.SDL = (SW_PORT2 & 0x10) >> 4;
	Switch.SDH = (SW_PORT2 & 0x20) >> 5;
	Switch.SCL = (SW_PORT2 & 0x40) >> 6;
	Switch.SCH = (SW_PORT2 & 0x80) >> 7;   

	Switch.SC = (Switch.SCL == 0 ? 1 : (Switch.SCH == 0 ? 3 : 2));
	Switch.SD = (Switch.SDL == 0 ? 1 : (Switch.SDH == 0 ? 3 : 2));
	Switch.SG = (Switch.SGL == 0 ? 1 : (Switch.SGH == 0 ? 3 : 2));
	Switch.SH = (Switch.SHL == 0 ? 1 : (Switch.SHH == 0 ? 3 : 2));


}

uint32_t debug_tick = 0;
void debug_loop(void)
{
	if((HAL_GetTick() - debug_tick) > 150)
	{
		read_tca6424_key();
		read_tca6424_switch();
		debug_tx1("SYS= %d£¬RTN= %d£¬PAGE_R= %d£¬PAGE_L= %d£¬TELE= %d£¬MDL= %d,ENTER= %d\r\n",
				Key.SYS,Key.RTN,Key.PAGE_R,Key.PAGE_L,Key.TELE,Key.MDL,Key.ENTER);
		debug_tx1("k1= %d£¬k2= %d£¬k3= %d£¬k4= %d,k5= %d£¬k6= %d\n",Key.k1,Key.k2,Key.k3,Key.k4,Key.k5,Key.k6);
		debug_tx1("T1_L= %d£¬T1_R= %d£¬T2_D= %d£¬T2_U= %d£¬T3_U= %d£¬T3_D= %d£¬T4_R= %d\n",
					Trim.T1_L,Trim.T1_R,Trim.T2_D,Trim.T2_U,Trim.T3_U,Trim.T3_D,Trim.T4_R);
		debug_tx1("T4_L= %d£¬T5_D= %d£¬T5_U= %d£¬T6_U= %d£¬T6_D= %d£¬SI= %d,SJ= %d\r\n",
		          Trim.T4_L,Trim.T5_D,Trim.T5_U,Trim.T6_U,Trim.T6_D,Switch.SI,Switch.SJ);
		debug_tx1("\r\n");

		debug_tick =  HAL_GetTick();
	}
}