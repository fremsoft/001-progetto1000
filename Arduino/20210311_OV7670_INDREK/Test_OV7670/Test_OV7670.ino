/*  INCLUDO LA LIBRERIA WIRE.H CHE SERVE AD UTILIZZARE 
 *  IL CANALE DI COMUNICAZIONE I2C SU PIN 20 e 21 SU
 *  ARDUINO MEGA
 */
#include <Wire.h>

/*  INDIRIZZO DELLA CHIP CAMERA OV7670 */
#define SCCB_ADDRESS  0x21
/*  7 PCLK - PH4  0001 0000  0x10
 *  8 HREF - PH5  0010 0000  0x20
 *  9 VREF - PH6  0100 0000  0x40
 **/
#define OV7670_PIXEL_CLOCK (PINH & 0b00010000)   // PIN 7
#define OV7670_HREF        (PINH & 0b00100000)   // PIN 8
#define OV7670_VSYNC       (PINH & 0b01000000)   // PIN 9
#ifndef OV7670_READ_PIXEL_BYTE
// PIN 22..29
// Add "nop" so the timing would be compatible with Uno/Nano
#define OV7670_READ_PIXEL_BYTE(b) \
                    b=PINC;\
                    asm volatile("nop");\
                    asm volatile("nop");\
                    asm volatile("nop");\
                    asm volatile("nop")
#endif

#define SCALE_FACTOR 4

/*
 * https://github.com/ComputerNerd/ov7670-no-ram-arduino-uno/blob/master/ov7670.h
 */

#define REG_GAIN      0x00  /* Gain lower 8 bits (rest in vref) */
#define REG_BLUE      0x01  /* blue gain */
#define REG_RED       0x02  /* red gain */
#define REG_VREF      0x03  /* Pieces of GAIN, VSTART, VSTOP */
#define REG_COM1      0x04  /* Control 1 */
#define COM1_CCIR656  0x40  /* CCIR656 enable */
#define REG_BAVE      0x05  /* U/B Average level */
#define REG_GbAVE 0x06  /* Y/Gb Average level */
#define REG_AECHH 0x07  /* AEC MS 5 bits */
#define REG_RAVE  0x08  /* V/R Average level */
#define REG_COM2  0x09  /* Control 2 */
#define COM2_SSLEEP 0x10  /* Soft sleep mode */
#define REG_PID   0x0a  /* Product ID MSB */
#define REG_VER   0x0b  /* Product ID LSB */
#define REG_COM3  0x0c  /* Control 3 */
#define COM3_SWAP 0x40  /* Byte swap */
#define COM3_SCALEEN  0x08  /* Enable scaling */
#define COM3_DCWEN  0x04  /* Enable downsamp/crop/window */
#define REG_COM4  0x0d  /* Control 4 */
#define REG_COM5  0x0e  /* All "reserved" */
#define REG_COM6  0x0f  /* Control 6 */
#define COM6_HREF_HB 0x80 /* Suppress PCLK on horiz blank */
#define REG_AECH  0x10  /* More bits of AEC value */
#define REG_CLKRC 0x11  /* Clocl control */
#define CLK_EXT   0x40  /* Use external clock directly */
#define CLK_SCALE 0x3f  /* Mask for internal clock scale */
#define REG_COM7  0x12  /* Control 7 */
#define COM7_RESET  0x80  /* Register reset */
#define COM7_FMT_MASK 0x38
#define COM7_FMT_VGA  0x00
#define COM7_FMT_CIF  0x20  /* CIF format */
#define COM7_FMT_QVGA 0x10  /* QVGA format */
#define COM7_FMT_QCIF 0x08  /* QCIF format */
#define COM7_RGB  0x04  /* bits 0 and 2 - RGB format */
#define COM7_YUV  0x00  /* YUV */
#define COM7_BAYER  0x01  /* Bayer format */
#define COM7_COLOR_BAR  0x02  /* transpartent color bar overlay */
#define COM7_PBAYER 0x05  /* "Processed bayer" */
#define REG_COM8  0x13  /* Control 8 */
#define COM8_FASTAEC  0x80  /* Enable fast AGC/AEC */
#define COM8_AECSTEP  0x40  /* Unlimited AEC step size */
#define COM8_BFILT  0x20  /* Band filter enable */
#define COM8_AGC  0x04  /* Auto gain enable */
#define COM8_AWB  0x02  /* White balance enable */
#define COM8_AEC  0x01  /* Auto exposure enable */
#define REG_COM9  0x14  /* Control 9- gain ceiling */
#define REG_COM10 0x15  /* Control 10 */
#define COM10_HSYNC 0x40  /* HSYNC instead of HREF */
#define COM10_PCLK_HB 0x20  /* Suppress PCLK on horiz blank */
#define COM10_PCLK_REV  0x10  /* Reverse PCLK */
#define COM10_HREF_REV  0x08  /* Reverse HREF */
#define COM10_VS_LEAD 0x04  /* VSYNC on clock leading edge */
#define COM10_VS_NEG  0x02  /* VSYNC negative */
#define COM10_HS_NEG  0x01  /* HSYNC negative */
#define REG_HSTART  0x17  /* Horiz start high bits */
#define REG_HSTOP 0x18  /* Horiz stop high bits */
#define REG_VSTART  0x19  /* Vert start high bits */
#define REG_VSTOP 0x1a  /* Vert stop high bits */
#define REG_PSHFT 0x1b  /* Pixel delay after HREF */
#define REG_MIDH  0x1c  /* Manuf. ID high */
#define REG_MIDL  0x1d  /* Manuf. ID low */
#define REG_MVFP  0x1e  /* Mirror / vflip */
#define MVFP_MIRROR 0x20  /* Mirror image */
#define MVFP_FLIP 0x10  /* Vertical flip */

