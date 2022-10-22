/*The 4 channel board from the top:
 *
 * Disp   Shift 2
 *        Shift 1
 *
 * The display pinout (seen from the top of the board)
 * 1   12
 * 2   11
 * 3   10
 * 4   9
 * 5   8
 * 6   7
 *
 * 1  Shift 1.4       E
 * 2  Shift 1.3       D
 * 3  Shift 1.7       DP (Only together with Common 2!)
 * 4  Shift 1.2       C
 * 5  Shift 1.6       G
 * 6  Shift     2.3   Common 1
 * 7  Shift 1.1       B
 * 8  Shift     2.2   Common 2
 * 9  Shift     2.1   Common 3
 * 10 Shift 1.5       F
 * 11 Shift 1.0       A
 * 12 Shift     2.0   Common 4
 * The 8 channel board:
 *
 *
 * Disp Shift 2   Shift 1
 *      Shift 3

 * 1  Shift 2.1     E
 * 2  Shift 2.3     D
 * 3  Shift 2.5     DP (Only together with Common 2!)
 * 4  Shift 2.7     C
 * 5  Shift     3.3 G
 * 6  Shift     3.5 Common 1
 * 7  Shift     3.4 B
 * 8  Shift     3.2 Common 2
 * 9  Shift     3.1 Common 3
 * 10 Shift 2.6     F
 * 11 Shift 2.4     A
 * 12 Shift 2.2     Common 4
 *
 * Or, mapped on shift register:
 * Shift 1.0  Ch8
 * Shift 1.1  Ch1
 * Shift 1.2  Ch2
 * Shift 1.3  Ch3
 * Shift 1.4  Ch4
 * Shift 1.5  Ch5
 * Shift 1.6  Ch6
 * Shift 1.7  Ch7
 *
 * Shift 2.0
 * Shift 2.1 E
 * Shift 2.2  Common 4
 * Shift 2.3  D
 * Shift 2.4  A
 * Shift 2.5  DP
 * Shift 2.6  F
 * Shift 2.7  C
 *
 * Shift 3.0
 * Shift 3.1  Common 3
 * Shift 3.2  Common 2
 * Shift 3.3  G
 * Shift 3.4  B
 * Shift 3.5  Common 1
 * Shift 3.6
 * Shift 3.7
 *
 *
 * ---Segment Display Screen----
--A--
F---B
--G--
E---C
--D--
 __  __   __  __
|__||__|.|__||__|
|__||__|'|__||__|
----------------------

Current consumption measurements:
U=10.0V

18.3 mA With nothing running

U=12.0 V
21.1 mA No display, 0xFF on relays but no output enable
234.7 mA No display, 0xFF on relays with output enable
18.3 mA No display, 0x00 on relays
95 mA LED D, Common 2, Relay 1


 */
#include "IO22D08.h"

static const uint8_t SYMBOLS[]={0x3F, 0x06, 0x5B, 0x4F};

IO22D08::IO22D08()
{
	_pin_595_0E = A1;
	_data		= 13;
	_clock 		= A3;
	_latch 		= A2;
}

void IO22D08::init()
{
	pinMode(_latch, OUTPUT);
	pinMode(_clock, OUTPUT);
	pinMode(_data, OUTPUT);

	pinMode(K1, INPUT);
	pinMode(K2, INPUT);
	pinMode(K3, INPUT);
	pinMode(K4, INPUT);
	
	pinMode(INPUT1, INPUT);
	pinMode(INPUT2, INPUT);
	pinMode(INPUT3, INPUT);
	pinMode(INPUT4, INPUT);
	pinMode(INPUT5, INPUT);
	pinMode(INPUT6, INPUT);
	pinMode(INPUT7, INPUT);
	pinMode(INPUT8, INPUT);

	digitalWrite(K1, HIGH);
	digitalWrite(K2, HIGH);
	digitalWrite(K2, HIGH);
	digitalWrite(K2, HIGH);

	digitalWrite(INPUT1, HIGH);
	digitalWrite(INPUT2, HIGH);
	digitalWrite(INPUT3, HIGH);
	digitalWrite(INPUT4, HIGH);
	digitalWrite(INPUT5, HIGH);
	digitalWrite(INPUT6, HIGH);
	digitalWrite(INPUT7, HIGH);
	digitalWrite(INPUT8, HIGH);

}

