#include <reent.h>
//some code from http://wiki.osdev.org/Porting_Newlib

//There is a 'nop' in this function because the 'write' function did not 
//call the writechar function before (and did not trigger the stub!)
__attribute__ ((noinline))
void writechar(char val)
{
	asm("nop");
}

//Open a file (stub function). 
//Note: If compiler optimisations are not set, 
//      it may erase the return value calculated by the stub
//      (-O0 should not be used...).
//      In that last case, the returned value is '0' and there is a problem with
//      the file descriptor (invalid) when reading.
__attribute__ ((noinline))  
int _open  (const char *name, int flags,int mode)
{
}

//write to a file (stub).
__attribute__ ((noinline))  
int _writeToFile (int file, char *buf, int len)
{
}

//read in a file stub function.
__attribute__ ((noinline))  
int _read  (int file, char *ptr, int len)
{
}

/***** here are basic functions to compile the newlib *****/

//Close a file
int _close (int file)
{
	return -1;
}

//Write a character to a file.
int _write (int file, char *buf, int len)
{
	if(file == 1 || file == 2) //stdout or stderr
	{
		int todo; 
		for (todo = 0; todo < len; todo++) {
			writechar(*buf++);
		}
		return len;
	} else return _writeToFile(file, buf, len);
}

//Status of a file
#include <sys/stat.h>
int _fstat (int file, struct stat *st) 
{
	st->st_mode = S_IFREG; //regular file.
	return 0;
}


//Set position in a file.
int _lseek (int file, int   offset,int   whence)
{
	return 0;
}

//allocate memory on the heap.
//used by malloc.
char *_sbrk(int incr){
	extern char end;		/* Defined by the linker */
	static char *heap_end;
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

int _isatty(int fd) {return 1;};

void _exit(int sig) {while(1);};