#define REG_AEW   0x24  /* AGC upper limit */
#define REG_AEB   0x25  /* AGC lower limit */
#define REG_VPT   0x26  /* AGC/AEC fast mode op region */
#define REG_HSYST 0x30  /* HSYNC rising edge delay */
#define REG_HSYEN 0x31  /* HSYNC falling edge delay */
#define REG_HREF  0x32  /* HREF pieces */
#define REG_TSLB  0x3a  /* lots of stuff */
#define TSLB_YLAST  0x04  /* UYVY or VYUY - see com13 */
#define REG_COM11 0x3b  /* Control 11 */
#define COM11_NIGHT 0x80  /* NIght mode enable */
#define COM11_NMFR  0x60  /* Two bit NM frame rate */
#define COM11_HZAUTO  0x10  /* Auto detect 50/60 Hz */
#define COM11_50HZ  0x08  /* Manual 50Hz select */
#define COM11_EXP 0x02
#define REG_COM12 0x3c  /* Control 12 */
#define COM12_HREF  0x80  /* HREF always */
#define REG_COM13 0x3d  /* Control 13 */
#define COM13_GAMMA 0x80  /* Gamma enable */
#define COM13_UVSAT 0x40  /* UV saturation auto adjustment */
#define COM13_UVSWAP  0x01  /* V before U - w/TSLB */
#define REG_COM14 0x3e  /* Control 14 */
#define COM14_DCWEN 0x10  /* DCW/PCLK-scale enable */
#define REG_EDGE  0x3f  /* Edge enhancement factor */
#define REG_COM15 0x40  /* Control 15 */
#define COM15_R10F0 0x00  /* Data range 10 to F0 */
#define COM15_R01FE 0x80  /*      01 to FE */
#define COM15_R00FF 0xc0  /*      00 to FF */
#define COM15_RGB565  0x10  /* RGB565 output */
#define COM15_RGB555  0x30  /* RGB555 output */
#define REG_COM16 0x41  /* Control 16 */
#define COM16_AWBGAIN 0x08  /* AWB gain enable */
#define REG_COM17 0x42  /* Control 17 */
#define COM17_AECWIN  0xc0  /* AEC window - must match COM4 */
#define COM17_CBAR  0x08  /* DSP Color bar */
/*
 * This matrix defines how the colors are generated, must be
 * tweaked to adjust hue and saturation.
 *
 * Order: v-red, v-green, v-blue, u-red, u-green, u-blue
 * They are nine-bit signed quantities, with the sign bit
 * stored in0x58.Sign for v-red is bit 0, and up from there.
 */
