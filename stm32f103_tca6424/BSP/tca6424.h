#ifndef __TCA6424_H__
#define __TCA6424_H__

#include "main.h"
#include "i2c.h"
#ifdef __cplusplus
extern "C" {
#endif
#define TCA6424A_I2C  &hi2c1

//#define TCA6424A_ADDRESS_ADDR_LOW   0x22 // address pin low (GND)
//#define TCA6424A_ADDRESS_ADDR_HIGH  0x23 // address pin high (VCC)
#define TCA6424A_ADDR_LOW   (0x22<<1) // address pin low (GND)
#define TCA6424A_ADDR_HIGH  (0x23<<1) // address pin high (VCC)
#define TCA6424A_DEFAULT_ADDRESS    TCA6424A_ADDRESS_ADDR_LOW

#if 1
#define TCA6424A_RA_INPUT0          0x00
#define TCA6424A_RA_INPUT1          0x01
#define TCA6424A_RA_INPUT2          0x02
#define TCA6424A_RA_OUTPUT0         0x04
#define TCA6424A_RA_OUTPUT1         0x05
#define TCA6424A_RA_OUTPUT2         0x06
#define TCA6424A_RA_POLARITY0       0x08
#define TCA6424A_RA_POLARITY1       0x09
#define TCA6424A_RA_POLARITY2       0x0A
#define TCA6424A_RA_CONFIG0         0x0C
#define TCA6424A_RA_CONFIG1         0x0D
#define TCA6424A_RA_CONFIG2         0x0E
#else

#define TCA6424A_RA_INPUT0          0x80
#define TCA6424A_RA_INPUT1          0x81
#define TCA6424A_RA_INPUT2          0x82
#define TCA6424A_RA_OUTPUT0         0x84
#define TCA6424A_RA_OUTPUT1         0x85
#define TCA6424A_RA_OUTPUT2         0x86
#define TCA6424A_RA_POLARITY0       0x88
#define TCA6424A_RA_POLARITY1       0x89
#define TCA6424A_RA_POLARITY2       0x8A
#define TCA6424A_RA_CONFIG0         0x8C
#define TCA6424A_RA_CONFIG1         0x8D
#define TCA6424A_RA_CONFIG2         0x8E
#endif



#define TCA6424_I2C_TIMEOUT 		1000

typedef struct tca6424_s
{
    uint8_t Port0;
    uint8_t Port1;
    uint8_t Port2;
    uint8_t p00;
    uint8_t p01;
    uint8_t p02;
    uint8_t p03;
    uint8_t p04;
    uint8_t p05;
    uint8_t p06;
    uint8_t p07;
    uint8_t p10;
    uint8_t p11;
    uint8_t p12;
    uint8_t p13;
    uint8_t p14;
    uint8_t p15;
    uint8_t p16;
    uint8_t p17;
    uint8_t p20;
    uint8_t p21;
    uint8_t p22;
    uint8_t p23;
    uint8_t p24;
    uint8_t p25;
    uint8_t p26;
    uint8_t p27;

}tca6424_t;
extern tca6424_t DeviceA;
extern tca6424_t DeviceB;



void tca6424_init(void);
void debug_loop(void);
#ifdef __cplusplus
}
#endif
#endif //__TCA9539_H__
