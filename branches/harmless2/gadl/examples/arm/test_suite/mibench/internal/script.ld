
ENTRY (_entryPoint)
SEARCH_DIR (.)

 
MEMORY {
  external_ram : org = 0x81000000, len = 10M
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

  .fini       : {} > external_ram 
  .eh_frame   : {} > external_ram
  .ARM.exidx  : {} > external_ram
  .init_array : {} > external_ram 
  .fini_array : {} > external_ram
  .jcr        : {} > external_ram 
  .data : {
    __data_start = . ;
    *(.data)
    . = ALIGN(4);
    edata = .;
    _edata = .;
    __data_end = . ;
  } > external_ram

  .bss : {
    __bss_start__ = . ;
    *(.bss)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = . ;
  } > external_ram

  end = .;
  _init_sp = 0x81000000 + 10M -4; /* stack is at end of RAM */
}
/*** EOF ***/