#define REG_CMATRIX_BASE0x4f
#define CMATRIX_LEN 6
#define REG_CMATRIX_SIGN0x58
#define REG_BRIGHT  0x55  /* Brightness */
#define REG_CONTRAS 0x56  /* Contrast control */
#define REG_CONTRAST_CENTER 0x57  /* Contrast center */
#define REG_GFIX  0x69  /* Fix gain control */
#define REG_REG76 0x76  /* OV's name */
#define R76_BLKPCOR 0x80  /* Black pixel correction enable */
#define R76_WHTPCOR 0x40  /* White pixel correction enable */
#define REG_RGB444  0x8c  /* RGB 444 control */
#define R444_ENABLE 0x02  /* Turn on RGB444, overrides 5x5 */
#define R444_RGBX 0x01  /* Empty nibble at end */
#define REG_HAECC1  0x9f  /* Hist AEC/AGC control 1 */
#define REG_HAECC2  0xa0  /* Hist AEC/AGC control 2 */
#define REG_BD50MAX 0xa5  /* 50hz banding step limit */
#define REG_HAECC3  0xa6  /* Hist AEC/AGC control 3 */
#define REG_HAECC4  0xa7  /* Hist AEC/AGC control 4 */
#define REG_HAECC5  0xa8  /* Hist AEC/AGC control 5 */
#define REG_HAECC6  0xa9  /* Hist AEC/AGC control 6 */
#define REG_HAECC7  0xaa  /* Hist AEC/AGC control 7 */
#define REG_BD60MAX 0xab  /* 60hz banding step limit */
#define COM7_FMT_CIF  0x20  /* CIF format */
#define COM7_RGB  0x04  /* bits 0 and 2 - RGB format */
#define COM7_YUV  0x00  /* YUV */
#define COM7_BAYER  0x01  /* Bayer format */
#define COM7_PBAYER 0x05  /* "Processed bayer" */
#define COM10_VS_LEAD   0x04  /* VSYNC on clock leading edge */
#define COM11_50HZ  0x08  /* Manual 50Hz select */
#define COM13_UVSAT 0x40  /* UV saturation auto adjustment */
#define COM15_R01FE 0x80  /*      01 to FE */
#define MTX1    0x4f  /* Matrix Coefficient 1 */
#define MTX2    0x50  /* Matrix Coefficient 2 */
#define MTX3    0x51  /* Matrix Coefficient 3 */
#define MTX4    0x52  /* Matrix Coefficient 4 */
#define MTX5    0x53  /* Matrix Coefficient 5 */
#define MTX6    0x54  /* Matrix Coefficient 6 */
#define MTXS    0x58  /* Matrix Coefficient Sign */
#define AWBC7   0x59  /* AWB Control 7 */
#define AWBC8   0x5a  /* AWB Control 8 */
#define AWBC9   0x5b  /* AWB Control 9 */
#define AWBC10    0x5c  /* AWB Control 10 */
#define AWBC11    0x5d  /* AWB Control 11 */
#define AWBC12    0x5e  /* AWB Control 12 */
#define REG_GFI   0x69  /* Fix gain control */
#define GGAIN   0x6a  /* G Channel AWB Gain */
#define DBLV    0x6b
#define AWBCTR3   0x6c  /* AWB Control 3 */
#define AWBCTR2   0x6d  /* AWB Control 2 */
#define AWBCTR1   0x6e  /* AWB Control 1 */
#define AWBCTR0   0x6f  /* AWB Control 0 */


/*
inline void waitForVsync(void) __attribute__((always_inline));
inline void waitForPixelClockRisingEdge(void) __attribute__((always_inline));
inline void waitForPixelClockLow(void) __attribute__((always_inline));
inline void waitForPixelClockHigh(void) __attribute__((always_inline));
inline void readPixelByte(uint8_t & byte) __attribute__((always_inline));

void CameraOV7670::waitForPixelClockRisingEdge() {
  waitForPixelClockLow();
  waitForPixelClockHigh();
}
void CameraOV7670::waitForPixelClockLow() {
  while(OV7670_PIXEL_CLOCK);
}
void CameraOV7670::waitForPixelClockHigh() {
  while(!OV7670_PIXEL_CLOCK);
}
void CameraOV7670::readPixelByte(uint8_t & byte) {
  OV7670_READ_PIXEL_BYTE(byte);
}
*/

