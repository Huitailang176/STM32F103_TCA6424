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

#define TCA6424A_AUTO_INCREMENT     0x80

#define TCA6424A_LOW                0
#define TCA6424A_HIGH               1

#define TCA6424A_POLARITY_NORMAL    0
#define TCA6424A_POLARITY_INVERTED  1

#define TCA6424A_OUTPUT             0
#define TCA6424A_INPUT              1



#define TCA6424_I2C_TIMEOUT 		1000

typedef struct tca6424_key_s
{
	uint8_t k1;
    uint8_t k2;
    uint8_t k3;
    uint8_t k4;
    uint8_t k5;
    uint8_t k6;
	uint8_t SYS;
	uint8_t MDL;
	uint8_t RTN;
	uint8_t PAGE_L;
	uint8_t PAGE_R;
	uint8_t TELE;
	uint8_t ENTER;
}tca6424_key_t;
extern tca6424_key_t Key;

typedef struct tca6424_switch_s
{
	uint8_t SAL;
    uint8_t SAH;
    uint8_t SA;
    uint8_t SBL;
    uint8_t SBH;
    uint8_t SB;
    uint8_t SCL;
    uint8_t SCH;
    uint8_t SC;
    uint8_t SDL;
    uint8_t SDH;
    uint8_t SD;
	uint8_t SEL;
    uint8_t SEH;
    uint8_t SE;
    uint8_t SFL;
    uint8_t SFH;
    uint8_t SF;
	uint8_t SGL;
    uint8_t SGH;
    uint8_t SG;
	uint8_t SHL;
    uint8_t SHH;
    uint8_t SH;
	uint8_t SI;
	uint8_t SJ;
}tca6424_switch_t;
extern tca6424_switch_t Switch;

typedef struct tca6424_trim_s
{
    uint8_t T1_L; 
    uint8_t T1_R; 
    uint8_t T2_U; 
    uint8_t T2_D; 
    uint8_t T3_U; 
    uint8_t T3_D; 
    uint8_t T4_L; 
    uint8_t T4_R; 
	uint8_t T5_U; 
    uint8_t T5_D; 
    uint8_t T6_U; 
    uint8_t T6_D; 
} tca6424_trim_t;
extern tca6424_trim_t Trim;


void tca6424_init(void);
void debug_loop(void);
#ifdef __cplusplus
}
#endif
#endif //__TCA9539_H__