void IO22D08::setCharacter(uint8_t charIdx, uint8_t common)
{
	uint8_t symbol = SYMBOLS[charIdx];

	_sr_7_seg.A = !((0x01 << 0) & symbol);
	_sr_7_seg.B = !((0x01 << 1) & symbol);
	_sr_7_seg.C = !((0x01 << 2) & symbol);
	_sr_7_seg.D = !((0x01 << 3) & symbol);
	_sr_7_seg.E = !((0x01 << 4) & symbol);
	_sr_7_seg.F = !((0x01 << 5) & symbol);
	_sr_7_seg.G = !((0x01 << 6) & symbol);

	_sr_7_seg.DP = 1; // TODO: Handle decimal point

	_sr_7_seg.Common1 = (common==0?1:0);
	_sr_7_seg.Common2 = (common==1?1:0);
	_sr_7_seg.Common3 = (common==2?1:0);
	_sr_7_seg.Common4 = (common==3?1:0);
}

void IO22D08::setRelay(uint8_t relay_Idx)
{
	// _sr_relays.Ch1 = (0x01 << 2) & 1;
	switch(relay_Idx)
	{
    	case 1:
			_sr_relays.Ch1 = 0x01;
			break;
    	case 2:
			_sr_relays.Ch2 = 0x01;
			break;
		case 3:
			_sr_relays.Ch3 = 0x01;
			break;
		case 4:
			_sr_relays.Ch4 = 0x01;
			break;
		case 5:
			_sr_relays.Ch5 = 0x01;
			break;
		case 6:
			_sr_relays.Ch6 = 0x01;
			break;
		case 7:
			_sr_relays.Ch7 = 0x01;
			break;
		case 8:
			_sr_relays.Ch8 = 0x01;
			break;
		default:
			break;
	}
}

void IO22D08::resetRelay(uint8_t relay_Idx)
{
	// _sr_relays.Ch1 = (0x01 << 0) & 0;
	switch(relay_Idx)
	{
    	case 1:
			_sr_relays.Ch1 = 0x00;
			break;
    	case 2:
			_sr_relays.Ch2 = 0x00;
			break;
		case 3:
			_sr_relays.Ch3 = 0x00;
			break;
		case 4:
			_sr_relays.Ch4 = 0x00;
			break;
		case 5:
			_sr_relays.Ch5 = 0x00;
			break;
		case 6:
			_sr_relays.Ch6 = 0x00;
			break;
		case 7:
			_sr_relays.Ch7 = 0x00;
			break;
		case 8:
			_sr_relays.Ch8 = 0x00;
			break;
		default:
			break;
	}
}



void IO22D08::updateShiftregs()
{
	digitalWrite(_latch, LOW);

	shiftOut(_data, _clock, MSBFIRST, _sr_7_seg.shiftreg3);
	shiftOut(_data, _clock, MSBFIRST, _sr_7_seg.shiftreg2);
	shiftOut(_data, _clock, MSBFIRST, _sr_relays.raw);

	digitalWrite(_latch, HIGH);

	digitalWrite(_pin_595_0E, LOW); // Enable relay output
}