void setup() {
  int i;
  
  // CONFIGURA OUTPUT COMPARE OC4A
  // SUL PIN NUMERO 6 PER GENERARE 
  // UN CLOCK A frequenza = 8 MHz
  pinMode(6, OUTPUT);
  TCCR4A = 0x40;
  TCCR4B = 0x09;
  OCR4A = 0;

  // CONFIGURO I PIN 7-8-9 COME INGRESSI
  pinMode(7, INPUT);  //PCLK - PH4
  pinMode(8, INPUT);  //HREF - PH5
  pinMode(9, INPUT);  //VREF - PH6
    
  // PORT-L PINS per Debug
  pinMode(42, OUTPUT); /* PORT - L7 - Most Significant bit */ 
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT); /* PORT - L0 - Least Significant bit*/ 
  PORTL = 0;
 
  /* Start using I2C on Arduino Mega Pins 20(SDA) 21(SCL) */
  Wire.begin();

  Serial.begin(115200);
  while (!Serial); // Leonardo: wait for serial monitor

  delay(10); // give camera some time to run before starting setup
  
  Serial.println("\nLETTURA REGISTRI OV7670");
  for (i = 0; i <= 0xCF; i++ ) { read_reg( i ); }

  Serial.println("\nPROGRAMMAZIONE MODALITA' QQVGA 10fps");
  
  /* QQVGA 160 x 120  2fps 
     185ms / 1,57ms = 120 righe
     805uSec / 2.5uSec = 320 ck / 2 = 160 colonne 
  */
  write_reg( REG_COM7, COM7_RESET );
  delay(500);

  /* REGISTER DEFAULT */
  write_reg( REG_COM7, COM7_RESET ); 
  write_reg( REG_TSLB, 0x04 );         /* OV */
  write_reg( REG_COM7, 0 );            /* VGA */
    /*
     * Set the hardware window.  These values from OV don't entirely
     * make sense - hstop is less than hstart.  But they work...
     */
  write_reg( REG_HSTART, 0x13 );
  write_reg( REG_HSTOP, 0x01 );
  write_reg( REG_HREF, 0xb6 );
  write_reg( REG_VSTART, 0x02 );
  write_reg( REG_VSTOP, 0x7a );
  write_reg( REG_VREF, 0x0a );
  write_reg( REG_COM3, 0 );
  write_reg( REG_COM14, 0 );
  /* Mystery scaling numbers */
  write_reg( 0x70, 0x3a );
  write_reg( 0x71, 0x35 );
  write_reg( 0x72, 0x11 );
  write_reg( 0x73, 0xf0 );
  write_reg( 0xa2, /* 0x02 changed to 1*/ 1 );
  write_reg( REG_COM10, 0 );
  /* Gamma curve values */
  write_reg( 0x7a, 0x20 );
  write_reg( 0x7b, 0x10 );
  write_reg( 0x7c, 0x1e );
  write_reg( 0x7d, 0x35 );
  write_reg( 0x7e, 0x5a );
  write_reg( 0x7f, 0x69 );
  write_reg( 0x80, 0x76 );
  write_reg( 0x81, 0x80 );
  write_reg( 0x82, 0x88 );
  write_reg( 0x83, 0x8f );
  write_reg( 0x84, 0x96 );
  write_reg( 0x85, 0xa3 );
  write_reg( 0x86, 0xaf );
  write_reg( 0x87, 0xc4 );
  write_reg( 0x88, 0xd7 );
  write_reg( 0x89, 0xe8 );
  /* AGC and AEC parameters.  
   *  Note we start by disabling those features,
   *  then turn them only after tweaking the values. */
  write_reg( REG_COM8, COM8_FASTAEC | COM8_AECSTEP );
  write_reg( REG_GAIN, 0 );
  write_reg( REG_AECH, 0 );
  write_reg( REG_COM4, 0x40 ); /* magic reserved bit */
  write_reg( REG_COM9, 0x18 ); /* 4x gain + magic rsvd bit */
  write_reg( REG_BD50MAX, 0x05 );
  write_reg( REG_BD60MAX, 0x07 );
  write_reg( REG_AEW, 0x95 );
  write_reg( REG_AEB, 0x33 );
  write_reg( REG_VPT, 0xe3 );
  write_reg( REG_HAECC1, 0x78 );
  write_reg( REG_HAECC2, 0x68 );
  write_reg( 0xa1, 0x03 ); /* magic */
  write_reg( REG_HAECC3, 0xd8 );
  write_reg( REG_HAECC4, 0xd8 );
  write_reg( REG_HAECC5, 0xf0 );
  write_reg( REG_HAECC6, 0x90 );
  write_reg( REG_HAECC7, 0x94 );
  write_reg( REG_COM8, COM8_FASTAEC | COM8_AECSTEP | COM8_AGC | COM8_AEC  );
  write_reg( 0x30, 0 );
  write_reg( 0x31, 0 );   /* disable some delays */
  /* Almost all of these are magic "reserved" values.  */
  write_reg( REG_COM5, 0x61 );
  write_reg( REG_COM6, 0x4b  );
  write_reg( 0x16, 0x02 );
  write_reg( REG_MVFP, 0x07 );
  write_reg( 0x21, 0x02 );
  write_reg( 0x22, 0x91 );
  write_reg( 0x29, 0x07 );
  write_reg( 0x33, 0x0b );
  write_reg( 0x35, 0x0b );
  write_reg( 0x37, 0x1d );
  write_reg( 0x38, 0x71 );
  write_reg( 0x39, 0x2a );
  write_reg( REG_COM12, 0x78 );
  write_reg( 0x4d, 0x40 );
  write_reg( 0x4e, 0x20 );
  write_reg( REG_GFIX, 0 );
  /* write_reg( 0x6b, 0x4a ); */
  write_reg( 0x74, 0x10 );
  write_reg( 0x8d, 0x4f );
  write_reg( 0x8e, 0 );
  write_reg( 0x8f, 0 );
  write_reg( 0x90, 0 );
  write_reg( 0x91, 0 );
  write_reg( 0x96, 0 );
  write_reg( 0x9a, 0 );
  write_reg( 0xb0, 0x84 );
  write_reg( 0xb1, 0x0c );
  write_reg( 0xb2, 0x0e );
  write_reg( 0xb3, 0x82 );
  write_reg( 0xb8, 0x0a );
  /* More reserved magic, some of which tweaks white balance */
  write_reg( 0x43, 0x0a );
  write_reg( 0x44, 0xf0 );
  write_reg( 0x45, 0x34 );
  write_reg( 0x46, 0x58 );
  write_reg( 0x47, 0x28 );
  write_reg( 0x48, 0x3a );
  write_reg( 0x59, 0x88 );
  write_reg( 0x5a, 0x88 );
  write_reg( 0x5b, 0x44 );
  write_reg( 0x5c, 0x67 );
  write_reg( 0x5d, 0x49 );
  write_reg( 0x5e, 0x0e );
  write_reg( 0x6c, 0x0a );
  write_reg( 0x6d, 0x55 );
  write_reg( 0x6e, 0x11 );
  write_reg( 0x6f, 0x9e );
  /* it was 0x9F "9e for advance AWB" */
  write_reg( 0x6a, 0x40 );
  write_reg( REG_BLUE, 0x40 );
  write_reg( REG_RED, 0x60 );
  write_reg( REG_COM8, COM8_FASTAEC | COM8_AECSTEP | COM8_AGC | COM8_AEC | COM8_AWB );
  /* Matrix coefficients */
  write_reg( 0x4f, 0x80 );
  write_reg( 0x50, 0x80 );
  write_reg( 0x51, 0  );
  write_reg( 0x52, 0x22 );
  write_reg( 0x53, 0x5e );
  write_reg( 0x54, 0x80 );
  write_reg( 0x58, 0x9e );
  write_reg( REG_COM16, COM16_AWBGAIN );
  write_reg( REG_EDGE, 0 );
  write_reg( 0x75, 0x05 );
  write_reg( REG_REG76, 0xe1 );
  write_reg( 0x4c, 0 );
  write_reg( 0x77, 0x01 );
  write_reg( REG_COM13, /*0xc3*/ 0x48 );
  write_reg( 0x4b, 0x09 );
  write_reg( 0xc9, 0x60 );
  /* write_reg( REG_COM16, 0x38 ); */
  write_reg( 0x56, 0x40 );
  write_reg( 0x34, 0x11 );
  write_reg( REG_COM11, COM11_EXP | COM11_HZAUTO );
  write_reg( 0xa4, 0x82 /* Was 0x88 */  );
  write_reg( 0x96, 0 );
  write_reg( 0x97, 0x30 );
  write_reg( 0x98, 0x20 );
  write_reg( 0x99, 0x30 );
  write_reg( 0x9a, 0x84 );
  write_reg( 0x9b, 0x29 );
  write_reg( 0x9c, 0x03 );
  write_reg( 0x9d, 0x4c );
  write_reg( 0x9e, 0x3f );
  write_reg( 0x78, 0x04 );
  /* Extra-weird stuff.  Some sort of multiplexor register */
  write_reg( 0x79, 0x01 ); write_reg( 0xc8, 0xf0 );
  write_reg( 0x79, 0x0f ); write_reg( 0xc8, 0x00 );
  write_reg( 0x79, 0x10 ); write_reg( 0xc8, 0x7e );
  write_reg( 0x79, 0x0a ); write_reg( 0xc8, 0x80 );
  write_reg( 0x79, 0x0b ); write_reg( 0xc8, 0x01 );
  write_reg( 0x79, 0x0c ); write_reg( 0xc8, 0x0f );
  write_reg( 0x79, 0x0d ); write_reg( 0xc8, 0x20 );
  write_reg( 0x79, 0x09 ); write_reg( 0xc8, 0x80 );
  write_reg( 0x79, 0x02 ); write_reg( 0xc8, 0xc0 );
  write_reg( 0x79, 0x03 ); write_reg( 0xc8, 0x40 );
  write_reg( 0x79, 0x05 ); write_reg( 0xc8, 0x30 );
  write_reg( 0x79, 0x26 );

  /* RGB 565 */
  write_reg( REG_COM7, COM7_RGB ); /* Selects RGB mode */
  write_reg( REG_RGB444, 0 );      /* No RGB444 please */
  write_reg( REG_COM1, 0x0 ); 
  write_reg( REG_COM15, COM15_RGB565 | COM15_R00FF );
  write_reg( REG_COM9, 0x6A );     /* 128x gain ceiling; 0x8 is reserved bit */
  write_reg( 0x4f, 0xb3 );         /* "matrix coefficient 1" */
  write_reg( 0x50, 0xb3 );         /* "matrix coefficient 2" */
  write_reg( 0x51, 0 );            /* vb */
  write_reg( 0x52, 0x3d );         /* "matrix coefficient 4" */
  write_reg( 0x53, 0xa7 );         /* "matrix coefficient 5" */
  write_reg( 0x54, 0xe4 );         /* "matrix coefficient 6" */
  write_reg( REG_COM13, /* COM13_GAMMA | */ COM13_UVSAT );

  /* QQ VGA 160 x 120 */
  write_reg( REG_COM3, COM3_DCWEN );  /* enable downsamp/crop/window */
  write_reg( REG_COM14, 0x1a );       /* divide by 4 */
  write_reg( 0x72, 0x22 );            /* downsample by 4 */
  write_reg( 0x73, 0xf2 );            /* divide by 4 */
  write_reg( REG_HSTART, 0x16 );
  write_reg( REG_HSTOP, 0x04 );
  write_reg( REG_HREF, 0xa4 );
  write_reg( REG_VSTART, 0x02 );
  write_reg( REG_VSTOP, 0x7a );
  write_reg( REG_VREF, 0x0a );

  /* setDisablePixelClockDuringBlankLines */
  write_reg( REG_COM10, read_reg( REG_COM10 ) | COM10_PCLK_HB );

  /* setDisableHREFDuringBlankLines */
  write_reg( REG_COM6, read_reg( REG_COM6 ) | COM6_HREF_HB );

  /* setInternalClockPreScaler(int preScaler) 
   *  FPS_5_Hz:    1;
   *  FPS_3p33_Hz: 2;
   *  FPS_2p5_Hz:  3;
   *  FPS_2_Hz:    4;
   *  FPS_1p66_Hz: 5;
   */  
   write_reg( REG_CLKRC, 0x80 | 4); // f = input / (val + 1)

  /* PLL MULTIPLIER 
   *  FPS_5_Hz = 0
   *  FPS_3p33_Hz = 1
   *  FPS_2p5_Hz = 2    
   *  FPS_2_Hz = 3
   *  FPS_1p66_Hz = 4
   */
  /* setRegister(DBLV, (read_reg( DBLV ) & 0b00111111) | (multiplier << 6)); */
  write_reg( DBLV, (read_reg( DBLV ) & 0b00111111) | 0b00000000  );

}

