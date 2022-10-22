/**@file
IO22D08.h - Library for the 8 channel Pro mini PLC board
Created by Daniel Gullberg, May 5, 2020
Released into the public domain.
 */

#ifndef IO22D08_H
#define IO22D08_H

#include "Arduino.h"

#ifdef IO22C04_USED
typedef struct
{
    union
    {
        uint16_t raw;
        struct
        {
            uint8_t A:1;            //!< Shift reg 1.0
            uint8_t B:1;            //!< Shift reg 1.1
            uint8_t C:1;            //!< Shift reg 1.2
            uint8_t D:1;            //!< Shift reg 1.3
            uint8_t E:1;            //!< Shift reg 1.4
            uint8_t F:1;            //!< Shift reg 1.5
            uint8_t G:1;            //!< Shift reg 1.6
            uint8_t DP:1;           //!< Shift reg 1.7
            uint8_t Common4:1;      //!< Shift reg 2.0
            uint8_t Common3:1;      //!< Shift reg 2.1
            uint8_t Common2:1;      //!< Shift reg 2.2
            uint8_t Common1:1;      //!< Shift reg 2.3
            uint8_t Unused2_4:1;    //!< Shift reg 2.4
            uint8_t Unused2_5:1;    //!< Shift reg 2.5
            uint8_t Unused2_6:1;    //!< Shift reg 2.6
            uint8_t Unused2_7:1;    //!< Shift reg 2.7
        };
    };
} shiftregs_7_seg_t;
#endif

typedef struct
{
    union
    {
        struct{
            uint8_t shiftreg2;      //!< Shift reg 2
            uint8_t shiftreg3;      //!< Shift reg 3
        };
        struct
        {
            uint16_t Unused2_0	:1;	//!< Shift reg 2.0
            uint16_t E          :1; //!< Shift reg 2.1
            uint16_t Common4    :1; //!< Shift reg 2.2
            uint16_t D          :1; //!< Shift reg 2.3
            uint16_t A          :1; //!< Shift reg 2.4
            uint16_t DP         :1; //!< Shift reg 2.5
            uint16_t F          :1; //!< Shift reg 2.6
            uint16_t C          :1; //!< Shift reg 2.7
            uint16_t Unused3_0  :1; //!< Shift reg 3.0
            uint16_t Common3    :1; //!< Shift reg 3.1
            uint16_t Common2    :1; //!< Shift reg 3.2
            uint16_t G          :1; //!< Shift reg 3.3
            uint16_t B          :1; //!< Shift reg 3.4
            uint16_t Common1    :1; //!< Shift reg 3.5
            uint16_t Unused3_6  :1; //!< Shift reg 3.6
            uint16_t Unused3_7  :1; //!< Shift reg 3.7
        };
    };
} shiftregs_7_seg_t;

typedef struct
{
    union
    {
        uint8_t raw;
        struct
        {
            uint8_t Ch8         :1; //!< Shift reg 1.0
            uint8_t Ch1         :1; //!< Shift reg 1.1
            uint8_t Ch2         :1; //!< Shift reg 1.2
            uint8_t Ch3         :1; //!< Shift reg 1.3
            uint8_t Ch4         :1; //!< Shift reg 1.4
            uint8_t Ch5         :1; //!< Shift reg 1.5
            uint8_t Ch6         :1; //!< Shift reg 1.6
            uint8_t Ch7         :1; //!< Shift reg 1.7
        };
    };
} shiftreg_relays_t;


class IO22D08
{
public:
    IO22D08();
    void init();           			//!< Initialize all ports
    void setCharacter(uint8_t, uint8_t); //!< Set character
    void setRelay(uint8_t);
    void resetRelay(uint8_t);
    void updateShiftregs();			//!< Shift out the data to the sift registers
    void test(int);
private:
    int _pin_595_0E; 				//!< Relay shift register NG-pin (Output enable)
    int _data;            			//!< Shift register data
    int _clock;            			//!< Shift register clock
    int _latch;            			//!< Shift register latch
    shiftregs_7_seg_t _sr_7_seg;  	//!< Shift registers for 7 segment display
    shiftreg_relays_t _sr_relays; 	//!< Shift register for relays

};


#endif
