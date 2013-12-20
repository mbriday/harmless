
ENTRY (_entryPoint)
SEARCH_DIR (.)

 
MEMORY {
  external_ram : org = 0x81000000, len = 1M
}

/*
 * Do not change the next code
 */
SECTIONS {
  .text : {
    *(.init);
    . = ALIGN(4);
    *(.text);
    . = ALIGN(4);
    *(.rodata);
    . = ALIGN(4);
    *(.rodata*);
    . = ALIGN(4);
    *(.glue_7t);
    . = ALIGN(4);
    *(.glue_7);
    . = ALIGN(4);
    etext = .;
  } > external_ram

  .data : {
    __data_start = . ;
    *(.data)
    . = ALIGN(4);
    edata = .;
    _edata = .;
    __data_end = . ;
  } > external_ram

  .bss : {
    __bss_start = . ;
    *(.bss)
    *(COMMON)
    . = ALIGN(4);
    __bss_end = . ;
    
  } > external_ram
  
  _init_sp = . ;
    
}
/*** EOF ***/