void processLine( uint8_t n_linea ) {

  uint8_t linea[ 320 ];
  uint8_t i;
  uint16_t j, pixel;
  
  noInterrupts();
  while( ! OV7670_VSYNC );
  
  for (i = 0; i <= n_linea; i++) {

    /* readLine() */
    
    j = 0;
        
    while( OV7670_PIXEL_CLOCK ); /* waitForPixelClockLow(); */
    
    /* è iniziata una riga */
        
    while ( j < 320 ) {
      
      while( !OV7670_PIXEL_CLOCK ); /* waitForPixelClockHigh(); */
    
      // DEBUG : PORTL = 0x80;  
      
      OV7670_READ_PIXEL_BYTE( linea[ j++ ] );
      
      // DEBUG : PORTL = 0x00; 

      while( OV7670_PIXEL_CLOCK ); /* waitForPixelClockLow(); */
    
      /* asm volatile("nop"); asm volatile("nop"); */
      /* asm volatile("nop"); asm volatile("nop"); */
      /* OV7670_READ_PIXEL_BYTE( linea[ j++] ); */
    }
          
  }
  interrupts();

 
  Serial.println( "<tr>");
    
  for (j = 0; j < 320; j+=(2*SCALE_FACTOR)) {

    pixel = ( linea[j] << 8 ) | ( linea[j+1] );

    // SCRITTURA OUTPUT HTML        
    Serial.print( "<td style=\"width:4px; height:4px; font-size:1px; background: #");

    /* RGB 565 rrrr rggg gggb bbbb
     * background HTML:  #rrggbb     
     *     rrrr r000
     *     gggg gg00
     *     bbbb b000
     **/
    Serial.print((pixel >> 12) & 0xF, HEX); Serial.print((pixel >> 8) & 0x8, HEX);  
    Serial.print((pixel >> 7)  & 0xF, HEX); Serial.print((pixel >> 3) & 0xC, HEX);  
    Serial.print((pixel >> 1)  & 0xF, HEX); Serial.print((pixel << 3) & 0x8, HEX);  
    Serial.print( "\"></td>");
    
  }

  Serial.println( "</tr>");
   
}


