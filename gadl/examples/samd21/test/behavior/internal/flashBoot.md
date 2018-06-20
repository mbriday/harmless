* run `st-util` in a terminal
* run `arm-none-eabi-gdb boot.elf` and then:

```gdb
tar extended-remote :4242
load
quit
```