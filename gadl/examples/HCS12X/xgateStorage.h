/**
 * XGate storage. This class is a wrapper to share the memory between the XGate model and the HC12 CPU.
 * Memory mapping:
 * - first 2Kb are registers -> match the 2kb of registers of the HC12
 * - 0x800 to    is Flash    -> mapped to 0x.. of the flash of the HC12 (with 512kb) 
 * - 0x    to    is RAM      -> mapped to 0x.. of the RAM of the HC12 (with 32kb).
 */

#ifndef __XGATE_STORAGE_H__ 
#define __XGATE_STORAGE_H__
#include "hc12/utils.h"
#include <string>

//32kb of RAM
#define RAMSIZE      0x8000
//16kb of XGate RAM (included in hc12 RAM)
#define XGRAMSIZE    0x4000
//512 kb of flash.
#define FLASHSIZE    0x80000

#define END_OF_HC12_RAM   0x0FFFFF
#define END_OF_HC12_FLASH 0x7FFFFF

#define END_OF_XGATE_FLASH (0xFFFF-XGRAMSIZE)
#define START_HC12_FLASH (END_OF_HC12_FLASH-FLASHSIZE+1)

class arch; //hc12 main object.

class xgateStorage
{
	arch *m_hc12;
	public:
	void setArch(arch *hc12) {m_hc12 = hc12;};
	
	xgateStorage(std::string, u32 size, u32 offset);

	u8  read8AtAddress(u32 address);
	u16 read16AtAddress(u32 address);

	void write8AtAddress(u32 address, u8 byte);
	void write16AtAddress(u32 address, u16 word);
	
	u16 get16AtAddr(u32 addr);
};

#endif