void IO22D08::test(int x)
{

	shiftreg_relays_t relays = {0};
	shiftregs_7_seg_t led = {0};


	led.A = 1;
	led.B = 1;
	led.C = 1;
	led.D = 0;
	led.E = 1;
	led.F = x;
	led.G = 1;

	led.Common2 = 1;

	relays.Ch1 = 0;
	relays.Ch2 = 0;
	relays.Ch3 = 0;
	relays.Ch4 = 0;
	relays.Ch5 = 0;
	relays.Ch6 = 0;
	relays.Ch7 = 0;
	relays.Ch8 = 0;

	digitalWrite(_latch, LOW);

	shiftOut(_data, _clock, MSBFIRST, led.shiftreg3);
	shiftOut(_data, _clock, MSBFIRST, led.shiftreg2);
	shiftOut(_data, _clock, MSBFIRST, relays.raw);

	digitalWrite(_latch, HIGH);

	digitalWrite(_pin_595_0E, LOW); // Enable relay output
}




#define uchar unsigned char
#define uint  unsigned int

int display_dat;
int key_value;
uint8_t relay_byte;

//Pin connected to latch of Digital Tube Module
const int latch = A2;
//Pin connected to click of Digital Tube Module
const int clock = A3;
//Pin connected to data of Digital Tube Module
const int data = 13;

const int K1 = 7;
const int K2 = 8;
const int K3 = 9;
const int K4 = 10;

const int INPUT1 = 2;
const int INPUT2 = 3;
const int INPUT3 = 4;
const int INPUT4 = 5;
const int INPUT5 = 6;
const int INPUT6 = 6;
const int INPUT7 = 12;
const int INPUT8 = 11;

const int pin_595_0E = A1;  // Relay shift register NG-pin (Output enable)

int relay1_delay_time = 1;//1-9999 seconds,Modify the number change the delay time
int relay2_delay_time = 1;//1-9999 seconds,Modify the number change the delay time
int relay3_delay_time = 1;//1-9999 seconds,Modify the number change the delay time
int relay4_delay_time = 1;//1-9999 seconds,Modify the number change the delay time

int relay1_time_left;
int relay2_time_left;
int relay3_time_left;
int relay4_time_left;

int relay1_display;
int relay2_display;
int relay3_display;
int relay4_display;


/*       NO.:0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22 23 24 25 26 27 28
Character :0,1,2,3,4,5,6,7,8,9,A, b, C, c, d, E, F, H, h, L, n, N, o, P, r, t, U, -,  ,*/
uchar  TUBE_SEG[] =
{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa7,0xa1,0x86,0x8e,0x89,0x8b,0xc7,0xab,0xc8,0xa3,0x8c,0xaf,0x87,0xc1,0xbf,0xff};//Common anode Digital Tube Character Gallery

uchar TUBE_NUM[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//Tuble bit number

uchar dat_buf[8];

//***********************************************
// dat : Data to be displayed
// com_num :  Digital Tube Common
//***********************************************
uchar dat;
uchar com_num;
void TubeDisplayOneByte()
{
	uint8_t shiftreg_2;
	uint8_t shiftreg_3;
	shiftreg_2 = 0x00; //Shift register 2
	shiftreg_3 = 0x10; //Shift register 3

	//ground latchPin and hold low for as long as you are transmitting
	digitalWrite(latch, LOW);

	shiftOut(data, clock, MSBFIRST, shiftreg_3);
	shiftOut(data, clock, MSBFIRST, shiftreg_2);
	shiftOut(data, clock, MSBFIRST, relay_byte);

	//return the latch pin high to signal chip that it
	//no longer needs to listen for information
	digitalWrite(latch, HIGH);

	if (relay_byte == 0x00)
	{
		relay_byte = 0x01;
	}
	else if(relay_byte == 0x80)
	{
		relay_byte = 0x00;
	}
	else
	{
		relay_byte = (relay_byte << 1);
	}
	relay_byte = 0x00;

}

uchar OneSecondCnt;
void TubeDisplay4Bit(void)
{
	if(com_num<3) com_num ++;else com_num=0;
	dat = dat_buf[com_num];
	TubeDisplayOneByte();

	OneSecondCnt--;
	if(OneSecondCnt==0)
	{
		OneSecondCnt = 200;
	}

}