void loop() {

  uint8_t i;
  

  Serial.println( "<html><body><table style=\"border-collapse:collapse;\">");

  for (i = 0; i < 120; i+=SCALE_FACTOR) {
  // DEBUG: while ( true ) { i = 0;

    processLine( i );
    
  }

  Serial.println( "</table></body></html>");

  while (true) ;

  
  unsigned int px1, px2, pixel;
  int n_riga;
  int n_pixel;

  int r = 36;
  int c = 40;

  // 7 PCLK - PH4  0001 0000  0x10
  // 8 HREF - PH5  0010 0000  0x20
  // 9 VREF - PH6  0100 0000  0x40

  Serial.println( "<html><body><table>");

  for (r=0; r< 70; r++) {
    
    Serial.println( "<tr>");

    for (c=0; c<82; c++) {

      n_riga = 0;
      // ASPETTO CHE V-SYNC VADA BASSO
      while ( (PINH & 0x40) != 0 ) { /* do nothing */ }
    
      // ASPETTO CHE H-SYNC VADA ALTO
      while ( (PINH & 0x60) == 0 ) { /* do nothing */ }

      // CICLA FINCHE' V-SYNC E' BASSO
      while ( (PINH & 0x40) == 0 ) 
      {               
        // CONTO QUANTE RIGHE CI SONO IN UNA SCHERMATA
        n_riga ++;
        n_pixel = 0;
        
        // INIZIA LA PRIMA RIGA
        while ( (PINH & 0x20) != 0 ) { 
    
          // ATTENDO PRIMO FRONTE POSITIVO DI P-CLK
          while ( (PINH & 0x10) == 0 ) { /* do nothing */ }
    
          // HO INDIVIDUATO UN FRONTE POSITIVO
          // CAMPIONO IL 1' BYTE  
          // DEBUG: PORTL = 0x80;  
          px1 = PINC;  // PARTE ALTA DI RGB-565 (R5-G3M)
          // DEBUG: PORTL = 0x00;
    
          // ATTENDO FRONTE NEGATIVO DI P-CLK
          while ( (PINH & 0x10) != 0 ) { /* do nothing */ }
    
          // ATTENDO SECONDO FRONTE POSITIVO DI P-CLK
          while ( (PINH & 0x10) == 0 ) { /* do nothing */ }
    
          // HO INDIVIDUATO IL SECONDO FRONTE POSITIVO
          // CAMPIONO IL 2' BYTE
          px2 = PINC;  // PARTE BASSA DI RGB-565 (G3L-B5)
          
          n_pixel ++ ;
    
          if (n_riga == r) {
    
             if (n_pixel == c) {
         
                pixel = ( px1 << 8 ) | ( px2 );
                
             }
            
          }
          
          // ATTENDO FRONTE NEGATIVO DI P-CLK
          while ( (PINH & 0x10) == 0 ) { /* do nothing */ }
    
          // DOVREI AVERE ANCHE IL FRONTE NEGATIVO DI H-SYNC
        }
       
        while ( (PINH & 0x60) == 0 ) { /* do nothing */ }
      }

      if (true) {

        // SCRITTURA OUTPUT HTML        
        Serial.print( "<td style=\"width:4px; height:4px; font-size:1px; background: #");
        Serial.print((pixel >> 12) & 0xF, HEX); Serial.print((pixel >> 8) & 0xF, HEX);  
        Serial.print((pixel >> 7)  & 0xF, HEX); Serial.print((pixel >> 3) & 0xF, HEX);  
        Serial.print((pixel >> 1)  & 0xF, HEX); Serial.print((pixel << 3) & 0xF, HEX);  
        Serial.print( "\">&nbsp;</td>");

      }
      else {

        // SCRITTURA DEL SINGOLO PIXEL
        Serial.print("N. riga = ");
        Serial.print(r);
        Serial.print(", N. pixel = ");
        Serial.print(c);  
        Serial.print(", R = ");
        Serial.print((pixel >> 8) & 0xF8);  
        Serial.print(", G = ");
        Serial.print((pixel >> 3) & 0xFC);  
        Serial.print(", B = ");
        Serial.println((pixel << 3) & 0xF8); 
         
      }

    }
      
    Serial.println( "</tr>");
  }

  Serial.println( "</table></body></html>");
  
  while (1); /* ciclo infinito: ferma esecuzione */
  
}


