#include <reent.h>
//some code from http://wiki.osdev.org/Porting_Newlib

void writechar(char val)
{
	//dummy ARM serial line.
	volatile char *serial = (char *)(0xE0028010);
	*serial = val;
}

//Open a file.
int _open  (const char *name, int flags,int mode) 
{
}

//Close a file
int _close (int file)
{
	return -1;
}

//write to a file (stub).
int _writeToFile (int file, char *buf, int len)
{
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

int _read  (int file, char *ptr, int len)
{
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

