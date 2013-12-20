#include <reent.h>
//some code from http://wiki.osdev.org/Porting_Newlib

void writechar(char val)
{
	//dummy PPC serial line.
	volatile char *serial = (char *)(0x00002FFF);
	*serial = val;
}

//Open a file.
int _open_r  (struct _reent *r,const char *name, int flags,int mode) 
{
}

//Close a file
int _close_r (struct _reent *r,int file)
{
	return -1;
}

//write to a file (stub).
int _writeToFile (int file, char *buf, int len)
{
}

//Write a character to a file.
int _write_r (struct _reent *r,int file, const void *buf, size_t len)
{
	char *tmp = (char *)buf;
	if(file == 1 || file == 2) //stdout or stderr
	{
		int todo; 
		for (todo = 0; todo < len; todo++) {
			writechar(*tmp++);
		}
		return len;
	} else return _writeToFile(file, tmp, len);
}

int _read_r  (struct _reent *r,int file, void *ptr, size_t len)
{
}

//Status of a file
#include <sys/stat.h>
int _fstat_r (struct _reent *r,int file, struct stat *st) 
{
	st->st_mode = S_IFREG; //regular file.
	return 0;
}


//Set position in a file.
_off_t _lseek_r (struct _reent *r,int file, _off_t offset,int   whence)
{
	return 0;
}



//allocate memory on the heap.
//used by malloc.
void *_sbrk_r(struct _reent *r,ptrdiff_t incr){
	extern char end;		/* Defined by the linker */
	static char *heap_end = 0;
    char *prev_heap_end;
     
	if (heap_end == 0) {
		heap_end = &end;
	}
    prev_heap_end = heap_end;
    //if (heap_end + incr > stack_ptr)
	//{
	//	_write (1, "Heap and stack collision\n", 25);
	//	abort ();
    //}

	heap_end += incr;
	return prev_heap_end;
}

int _isatty_r(struct _reent *r,int fd) {return 1;};

void _exit(int sig) {while(1);};