/* 
 *  FUNZIONE PER LA LETTURA DI UN REGISTRO DELLA CHIP CAMERA OV7670
 */
byte read_reg(byte regNumber ) {
    byte val;

    // LETTURA DEL REGISTRO
    Wire.beginTransmission(SCCB_ADDRESS);
    Wire.write(regNumber);
    Wire.endTransmission();
  
    Wire.requestFrom((uint8_t)SCCB_ADDRESS, (uint8_t)1);
    val = Wire.read();

    // DEBUG:
    Serial.print("[");
    Serial.print(regNumber, HEX);
    Serial.print("] = ");
    Serial.println(val, HEX);

    return val;
}

/* 
 *  FUNZIONE PER LA SCRITTURA DI UN REGISTRO DELLA CHIP CAMERA OV7670
 */
void write_reg(byte regNumber, byte to_val ) {
    byte from_val;

    // LETTURA DEL REGISTRO PER MODALITA' VERBOSE
    Wire.beginTransmission(SCCB_ADDRESS);
    Wire.write(regNumber);
    Wire.endTransmission();
  
    Wire.requestFrom((uint8_t)SCCB_ADDRESS, (uint8_t)1);
    from_val = Wire.read();

    // SCRITTURA DEL VALORE NEL REGISTRO DESIDERATO
    Wire.beginTransmission(SCCB_ADDRESS);
    Wire.write(regNumber);
    Wire.write(to_val);
    Wire.endTransmission();

    // DEBUG:
    Serial.print("[");
    Serial.print(regNumber, HEX);
    Serial.print("] from ");
    Serial.print(from_val, HEX);
    Serial.print(" to ");
    Serial.println(to_val, HEX);

}
