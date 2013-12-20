#include "hc12/arch.h"
#include "xgateStorage.h"
#include <iostream>
using namespace std;

xgateStorage::xgateStorage(std::string , u32 , u32 ) 
{
	m_hc12 = NULL;
}

u8  xgateStorage::read8AtAddress(u32 address)
{
	if(address < 0x800)                       //register
		return m_hc12->Mem_registers_read8(address);
	if(address < END_OF_XGATE_FLASH)          //flash
		return m_hc12->Mem_read8(address+START_HC12_FLASH);
	return m_hc12->Mem_read8(address + 0xF0000);  //ram
}

u16 xgateStorage::read16AtAddress(u32 address)
{
	if(address < 0x800)                       //register
		return m_hc12->Mem_registers_read16(address);
	if(address < END_OF_XGATE_FLASH)          //flash
		return m_hc12->Mem_read16(address+START_HC12_FLASH);
	return m_hc12->Mem_read16(address + 0xF0000);  //ram
}

void xgateStorage::write8AtAddress(u32 address, u8 byte)
{
	if(address < 0x800)                       //register
		m_hc12->Mem_registers_write8(address, byte);
	if(address < END_OF_XGATE_FLASH)          //flash
		cerr << "ERROR: XGate connot write into flash! addr is 0x " << hex << address << endl;
	else m_hc12->Mem_write8(address + 0xF0000, byte);  //ram
}

void xgateStorage::write16AtAddress(u32 address, u16 word)
{
	if(address < 0x800)                       //register
		 m_hc12->Mem_registers_write16(address, word);
	if(address < END_OF_XGATE_FLASH)          //flash
		cerr << "ERROR: XGate connot write into flash! addr is 0x " << hex << address << endl;
	else m_hc12->Mem_write16(address + 0xF0000, word);  //ram
}

u16 xgateStorage::get16AtAddr(u32 address)
{
	if(address < 0x800)                       //register
	{	
		storage *ro = m_hc12->Mem_getChunk(address);
		return ro->get16AtAddr(address);
	}
	if(address < END_OF_XGATE_FLASH)          //flash
	{
		storage *ro = m_hc12->Mem_getChunk(address+START_HC12_FLASH);
		return ro->get16AtAddr(address+START_HC12_FLASH);
	}
	storage *ro = m_hc12->Mem_getChunk(address + 0xF0000);
	return ro->get16AtAddr(address + 0xF0000);  //ram	
}
