/**************************************************************************/
/*! 
    @file     MCP455X.h
    @author   C. Schnarel
	@license  BSD (see license.txt)
	
	This is a library for the Microchip Digital Potentiometer series.

	@section  HISTORY

    2013-Dec-24  - First release, C. Schnarel
*/
/**************************************************************************/

#ifndef _MCP4551_H_
#define _MCP4551_H_

#ifdef ARDUINO
    #if ARDUINO < 100
        #include "WProgram.h"
    #else
        #include "Arduino.h"
    #endif
#else
    #include "ArduinoWrapper.h"
#endif

// #include <Wire.h>

// Address is determined by formulat below. If An is GND, value is 0.
// If An is VCC, value is 1. If chip doesn't have the pin, then it is 1.
//
// 0b0101:A2:A1:A0

// I2C Address of device
#define MCP4551_DEFAULT_ADDRESS	0x2E	// A0 is connected to GND
#define MCP4551_ADDRESS_A0_VCC	0x2F	// A0 is connected to VCC
#define MCP4551_ADDRESS_A0_GND	0x2E	// A0 is connected to GND

// Command definitions (sent to WIPER register)
#define MCP4551_CMD_WRITE	0x00
#define MCP4551_CMD_INC		0x04
#define MCP4551_CMD_DEC		0x08
#define MCP4551_CMD_READ	0x0C

// Control bit definitions (sent to TCON register)
#define MCP4551_TCON_GC_EN	0x100
#define MCP4551_TCON_R0_EN	0x008
#define MCP4551_TCON_A_EN	0x004
#define MCP4551_TCON_W_EN	0x002
#define MCP4551_TCON_B_EN	0x001
#define MCP4551_TCON_ALL_EN	0x1FF

// Register addresses
#define MCP4551_RA_WIPER	0x00
#define MCP4551_RA_WIPER2	0x10
#define MCP4551_RA_NVWIPER	0x20
#define MCP4551_RA_NVWIPER2	0x30
#define MCP4551_RA_TCON		0x40

// Common WIPER values
#define MCP4551_WIPER_MID	0x080
#define MCP4551_WIPER_A		0x100
#define MCP4551_WIPER_B		0x000

class MCP4551 {
    public:
       enum AddressPin { GND=1, VCC=0 };

        MCP4551();
        MCP4551(uint8_t address);
        MCP4551(AddressPin a0, AddressPin a1=VCC, AddressPin a2=VCC);
        
        void begin(void);
        bool testConnection(void);

	bool setRegister(uint8_t reg, uint16_t value);  // returns true if no errors
	int16_t getRegister(uint8_t reg);

	bool setFlag(uint8_t flag, bool value);

	// Write the Wiper register
	bool setWiper(uint16_t value);  // returns true if no errors
	bool setNVWiper(uint16_t value);  // returns true if no errors
	bool setOhm(int r, int r_ab, int nbits);
        
	// Increments the Wiper register
	bool incWiper(void);  // increments the wiper register - stops at 0x100

	// Decrements the Wiper register
	bool decWiper(void);  // decrements the wiper register - stops at 0x000

     // Read the Wiper register
     int16_t getWiper(void);  // returns -1 if errors

    private:
        uint8_t devAddr;
};

#endif /* _MCP4551_H_ */
