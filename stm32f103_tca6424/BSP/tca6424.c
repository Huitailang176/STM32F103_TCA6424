#include "tca6424.h"
#include "usart.h"
static void tca6424_reg_read(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{

    HAL_I2C_Mem_Read(TCA6424A_I2C, addr, reg,
                     1, data, len, TCA6424_I2C_TIMEOUT);
}

static void tca6424_reg_write(uint8_t addr, uint8_t reg, uint8_t data)
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

    tca6424_reg_write(TCA6424A_ADDR_LOW, TCA6424A_RA_CONFIG0, 0xFF);
    tca6424_reg_write(TCA6424A_ADDR_LOW, TCA6424A_RA_CONFIG1, 0xFF);
    tca6424_reg_write(TCA6424A_ADDR_LOW, TCA6424A_RA_CONFIG2, 0xFF);
    tca6424_reg_write(TCA6424A_ADDR_LOW, TCA6424A_RA_POLARITY0, 0x00);
    tca6424_reg_write(TCA6424A_ADDR_LOW, TCA6424A_RA_POLARITY1, 0x00);
    tca6424_reg_write(TCA6424A_ADDR_LOW, TCA6424A_RA_POLARITY2, 0x00);

    tca6424_reg_write(TCA6424A_ADDR_HIGH, TCA6424A_RA_CONFIG0, 0xFF);
    tca6424_reg_write(TCA6424A_ADDR_HIGH, TCA6424A_RA_CONFIG1, 0xFF);
    tca6424_reg_write(TCA6424A_ADDR_HIGH, TCA6424A_RA_CONFIG2, 0xFF);
    tca6424_reg_write(TCA6424A_ADDR_HIGH, TCA6424A_RA_POLARITY0, 0x00);
    tca6424_reg_write(TCA6424A_ADDR_HIGH, TCA6424A_RA_POLARITY1, 0x00);
    tca6424_reg_write(TCA6424A_ADDR_HIGH, TCA6424A_RA_POLARITY2, 0x00);
}



void read_tca6424_port(tca6424_t *Device)
{

    tca6424_reg_read(TCA6424A_ADDR_LOW, TCA6424A_RA_INPUT0, &Device->Port0, 1);
    tca6424_reg_read(TCA6424A_ADDR_LOW, TCA6424A_RA_INPUT1, &Device->Port1, 1);
    tca6424_reg_read(TCA6424A_ADDR_LOW, TCA6424A_RA_INPUT2, &Device->Port2, 1);

    Device->p00 = Device->Port0 & 0x01;
    Device->p01 = (Device->Port0 & 0x02) >> 1;
    Device->p02 = (Device->Port0 & 0x04) >> 2;
    Device->p03 = (Device->Port0 & 0x08) >> 3;
    Device->p04 = (Device->Port0 & 0x10) >> 4;
    Device->p05 = (Device->Port0 & 0x20) >> 5;
    Device->p06 = (Device->Port0 & 0x40) >> 6;
    Device->p07 = (Device->Port0 & 0x80) >> 7;
    Device->p10 = Device->Port1 & 0x01;
    Device->p11 = (Device->Port1 & 0x02) >> 1;
    Device->p12 = (Device->Port1 & 0x04) >> 2;
    Device->p13 = (Device->Port1 & 0x08) >> 3;
    Device->p14 = (Device->Port1 & 0x10) >> 4;
    Device->p15 = (Device->Port1 & 0x20) >> 5;
    Device->p16 = (Device->Port1 & 0x40) >> 6;
    Device->p17 = (Device->Port1 & 0x80) >> 7;
    Device->p20 = Device->Port2 & 0x01;
    Device->p21 = (Device->Port2 & 0x02) >> 1;
    Device->p22 = (Device->Port2 & 0x04) >> 2;
    Device->p23 = (Device->Port2 & 0x08) >> 3;
    Device->p24 = (Device->Port2 & 0x10) >> 4;
    Device->p25 = (Device->Port2 & 0x20) >> 5;
    Device->p26 = (Device->Port2 & 0x40) >> 6;
    Device->p27 = (Device->Port2 & 0x80) >> 7;
}

tca6424_t DeviceA;
tca6424_t DeviceB;
uint32_t debug_tick = 0;
void debug_loop(void)
{
    if ((HAL_GetTick() - debug_tick) > 100)
    {
        read_tca6424_port(&DeviceA);
        read_tca6424_port(&DeviceB);
		debug_tx1("A_P00=%d,A_P01=%d,A_P02=%d,A_P03=%d,A_P04=%d,A_P05=%d,A_P06=%d,A_P07=%d\n",\
			DeviceA.p00,DeviceA.p01,DeviceA.p02,DeviceA.p03,DeviceA.p04,DeviceA.p05,DeviceA.p06,DeviceA.p07);
        debug_tx1("A_P10=%d,A_P11=%d,A_P12=%d,A_P13=%d,A_P14=%d,A_P15=%d,A_P16=%d,A_P17=%d\n",\
			DeviceA.p10,DeviceA.p11,DeviceA.p12,DeviceA.p13,DeviceA.p14,DeviceA.p15,DeviceA.p16,DeviceA.p17);
        debug_tx1("A_P20=%d,A_P21=%d,A_P22=%d,A_P23=%d,A_P24=%d,A_P25=%d,A_P26=%d,A_P27=%d\n",\
            DeviceA.p20,DeviceA.p21,DeviceA.p22,DeviceA.p23,DeviceA.p24,DeviceA.p25,DeviceA.p26,DeviceA.p27);
        debug_tx1("B_P00=%d,B_P01=%d,B_P02=%d,B_P03=%d,B_P04=%d,B_P05=%d,B_P06=%d,B_P07=%d\n",\
            DeviceB.p00,DeviceB.p01,DeviceB.p02,DeviceB.p03,DeviceB.p04,DeviceB.p05,DeviceB.p06,DeviceB.p07);
        debug_tx1("B_P10=%d,B_P11=%d,B_P12=%d,B_P13=%d,B_P14=%d,B_P15=%d,B_P16=%d,B_P17=%d\n",\
            DeviceB.p10,DeviceB.p11,DeviceB.p12,DeviceB.p13,DeviceB.p14,DeviceB.p15,DeviceB.p16,DeviceB.p17);
        debug_tx1("B_P20=%d,B_P21=%d,B_P22=%d,B_P23=%d,B_P24=%d,B_P25=%d,B_P26=%d,B_P27=%d\n",\
            DeviceB.p20,DeviceB.p21,DeviceB.p22,DeviceB.p23,DeviceB.p24,DeviceB.p25,DeviceB.p26,DeviceB.p27);
        debug_tx1("\r\n");

        debug_tick = HAL_GetTick();
    }
}
