# JSON test file format

## basic information

* `instruction` : the name of the instruction during the test
* `size` : the size of the instruction in bytes. This is required in the test to update the PC correctly.

## init

The init section gives default values for registers (or memory location) only once at startup:

```JSON
"init": {
  "sp": "0x8",
  "lr": "0xdead"
  "0x0800002c": "0x20000100"
}
```

## test execution
Test generation is based on both the simulation and real execution of one instruction with different cases. The 2 main properties are `src` and `dest`, which gives register value (no difference between `src` and `dest`):

```JSON
"src":
{
  "Rm" : {
    "idx": ["r0","r2","r7"],
    "val": ["0", "0x12345678", "0xffffffff", "0xac533c5a", "0xaaaa5555"]
  },
  "imm3": {
    "imm": [0, "0x5", "0x6", "0x7"]
  }
}
```
It sets the register `Rm` (used in the mnemonic), with different reg numbers:

 * `idx` is used in the mnemonic
 * `val` stores the different values for each `idx`

Previous example leads to multiply the number of tests to 3x5=15 cases.

They can also have immediat values. Here, the `imm3` is used in the mnemonic, and the `imm` is a keyword.

**Note:** If the same index is used in with two registers, the init is done once! It may leads to invalid memory locations with load/store instructions.


## Mnemonic

The mnemonic is defined with the "mnemo" keyword. Parameters are defined between `{}` and should refer to:
  * a register name -> it will be replaced by the `idx` subset.
  * an immediat value -> il will be replaced by the `imm` subset.
  * a `label` keyword when there is a `codeData` section.

The mnemonic should be recognized by the assembler:
```JSON
"mnemo": "asrs {Rd}, {Rm}, #{imm5}"
```
## Comments
the `note` keyword allows to add a text that may be displayed during the execution of tests.

## Memory
### data embbeded in code (i.e. to a label)

The `codeData` keyword is used:

```JSON
"codeData": {
  "post": ["0", "0x23456789", "0xffffffff", "0xac578c5a", "0xaaaa555c"]
}
```
Here, 5 labels are generated at the end of the code (`post`) which implies a positive offset in instruction. It can generate a negative offset with `pre`.
In the mnemonic, the `label` keyword should be used. The generated code is:

```as
.Label0:
	.word 0
.Label1:
	.word 591751049
.Label2:
...
```

In case of a branch instruction, we can insert directly an opcode (`e7fe` is `b .`):

```JSON
	"codeData": {
		"post": ["0xe7fee7fe", "0xe7fee7fe", "0xe7fee7fe"]
	},
```

### basic RAM

The memory is defined in a dedicated section (same level as 'src', 'dest' or 'instruction':

```JSON
	"mem" : {
		"addr": ["0x20000100", "0x200001f0", "0x2000022b",
		         "0x20001000", "0x200010f0", "0x2000112b",
		         "0x20002000", "0x200010f0", "0x2000212b"],
		"val": ["0x0", "0xffffffff", "0xaacc5555", "0x23456789"]
	}
```

Let's call `nbVal` the number of values in `val` list.
The values used for memory addresses are defined as.

* each address gets the same value defined in `val`: There are `nbVal` tests.
* each address gets different values from the `val` list, with a circular approach (`nbVal` tests):
	* The first address gets the first value, the second address the second value and so on. 
	* For the next test, the first addres gets the second value, the second addres the third value… 
	* if there are more addresses than values, it gets new values from the beginning.


As a consequence, a memory section implies that there are `2 
x nbVal`  tests for each previous combinations.

The memory addresses are initialised before each test, and are compared in the gdb/harmless final comparison (one column for each memory address).

**Note**: The program code is loaded in RAM: Do not use first addresses (`0x20000000`…), but start at `0x20000100` min.





