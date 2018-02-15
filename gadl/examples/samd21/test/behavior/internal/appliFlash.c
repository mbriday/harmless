
typedef void (*it_handler)(void);
extern unsigned long _estack;
void _start(void);
void null_it(void);
void sc_handler(void);

__attribute__ ((section(".isr_vector"))) it_handler tpl_it_vectors[] = {
  (it_handler)&_estack,
  (it_handler)_start,  /* reset     */
  (it_handler)null_it, /* nmi       */
  (it_handler)null_it, /* HardFault */
  (it_handler)null_it, /* MemManage */
  (it_handler)null_it, /* BusFault  */
  (it_handler)null_it, /* UsageFault*/
  (it_handler)0xFEEDDEB0, /* Magic number */
  (it_handler)null_it,
  (it_handler)null_it,
  (it_handler)null_it,
  (it_handler)sc_handler,
  (it_handler)null_it,
  (it_handler)null_it,
  (it_handler)null_it,
  (it_handler)null_it  /* Systick */
};

void null_it(void) {
	while(1);
}
